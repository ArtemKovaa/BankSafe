#include "cl_reader.h"
#include "cl_application.h"

// Чтение данных и команд

cl_reader::cl_reader(cl_base* parent, string name) :cl_base(parent, name) {
	this->class_number = 7;
}

// Метод обработчика
void cl_reader::handle_signal(string input) {
	if (input == "system") {
		getline(cin, input);
		emit_signal(SIGNAL_D(cl_reader::emit_signal_to_system), input);
		while (getline(cin, input)) {
			if (input == "Completing key entry") break;
			emit_signal(SIGNAL_D(cl_reader::emit_signal_to_server), input);
		}
	}
	else {
		getline(cin, input);
		emit_signal(SIGNAL_D(cl_reader::emit_signal_to_remote_control), input);
	}
	
}

void cl_reader::emit_signal_to_system(string& input) {

}
void cl_reader::emit_signal_to_server(string& input) {

}
void cl_reader::emit_signal_to_remote_control(string& input) {

}