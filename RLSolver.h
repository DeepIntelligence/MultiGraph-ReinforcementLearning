#include "MultiGraph_QL.h"
#include "model.h"

struct TrainingPara{
    int numEpisodes;
    int maxIter;
    double learningRate;
    double discount;

};

class RLSolver {
public:
    RLSolver(Model& m, MultiGraph_QL& g, TrainingPara tp);
    void train();
    double getRewards();
    bool targetReached();


private:
    Model& model;    
    MultiGraph_QL& graph;
    TrainingPara trainingPara;



};