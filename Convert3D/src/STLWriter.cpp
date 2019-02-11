//
// Created by sardnarellum on 2019. 02. 09..
//

#include <fstream>
#include <stdexcept>
#include <cmath>
#include "STLWriter.h"

STLWriter::STLWriter(const std::string& dst, const InternalStorage& is)
: _ostrm(dst, std::ios::binary), _is(is) {
    if (!_ostrm.is_open()) {
        throw std::runtime_error(dst + " _st not found.");
    }
}

void write(std::ofstream& ofs, const Vec3& v) {
    ofs.write((char*)&std::get<0>(v), sizeof(typename std::tuple_element<0, Vec3>::type));
    ofs.write((char*)&std::get<1>(v), sizeof(typename std::tuple_element<1, Vec3>::type));
    ofs.write((char*)&std::get<2>(v), sizeof(typename std::tuple_element<2, Vec3>::type));
}

void STLWriter::Run() {
    if (_ostrm.is_open()) {
        char header[80] = "binary stl";
        _ostrm.write((char*)header, 80*sizeof(char));

        auto triangles = [this]() {
            std::vector<Triangle> triangles;
            for (const auto& face: _is.f) {
                for (auto i = 2u; i < face.size(); ++i) {
                    auto a = _is.v[std::get<0>(face[0])];
                    auto b = _is.v[std::get<0>(face[i-1])];
                    auto c = _is.v[std::get<0>(face[i])];

                    auto norm = [](const auto& a, const auto& b, const auto& c) {
                        auto minus = [](const auto& a, const auto& b) {
                            return Vec3(
                                std::get<0>(a) - std::get<0>(b),
                                std::get<1>(a) - std::get<1>(b),
                                std::get<2>(a) - std::get<2>(b));
                        };                        
                        auto n = [](const auto& a, const auto& b) {
                            Vec3 n = Vec3(
                                std::get<1>(a)*std::get<2>(b) - std::get<2>(a)*std::get<1>(b),
                                std::get<2>(a)*std::get<0>(b) - std::get<0>(a)*std::get<2>(b),
                                std::get<0>(a)*std::get<1>(b) - std::get<1>(a)*std::get<0>(b)
                            );

                            auto len = [](const auto& a) {                                
                                return std::sqrt(
                                    std::pow(std::get<0>(a), 2) +
                                    std::pow(std::get<1>(a), 2) +
                                    std::pow(std::get<2>(a), 2)
                                );;
                            }(n);

                            if (len > 0){
                                std::get<0>(n) = std::get<0>(n) / len;
                                std::get<1>(n) = std::get<1>(n) / len;
                                std::get<2>(n) = std::get<2>(n) / len;
                            }
                            return n;
                        }(minus(a, b), minus(b, c));
                        return n;
                    }(a, b, c);

                    triangles.emplace_back(norm, a, b, c);
                }                
            }
            return triangles;
        }();

        uint32_t cTriangles = triangles.size();
        _ostrm.write((char*)&cTriangles, sizeof(uint32_t));

        for (const auto& e: triangles) {
            std::apply([this](auto& ...x){(..., write(_ostrm, x));}, e);
            uint16_t attr = 0;
            _ostrm.write((char*)&attr, sizeof(uint16_t));
        }

        _ostrm.close();
    }
}
