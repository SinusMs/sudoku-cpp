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
    std::cout << "+ - - - + - - - + - - - + i" << std::endl;
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
    std::cout << "j";
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

}

void Sudoku::Solution()
{

}
