#ifndef BUOY_HANDLER_H
#define BUOY_HANDLER_H

#include <string>
#include <cstdint>

using namespace std;


class BuoyHandler
{
    public:
        int buoy;
        struct buoyData
        {
            int32_t wind_dir;
            int32_t wind_spd;
            int32_t wave_hgt;
            int32_t wave_prd;
            int32_t wave_dir;
            int32_t pressure;
        }data;
        
        BuoyHandler(int buoy);
        int updateBuoyData(int buoy);
        int updateBuoyData();
        void buoyToString(void);
    
    private:
};


#endif /* BUOY_HANDLER_H */

