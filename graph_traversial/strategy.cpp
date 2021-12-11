//
// Created by dilshod on 03.12.2021.
//

#include "strategy.h"

void Strategy::begin(const Graph::vertex &ver) {
    traverser->begin(ver);
}

void Strategy::end() {
    traverser->end();
}

void Strategy::visit_vertex(const Graph::vertex &ver) {
    traverser->visit_vertex(ver);
}

void Strategy::visit_edge(const Graph::vertex &source, const Graph::vertex &destination) {
    traverser->visit_edge(source, destination);
}

bool Strategy::is_finished() {
    return traverser->is_finished();
}

Strategy::Strategy(const Graph &graph, std::shared_ptr<Traverser> &traverser): graph(graph), traverser(traverser){}

std::vector<Graph::vertex> Strategy::get_path() const{
    return traverser->get_path();
}

bool Strategy::is_cyclic() const {
    return traverser->is_cyclic();
}
