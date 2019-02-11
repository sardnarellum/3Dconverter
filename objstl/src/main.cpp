#include <iostream>
#include "Convert3D.hpp"
#include "SimpleObjReader.h"
#include "STLWriter.h"

int main(int argc, char* argv[]) {

    if (3 == argc) {
        try {
            Convert3D<SimpleObjReader, STLWriter> converter(argv[1], argv[2]);
            converter.Run();
        }
        catch (std::exception& e){
            std::cout << e.what() << std::endl;
        }
    }
    else {
        std::cout << "Incorrect number of cmd arguments, usage: objstl src.obj dst.stl" << std::endl;
    }
    return 0;
}