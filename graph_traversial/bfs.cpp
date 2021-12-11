//
// Created by dilshod on 03.12.2021.
//

#include "bfs.h"

BFS::BFS(const Graph &graph, std::shared_ptr<Traverser> &traverser) : Strategy(graph, traverser){}

void BFS::execute(const Graph::vertex &ver) {
    if (this->graph.count_of_vertices() == 0) {
        return;
    }
    previous.clear();
    std::queue<Graph::vertex> qu;

    begin(ver);
    qu.push(ver);
    previous[ver] = ver;
    while(not qu.empty()){
        auto vertex = qu.front();
        qu.pop();

        visit_vertex(vertex);
        visit_edge(previous.at(vertex), vertex);

        if(is_finished()){
            break;
        }

        const auto& adj_ver = graph.adjacent_vertices(vertex);
        for(auto v = adj_ver.crbegin(); v != adj_ver.crend(); v++){
            auto temp_vertex = *v;
            if(temp_vertex != previous[vertex]){
                qu.push(temp_vertex);
                previous[temp_vertex] = vertex;
            }
        }
    }
    end();
}
