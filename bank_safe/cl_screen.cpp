#include "cl_screen.h"

// Ёкран пульта управлени€

cl_screen::cl_screen(cl_base* parent, string name) :cl_base(parent, name) {
	this->class_number = 6;
}

void cl_screen::handle_signal_from_system(string text) {
	cout << text;
}

void cl_screen::handle_signal_from_remote_control(string text) {
	if (text.length() > 1) {
		cout << '\n' << text;
	}
	else {
		if (text == "0") {
			cout << "\nEnter the code";
		}
		else {
			cout << "\nReady to work";
		}
	}
	
}