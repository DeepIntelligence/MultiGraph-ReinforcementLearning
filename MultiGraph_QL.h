#pragma once

#include <vector>
#include <unordered_map>
#include <random>
#include "MultiGraphBase.h"
// Vertex usually needs to redefine a hasher and a equal function for the state
struct State{
    int rowIdx, colIdx;
};

namespace std{
template<>
struct hash<State>{
    typedef State argument_type;
    typedef std::size_t result_type;
    result_type operator()(const argument_type& s) const{
    result_type h1=std::hash<int>()(s.rowIdx);
    result_type h2 = std::hash<int>()(s.rowIdx);
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
    double Q;    
    Vertex(State s0,int index0):s(s0),index(index0),Q(0.0){}
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


struct RandomStream{
std::random_device rd;
//std::mt19937 gen(rd());
//std::uniform_real_distribution<> dis(0, 1);
//  double next(){return dis(gen);}
};

class MultiGraph_QL: public MultiGraphBase<Vertex, Edge, State>{
public: 
    MultiGraph_QL(int numActions0):MultiGraphBase(numActions){}
    void update_Q(Experience exp, double learningRate, double discount);
    int selectNextAction(State currState);
private: 
    RandomStream randu;

    
};
