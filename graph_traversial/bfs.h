#pragma once
#include <queue>
#include "strategy.h"

class BFS : public Strategy{
    void execute(const Graph::vertex& ver) override;
public:
    BFS() = delete;
    explicit BFS(const Graph& graph, std::shared_ptr<Traverser>& traverser);
};