//Including required libraries
#include <stdio.h>
#include <stdlib.h>


//Declaring the global variables (const meaning it will not be changed)
#define gridSize 10
char hiddenBoard[gridSize][gridSize];
char userBoard[gridSize][gridSize];

//Declaring the functions that will be used in the code
int isValid(int row, int col);
void increment();
void incrementCheck(int i, int j);
void printGrid();
int check(int row, int col);
void flag(int row, int col);
int checkWin();
void setMines();
//Simply here for testing purposes! left it simply to be able to look back at it
void printHiddenGrid();

//Main function
int main() {
    //Create the hidden board
    for (int i = 0; i < gridSize; i++){
        for (int j = 0; j < gridSize; j++){
            //Setting each element equal to the character 0
            hiddenBoard[i][j] = '0';
        }
    }

    //Calling the setMines() function to set the mines
    setMines();
    //Calling the increment() function to increment the elements around a mine
    increment();

    //Create the user's board
    for (int i = 0; i < gridSize; i++){
        for (int j = 0; j < gridSize; j++){
            //Setting each element equal to the character *
            userBoard[i][j] = '*';
        }
    }

    //Printing the hidden grid using the printHiddenGrid() function ONLY if the user wants to see the hidden board
//    printHiddenGrid();

    //Creating a while loop that runs as long as the checkWin() function returns zero - meaning that the game
    //has yet to be won
    while (checkWin() == 0){ //IS THIS THE RIGHT WAY OF FORMATTING THIS???

        //Printing the grid by calling the printGrid() function
        printGrid();

        //Initializing variables for the user's inputs
        char userInput;
        int row, col;
        //Printing the messages to the user to let them know to enter either a check of a flag along with
        //the coordinates
        printf("Enter 'c' for check cell, 'f' for flag cell.\n");
        printf("Enter command & chosen cell (row & col): ");
        scanf("%c %d %d", &userInput, &row, &col);
        printf("\n");

        //Calling the isValid function to check whether the user's entered coordinates are
        if (isValid(row, col) == 0){
            printf("Invalid input, please enter a integer between 0 and 9 inclusive.");
            continue;
        }

        //If the user's input is f, call the flag function
        if (userInput == 'f'){
            flag(row, col);
        }

        //If the user's input is c, call the check function to check the element at the coordinates they entered
        if (userInput == 'c'){
            if (check(row, col)) {
                //After the element is checked, check if the win conditions are satisfied by calling the
                //checkWin function
                if (checkWin()) {
                    printf("Congratulations! You win!");
                    break;
                }
            }
            //If the check function returns 0, the element must be a mine
            else {
                //Show the user that the element is a mine and print the grid once more
                userBoard[row][col] = 'M';
                printGrid();
                //Print the statement telling the user they've hit a mine
                printf("You hit a mine, game over.");
                break;
            }
        }
    }
}

//Defining the isValid function which checks if the coordinates entered/checked are valid
int isValid(int row, int col){
    //If the coordinate is 0 or bigger and smaller than 10 (so 9 max), then the coordinate is valid - return 1
    if ((row >= 0) && (row < gridSize) && (col >= 0) && (col < gridSize)){
        return(1);
    }
    //If not, return zero
    else{
        return(0);
    }
}

//Defining the increment function
void increment(){
    //Create a for loop which checks if an element in the grid is a mine
    for (int i = 0; i < gridSize; i++){
        for (int j = 0; j < gridSize; j++){
            //If the element is a mine, then increment every space around it by 1
            if (hiddenBoard[i][j] == 'M'){
                for (int m = -1; m <= 1; m++){
                    for (int n = -1; n <= 1; n++){
                        //Making sure it is within the bounds
                        if (i+m != -1 && j+n != -1 && i+m != gridSize && j+n != gridSize){
                            //If the condition is satisfied, then call the incrementCheck function
                            incrementCheck(i+m, j+n);

                        }
                    }
                }
            }
        }
    }
}

//Defining the incrementCheck function
void incrementCheck(int i, int j){
    //Checking if the element from the hidden board is not a mine and is a valid coordinate
    if (hiddenBoard[i][j] != 'M' && isValid(i, j)){
        //If the conditions are satisfied, increment the element at the desired coordinates
        hiddenBoard[i][j]++;
    }
}

//Defining the printGrid function
void printGrid(){
    //For loop to iterate through each element of the grid and printing it out
    for (int i = 0; i < gridSize; i++){
        for (int j = 0; j < gridSize; j++){
            //Printing the element of the grid with two spaces after it to respect formatting guidelines
            printf("%c  ", userBoard[i][j]);
        }
        //After each row, move on to a new line
        printf("\n");
    }
}

//Defining the printHiddenGrid function, which is only used for testing purposes
void printHiddenGrid(){
    //For loop to iterate through each element of the grid and printing it out
    for (int i = 0; i < gridSize; i++){
        for (int j = 0; j < gridSize; j++){
            //Printing the element of the grid with two spaces after it to respect formatting guidelines
            printf("%c  ", hiddenBoard[i][j]);
        }
        //After each row, move on to a new line
        printf("\n");
    }
}

//Defining the check function
int check(int row, int col) {
    //Checking if the coordinates are valid
    if (isValid(row, col) == 1){
        //If the element at the coordinates is a mine, return 0
        if (hiddenBoard[row][col] == 'M') {
            return(0);
        }
        if (userBoard[row][col] == '*' && userBoard[row][col] != 'F') {
            //If the element in the user grid at the coordinate is not a flag and is hidden (so *),
            //then reveal it by setting it equal to the element from the hidden grid
            userBoard[row][col] = hiddenBoard[row][col];
            if (hiddenBoard[row][col] == '0') {
                //If the element is 0, then that means that there are no mines directly next to it
                //therefore recursively call the check function again to reveal the spaces next to that element
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        check(row+i,col+j);
                    }
                }
            }
        }
        //If it is not a mine, return 1
        return(1);
    }
}

//Defining the flag function
void flag(int row, int col){
    //Checking if the element is still hidden or not
    if (userBoard[row][col] == '*') {
        //If it is hidden, then it can be flagged - so set it equal to F
        userBoard[row][col] = 'F';
    }
}

//Defining the checkWin function
int checkWin(){
    //Initializing and assigning the count variable equal to 0
    int count = 0;

    for (int i = 0; i < gridSize; i++){
        for (int j = 0; j < gridSize; j++){
            if (userBoard[i][j] == '*'){
                //Checking every element of the grid for any hidden elements, if the element is hidden
                //increase the count by 1
                count++;
            }
        }
    }
    //If the count is 0, meaning that there are no more hidden elements, or the count is 10, meaning there
    //are 10 hidden elements (either they are all flags or they all the mines are still hidden - but only
    //the mines), then return 1
    if (count == 0 || count == 10){
        return(1);
    }
    //If there are still hidden elements, or there are not exactly 10 hidden elements left, return 0
    else if (count != 0 && count != 10){
        return(0);
    }
}

//Defining the setMines function
void setMines(){
    //Seeding with a value of 2
    srand(2);
    int count = 0;
    while(count < 10){
        //Setting 10 mines
        //Randomizing the row coordinate
        //LIMITING RANDOMNESS FOR TESTING PURPOSES
        int x = rand() % gridSize;
        //Randomizing the col coordinate
        int y = rand() % gridSize;
        //If the board is not already a mine, set it equal to a mine
        if (hiddenBoard[x][y] == '0') {
            hiddenBoard[x][y] = 'M';
            //Increasing the count by 1
            count++;
        }
    }
}