#include "cl_server.h"

// Сервер и программное обеспечение

cl_server::cl_server(cl_base* parent, string name) :cl_base(parent, name) {
	this->class_number = 5;
}

void cl_server::emit_signal_to_remote_control(string& text) {

}

void cl_server::handle_signal_from_remote_control(string text) {
	int choice = stoi(text.substr(0, text.find(' ')));
	text = text.substr(text.find(' ') + 1, text.length());
	int number = stoi(text.substr(0, text.find(' ')));
	text = text.substr(text.find(' ') + 1, text.length());
	switch (choice) {
	case 1:
		for (int i = 0; i < safe_boxes_information.size(); i++) {
			if (safe_boxes_information[i]->number == number && safe_boxes_information[i]->client_key == stoi(text)) {
				text = "1";
				emit_signal(SIGNAL_D(cl_server::emit_signal_to_remote_control), text); 
				return;
			}
		}
		text = "0";
		emit_signal(SIGNAL_D(cl_server::emit_signal_to_remote_control), text);
		break;
	case 2:

		break;
	}
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