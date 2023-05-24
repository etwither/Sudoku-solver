#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
using namespace std;

#define N 9

void create(int puzzle[N][N]);
void const printP(int puzzle[N][N]);
bool solve(int puzzle[N][N]);
bool getEmpty(int puzzle[N][N], int &col, int &row);
bool isSafe(int num, int puzzle[N][N], int col, int row);

int main(){
  int puzzle[N][N];
  
  create(puzzle);
  
  //solve(puzzle);
  
  return 0;
}

//creates a puzzle for the program to solve
//TODO: add difficulty
void create(int puzzle[N][N]){

  vector<int> numbers = {1,2,3,4,5,6,7,8,9};
  random_device rd;
  mt19937 rng(rd());
  shuffle(numbers.begin(), numbers.end(), rng);
  
  int temp;
  
  //set every spot to zero
  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      puzzle[i][j] = 0;
    }
  }
  
  for(int i=0; i<N; i=i+3){
    for(int j=0; j<N; j++){
      if(isSafe(numbers[j], puzzle, j, i)){
        puzzle[i][j] = numbers[j];
      }
    }
    for(int k=0; k<3; k++){
      temp = numbers[8];
      numbers.pop_back();
      numbers.insert(numbers.begin(), temp);
    }
  }
  
  solve(puzzle);
  
  cout << "New puzzle:\n";
  printP(puzzle);
}

//print out sudoku puzzle
void const printP(int puzzle[N][N]){
  for(int i=0;i<N;i++){
    if(i%3 == 0){
      cout << "-------------------------\n";
    }
    for(int j=0;j<N;j++){
      if(j%3 == 0){
        cout << "| ";
      }
      cout << puzzle[i][j] << ' ';
    }
    cout << "|\n";
  }
  cout << "-------------------------\n\n";
}

//solves the puzzle
bool solve(int puzzle[N][N]){
  int col, row;
  
  //finds the next empty (0) spot
  if(!getEmpty(puzzle, col, row)){
    return true; //no empty spots, puzzle is solved
  }
  
  //tries to fill the empty spot with a number 1-9
  for(int i=1; i<=N; i++){
    //trive to find a safe place to put the number
    if(isSafe(i, puzzle, col, row)){
      puzzle[row][col] = i;
     
    //recursively solve the puzzle 
    if(solve(puzzle)){
      return true;
    }
      //if no solution if found reset it
      puzzle[row][col] = 0;
    }
  }
  
  return false;
  
}

//finds the first empty (0) spot available
bool getEmpty(int puzzle[N][N], int &col, int &row){
  for(row=0; row<N; row++){
    for(col=0; col<N; col++){
      if(puzzle[row][col] == 0){
        return true;
      }
    }
  }
  return false;
}

//checks to see if there are any conflicting nubers is a spot
bool isSafe(int num, int puzzle[N][N], int col, int row){
  //check if column is safe
  for(int i=0; i<N; i++){
    if(puzzle[i][col] == num){
      //cout << "col not safe\n";
      return false;
    }
  }
  
  //check is row is safe
  for(int i=0; i<N; i++){
    if(puzzle[row][i] == num){
      //cout << "row not safe\n";
      return false;
    }
  }
  
  //check if 3 by 3 grid is safe
  int colTemp = col-col%3;
  int rowTemp = row-row%3;
  
  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      if(puzzle[i+rowTemp][j+colTemp] == num){
        //cout << "grid not safe\n";
        return false;
      }
    }
  }
  
  return true;
}
