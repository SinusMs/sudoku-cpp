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
	std::vector<std::string> GetInput();
	bool isValidCellInput(const std::string& s);
	void Help();
	void ListFiles();
};

