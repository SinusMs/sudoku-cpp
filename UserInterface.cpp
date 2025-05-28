#include "UserInterface.h"
#include <string>
#include <iostream>
#include <sstream>
#include <filesystem>

UserInterface::~UserInterface()
{
	// free any memory that might have been manually allocated on the heap
	if (sudoku != nullptr)
		delete sudoku;
}

int UserInterface::Loop()
{
	PrintTitle();
	//std::cout << std::endl;
	//Help();
	//std::cout << std::endl;
	//ListFiles();

	while (true) {
		std::vector<std::string> input = GetInput();
		
		if (input.size() == 0) {
			PrintInvalidInput();
		}
		else if (input.at(0) == "files") {
			ListFiles();
		}
		else if (input.at(0) == "load" && input.size() == 2) {
			try {
				if (sudoku != nullptr)
					delete sudoku;
				sudoku = new Sudoku("./sudokus/" + input.at(1));
				TryPrintSudoku();
			}
			catch (const std::exception& e) {
				PrintException(e);
			}
		}
		else if (input.at(0) == "help") {
			Help();
		}
		else if (input.at(0) == "exit") {
			return 0;
		}
		else if (isValidCellInput(input.at(0))) {
			if (SudokuPresent()) {
				try {
					sudoku->SetCell(input.at(0)[0] - '1', input.at(0)[1] - '1', input.at(0)[2] - '0');
					TryPrintSudoku();
				}
				catch (const std::exception& e) {
					PrintException(e);
				}
			}
		}
		else if (input.at(0) == "undo") {
			if (SudokuPresent()) {
				try {
					sudoku->Undo();
					TryPrintSudoku();
				}
				catch (const std::exception& e) {
					PrintException(e);
				}
			}
		}
		else if (input.at(0) == "validate") {
			if (SudokuPresent()) {
				sudoku->Validate();
			}
		}
		else if (input.at(0) == "solution") {
			if (SudokuPresent()) {
				sudoku->Solution();
				TryPrintSudoku();
			}
		}
		else if (input.at(0) == "print") {
			if (SudokuPresent())
			TryPrintSudoku();
		}
		else {
			PrintInvalidInput();
		}
	}
}

void UserInterface::PrintException(const std::exception& e)
{
	std::cout << "\033[31m" << "Exception: " << e.what() << "\033[0m" << std::endl;
}

void UserInterface::TryPrintSudoku()
{
	if (sudoku != nullptr)
		sudoku->Print();
}

void UserInterface::PrintInvalidInput()
{
	std::cout << "\033[31m" << "Invalid Input! Type \"help\" for help." << "\033[0m" << std::endl;
}


std::vector<std::string> UserInterface::GetInput()
{
	std::cout << "\033[33m" << std::endl << ">>> ";
	std::string input;
	std::getline(std::cin, input);
	std::cout << "\033[0m";
	std::istringstream iss(input);
	std::vector<std::string> split_input;
	std::string word;
	while (iss >> word) {
		split_input.push_back(word);
	}

	return split_input;
}

bool UserInterface::isValidCellInput(const std::string& s) {
	return s.size() == 3 &&
		s[0] >= '1' && s[0] <= '9' &&
		s[1] >= '1' && s[1] <= '9' &&
		s[2] >= '0' && s[2] <= '9';
}

void UserInterface::Help()
{
	std::cout << "\033[36m" << "AVAILABLE COMMANDS" << "\033[0m" << std::endl;
	std::cout << "files" << std::endl;
	std::cout << "\tlist all available sudoku files" << std::endl;
	std::cout << "load <filename>" << std::endl;
	std::cout << "\tload the sudoku puzzle" << std::endl;
	std::cout << "<row><column><value>" << std::endl;
	std::cout << "\texample: to write a 7 in the middle of the field, type \"557\" " << std::endl;
	std::cout << "\tuse value 0 to clear a field (e.g. 550)" << std::endl;
	std::cout << "undo" << std::endl;
	std::cout << "\tundo the last move" << std::endl;
	std::cout << "validate" << std::endl;
	std::cout << "\tvalidate your solution" << std::endl;
	std::cout << "solution" << std::endl;
	std::cout << "\tautomatically solve the sudoku" << std::endl;
	std::cout << "print" << std::endl;
	std::cout << "\tprint the sudoku currently loaded in memory" << std::endl;
	std::cout << "help" << std::endl;
	std::cout << "\tdisplay this help message" << std::endl;
	std::cout << "exit" << std::endl;
	std::cout << "\texit the application" << std::endl;
}

void UserInterface::ListFiles()
{
	try {
		std::cout << "\033[36m" << "AVAILABLE FILES" << "\033[0m" << std::endl;
		for (const auto& entry : std::filesystem::directory_iterator("./sudokus")) {
			if (entry.is_regular_file()) {
				std::cout << entry.path().filename().string() << std::endl;
			}
		}
	}
	catch (const std::exception& e) {
		PrintException(e);
	}
}

void UserInterface::PrintTitle() {
		std::cout << "\033[36m" << R"(
   d888888o.    8 8888      88  8 888888888o.           ,o888888o.      8 8888     ,88'  8 8888      88 
 .`8888:' `88.  8 8888      88  8 8888    `^888.     . 8888     `88.    8 8888    ,88'   8 8888      88 
 8.`8888.   Y8  8 8888      88  8 8888        `88.  ,8 8888       `8b   8 8888   ,88'    8 8888      88 
 `8.`8888.      8 8888      88  8 8888         `88  88 8888        `8b  8 8888  ,88'     8 8888      88 
  `8.`8888.     8 8888      88  8 8888          88  88 8888         88  8 8888 ,88'      8 8888      88 
   `8.`8888.    8 8888      88  8 8888          88  88 8888         88  8 8888 88'       8 8888      88 
    `8.`8888.   8 8888      88  8 8888         ,88  88 8888        ,8P  8 888888<        8 8888      88 
8b   `8.`8888.  ` 8888     ,8P  8 8888        ,88'  `8 8888       ,8P   8 8888 `Y8.      ` 8888     ,8P 
`8b.  ;8.`8888    8888   ,d8P   8 8888    ,o88P'     ` 8888     ,88'    8 8888   `Y8.      8888   ,d8P  
 `Y8888P ,88P'     `Y88888P'    8 888888888P'           `8888888P'      8 8888     `Y8.     `Y88888P'   

)" 
<< "\033[33m" << "Type \"help\" for help!" << "\033[0m" << std::endl;
}

bool UserInterface::SudokuPresent()
{
	if (sudoku == nullptr) {
		std::cout << "\033[31m" << "No sudoku in memory! Load a sudoku using \"load <filename>\" or view help using \"help\"" << "\033[0m" << std::endl;
		return false;
	}
	return true;
}
