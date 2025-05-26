#pragma once
class GridCell
{
public:
	int value;
	bool editable;

	GridCell(int value, bool editable) : value(value), editable(editable){ }
};

