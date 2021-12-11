#pragma once

#include "find_path.h"

class FindPathToVertex final : public FindPath{
    const Graph::vertex purpose;
    bool comparator(const Graph::vertex& vertex) override;
    bool comparator(const Graph::vertex& source, const Graph::vertex& destination) override;
    void trace_path() override;
public:
    FindPathToVertex() = delete;
    explicit FindPathToVertex(const Graph::vertex& target);
};