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
	Help();
	ListFiles();

	while (true) {
		if (sudoku != nullptr)
			sudoku->Print();
		std::vector<std::string> input = GetInput();
		
		if (input.size() == 0) {
			std::cout << "Invalid Input! Type \"help\" for help." << std::endl;
		}
		else if (input.at(0) == "files") {
			ListFiles();
		}
		else if (input.at(0) == "load" && input.size() == 2) {
			sudoku = new Sudoku("./sudokus/" + input.at(1));
		}
		else if (input.at(0) == "help") {
			Help();
		}
		else if (input.at(0) == "exit") {
			return 0;
		}
		else if (sudoku != nullptr) {
			if (isValidCellInput(input.at(0))) {
				sudoku->SetCell(input.at(0)[0] - '1', input.at(0)[1] - '1', input.at(0)[2] - '0');
			}
			else if (input.at(0) == "undo") {
				sudoku->Undo();
			}
			else if (input.at(0) == "validate") {
				sudoku->Validate();
			}
			else if (input.at(0) == "solution") {
				sudoku->Solution();
			}
			else {
				std::cout << "Invalid Input! Type \"help\" for help." << std::endl;
			}
		}
		else {
			std::cout << "Invalid Input! Type \"help\" for help." << std::endl;
		}
	}
}


std::vector<std::string> UserInterface::GetInput()
{
	std::string input;
	std::getline(std::cin, input);
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
	std::cout << std::endl;
	std::cout << "\033[33m" << "AVAILABLE COMMANDS:" << "\033[0m" << std::endl;
	std::cout << "files" << std::endl;
	std::cout << "\tlist all available sudoku files" << std::endl;
	std::cout << "load <filename>" << std::endl;
	std::cout << "\tload the sudoku puzzle" << std::endl;
	std::cout << "<row><column><value>" << std::endl;
	std::cout << "\texample: to write a 7 in the middle of the field, type \"557\"" << std::endl;
	std::cout << "undo" << std::endl;
	std::cout << "\tundo the last move" << std::endl;
	std::cout << "validate" << std::endl;
	std::cout << "\tvalidate your solution" << std::endl;
	std::cout << "solution" << std::endl;
	std::cout << "\tautomatically solve the sudoku" << std::endl;
	std::cout << "help" << std::endl;
	std::cout << "\tdisplay this help message" << std::endl;
	std::cout << "exit" << std::endl;
	std::cout << "\texit the application" << std::endl << std::endl;
}

void UserInterface::ListFiles()
{
	std::cout << "Available files:" << std::endl;
	for (const auto& entry : std::filesystem::directory_iterator("./sudokus")) {
		if (entry.is_regular_file()) {
			std::cout << entry.path().filename().string() << std::endl;
		}
	}
	std::cout << std::endl;
}
