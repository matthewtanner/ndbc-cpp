#include <iostream>
#include <string>
#include <curl/curl.h>
#include <sstream>

#include "BuoyDataFetcher.h"

#define BUOY_FILE_COL_WDIR  5
#define BUOY_FILE_COL_WSPD  6
#define BUOY_FILE_COL_WVHT  8
#define BUOY_FILE_COL_DPD   9
#define BUOY_FILE_COL_MWD   11
#define BUOY_FILE_COL_PRES  12

#define FEET_PER_METER 3.28084

using namespace std;

const string NDBC_URL = "https://www.ndbc.noaa.gov/data/realtime2/";


static size_t WriteCallback(void *data, size_t size, size_t nmemb,
        void *userp)
{
    ((string*)userp)->append((char*)data, size * nmemb);
    
    return size * nmemb;
}


int fetchBuoyString(string url, string *buf)
{
    CURL *bdata;
    CURLcode bdata_result;

    bdata = curl_easy_init();
    if(bdata) {
        
        curl_easy_setopt(bdata, CURLOPT_URL, url.c_str());
        curl_easy_setopt(bdata, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(bdata, CURLOPT_WRITEDATA, buf);
        
        bdata_result = curl_easy_perform(bdata);
        if(bdata_result) 
        {
            cout << "Error downloading buoy data" << endl;
            return -1;
        }
    
    }
    curl_easy_cleanup(bdata);
   
    return 0;
}

int parseBuoyData(string rawdata, BuoyHandler::buoyData *data)
{
    string line;
    string colstr;
    uint8_t column = 0;
    
    istringstream ss(rawdata); 
    
    /* Data starts on 3rd line */
    getline (ss, line);
    getline (ss, line);
    getline (ss, line);
   
    istringstream ssline(line);
    while (getline(ssline, colstr, ' '))
    {
        if (colstr != "")
        {
            try
            {
                switch (column)
                {
                    case BUOY_FILE_COL_WDIR:
                        data->wind_dir = stoi(colstr, 0, 10);
                        break;
                    case BUOY_FILE_COL_WSPD:
                        data->wind_spd = stoi(colstr, 0, 10);
                        break;
                    case BUOY_FILE_COL_WVHT:
                        data->wave_hgt = stoi(colstr, 0, 10) * FEET_PER_METER;
                        break;
                    case BUOY_FILE_COL_DPD:
                        data->wave_prd = stoi(colstr, 0, 10);
                        break;
                    case BUOY_FILE_COL_MWD:
                        data->wave_dir = stoi(colstr, 0, 10);
                        break;
                    case BUOY_FILE_COL_PRES:
                        data->pressure = stoi(colstr, 0, 10);
                        break;
                    default:
                        break;
                }
            }
            catch (int e)
            {
                cout << "Error parsing NDBC buoy file" << endl;
                return -1;
            }
            column ++;
        }
    }

    return 0; 
}
   

void BuoyHandler::buoyToString(void)
{
    BuoyHandler::buoyData data = this->data;
    cout << "Wind Dir: " + to_string(data.wind_dir) << endl;
    cout << "Wind Spd: " + to_string(data.wind_spd) << endl;
    cout << "Wave hgt: " + to_string(data.wave_hgt) << endl;
    cout << "Wave prd: " + to_string(data.wave_prd) << endl;
    cout << "Wave Dir: " + to_string(data.wave_dir) << endl;
    cout << "Pressure: " + to_string(data.pressure) << endl;
}


int BuoyHandler::updateBuoyData(int buoy)
{
    string bdata_str;
    
    string url = NDBC_URL + to_string(buoy) + ".txt";
    if (fetchBuoyString(url, &bdata_str) < 0)
    {
        cout << "Error fetching buoy data from " + url << endl;
    }
   
    parseBuoyData(bdata_str, &this->data);

    return 0;
}

int BuoyHandler::updateBuoyData()
{
    return this->updateBuoyData(this->buoy);
}

BuoyHandler::BuoyHandler(int buoy)
{
    this->buoy = buoy;
}
