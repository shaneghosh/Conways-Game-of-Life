/** =======================================================================
 * Author: Shane Ghosh
 * Date:  Nov 16, 2021
 *
 * Purpose   Conways Game of Life.
 *
 * Course:   Programming 25
 * Teacher:  Ms. Deepeka Dalal
* ========================================================================*/
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
    //Initializes board dimentiones, user inputs and values
    int boardHeight, boardLength;
    int userInput;
    int genVal;
    int vertVal {0}, horizVal {0};

    //Welcome Message
    cout << "Welcome to Conways Game of Life." << endl;

    //Gameboard dimention input
    cout << "Please enter the gameboard height: " << endl;
    cin >> boardHeight;

    //Data sanitation for gameboard height
    while (boardHeight < 1 ){
        cout << "Please enter a value that is greater than 0! " << endl;
        cout << "Please enter the gameboard height: " << endl;
        cin >> boardHeight;
    }

    //Gameboard dimention input
    cout << "Please enter the gameboard length: " << endl;
    cin >> boardLength;

    //Data sanitation for gameboard height
    while (boardLength < 1 ){
        cout << "Please enter a value that is greater than 0! " << endl;
        cout << "Please enter the gameboard length: " << endl;
        cin >> boardLength;
    }

    //Input for amount of times(gens) user wants to see game matrix
    cout << "Please enter the amount of generation that you would like to run: ";
    cin >> genVal;

    //Data sanitation
    while (genVal < 1 ){
        cout << "Please enter a value that is greater than 0! " << endl;
        cout << "Please enter the amount of generation that you would like to run: ";
        cin >> genVal;
    }

    //copies board height and length to use and mutate
    const size_t rowNum = boardHeight;
    const size_t colNum = boardLength;

    //creates a game board string and a copy of the gameboard
    string gameBoard[rowNum][colNum];
    string copyList[rowNum][colNum];

    //board size is the length times height + count is set to one
    const size_t boardSize = boardHeight * boardLength;
    int countNum = 1;


    //This loop iterates through to create inital gameboard
    for (int i{0}; i < rowNum; i++)
    {
        for (int j{0}; j < colNum; j++)
        {
            gameBoard [i][j] = to_string(countNum);
            copyList[i][j] = to_string(countNum);
            countNum ++;
        }
    }

    //prints out initial board
    for( auto &row : gameBoard)
    {
        for(auto col : row)
             cout << setw(4) << col << " ";
        cout<<endl;
    }


    do
    {
        //asks the user for amount of cells they to bring to life
        cout << "Please enter the cell you would like to bring to life (0 to quit): ";
        cin >> userInput;

        //Data sanitation to make sure correct cells are chosen
        while (userInput < 0 || userInput > boardSize){
            cout << "Please enter a value that is on the board! " << endl;
            cout << "Please enter the cell you would like to bring to life (0 to quit): " << endl;
            cin >> userInput;
        }

        //if loop which
        if (userInput <= boardSize && userInput > 0)
        {
                    if (userInput % colNum != 0)
                        vertVal = floor(userInput/colNum);
                    else if (userInput % colNum == 0)
                        vertVal = floor(userInput/colNum -1);
                    if (userInput % colNum == 0)
                        horizVal = colNum - 1;
                    else if (userInput % colNum != 0)
                        horizVal = (userInput % colNum) - 1;
                    gameBoard[vertVal][horizVal] = "@";
                    copyList[vertVal][horizVal] = "@";

        }

    //Lets user stop entering numbers
    } while (userInput != 0);

    //message to notify user
    cout << "This is your initial gameboard: " << endl;

    //prints out gameboard
    for( auto &row : gameBoard)
    {
        for(auto col : row)
             cout << setw(4) << col << " ";
        cout<<endl;
    }
    cout << endl;

    //for loop runs for every generation there is to print and make a matrix for each generation
    for (int currentGen{1}; currentGen <= genVal; currentGen++)
    {

        //vectors initialized
        vector<int>stayVec;
        vector<int>underVec;
        vector<int>overVec;
        vector<int>newVec;

        // For loop runs the code for every string in the vector (gameboard)
        for (int currentNum{1}; currentNum <= boardSize; currentNum++)
        {
           //calculates the position of the number
           int horizCoord = 0;
           int vertCoord = 0;
           if (currentNum % colNum != 0)
           {
               vertCoord = floor(currentNum/colNum);
               horizCoord = (currentNum % colNum) - 1;
           }
           else if (currentNum % colNum == 0)
           {
               vertCoord = floor((currentNum/colNum) -1);
               horizCoord = colNum - 1;
           }


           //Values that store info about surrounding of the cell
           int aroundIt = 0;
           int checkAbove = vertCoord - 1;
           int checkBelow = vertCoord + 1;
           int checkLeft = horizCoord - 1;
           int checkRight = horizCoord + 1;

           //Runs if there is a row above the cell
           if (checkAbove >= 0)
           {
                    //adds one to counter (aroundIt) if there is a cell directly above it
                   if (gameBoard[vertCoord - 1][horizCoord] == "@")
                       aroundIt += 1;

                   //adds one to counter (aroundIt) if there is a cell directly to the above and left
                   if (checkLeft >= 0)
                   {
                       if (gameBoard[vertCoord - 1][horizCoord - 1] == "@")
                           aroundIt += 1;
                   }
                   //adds one to counter (aroundIt) if there is a cell directly to the above and right
                   if (checkRight < colNum)
                   {
                       if (gameBoard[vertCoord - 1][horizCoord + 1] == "@")
                           aroundIt += 1;
                   }
            }

           //Last code block but checks for below (checks directly above, above right, above left - adds to around it accordingly)
           if (checkBelow < rowNum)
           {

                   if (gameBoard[vertCoord + 1][horizCoord] == "@")
                       aroundIt += 1;
                   if (checkLeft >= 0)
                   {
                       if (gameBoard[vertCoord + 1][horizCoord - 1] == "@")
                           aroundIt += 1;
                   }
                   if (checkRight < colNum)
                   {
                       if (gameBoard[vertCoord + 1][horizCoord + 1] == "@")
                           aroundIt += 1;
                   }
           }

           // Adds 1 to around it if there is an @ directly beside current number (left)
           if (checkLeft >= 0)
           {
                   if (gameBoard[vertCoord][horizCoord - 1] == "@")
                           aroundIt += 1;
           }

           // Adds 1 to around it if there is an @ directly beside current number (right)
           if (checkRight < colNum)
           {
               if (gameBoard[vertCoord][horizCoord + 1] == "@")
                       aroundIt += 1;
           }

           // Determines if the cell is born, die, underpopulation, overpopulation, ect. (based on code above)
           if (aroundIt < 2 && aroundIt >= 0 && gameBoard[vertCoord][horizCoord] == "@")
           {
               underVec.push_back(currentNum);
               copyList[vertCoord][horizCoord] = to_string(currentNum);

           }
           else if (aroundIt > 3 && gameBoard[vertCoord][horizCoord] == "@")
           {
               overVec.push_back(currentNum);
               copyList[vertCoord][horizCoord] = to_string(currentNum);

           }
           else if (aroundIt == 3 && gameBoard[vertCoord][horizCoord] != "@")
           {
               newVec.push_back(currentNum);
               copyList[vertCoord][horizCoord] = "@";

           }
           else if ((aroundIt == 3 || aroundIt == 2) && (gameBoard[vertCoord][horizCoord] == "@"))
               stayVec.push_back(currentNum);

        }

        // Copies the current values in copyList (printing list) to gameBoard (calculation list) for comparison on next generation
        std::copy(&copyList[0][0], &copyList[0][0]+rowNum*colNum,&gameBoard[0][0]);

        cout << "Generation: " << currentGen << endl;

        //Displays to user the gameboard after all mutations that happen over a generation
        for( auto &row : copyList)
        {
            for(auto col : row)
                 cout << setw(4) << col << " ";
            cout<<endl;
        }

        cout << endl;

        //Displays cells that die over overpopulation or underpopulation, new cells and non - changing cells
        cout << "Cells that died of underpopulation: ";

        for(int elem : underVec)
            cout << elem << " ";
        cout << endl;

        cout << "Cells that died of overpopulation: ";

        for(int elem : overVec)
            cout << elem << " ";
        cout << endl;

        cout << "Cells that came to life: ";

        for(int elem : newVec)
            cout << elem << " ";
        cout << endl;

        cout << "Cells that stayed alive: ";

        for(int elem : stayVec)
            cout << elem << " ";
        cout << endl;
        cout << endl;

    }

    return 0;
}
