#ifndef SURFBREAK_H
#define SURFBREAK_H

#include <vector>
#include <string>

#include <pixel.hpp>

#include "Forecast.h"

using namespace std;

const int NUM_LEDS = 8;

class SurfBreak {
    public:
        string location;
        string dataPath;
        int image_pos_x;
        int image_pos_y;
        string data_path;
        string config_path;
        vector<Forecast*> forecasts;

        SurfBreak();
        ~SurfBreak();

        int loadData(string configPath);
        int drawLeds(string configPath);
        void dumpValues();

    private:
        PixelBone_Pixel *strip;
        int loadConfig(string configPath);

};

#endif /* SURFBREAK_H */
