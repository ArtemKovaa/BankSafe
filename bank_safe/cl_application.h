#ifndef CL_APPLICATION_H
#define CL_APPLICATION_H

#include "cl_base.h"
#include "cl_remote_control.h"
#include "cl_safe.h"
#include "cl_safe_box.h"
#include "cl_server.h"
#include "cl_screen.h"
#include "cl_reader.h"

// ?????? ?????? - 1
class cl_application : public cl_base {

private:
	bool system_indicator = true;
	string command;

public:
	cl_application(cl_base* parent);
	void build_tree_objects();
	int exec_app();
	//cl_base::TYPE_SIGNAL get_signal_method(cl_base* pointer);
	//cl_base::TYPE_HANDLER get_handler_method(cl_base* pointer);
	void emit_build_signal_to_reader(string& text);
	void emit_command_signal_to_reader(string& text);
	void handler_method(string input);
	void handle_signal_from_remote_control(string text);
	void emit_signal_to_screen(string& text);
};

#endif
