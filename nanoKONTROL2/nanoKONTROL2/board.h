#pragma once
#include "input.h"

class board
{
	friend class board_controller;

protected:
	explicit board(const string& port_name);
	virtual ~board();

public:
	const string port_name;

	virtual input* operator[](const uchar index) = 0;
};
