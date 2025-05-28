#include "Undo.h"
#include <iostream>

void Undo::PushAndDo(GridCell& gridcell, int value)
{
	undoStack.push(UndoAction(gridcell, gridcell.value));
	gridcell.value = value;
}

void Undo::PopAndUndo()
{
	if (undoStack.empty())
		throw std::runtime_error("No undo actions in memory!");
	UndoAction undoAction = undoStack.top();
	undoAction.gridCell.value = undoAction.value;
	undoStack.pop();
}
