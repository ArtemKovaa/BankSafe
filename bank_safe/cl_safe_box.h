#ifndef CL_SAFE_BOX_H
#define CL_SAFE_BOX_H

#include "cl_base.h"

// Номера класса - 4
class cl_safe_box : public cl_base {

private:
	int number;

public:
	cl_safe_box(cl_base* parent, int number, string name = "Default");
	int get_number();
	void signal_method(string& text);
	void handler_method(string text);
};

#endif