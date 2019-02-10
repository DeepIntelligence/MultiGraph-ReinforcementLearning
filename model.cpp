#include <iostream>
#include <fstream>
#include <sstream>
#include "model.h"


Model::Model(std::string filename){
    this->readBitmap(filename);
    rand = std::make_shared<RandomStream>(0, this->colBM*this->rowBM-1);
}

Model::~Model(){
    for (int i = 0; i < rowBM; i++ ){
        delete[] bitmap[i];
    }

    delete[] bitmap;
}

void Model::run(int action){
    switch(action){ 
        case 0: 
            if (!this->isOnObstacle(currState.rowIdx - 1, currState.colIdx)){
                oldState = currState;
                currState.rowIdx -=1;
            }
            break;
        case 1:
            if (!this->isOnObstacle(currState.rowIdx + 1, currState.colIdx)){
                oldState = currState;
                currState.rowIdx +=1;
            }
            break;
        case 2:
            if (!this->isOnObstacle(currState.rowIdx, currState.colIdx - 1)){
                oldState = currState;
                currState.colIdx -=1;
            }
            break;
        case 3:
            if (!this->isOnObstacle(currState.rowIdx, currState.colIdx + 1)){
                oldState = currState;
                currState.colIdx +=1;
            }
            break;
        default:break;
    }
}        


void Model::createInitialState(){
    int col;
    int row;

    while( true ){
    int index = rand->nextInt();
    col = index % this->colBM;
    row = index / this->rowBM;
    if (!this->isOnObstacle(row,col)) break;
    }
    currState.colIdx = col;
    currState.rowIdx = row;
}

bool Model::isOnObstacle(int i,int j){
    
    if (i >= 0 && j >= 0 && i < rowBM && j < colBM){
        return (bitmap[i][j] == 0);
    }
    return true;
}

void Model::readBitmap(std::string s) {

    std::ifstream is;
    is.open(s);
    std::string line;
    std::string data;
    int lineNum = 0;
    int row = 0;
    int temp;
    while (getline(is, line)) {
        lineNum++;
        std::stringstream linestream(line);

        if (lineNum == 1) {
            linestream>>rowBM;
            std::cout << "The number of rows of the matrix are: " << rowBM << std::endl;
        } else if (lineNum == 2) {
            linestream>>colBM;
            std::cout << "The number of rows of the matrix are: " << colBM << std::endl;
            bitmap = new int*[rowBM];
            for (int i = 0; i < rowBM; i++) {
                bitmap[i] = new int[colBM];
            }
        } else {


            for (int i = 0; i < colBM; i++) {
                linestream>>temp;
                bitmap[row][i] = temp;
            }
            row++;
        }
    }
    std::ofstream os;
    os.open(s + "mapdata.txt");
    for (int i = 0; i < rowBM; i++) {
        for (int j = 0; j < colBM; j++) {
            if (bitmap[i][j] == 1) os << j << "\t" << i << std::endl;
            ;
        }
    }
    os.close();
    is.close();


    os.open(s + "walldata.txt");
    int count = 0;
    for (double i = -1; i <= rowBM; i += 0.5) {
        for (double j = -1; j <= colBM; j += 0.5) {
            if ((int) round(i) >= 0 && (int) round(i) < rowBM && (int) round(j) >= 0 && (int) round(j) < colBM) {
                if (bitmap[(int) round(i)][(int) round(j)] == 0) {
                    count++;
                    os << count << "\t" << j << "\t" << i << std::endl;
                }
            } else if (abs(i + 1) < 0.25 || abs(i - rowBM) < 0.25 ||
                    abs(j + 1) < 0.25 || abs(j - colBM) < 0.25) {
                count++;
                os << count << "\t" << j << "\t" << i << std::endl;
            }
        }

    }
    os.close();
}
