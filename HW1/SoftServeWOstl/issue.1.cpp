#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>

#include "FileWithStructur.h"


int main(int argc, char** argv) 
{
    
    generator::createFile(argc,argv);
    generator::SortFile(argc,argv);
    
    
    return 0;
}