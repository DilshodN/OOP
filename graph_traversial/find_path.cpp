//
// Created by dilshod on 03.12.2021.
//

#include "find_path.h"

void FindPath::visit_vertex(const Graph::vertex &ver) {
    _is_finished = comparator(ver);
}

void FindPath::visit_edge(const Graph::vertex &source, const Graph::vertex &destination) {
    _is_finished = comparator(source, destination);
    previous[destination] = source;
}

void FindPath::end() {
    if(not _is_finished){
        path.clear();
        return;
    }
    trace_path();
    std::reverse(path.begin(), path.end());
}


