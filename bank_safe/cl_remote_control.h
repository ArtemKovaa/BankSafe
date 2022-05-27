#ifndef CL_REMOTE_CONTROL_H
#define CL_REMOTE_CONTROL_H

#include "cl_base.h"

// Номера класса - 2
class cl_remote_control : public cl_base {

public:
	cl_remote_control(cl_base* parent, string name = "Default");
	void signal_method(string& text);
	void handler_method(string text);
};

#endif