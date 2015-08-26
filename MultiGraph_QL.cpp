#include <cstdlib>
#include <iostream>
#include <fstream>
#include "MultiGraph_QL.h"

// if such state not exists, add a new vertex representing the state to the graph
void MultiGraph_QL::update_Q(State s){
    auto it = mapStateToIndex.find(s);
    if (it == mapStateToIndex.end()){
         this->addVertex(Vertex(s,numV++,numActions));
    }

}

void MultiGraph_QL::update_Q(Experience exp, double learningRate, double discount){
 
     // first check whether the target/new state exist or not
     // if not, then add this vertex and corresponding edge to the graph
     // After adding, update the Q value
     auto it = mapStateToIndex.find(exp.newState);
     int index0, index1;
     if (it == mapStateToIndex.end()){
         this->addVertex(Vertex(exp.newState,numV++,numActions));
         index1 = numV - 1;
 //        std::cout << mapStateToIndex.size() << std::endl;
         index0 = mapStateToIndex[exp.oldState];
         this->addEdge(Edge(index0,index1,exp.action));
     } else {
     index0 = mapStateToIndex[exp.oldState];
     index1 = mapStateToIndex[exp.newState];
     }
     Vertices[index0].Q[exp.action] = Vertices[index0].Q[exp.action] + 
             learningRate*(exp.reward + discount*Vertices[index1].maxQ()-Vertices[index0].Q[exp.action]);
 }
 
int MultiGraph_QL::selectNextAction(State currState){
    int action;
    int index = this->mapStateToIndex[currState];
    if (Vertices[index].maxQIdx() == Vertices[index].minQIdx()){
         action = randu->nextInt();
    } else {
        action = Vertices[index].maxQIdx();
    }
    return action;

}
 
void MultiGraph_QL::outputQ(std::string filename){
    std::ofstream os;
    os.open(filename);
    for(int i = 0; i < this->numV; i++) {
        os << i << "\t";
        os << Vertices[i].s.rowIdx << "\t" << Vertices[i].s.colIdx << "\t";
        for (int j = 0; j < this->numActions; j++){
            os << Vertices[i].Q[j] << "\t" ;
        }
        os << Vertices[i].maxQ() << "\t" << Vertices[i].maxQIdx() << std::endl;
    }



}
