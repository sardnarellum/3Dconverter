//
// Created by sardnarellum on 2019. 02. 09..
//

#pragma once

#include <fstream>
#include "Types.h"

using LineRef = std::vector<size_t>;

class SimpleObjReader {
public:
    SimpleObjReader(const std::string& src, InternalStorage& storage);

    void Run();

private:
    std::ifstream _is;
    InternalStorage& _st;
};
