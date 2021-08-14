#include<iostream>
#include<string>
#include<chrono>
#include"Sudoku.h"


using namespace std;
using namespace std::chrono;

#define UNASSIGNED 0



int main(int argc, char** argv)
{
    
    if(argc!=2){
        cout<<"Programme is required only one arugemnt which should contains the input file Name"<<endl;
        cout<<"<--Programme ended-->"<<endl;
        return -1;
    }

    
    
   string InputfileName=argv[1];
   InputfileName=InputfileName.substr(0,InputfileName.find("."));

   high_resolution_clock::time_point start = high_resolution_clock::now(); 

   Sudoku_Solver sudoku(InputfileName);
   sudoku.solve();
   sudoku.printGrid();    

   high_resolution_clock::time_point stop = high_resolution_clock::now(); 


    cout << "Exceution Time | "<<endl;
    auto sec = duration_cast<seconds>(stop - start); 
    cout << "          seconds      : "<<sec.count() << endl; 
    auto millisec = duration_cast<milliseconds>(stop - start); 
    cout << "          milliseconds : "<<millisec.count() << endl; 
    auto microsec = duration_cast<microseconds>(stop - start); 
    cout << "          microseconds : "<<microsec.count() << endl; 

   

	return 0;
}


