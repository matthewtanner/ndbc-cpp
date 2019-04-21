#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "BuoyDataFetcher.h"

using namespace std;

void usage()
{
    std::cout << "Usage: lakecast <configfile path>\n";
}


int main(int argc, char *argv[]) 
{
    
    /* Validate args */
//    if(argc != 2) {
//        usage();
//        exit(1);
//    }

    //SurfBreak surfbreak;
    //surfbreak.drawLeds(argv[1]);
    getBuoyData("https://www.ndbc.noaa.gov/data/realtime2/46042.txt", "bdata.txt");
    

    return 0;
}
