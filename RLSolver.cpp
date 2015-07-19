#include "RLSolver.h"

RLSolver::RLSolver(Model& m, MultiGraph_QL& g, TrainingPara tp):
model(m),graph(g), trainingPara(tp){
	
		
}

void RLSolver::train(){
    int iter = 0;
    int action = 0;
    for( int i = 0; i < trainingPara.numEpisodes; i++) {
	model.createInitialState();
	while(!targetReached() && iter < trainingPara.maxIter) {
            State oldState = model.getCurrState();
            action = graph.selectNextAction(oldState);
            model.run(action);
            State newState = model.getCurrState();
            double reward = this->getRewards();
            graph.update_Q(Experience(oldState, newState, action, reward), trainingPara.learningRate, trainingPara.discount);
					
            }
		
	}	
	
//	this->getPolicy();
}

double RLSolver::getRewards(){return 0;}
bool RLSolver::targetReached(){return false;}

