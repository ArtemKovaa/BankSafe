#ifndef CL_SAFE_BOX_H
#define CL_SAFE_BOX_H

#include "cl_base.h"

// Номера класса - 4
class cl_safe_box : public cl_base {

private:
	int number;
	bool is_open = false;


public:
	cl_safe_box(cl_base* parent, int number, string name = "Default");
	void signal_method(string& text);
	void handler_method(string text);
};

#endif