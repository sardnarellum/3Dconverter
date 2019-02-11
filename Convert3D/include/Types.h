//
// Created by sardnarellum on 2019. 02. 10..
//

#pragma once

#include <vector>
#include <optional>
#include <tuple>

using Vec3     = std::tuple<float, float, float>;
using Vertices = std::vector<Vec3>;
using Face     = std::vector<std::tuple<size_t, std::optional<size_t>, std::optional<size_t>>>;
using Faces    = std::vector<Face>;


struct InternalStorage {
    Vertices v;
    Vertices vt;
    Vertices vn;
    Faces f;
};
