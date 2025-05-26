#pragma once
#include <stack>
#include "GridCell.h"

class UndoAction 
{
public:
	int value;
	GridCell& gridCell;
	UndoAction(GridCell& gridCell, int value) : gridCell(gridCell), value(value) {}
};

class Undo
{
public:
	void PushAndDo(GridCell& gridcell, int value);
	void PopAndUndo();
private:
	std::stack<UndoAction> undoStack;
};