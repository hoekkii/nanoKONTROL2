#pragma once
#include <vector>

typedef void(*input_callback) (void* data, void* in, const bool& new_state, const double& deltatime);
typedef unsigned char uchar;
typedef std::string string;

class input
{
	friend class board_controller;

protected:
	explicit input(const uchar& id, const string& name);
	virtual ~input();
	virtual void change(const bool& new_state, const double& deltatime) = 0;

public:
	uchar id() const;
	string name() const;
	uchar value() const;
	void value(const uchar& value);
	bool is_min() const;
	bool is_max() const;
	input_callback callback = nullptr;

private:
	const uchar _id;
	const string _name;
	uchar _value;
};
