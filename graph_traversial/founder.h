#pragma once

#include "strategy.h"
#include "graph.h"
#include "traverser.h"

class Founder final{
    const std::shared_ptr<Strategy> st;
    const Graph& graph;
public:
    Founder() = delete;
    Founder(const Graph&, std::shared_ptr<Strategy>);
    void find(const Graph::vertex&);
    [[nodiscard]] std::vector<Graph::vertex> get_path() const;
    [[nodiscard]] bool is_cyclic() const;
};