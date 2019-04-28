/******************************************************************************
* MIT License
*
* Copyright (c) 2019 Matthew Tanner
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
****************************************************************************//*
* @file
*
* @brief Implementation of NdbcBuoy class
*
* @author Matthew Tanner
******************************************************************************/
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <sstream>

#include "NdbcBuoy.h"

#define FEET_PER_METER 3.28084

using namespace std;

const string NDBC_URL = "https://www.ndbc.noaa.gov/data/realtime2/";


static size_t WriteCallback(void *data, size_t size, size_t nmemb,
        void *userp)
{
    ((string*)userp)->append((char*)data, size * nmemb);
    
    return size * nmemb;
}


int NdbcBuoy::parseBuoyData(string rawdata, vector<float> &data)
{
    string      line;
    string      colstr;
    uint8_t     column = 0;

    istringstream ss(rawdata); 
    
    /* Data starts on 3rd line */
    getline (ss, line);
    getline (ss, line);
    getline (ss, line);
   
    istringstream ssline(line);
    while ((getline(ssline, colstr, ' ')) && (column < data.size()))
    {
        if (colstr != "")
        {
            try
            {
                data[column] = stof(colstr, NULL);
            }
            catch (std::out_of_range& e)
            {
                data[column] = BUOYDATA_ERROR;
            }
            catch (...) {}
            column ++;
        }
    }

    return 0; 
}


int NdbcBuoy::fetchBuoyData(string *buf, string dataset)
{
    CURL *bdata;
    CURLcode bdata_result;

    string url = NDBC_URL + to_string(this->station) + "." + dataset;
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


int NdbcBuoy::updateData(int station)
{
    this->station = station;

    return this->updateData();
}


int NdbcBuoy::updateData()
{
    string txtdata_str;
    string specdata_str;
    string cwinddata_str;
 
    /* Update txt */
    if (fetchBuoyData(&txtdata_str, "txt") < 0)
    {
        cout << "Error fetching txt data" << endl;
    }
    parseBuoyData(txtdata_str, this->txt_data);
    
    /* Update spec */
    if (fetchBuoyData(&specdata_str, "spec") < 0)
    {
        cout << "Error fetching txt data" << endl;
    }
    parseBuoyData(specdata_str, this->spec_data);

    /* Update cwind */
    if (fetchBuoyData(&cwinddata_str, "cwind") < 0)
    {
        cout << "Error fetching txt data" << endl;
    }
    parseBuoyData(cwinddata_str, this->cwind_data);

    return 0;
}


float NdbcBuoy::getTxtData(enum txtDataIndex index)
{
    return txt_data[index];
}

float NdbcBuoy::getSpecData(enum specDataIndex index)
{
    return spec_data[index];
}

float NdbcBuoy::getCwindData(enum cwindDataIndex index)
{
    return cwind_data[index];
}

NdbcBuoy::NdbcBuoy(int station)
        : txt_data(NUM_TXT_ELEMENTS)
        , spec_data(NUM_SPEC_ELEMENTS) 
        , cwind_data(NUM_CWIND_ELEMENTS)
{
    this->station = station;

    fill(this->txt_data.begin(), this->txt_data.end(),
            BUOYDATA_NOT_AVAILABLE);
    fill(this->spec_data.begin(), this->spec_data.end(), 
            BUOYDATA_NOT_AVAILABLE);
    fill(this->cwind_data.begin(), this->cwind_data.end(), 
            BUOYDATA_NOT_AVAILABLE);
}


