#ifndef CL_SAFE_H
#define CL_SAFE_H

#include "cl_base.h"

// Номера класса - 3
class cl_safe : public cl_base {

private:
	int rows_count;
	int columns_count;
	int safe_boxes_count;
	cl_base* ** safe_boxes;
	//vector<vector<cl_base*>> safe_boxes;

public:
	cl_safe(cl_base* parent, int rows_count, int columns_count, string name = "Default");
	void fill_safe();
	void signal_method(string& text);
	void handler_method(string text);
	cl_base* find_safe_box(int number);
};

#endif