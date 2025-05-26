#pragma once
#include <string>
#include "GridCell.h"
#include "Undo.h"

class Sudoku
{
private:
	// Use array of pointers to avoid automatic construction of all GridCell objects and construct them manually in Sudoku constructor
	GridCell* sudoku[9][9];
	Undo undo;
	bool ValidateCell(int i, int j);
	bool SolutionRec();
public:
	Sudoku(std::string file);
	~Sudoku();
	void Print();
	void SetCell(int i, int j, int value);
	void Undo();
	void Validate();
	void Solution();
};

