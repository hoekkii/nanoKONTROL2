#pragma once
#include "input.h"

class toggle : public input
{
public:
	toggle(const uchar& id, const string& name);
	bool toggle_value() const;


protected:
	void change(const bool& new_state, const double& deltatime) override;

private:
	bool _toggle_value;
};
