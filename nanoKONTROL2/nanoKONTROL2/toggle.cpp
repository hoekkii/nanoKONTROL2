#include "toggle.h"
#include <iostream>

toggle::toggle(const uchar& id, const string& name) : input(id, name)
{
	_toggle_value = false;
}

bool toggle::toggle_value() const
{
	return _toggle_value;
}

void toggle::change(const bool& new_state, const double& deltatime)
{
	if (!value())
		return;

	_toggle_value = !_toggle_value;
}
