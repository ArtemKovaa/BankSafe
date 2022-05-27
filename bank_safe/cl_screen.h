#ifndef CL_SCREEN_H
#define CL_SCREEN_H

#include "cl_base.h"

// Номера класса - 6
class cl_screen : public cl_base {

public:
	cl_screen(cl_base* parent, string name = "Default");
	void handle_signal_from_system(string text);
	void handle_signal_from_remote_control(string text);
};

#endif