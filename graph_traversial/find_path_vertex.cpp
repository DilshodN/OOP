//
// Created by dilshod on 03.12.2021.
//

#include "find_path_vertex.h"

bool FindPathToVertex::comparator(const Graph::vertex &vertex) {
    return purpose == vertex;
}

bool FindPathToVertex::comparator(const Graph::vertex &source, const Graph::vertex &destination) {
    return _is_finished;
}

void FindPathToVertex::trace_path() {
    auto goal = purpose;
    while (goal != first){
        path.emplace_back(goal);
        goal = previous[goal];
    }
    path.emplace_back(goal);
}

FindPathToVertex::FindPathToVertex(const Graph::vertex &target) : FindPath(), purpose(target) {}


