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
//    uint8_t i;

    NdbcBuoy buoy(46042); 
    buoy.updateData();
   
////    buoy.buoyToString();
//    for (i = 0; i < buoy.cwind.data.size(); i++)
//    {
//        cout << buoy.cwind.data[i] << endl;
//    }
    return 0;
}
