#include "MultiGraph_QL.h"
#include "model.h"

struct TrainingPara{
    TrainingPara(){}
    int numEpisodes;
    int maxIter;
    double learningRate;
    double discount;
    State targetState;
    int defaultBigValue;
};

class RLSolver {
public:
    RLSolver(Model& m, MultiGraph_QL& g, TrainingPara tp);
    void train();
    double getRewards(State oldS, State newS);
    bool targetReached(State s);


private:
    Model& model;    
    MultiGraph_QL& graph;
    TrainingPara trainingPara;



};