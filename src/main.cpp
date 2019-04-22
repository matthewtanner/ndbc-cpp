#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "BuoyHandler.h"

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

    BuoyHandler bhandler(46042); 
    bhandler.updateBuoyData();
   
    bhandler.buoyToString();

    return 0;
}
