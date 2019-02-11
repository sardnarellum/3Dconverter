//
// Created by sardnarellum on 2019. 02. 09..
//

#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <functional>
#include <iterator>
#include <tuple>
#include <deque>
#include <regex>
#include "SimpleObjReader.h"

SimpleObjReader::SimpleObjReader(const std::string& src, InternalStorage& storage)
: _is(src), _st(storage) {
    if (!_is.is_open()){
        throw std::runtime_error(src + " _st not found.");
    }
}

template<typename Out>
void split(const std::string &s, char delim, Out result, bool skipEmptyElems = true) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        if (!skipEmptyElems || !item.empty()) {
            *(result++) = item;
        }
    }
}

void insert(Vertices& v, LineRef& lr, const std::string& x, const std::string& y, const std::string& z) {
    v.emplace_back(std::stof(x), std::stof(y), std::stof(z));
    lr.emplace_back(v.size() - 1);
}

size_t findHistoryReference(const LineRef& h, int rawIndex) {
    if (rawIndex >= 0) {
        return rawIndex-1; // obj runs from 1
    }

    return h[h.size()+rawIndex];
}

void insert(Faces& faces, LineRef& lr, std::deque<std::string> refs) {
    Face f;
    if (refs.front().find('/') != std::string::npos) {
        for (const auto& e: refs) {
            std::vector<std::string> triplet;
            split(e, '/', std::back_inserter(triplet), false);

            auto v = findHistoryReference(lr, std::stoi(triplet[0]));
            auto vt = triplet[1].size() != 0
                    ? std::optional<size_t>(findHistoryReference(lr, std::stoi(triplet[1])))
                    : std::nullopt;
            auto vn = triplet[2].size() != 0
                    ? std::optional<size_t>(findHistoryReference(lr, std::stoi(triplet[2])))
                    : std::nullopt;
            f.emplace_back(v, vt, vn);
        }
    }
    else {
        for (const auto& e: refs) {
            f.emplace_back(findHistoryReference(lr, std::stoi(e)), std::nullopt, std::nullopt);
        }
    }
    faces.push_back(std::move(f));
    lr.emplace_back(-1);
}

void SimpleObjReader::Run() {
    LineRef lr;

    if (_is.is_open()) {
        std::string line;

        while (std::getline(_is, line)) {
            const auto hashPos = line.find('#');
            if (std::string::npos != hashPos) {
                line.erase(line.begin() + hashPos, line.end());
            }
            line = std::regex_replace(line, std::regex("^ +| +$|( ) +"), "$1");
            if (0 < line.size()) {
                std::deque<std::string> elems;
                split(line, ' ', std::back_inserter(elems));

                if (0 == elems[0].compare("v")) {
                    insert(_st.v, lr, elems[1], elems[2], elems[3]);
                } else if (0 == elems[0].compare("vt")) {
                    insert(_st.vt, lr, elems[1], elems[2], elems[3]);
                } else if (0 == elems[0].compare("vn")) {
                    insert(_st.vn, lr, elems[1], elems[2], elems[3]);
                } else if (0 == elems[0].compare("f")) {
                    elems.pop_front();
                    insert(_st.f, lr, elems);
                }
            }
        }
        _is.close();
    }
}
