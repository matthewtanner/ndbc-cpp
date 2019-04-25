#ifndef NDBC_BUOY_H
#define NDBC_BUOY_H

#include <string>
#include <cstdint>
#include <bits/stdc++.h>


class NdbcBuoy
{
    public:

        const float BUOYDATA_NOT_AVAILABLE = -998;
        const float BUOYDATA_ERROR = -999;
        int station;
        struct txtData
        {
            enum txtDataIndex
            {
                TXT_INDEX_YY,
                TXT_INDEX_MM,
                TXT_INDEX_DD,
                TXT_INDEX_HR,
                TXT_INDEX_MN,
                TXT_INDEX_WDIR,
                TXT_INDEX_WSPD,
                TXT_INDEX_GST,
                TXT_INDEX_WVHT,
                TXT_INDEX_DPD,
                TXT_INDEX_APD,
                TXT_INDEX_MWD,
                TXT_INDEX_PRES,
                TXT_INDEX_ATMP,
                TXT_INDEX_WTMP,
                TXT_INDEX_DEWP,
                TXT_INDEX_VIS,
                TXT_INDEX_PTDY,
                TXT_INDEX_TIDE,
                NUM_TXT_ELEMENTS
            };
            txtData() : data(NUM_TXT_ELEMENTS) {}
            std::vector<float> data;
        } txt;
        
        struct specData
        {
            enum txtDataIndex
            {
                SPEC_INDEX_YY,
                SPEC_INDEX_MM,
                SPEC_INDEX_DD,
                SPEC_INDEX_HR,
                SPEC_INDEX_MN,
                SPEC_INDEX_WVHT,
                SPEC_INDEX_SWH,
                SPEC_INDEX_SWP,
                SPEC_INDEX_WWH,
                SPEC_INDEX_WWP,
                SPEC_INDEX_SWD,
                SPEC_INDEX_WWD,
                SPEC_INDEX_STEEPNESS,
                SPEC_INDEX_APD,
                SPEC_INDEX_MWD,
                NUM_SPEC_ELEMENTS
            };
            specData() : data(NUM_SPEC_ELEMENTS) {}
            std::vector<float> data;
        } spec;
        
        struct cwindData
        {
            enum cwindDataIndex
            {
                CWIND_INDEX_YY,
                CWIND_INDEX_MM,
                CWIND_INDEX_DD,
                CWIND_INDEX_HR,
                CWIND_INDEX_MN,
                CWIND_INDEX_WDIR,
                CWIND_INDEX_WSPD,
                CWIND_INDEX_GDR,
                CWIND_INDEX_GST,
                CWIND_INDEX_GTIME,
                NUM_CWIND_ELEMENTS
            };
            cwindData() : data(NUM_CWIND_ELEMENTS) {}
            std::vector<float> data;
        } cwind;
        
        NdbcBuoy(int station);
        int updateData(int station);
        int updateData();
    
    private:
        int fetchBuoyData(std::string *buf, std::string dataset);
        int parseBuoyData(std::string rawdata, std::vector<float> &data);

};


#endif /* BUOY_HANDLER_H */

