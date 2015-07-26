#include <iostream>
#include "RLSolver.h"

RLSolver::RLSolver(Model& m, MultiGraph_QL& g, TrainingPara tp):
model(m),graph(g), trainingPara(tp){		
}

void RLSolver::train(){
    int iter;
    int action = 0;
    char tag[10];
    for( int i = 0; i < trainingPara.numEpisodes; i++) {
        std::cout << "training Episodes " << i << std::endl;
        iter = 0;
	model.createInitialState();
        graph.update_Q(model.getCurrState());
	while(!targetReached(model.getCurrState()) && iter < trainingPara.maxIter) {
            State oldState = model.getCurrState();
            action = graph.selectNextAction(oldState);
            model.run(action);
            State newState = model.getCurrState();
            double reward = this->getRewards(oldState, newState);
            graph.update_Q(Experience(oldState, newState, action, reward), trainingPara.learningRate, trainingPara.discount);
            iter++;
            std::cout << "numV " << graph.getNumV() << " numE " << graph.getNumE() << std::endl;
        }
        if ( (i+1)%50 == 0){
        sprintf(tag,"%d",i);
        graph.outputQ("Q_"+(std::string)tag);
        }
    }	
	
//	this->getPolicy();
}

double RLSolver::getRewards(State oldState, State currState){
    if (oldState.equals(currState) ){
        return -trainingPara.defaultBigValue;
    } else if (currState.equals(trainingPara.targetState)){
        return 1;
    } else {
        return 0;
    }
}
bool RLSolver::targetReached(State s){
    if( s.equals(trainingPara.targetState)){
        std::cout << "hit target!!!!!!!!!!!!!!!!!!!!" << std::endl;
        return true;
    }
    
    return false;
}

