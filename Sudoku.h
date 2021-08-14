#pragma once 

#include<cmath>
#include<vector>
#include<string>

using namespace std;

class Sudoku_Solver{

    private:
        vector<vector<int>> grid;
        vector<vector<int>> possibleValues;
        string fileName;
        // int expandedNodes=0;
        int Num=9; //dimention of the gride
        int Box=3; // box wdith

        vector<int> getPossibleValues(int row, int col);
        void writeTheGridOnFile(bool isPrint);
        void readGrid();
        void getUnsidedLocation(int& row, int& col);
        vector<vector<int>> getRemaningValues();
        bool isEmptyDomainProduced(int row,int col,int choice);
        bool solveSudoKu();  
        vector< vector<int> >::iterator row;
        vector<int>::iterator col;   
    
    public:
        Sudoku_Solver(string file_Name){
            fileName=file_Name;
            readGrid();
            Num=grid.size();
            Box=sqrt(Num);
            possibleValues=getRemaningValues();
        }
        void solve(){
		    writeTheGridOnFile(solveSudoKu());
        }
        void printGrid();
};
