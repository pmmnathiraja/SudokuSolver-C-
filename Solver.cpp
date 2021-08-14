#include"Sudoku.h"
#include<fstream>
#include<istream>
#include<sstream>
#include<algorithm>
#include<iostream>
#include<string>


using namespace std;

#define UNASSIGNED 0

void Sudoku_Solver::readGrid(){
    ifstream readFile(fileName+".txt");
    string line;
    int number;
    while (getline (readFile, line)) {
        istringstream stringStream(line);
        vector<int> temp;
        while (stringStream >> number) 
        {
            temp.push_back(number);
        }
        grid.push_back(temp);
    }

}

vector<vector<int>> Sudoku_Solver::getRemaningValues(){
    vector<vector<int>>  possibleValues;
    for(int row=0;row<Num;row++){
        for(int col=0;col<Num;col++){
            if(grid[row][col]!=0){
                possibleValues.push_back(vector<int>{-15});
            }
            else{
                possibleValues.push_back(getPossibleValues(row,col));
            }
        }
    }
    return possibleValues;
}

void Sudoku_Solver::writeTheGridOnFile(bool isPrint)
{
    fstream outputFile;
    outputFile.open(fileName+"_output.txt",fstream::out);

    if(isPrint){
    for (row = grid.begin(); row != grid.end(); row++) {
         for (col = row->begin(); col != row->end(); col++) {
                outputFile << *col << " ";
             }
            outputFile << endl;
        }
    }else{
         outputFile << "No solution exists";
    }
}

void Sudoku_Solver::printGrid()
{
    for (row = grid.begin(); row != grid.end(); row++) {
         for (col = row->begin(); col != row->end(); col++) {
                cout << *col << " ";
      }
      cout << endl;
    }
    cout << endl;
}



vector<int> Sudoku_Solver::getPossibleValues(int row, int col){

     vector<int> vec={1,2,3,4,5,6,7,8,9 };

     if(Num!=9){
        vec={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
     }
 
    for (int col1 = 0; col1 < Num; col1++){
           vec.erase(remove(vec.begin(), vec.end(), grid[row][col1]), vec.end());
    }
    for (int row1 = 0; row1 < Num; row1++){
        vec.erase(remove(vec.begin(), vec.end(), grid[row1][col]), vec.end());
    }

        int boxRow = row - row % Box;
        int boxCol = col - col % Box;
    for (int row1 = 0; row1 < Box; row1++){
		for (int col1 = 0; col1 < Box; col1++){
            vec.erase(remove(vec.begin(), vec.end(), grid[boxRow+row1][boxCol+col1]), vec.end());
        }
    }
    return vec;

}

void Sudoku_Solver::getUnsidedLocation(int& row, int& col){
   
    int minVal=100;
    int minIndex=0;  

    for(int i=0;i<possibleValues.size();i++){
        int tempsize=possibleValues[i].size();
        if(possibleValues[i][0]==-15){
            tempsize=Num+1;
        }
        if(minVal>tempsize){
            minVal=tempsize;
            minIndex=i;
        }
    }

    if (minVal==Num+1){
        row=-1;
        col=-1;
    }else{
        row=floor(minIndex/Num);
        col=minIndex%Num;
    }   
}

bool Sudoku_Solver::isEmptyDomainProduced(int row,int col,int choice){
    vector<int> elemnt = possibleValues[row*Num+col];
     possibleValues.erase(possibleValues.begin() + row*Num+col);
    if(find(possibleValues.begin(), possibleValues.end(), vector<int>{}) != possibleValues.end()){
        possibleValues.insert(possibleValues.begin() + row*Num+col, elemnt);
        return true;
    }else{
        possibleValues.insert(possibleValues.begin() + row*Num+col, elemnt);
        return false;
    }

}


bool Sudoku_Solver::solveSudoKu(){
    int row,col;
    getUnsidedLocation(row,col);
    if(row==-1)
        return true;
    else{
        for(int k=0;k<possibleValues[row*Num+col].size();k++){
            grid[row][col]=possibleValues[row*Num+col][k];
            vector<vector<int>> cpy(possibleValues.size());
            copy(possibleValues.begin(), possibleValues.end(), cpy.begin());
            possibleValues=getRemaningValues();        
            if(!isEmptyDomainProduced(row,col,possibleValues[row*Num+col][k])){
                
                if(solveSudoKu())
                    return true;
            }
            grid[row][col]=0;
            possibleValues=cpy;
        }
    }
    return false;
}