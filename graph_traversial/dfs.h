#pragma once
#include "strategy.h"
#include <stack>

class DFS : public Strategy{
    void execute(const Graph::vertex& ver) override;
public:
    DFS() = delete;
    explicit DFS(const Graph& graph, std::shared_ptr<Traverser>& traverser);
};