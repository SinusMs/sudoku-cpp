#include "Sudoku.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Sudoku::Sudoku(std::string file)
{
    std::ifstream inFile(file);
    std::string data;

    if (inFile.is_open()) {
        std::ostringstream ss;
        ss << inFile.rdbuf();  // Read entire file into stringstream
        data = ss.str();
        inFile.close();

        std::cout << "Data loaded:\n" << data << "\n";
    }
    else {
        std::cerr << "Failed to open file for reading.\n";
    }

    int charIndex = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int cellData = data[charIndex] - '0';
            sudoku[i][j] = new GridCell(cellData, cellData == 0);
            charIndex++;
        }
    }
}

Sudoku::~Sudoku()
{
    // free any memory that might have been manually allocated on the heap
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j] != nullptr)
                delete sudoku[i][j];
        }
    }
}

void Sudoku::Print()
{
    std::cout << "+ - - - + - - - + - - - +" << std::endl;
    for (int j = 0; j < 9; j++) {
        std::cout << "| ";
        for (int i = 0; i < 9; i++) {
            int val = sudoku[i][j]->value;
            if (sudoku[i][j]->editable)
                std::cout << (val == 0 ? "." : std::to_string(val)) << " ";
            else
                std::cout << "\033[36m" << (val == 0 ? "." : std::to_string(val)) << "\033[0m" << " ";

            if ((i + 1) % 3 == 0)
                std::cout << "| ";
        }
        std::cout << j + 1 << std::endl;
        if ((j + 1) % 3 == 0)
            std::cout << "+ - - - + - - - + - - - +" << std::endl;
    }
    std::cout << " ";
    for (int i = 1; i <= 9; i++) {
        std::cout << " " << i;
        if (i % 3 == 0)
            std::cout << "  ";
    }
    std::cout << std::endl;
}

bool Sudoku::SetCell(int i, int j, int value)
{
    if (!sudoku[i][j]->editable)
        return false;

    undo.PushAndDo(*sudoku[i][j], value);
}

void Sudoku::Undo()
{
    undo.PopAndUndo();
}

void Sudoku::Validate()
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (!ValidateCell(i, j)) {
                std::cout << "\033[31m" << "Sudoku invalid! Invalid cell found at i=" << i + 1 << " j=" << j + 1 << " with value " << sudoku[i][j]->value << "\033[0m" << std::endl;
                return;
            }
        }
    }
    std::cout << "\033[32m" << "Congrats, the Sudoku is valid!" << "\033[0m" << std::endl;
}

bool Sudoku::ValidateCell(int i, int j)
{
    int n = sudoku[i][j]->value;

    if (n == 0)
        return false;

    for (int idx = 0; idx < 9; idx++) {
        if (idx != j && sudoku[i][idx]->value == n)
            return false;
        if (idx != i && sudoku[idx][j]->value == n)
            return false;
    }

    int iOffset = (i / 3) * 3;
    int jOffset = (j / 3) * 3;
    for (int col = 0; col < 3; col++) {
        for (int row = 0; row < 3; row++) {
            if (iOffset + col == i && jOffset + row == j)
                continue;
            if (sudoku[iOffset + col][jOffset + row]->value == n)
                return false;
        }
    }
    
    return true;
}

void Sudoku::Solution()
{
    if (SolutionRec()) {
        std::cout << "\033[32m" << "Solved the Sudoku!" << "\033[0m" << std::endl;
    }
    else {
        std::cout << "\033[31m" << "No Solution Found! Note that values entered by the user are not overwritten by the algorithm and therefore might make the sudoku unsolvable." << "\033[0m" << std::endl;
    }
}

bool Sudoku::SolutionRec()
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j]->value == 0) {
                for (int n = 1; n <= 9; n++) 
                {
                    sudoku[i][j]->value = n;
                    if (ValidateCell(i, j)) {
                        if (SolutionRec())
                            return true;
                    }
                    sudoku[i][j]->value = 0;
                }
                return false;
            }
        }
    }
    return true;
}
