#pragma once
#include <string>
#include "MultiGraph_QL.h"


class Model{

public:
    Model(std::string filename);
    ~Model();
    void run(int action);	
    State getCurrState(){return currState;};
    void createInitialState();

private:
    bool isOnObstacle(int i, int j);
    void readBitmap(std::string filename);
    State oldState, currState;
    int **bitmap;
    int rowBM;
    int colBM;
    std::shared_ptr<RandomStream> rand;

};
