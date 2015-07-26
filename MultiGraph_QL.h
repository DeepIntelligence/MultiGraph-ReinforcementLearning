#pragma once

#include <vector>
#include <unordered_map>
#include <random>
#include <memory>
#include <string>
#include "MultiGraphBase.h"
// Vertex usually needs to redefine a hasher and a equal function for the state
struct State{
    State(){}
    State(int i, int j):rowIdx(i), colIdx(j){}
    bool equals(const State& other) const{
        return (this->rowIdx==other.rowIdx)&&(this->colIdx == other.colIdx);
    }
    int rowIdx, colIdx;
};

namespace std{
template<>
struct hash<State>{
    typedef State argument_type;
    typedef std::size_t result_type;
    result_type operator()(const argument_type& s) const{
    result_type h1=std::hash<int>()(s.rowIdx);
    result_type h2 = std::hash<int>()(s.colIdx);
    return h1^(h2<<1);
    }
};

template<>
struct equal_to<State>{
    bool operator()(const State &s1, const State &s2) const{
    return (s1.rowIdx==s2.rowIdx)&&(s1.colIdx == s2.colIdx);
    }
};
}
struct Vertex{
    State s;
    int index;
    int numActions;
    double* Q;    
    Vertex(State s0, int index0, int numActions0):s(s0),index(index0), numActions(numActions0){
        Q = new double[numActions0];
        for (int i = 0; i < numActions; i++)
            Q[i] = 0.0;
    }
    Vertex(const Vertex& v){
        s = v.s;
        index = v.index;
        numActions = v.numActions;
        Q = new double[numActions];
        for (int i = 0; i < numActions; i++)
            Q[i] = v.Q[i];
    }
    ~Vertex(){
        delete Q;
    }
    State& getState(){return s;}
    double maxQ(){
        double Qtemp = Q[0];
        for (int i = 0; i < numActions; i++ ){
            if (Q[i] > Qtemp) Qtemp = Q[i];
        }
        return Qtemp;
    
    }
    
    int maxQIdx(){
        double Qtemp = Q[0];
        int idx = 0;
        for (int i = 0; i < numActions; i++ ){
            if (Q[i] > Qtemp) {
                Qtemp = Q[i];
                idx = i;
            }
        }
        return idx;
    
    
    }
    int minQIdx(){
        double Qtemp = Q[0];
        int idx = 0;
        for (int i = 0; i < numActions; i++ ){
            if (Q[i] < Qtemp) {
                Qtemp = Q[i];
                idx = i;
            }
        }
        return idx;
    
    
    }
    
};

struct Edge{
    int from, to;
    int action;
    Edge(int from0, int to0, int action0):from(from0),to(to0),action(action0){}
};

struct Experience{
 State oldState, newState;
 int action;
 double reward;
 Experience(State s0,  State s1,int a0, double r):
    oldState(s0), newState(s1), action(a0), reward(r){}
};


class RandomStream{
private:
    std::shared_ptr<std::mt19937> genPtr;
    std::shared_ptr<std::uniform_real_distribution<>> randomPtr_unitformReal;
    std::shared_ptr<std::uniform_int_distribution<>> randomPtr_unitformInt; 
public:     
    RandomStream(){
        
        std::random_device rd;
        genPtr = std::make_shared<std::mt19937>(rd());
        randomPtr_unitformReal = std::make_shared<std::uniform_real_distribution<>>(0.0, 1.0);
    }
    RandomStream(int low , int high){
        
        std::random_device rd;
        genPtr = std::make_shared<std::mt19937>(rd());
        
        randomPtr_unitformReal = std::make_shared<std::uniform_real_distribution<>>(0.0, 1.0);
        randomPtr_unitformInt = std::make_shared<std::uniform_int_distribution<>>(low, high);
    }
    double nextDou(){return (*randomPtr_unitformReal)(*genPtr);}
    int nextInt(){return (*randomPtr_unitformInt)(*genPtr);}
};

class MultiGraph_QL: public MultiGraphBase<Vertex, Edge, State>{
public: 
    MultiGraph_QL(int numActions0):MultiGraphBase<Vertex, Edge, State>(numActions0){
        randu = new RandomStream(0,numActions0-1);
    }
    void update_Q(Experience exp, double learningRate, double discount);
    void update_Q(State s);
    void outputQ(std::string filename);
    int selectNextAction(State currState);
private: 
    RandomStream* randu;

    
};
