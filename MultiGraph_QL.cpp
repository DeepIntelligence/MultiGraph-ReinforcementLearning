#include <cstdlib>
#include "MultiGraph_QL.h"


void MultiGraph_QL::update_Q(Experience exp, double learningRate, double discount){
 
     // first check whether the target/new state exist or not
     // if not, then add this vertex and corresponding edge to the graph
     // After adding, update the Q value
     auto it = mapStateToIndex.find(exp.newState);
     int index0, index1;
     if (it == mapStateToIndex.end()){
         this->addVertex(Vertex(exp.newState,numV++));
         index1 = it->second;
         index0 = mapStateToIndex[exp.oldState];
         this->addEdge(Edge(index0,index1,exp.action));
     } 
     index0 = mapStateToIndex[exp.oldState];
     index1 = mapStateToIndex[exp.newState];
     Vertices[index0].Q = Vertices[index0].Q + 
             learningRate*(exp.reward + discount*Vertices[index1].Q-Vertices[index0].Q);
 }
 
int MultiGraph_QL::selectNextAction(State currState){
    int action;
    // if this state/vertex has no outEdges, there we just randomly select one action
//    int verIdx = mapStateToIndex[currState];
//    if( outEdges[][Idx].size() == 0){
        
//    } 
    

    return action;

}
 
