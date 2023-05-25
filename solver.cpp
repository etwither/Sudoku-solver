#include <iostream>
#include "solverFunctions.h"
using namespace std;

#define N 9

int main(){
  int puzzle[N][N];
  
  create(puzzle, text());
  cout << "New Puzzle:\n";
  printP(puzzle);
  
  string temp;
  cout << "Enter anything to see solution: ";
  cin >> temp;
  solve(puzzle);
  cout << "Solution:\n";
  printP(puzzle);
  
  return 0;
}
