#ifndef CL_REMOTE_CONTROL_H
#define CL_REMOTE_CONTROL_H

#include "cl_base.h"

// Номера класса - 2
class cl_remote_control : public cl_base {

private:
	int current_safe_box_number;
	int stage = 0;
	string correctness;

public:
	cl_remote_control(cl_base* parent, string name = "Default");
	void emit_signal_to_reader(string& text);
	void handle_signal_from_reader(string text);
	void emit_signal_to_safe(string& text);
	void handle_signal_from_safe(string text);
	void emit_signal_to_server(string& text);
	void handle_signal_from_server(string text);
	void handle_signal_from_system(string text);
	void emit_signal_to_system(string& text);
	void emit_signal_to_screen(string& text);
};

#endif