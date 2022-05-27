#include "cl_remote_control.h"

// Пульт управления

cl_remote_control::cl_remote_control(cl_base* parent, string name) :cl_base(parent, name) {
	this->class_number = 2;
}

void cl_remote_control::emit_signal_to_reader(string& text) {}

void cl_remote_control::handle_signal_from_reader(string text) {
	int number;
	string command = (text.substr(0, text.find(' ')));
	text = text.substr(text.find(' ') + 1, text.length());

	if (command == "BOX") {
		command = "1 ";
		command += text;
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_safe), command);
	}
	else if (command == "CLIENT_KEY") {
		number = stoi(text.substr(0, text.find(' ')));

	}
	else if (command == "BANK_KEY") {
		number = stoi(text.substr(0, text.find(' ')));

	}
	else if (command == "CLOSE_BOX") {
		number = stoi(text.substr(0, text.find(' ')));

	}
	else if (command == "CANCEL") {

	}
	else if (command == "Turn off the safe ") {

	}
	else if (command == "SHOWTREE") {

	}
}

void cl_remote_control::emit_signal_to_safe(string& text) {

}

void cl_remote_control::handle_signal_from_safe(string text, int number) {

}

void cl_remote_control::emit_signal_to_server(string& text) {

}

void cl_remote_control::handle_signal_from_server(string text) {

}

void cl_remote_control::emit_signal_to_system() {

}