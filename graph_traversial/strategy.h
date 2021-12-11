#pragma once
#include "traverser.h" // Traverser
#include "graph.h" // Graph
#include <memory> // std::shared_ptr

class Strategy{
protected:
    friend class Founder;
    void begin(const Graph::vertex& ver);
    void end();
    void visit_vertex(const Graph::vertex& ver);
    void visit_edge(const Graph::vertex& source, const Graph::vertex& destination);
    bool is_finished();
    const Graph& graph;
    std::shared_ptr<Traverser> traverser;
    std::map<Graph::vertex, Graph::vertex> previous;
    virtual void execute(const Graph::vertex& ver) = 0;
    [[nodiscard]] virtual std::vector<Graph::vertex> get_path() const;
    [[nodiscard]] bool is_cyclic() const;
public:
    Strategy() = delete;
    explicit Strategy(const Graph& graph, std::shared_ptr<Traverser>& traverser);
    virtual ~Strategy() = default;
};
