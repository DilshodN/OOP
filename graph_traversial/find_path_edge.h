#pragma once
#include "find_path.h"
class FindPathToEdge final : public FindPath{
    const Graph::vertex _source, _destination;
    bool comparator(const Graph::vertex& vertex) override;
    bool comparator(const Graph::vertex& source, const Graph::vertex& destination) override;
    void trace_path() override;

public:
    FindPathToEdge() = delete;
    explicit FindPathToEdge(const Graph::vertex& source, const Graph::vertex& destination);
};