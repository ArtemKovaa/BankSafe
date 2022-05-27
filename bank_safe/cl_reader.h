#ifndef CL_READER_H
#define CL_READER_H

#include "cl_base.h"

// Номер класса - 7
class cl_reader : public cl_base {

public:
	cl_reader(cl_base* parent, string name = "Default");
	void handle_signal(string input);
	void emit_signal_to_system(string& input);
	void emit_signal_to_server(string& input);
	void emit_signal_to_remote_control(string& input);
};


#endif
