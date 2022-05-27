#ifndef CL_SERVER_H
#define CL_SERVER_H

#include "cl_base.h"

// Номера класса - 5
class cl_server : public cl_base {

private:
	struct safe_box_struct {
		int number;
		int client_key;
		int bank_key;
	};
	vector<safe_box_struct*> safe_boxes_information; // База данных хранения информации о ячейках

public:
	cl_server(cl_base* parent, string name = "Default");
	void emit_signal_to_remote_control(string& text);
	void handle_signal_from_reader(string input);
	void handle_signal_from_remote_control(string input);
	void show_inf();
};

#endif