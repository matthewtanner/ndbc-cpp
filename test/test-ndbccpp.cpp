#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "NdbcBuoy.h"

#define MONTEREY_BAY_BUOY 46042

using namespace std;

int main(int argc, char *argv[]) 
{
    int i;
    
    NdbcBuoy buoy(MONTEREY_BAY_BUOY); 
    buoy.updateData();
   
    for (i = buoy.SPEC_DATA_YY; i < buoy.NUM_SPEC_ELEMENTS; i++)   
    {
         cout << buoy.getSpecData((NdbcBuoy::specDataIndex)i) << endl;
    }

    return 0;
}
