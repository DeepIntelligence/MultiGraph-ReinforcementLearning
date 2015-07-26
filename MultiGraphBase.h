#pragma once

#include <vector>
#include <unordered_map>

//MultiGraph for decision making and reinforcement learning
//MultiGraph will map vertex to integers
//

template<typename Vertex_t, typename Edge_t, typename State_t>
class MultiGraphBase{
    protected:
    std::vector< std::vector<Edge_t> > *outEdges;
    std::vector< std::vector<Edge_t> > *inEdges;
    std::vector<Vertex_t> Vertices;
    int numActions;
    int numV,numEdges;

    public:
    std::unordered_map<State_t, int> mapStateToIndex;        
    MultiGraphBase(int numActions0):numActions(numActions0){
        outEdges = new std::vector< std::vector<Edge_t> >[numActions];
        inEdges = new std::vector< std::vector<Edge_t> >[numActions];
        numV = 0;
        numEdges = 0;
    }    
        
    void addEdge(Edge_t e){
        outEdges[e.action][e.from].push_back(e);
        inEdges[e.action][e.to].push_back(e);
        numEdges++;
    }
    void addVertex(Vertex_t v){    
        Vertices.push_back(v);
        for(int m = 0; m < numActions; m++){
            outEdges[m].push_back(std::vector<Edge_t>());
            inEdges[m].push_back(std::vector<Edge_t>());            
        }
        mapStateToIndex[v.s] = v.index;
    }
    int getNumV(){return numV;}
    int getNumE(){return numEdges;}
    int getNumActions(){return numActions;}

//    const std::vector<Edge_t> getOutEdges(const State_t v, Action_t a);

};
