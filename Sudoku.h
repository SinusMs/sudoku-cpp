#pragma once
#include <string>
#include "GridCell.h"
#include "Undo.h"

class Sudoku
{
public:
	// Use array of pointers to avoid automatic construction of all GridCell objects and construct them manually in Sudoku constructor
	GridCell* sudoku[9][9];
	Undo undo;
	Sudoku(std::string file);
	~Sudoku();
	void Print();
	bool SetCell(int i, int j, int value);
	void Undo();
	void Validate();
	bool ValidateCell(int i, int j);
	void Solution();
	bool SolutionRec();
};

