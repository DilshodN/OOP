#include "traverser.h"
#include <set> // std::set

class CheckCyclic : public Traverser{
    std::set<Graph::vertex> visited;
    std::map<Graph::vertex, Graph::vertex> previous;
public:
    CheckCyclic() = default;
    void visit_vertex(const Graph::vertex& ver) override;
    void visit_edge(const Graph::vertex& source, const Graph::vertex& destination) override;
    void end() override;
};