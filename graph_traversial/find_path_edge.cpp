//
// Created by dilshod on 03.12.2021.
//

#include "find_path_edge.h"

bool FindPathToEdge::comparator(const Graph::vertex &vertex) {
    return _is_finished;
}

bool FindPathToEdge::comparator(const Graph::vertex &source, const Graph::vertex &destination) {
    return _source == source and _destination == destination;
}

void FindPathToEdge::trace_path() {
    auto goal = _destination;
    while (goal != first){
        path.emplace_back(goal);
        goal = previous[goal];
    }
    path.emplace_back(goal);
}

FindPathToEdge::FindPathToEdge(const Graph::vertex &source, const Graph::vertex &destination)
: FindPath(), _source(source), _destination(destination){}
