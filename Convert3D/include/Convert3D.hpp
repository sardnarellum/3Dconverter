//
// Created by sardnarellum on 2019. 02. 09..
//

#pragma once

#include <string>

#include "Types.h"

template <typename Reader, typename Writer>
class Convert3D {
public:
    Convert3D(const std::string& src, const std::string& dst) : st(), r(src,st), w(dst,st) {}
    void Run();

private:
    InternalStorage st;
    Reader r;
    Writer w;
};

template <typename Reader, typename Writer>
void Convert3D<Reader, Writer>::Run() {
    r.Run();
    w.Run();
}