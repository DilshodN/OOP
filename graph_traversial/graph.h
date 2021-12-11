#pragma once
#include <map> // std::map
#include <vector> // std::vector

class Graph final{
public:
    using vertex = long long;
    Graph() = default;
    explicit Graph(const std::vector<std::pair<vertex, vertex>>& v){
        for(const auto& [ver1, ver2]: v){
            add_edge(ver1, ver2);
        }
    }

    void add_edge(const vertex& source, const vertex& destination){
        // 4 cases:
        // 1) s, d – exist
        // 2) s – exist, d – not exist
        // 3) s – not exist, d – exist
        // 4) s – not exist, d – not exist
        if(graph.contains(source) && std::find(graph[source].begin(), graph[source].end(), destination) != graph[source].end()){
            return;
        }
        graph[source].push_back(destination);
        graph[destination];
    }
    [[nodiscard]] std::vector<vertex> adjacent_vertices(const vertex& vertex) const{
        return graph.at(vertex);
    }
    [[nodiscard]] size_t count_of_vertices() const noexcept{
        return graph.size();
    }
private:
    std::map<vertex, std::vector<vertex>> graph;
};
