//
// Created by dilshod on 02.12.2021.
//

#include "traverser.h"

void Traverser::begin(const Graph::vertex &_first) {
    first = _first;
    _is_finished = _is_cyclic = false;
    path.clear();
}

bool Traverser::is_finished() const {
    return _is_finished;
}

bool Traverser::is_cyclic() const {
    return _is_cyclic;
}

std::vector<Graph::vertex> Traverser::get_path() const{
    return path;
}
