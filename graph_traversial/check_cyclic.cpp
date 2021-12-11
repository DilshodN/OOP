//
// Created by dilshod on 03.12.2021.
//

#include "check_cyclic.h"

void CheckCyclic::visit_vertex(const Graph::vertex &ver) {
    if(visited.find(ver) != visited.end()){
        _is_finished = _is_cyclic = true;
        return;
    }
    visited.emplace(ver);
}

void CheckCyclic::visit_edge(const Graph::vertex &source, const Graph::vertex &destination) {}

void CheckCyclic::end() {}
