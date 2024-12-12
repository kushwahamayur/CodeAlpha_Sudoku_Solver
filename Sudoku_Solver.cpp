#include <iostream>
#include <vector>

using namespace std;

// Function to print the Sudoku grid
void printBoard(const vector<vector<int>> &board)
{
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to check if placing a number is valid in the current row, column, and 3x3 subgrid
bool isValid(const vector<vector<int>> &board, int row, int col, int num)
{
    // Check if num is not repeated in the current row and column
    for (int i = 0; i < 9; ++i)
    {
        if (board[row][i] == num || board[i][col] == num)
        {
            return false;
        }
    }

    // Check if num is not repeated in the current 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board[startRow + i][startCol + j] == num)
            {
                return false;
            }
        }
    }

    return true;
}

// Backtracking function to solve the Sudoku puzzle
bool solveSudoku(vector<vector<int>> &board)
{
    for (int row = 0; row < 9; ++row)
    {
        for (int col = 0; col < 9; ++col)
        {
            // If the cell is empty (represented by 0)
            if (board[row][col] == 0)
            {
                // Try all numbers from 1 to 9
                for (int num = 1; num <= 9; ++num)
                {
                    if (isValid(board, row, col, num))
                    {
                        board[row][col] = num; // Place the number

                        // Recursively try to solve the rest of the board
                        if (solveSudoku(board))
                        {
                            return true;
                        }

                        // If placing num doesn't lead to a solution, reset the cell
                        board[row][col] = 0;
                    }
                }
                return false; // No valid number can be placed, backtrack
            }
        }
    }

    return true; // The board is completely filled and valid
}

int main()
{
    vector<vector<int>> board = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}};

    if (solveSudoku(board))
    {
        cout << "Solved Sudoku: \n";
        printBoard(board);
    }
    else
    {
        cout << "No solution exists." << endl;
    }

    return 0;
}
