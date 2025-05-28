#pragma once
#include "Sudoku.h"
#include <vector>
class UserInterface
{
public:
	// use pointer so the variable is nullable and not autmativally constructed
	Sudoku* sudoku;
	~UserInterface();
	int Loop();
private:
	void PrintException(const std::exception& e);
	void TryPrintSudoku();
	void PrintInvalidInput();
	void PrintTitle();
	bool SudokuPresent();
	std::vector<std::string> GetInput();
	bool isValidCellInput(const std::string& s);
	void Help();
	void ListFiles();
};

