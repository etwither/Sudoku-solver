#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <time.h>
#include <string>
#include "solverFunctions.h"
using namespace std;

#define N 9

//asks for level of difficulty
char const text(){
  string choice;
  //loops until it gets the correct input
  while(1){
    cout << "Enter your difficulty level (E, M, H): ";
    cin >> choice;
    choice[0] = toupper(choice[0]);
    if((choice[0] == 'E' || choice[0] == 'M' || choice[0] == 'H') && choice.length() == 1){
      return choice[0];
    }
    
    cout << "ERROR: Invalid input\n\n";
  }
}

//creates a puzzle for the program to solve
void create(int puzzle[N][N], char dif){

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
  
  //remove x amount of spots based on difficulty
  if(dif == 'E'){
    remove(puzzle, 45);
  }
  else if(dif == 'M'){
    remove(puzzle, 55);
  }
  else if(dif == 'H'){
    remove(puzzle, 75);
  }
}

//changes spots back to empty
void remove(int puzzle[N][N], int rAmount){
  //seed ramdom
  srand(time(0));
  
  //change random spot back to 0
  for(int i=0; i<rAmount; i++){
    puzzle[(rand()%8)+1][(rand()%8)+1] = 0;
  }
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
