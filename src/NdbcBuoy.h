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
        
        enum txtDataIndex
        {
            TXT_DATA_YY,
            TXT_DATA_MM,
            TXT_DATA_DD,
            TXT_DATA_HR,
            TXT_DATA_MN,
            TXT_DATA_WDIR,
            TXT_DATA_WSPD,
            TXT_DATA_GST,
            TXT_DATA_WVHT,
            TXT_DATA_DPD,
            TXT_DATA_APD,
            TXT_DATA_MWD,
            TXT_DATA_PRES,
            TXT_DATA_ATMP,
            TXT_DATA_WTMP,
            TXT_DATA_DEWP,
            TXT_DATA_VIS,
            TXT_DATA_PTDY,
            TXT_DATA_TIDE,
            NUM_TXT_ELEMENTS
        };
    
        enum specDataIndex
        {
            SPEC_DATA_YY,
            SPEC_DATA_MM,
            SPEC_DATA_DD,
            SPEC_DATA_HR,
            SPEC_DATA_MN,
            SPEC_DATA_WVHT,
            SPEC_DATA_SWH,
            SPEC_DATA_SWP,
            SPEC_DATA_WWH,
            SPEC_DATA_WWP,
            SPEC_DATA_SWD,
            SPEC_DATA_WWD,
            SPEC_DATA_STEEPNESS,
            SPEC_DATA_APD,
            SPEC_DATA_MWD,
            NUM_SPEC_ELEMENTS
        };
    
        enum cwindDataIndex
        {
            CWIND_DATA_YY,
            CWIND_DATA_MM,
            CWIND_DATA_DD,
            CWIND_DATA_HR,
            CWIND_DATA_MN,
            CWIND_DATA_WDIR,
            CWIND_DATA_WSPD,
            CWIND_DATA_GDR,
            CWIND_DATA_GST,
            CWIND_DATA_GTIME,
            NUM_CWIND_ELEMENTS
        };
        
        NdbcBuoy(int station);
        int updateData(int station);
        int updateData();
        float getTxtData(enum txtDataIndex index);
        float getSpecData(enum specDataIndex index);
        float getCwindData(enum cwindDataIndex index);
    
    private:
        std::vector<float> txt_data;
        std::vector<float> spec_data;
        std::vector<float> cwind_data;
        
        int fetchBuoyData(std::string *buf, std::string dataset);
        int parseBuoyData(std::string rawdata, std::vector<float> &data);
};

#endif /* BUOY_HANDLER_H */

