//
// Created by sardnarellum on 2019. 02. 09..
//

#pragma once

#include <iostream>
#include "Types.h"

using Triangle = std::tuple<Vec3, Vec3, Vec3, Vec3>;

class STLWriter {
public:
    STLWriter(const std::string& dst, const InternalStorage& is);
    void Run();

private:
    std::ofstream _ostrm;
    const InternalStorage& _is;
};
