#ifndef CL_SAFE_H
#define CL_SAFE_H

#include "cl_base.h"
#include "cl_safe_box.h"

// Номера класса - 3
class cl_safe : public cl_base {

private:
	int rows_count;
	int columns_count;
	int safe_boxes_count;
	cl_safe_box* ** safe_boxes;

public:
	cl_safe(cl_base* parent, int rows_count, int columns_count, string name = "Default");
	void fill_safe();
	cl_base* find_safe_box(int number);
	void emit_signal_to_remote_control(string& text);
	void handle_signal_from_remote_control(string text);
};

#endif