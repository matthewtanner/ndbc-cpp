#include <iostream>
#include <string>
#include <curl/curl.h>
//#include <stdio>

#include "BuoyDataFetcher.h"

using namespace std;

int getBuoyData(string url, string filepath)
{
    CURL *bdata;
    CURLcode bdata_result;
    FILE *fp;

    bdata = curl_easy_init();
    if(bdata) {
        // Open file
        fp = fopen(filepath.c_str(), "wb");
        if(fp == NULL) cout << "Error opening file" << filepath << endl; 
        
        curl_easy_setopt(bdata, CURLOPT_URL, url.c_str());
        curl_easy_setopt(bdata, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(bdata, CURLOPT_WRITEDATA, fp);
        
        bdata_result = curl_easy_perform(bdata);
        if(bdata_result) {
            cout << "Error downloading buoy data" << endl;
        }
    
    }
    curl_easy_cleanup(bdata);
    fclose(fp);
    
    return 0;
}

