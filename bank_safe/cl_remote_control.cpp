#include "cl_remote_control.h"

// Пульт управления

cl_remote_control::cl_remote_control(cl_base* parent, string name) :cl_base(parent, name) {
	this->class_number = 2;
	this->current_safe_box_number = 0;
}

void cl_remote_control::emit_signal_to_reader(string& text) {}

void cl_remote_control::handle_signal_from_reader(string text) {
	int number;
	string command = (text.substr(0, text.find(' '))); // Команда для выполнения
	text = text.substr(text.find(' ') + 1, text.length());

	if (command == "BOX") {
		command = "1 "; // Возможно можно убрать, добавлено для множественного выбора в сейфе
		command += text;
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_safe), command);
	}
	else if (command == "CLIENT_KEY") {
		command = "1 ";
		command += to_string(current_safe_box_number);
		command += " ";
		command += text;
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_server), command);
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

void cl_remote_control::handle_signal_from_safe(string text) {
	if (text.length() > 0) {
		current_safe_box_number = stoi(text.substr(0, text.find(' ')));
		text = text.substr(text.find(' ') + 1, text.length());
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_screen), text);
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_reader), text);
	}
	else {
		text = "1";
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_screen), text);
	}
}

void cl_remote_control::emit_signal_to_server(string& text) {

}

void cl_remote_control::handle_signal_from_server(string text) {
	if (text == "1") {
		text = "Enter the bank code";
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_screen), text);
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_reader), text);
	}
	else {
		text = "The client is key is incorrect";
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_screen), text);
	}
}

void cl_remote_control::emit_signal_to_system() {

}

void cl_remote_control::emit_signal_to_screen() {

}