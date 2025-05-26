#include "Undo.h"

void Undo::PushAndDo(GridCell& gridcell, int value)
{
	undoStack.push(UndoAction(gridcell, gridcell.value));
	gridcell.value = value;
}

void Undo::PopAndUndo()
{
	if (undoStack.empty()) return;
	UndoAction undoAction = undoStack.top();
	undoAction.gridCell.value = undoAction.value;
	undoStack.pop();
}
