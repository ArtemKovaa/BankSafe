#include "cl_screen.h"

// Ёкран пульта управлени€

cl_screen::cl_screen(cl_base* parent, string name) :cl_base(parent, name) {
	this->class_number = 6;
}

void cl_screen::handle_signal_from_system(string text) {
	cout << text;
}

void cl_screen::handle_signal_from_remote_control(string text) {
	if (text == "needs_client_key") {
		cout << "\nEnter the code";
	}
	else if (text == "needs_bank_key") {
		cout << "\nEnter the bank code";
	}
	else if (text == "is_open") {
		cout << "\nThe safe deposit box is open";
		cout << "\nReady to work";
	}
	else if (text.substr(0, text.find(' ')) == "now_open") {
		text = text.substr(text.find(' ') + 1, text.length());
		cout << "\nThe safe deposit box " << text << " is open";
		cout << "\nReady to work";
	}
	else if (text == "error") {
		cout << "\nError in the command sequence\nReady to work";
	}
	else if (text == "cancel" || text == "next") {
		cout << "\nReady to work";
	}
	else if (text == "client_incorrect") {
		cout << "\nThe client is key is incorrect\nReady to work";
	}
	else if (text == "bank_incorrect") {
		cout << "\nThe bank is key is incorrect\nReady to work";
	}
}