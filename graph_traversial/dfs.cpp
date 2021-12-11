
#include "dfs.h"

DFS::DFS(const Graph &graph, std::shared_ptr<Traverser>& traverser) : Strategy(graph, traverser) {}

void DFS::execute(const Graph::vertex &ver) {
    if(graph.count_of_vertices() == 0){
        return;
    }
    previous.clear();
    std::stack<std::pair<Graph::vertex, bool>> st;
    begin(ver);

    st.push(std::make_pair(ver, false));
    previous[ver] = ver;
    while(not st.empty()){
        auto& [vertex, discovered] = st.top();
        if(not discovered){
            visit_vertex(vertex);
            visit_edge(previous.at(vertex), vertex);
            discovered = true;

            if(is_finished()){
                break;
            }

            const auto& adj_ver = graph.adjacent_vertices(vertex);
            for(auto v = adj_ver.crbegin(); v != adj_ver.crend(); v++){
                auto temp_vertex = *v;
                if(temp_vertex != previous[vertex]){
                    st.push(std::make_pair(temp_vertex, false));
                    previous[temp_vertex] = vertex;
                }
            }
        }
        else{
            st.pop();
        }
    }
    end();
}


