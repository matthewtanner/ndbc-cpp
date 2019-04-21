#include <string>
#include <fstream>
#include <streambuf>
#include <vector>
#include <iostream>

#include <pixel.hpp>
#include <json/json.h>

#include "SurfBreak.h"
#include "Forecast.h"

using namespace std;

#define BRIGHTNESS 0.2

int SurfBreak::loadConfig(string configPath)
{
    ifstream ifs(configPath.c_str());
    string json_string;
    Json::Value root;
    Json::Reader reader;
    unsigned int i;

    json_string.assign( (istreambuf_iterator<char>(ifs)),
                        (istreambuf_iterator<char>()  ) );

    bool result = reader.parse(json_string, root, false);
    if(not result) {
        cout<<"Failed to parse JSON in loadconfig"<<endl
            <<reader.getFormattedErrorMessages()
            <<endl;
        return -1;
    }
    
    Json::Value dpath = root["dataPath"];
    dataPath = dpath.asString() + "data.json";
    Json::Value forecast = root["forecast"];
    location = forecast["location"].asString();
    image_pos_x = forecast["pixel_x"].asInt();
    image_pos_y = forecast["pixel_y"].asInt();

    Json::Value images = forecast["images"];
    for(i = 0; i < images.size(); i++){
        Forecast *fcast = new Forecast();
        fcast->timeOffset = images[i]["timeoffset"].asInt();
        forecasts.push_back(fcast);
    }

    return 0;
}


int SurfBreak::loadData(string configPath)
{
    string json_string;
    Json::Value root;
    Json::Reader reader;
    unsigned int p, i;

    loadConfig(configPath);

    ifstream ifs(dataPath.c_str());
    
    json_string.assign( (istreambuf_iterator<char>(ifs)),
                        (istreambuf_iterator<char>()  ) );
    bool result = reader.parse(json_string, root, false);
    if(not result) {
        cout<<"Failed to parse JSON in loadData"<<endl
            <<reader.getFormattedErrorMessages()
            <<endl;
        return -1;
    }
   
    const Json::Value fcasts = root["fcasts"];

    for(p=0; p < forecasts.size(); p++){
        for(i = 0; i < fcasts.size(); i++){
            Json::Value current = fcasts[i];

            if(forecasts[p]->timeOffset == 
                    current["timeoffset"].asInt())
            {
                Json::Value rgb = current["rgb"];
                forecasts[p]->led.red = rgb["red"].asInt();
                forecasts[p]->led.green = rgb["green"].asInt();
                forecasts[p]->led.blue = rgb["blue"].asInt();
            }
        }
    }

    return 0;
}


int led_equal(struct led_colors led1, struct led_colors led2)
{
    return (led1.red == led2.red &&
            led1.green == led2.green &&
            led1.blue == led2.blue);
}

int SurfBreak::drawLeds(string configPath)
{
    unsigned int i;
    
    loadData(configPath);
    struct led_colors led; 
    
//    cout << "drawLeds" << endl << endl;
   
    for(i = 0; i < forecasts.size(); i++)
    {
        int c;
        led = forecasts[i]->led;
        for(c = 0; c < 15; c++)
        {
            if(led_equal(led, noaa_colors[c]))
                led = adjusted_colors[c];
            
        }
        strip->setPixelColor(i, led.red*BRIGHTNESS, led.green*BRIGHTNESS, led.blue*BRIGHTNESS);     
        
//        cout << "fcast #" << i << endl;
//        cout << "timeoffset " << forecasts[i]->timeOffset << endl; 
//        cout << "red " << led.red << endl; 
//        cout << "green "<< led.green << endl; 
//        cout << "blue " << led.blue << endl; 
//        cout << endl;
    } 
    strip->show();

    return 0;
}

#ifdef DEBUG
void SurfBreak::dumpValues()
{
    unsigned int i;

    cout<<"location: "<<location<<endl;
    cout<<"image pos x: "<<image_pos_x<<endl;
    cout<<"image pos y: "<<image_pos_y<<endl;
    
    for(i = 0; i < forecasts.size(); i++){
        cout << "fcast #" << i << endl;
        cout << "timeoffset " << forecasts[i]->timeOffset << endl; 
        cout << "red " << forecasts[i]->led.red << endl; 
        cout << "green "<< forecasts[i]->led.green << endl; 
        cout << "blue " << forecasts[i]->led.blue << endl; 
        cout << endl;
    }

}
#endif

SurfBreak::SurfBreak() 
{
   strip = new PixelBone_Pixel(NUM_LEDS);
}

SurfBreak::~SurfBreak() 
{
    unsigned int i;
    
    for(i = 0; i < forecasts.size(); i++) {
        delete(forecasts[i]);
    }    
    free(strip);
}

