#include "cl_server.h"

// Сервер и программное обеспечение

cl_server::cl_server(cl_base* parent, string name) :cl_base(parent, name) {
	this->class_number = 5;
}

void cl_server::emit_signal_to_remote_control(string& text) {

}

void cl_server::handle_signal_from_remote_control(string input) {

}

void cl_server::handle_signal_from_reader(string input) {
	int first_value, second_value, third_value;

	first_value = stoi(input.substr(0, input.find(' ')));
	input = input.substr(input.find(' ') + 1, input.length());
	second_value = stoi(input.substr(0, input.find(' ')));
	input = input.substr(input.find(' ') + 1, input.length());
	third_value = stoi(input);
	
	safe_box_struct* safe_box_information = new safe_box_struct();
	safe_box_information->number = first_value;
	safe_box_information->client_key = second_value;
	safe_box_information->bank_key = third_value;
	safe_boxes_information.push_back(safe_box_information);
}