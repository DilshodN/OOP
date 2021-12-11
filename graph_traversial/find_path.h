#pragma once

#include "traverser.h"

class FindPath : public Traverser{
protected:
    std::map<Graph::vertex, Graph::vertex> previous{};

    virtual bool comparator(const Graph::vertex& ver) = 0;
    virtual bool comparator(const Graph::vertex& source, const Graph::vertex& destination) = 0;
    virtual void trace_path() = 0;

public:
    FindPath() = default;
    void visit_vertex(const Graph::vertex& ver) override;
    void visit_edge(const Graph::vertex& source, const Graph::vertex& destination) override;
    void end() override;
    ~FindPath() override = default;
};