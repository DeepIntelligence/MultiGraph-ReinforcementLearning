#pragma once
#include <string>
#include "MultiGraph_QL.h"


class Model{

public:
    Model(std::string filename);
    void run(int action);	
    State getCurrState(){return currState;};
    void createInitialState();
private:
    State oldState, currState;

};
