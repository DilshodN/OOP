#pragma once

#include "graph.h" // Graph

class Traverser{
protected:
    friend class Strategy;
    bool _is_finished = false, _is_cyclic = false;
    Graph::vertex first{};
    std::vector<Graph::vertex> path{};
    virtual void begin(const Graph::vertex& first);
    virtual void visit_vertex(const Graph::vertex& ver) = 0;
    virtual void visit_edge(const Graph::vertex& source, const Graph::vertex& destination) = 0;

    virtual void end() = 0;

    [[nodiscard]] std::vector<Graph::vertex> get_path() const;
    [[nodiscard]] bool is_finished() const;
    [[nodiscard]] bool is_cyclic() const;
public:
    Traverser() = default;
    virtual ~Traverser() = default;
};

