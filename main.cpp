#include <string>
#include "RLSolver.h"
#include "MultiGraph_QL.h"
#include "model.h"
#include <iostream>



int main(){
    TrainingPara trainingPara;
    trainingPara.discount = 0.99;
    trainingPara.learningRate = 0.1;
    trainingPara.maxIter = 50;
    trainingPara.numEpisodes = 1000;
    trainingPara.defaultBigValue = 100;
    trainingPara.targetState = State(1,1);
    int numActions = 4;
    std::string mapfile;
    Model model("map.txt");

    
    MultiGraph_QL g(numActions);

    
   RLSolver solver(model,g,trainingPara);
    solver.train();
    return 0;
}
