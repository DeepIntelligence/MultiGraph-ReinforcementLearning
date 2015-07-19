#include <string>
#include "RLSolver.h"
#include "MultiGraph_QL.h"
#include "model.h"

int main(){
    TrainingPara trainingPara;
    trainingPara.discount = 0.99;
    trainingPara.learningRate = 0.1;
    trainingPara.maxIter = 50;
    trainingPara.numEpisodes = 100;
    int numActions = 4;
    std::string mapfile;
    Model model(mapfile);
    MultiGraph_QL g(numActions);
    RLSolver solver(model,g,trainingPara);

    return 0;
}
