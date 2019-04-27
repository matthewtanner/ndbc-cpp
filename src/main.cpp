#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "NdbcBuoy.h"

using namespace std;

void usage()
{
    std::cout << "Usage: lakecast <configfile path>\n";
}


int main(int argc, char *argv[]) 
{
    int i;
    
    NdbcBuoy buoy(46042); 
    buoy.updateData();
   
    for (i = buoy.SPEC_DATA_YY; i < buoy.NUM_SPEC_ELEMENTS;
                i++)   
    {
   
         cout << buoy.getSpecData((NdbcBuoy::specDataIndex)i) << endl;
    }

    return 0;
}
