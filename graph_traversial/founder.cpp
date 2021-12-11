//
// Created by dilshod on 04.12.2021.
//

#include "founder.h"

#include <utility>

Founder::Founder(const Graph& graph,std::shared_ptr<Strategy> st) : graph(graph), st(std::move(st)){}

void Founder::find(const Graph::vertex& target) {
    st->execute(target);
}

std::vector<Graph::vertex> Founder::get_path() const {
    return st->get_path();
}



bool Founder::is_cyclic() const{
    return st->is_cyclic();
}


