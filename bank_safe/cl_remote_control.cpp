#include "cl_remote_control.h"

// Пульт управления

cl_remote_control::cl_remote_control(cl_base* parent, string name) :cl_base(parent, name) {
	this->class_number = 2;
}

// Метод сигнала
void cl_remote_control::signal_method(string& text) {
	cout << "\nSignal from " << get_absolute_path();
	text += " (class: 2)";
}

// Метод обработчика
void cl_remote_control::handler_method(string text) {
	string command;
	int number;
	if (text.find(' ') > 0 && text.find(' ') < text.length()) {
		command = text.substr(text.find(' '));
		number = stoi(text.substr(text.find(' ') + 1, text.length()));
	}
	else command = text;

	if (command == "BOX") {

	}
	if (command == "CLIENT_KEY") {

	}
	if (command == "BANK_KEY") {

	}
	if (command == "CLOSE_BOX") {

	}
	if (command == "CANCEL") {

	}
	if (command == "Turn off the safe ") {

	}
	if (command == "SHOWTREE") {

	}


	cout << "\nSignal to " << get_absolute_path() << " Text: " << text;
}