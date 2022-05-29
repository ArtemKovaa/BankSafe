#include "cl_application.h"

cl_application::cl_application(cl_base* parent) :cl_base(parent) {
	this->class_number = 1;
}

void cl_application::build_tree_objects() {
	// Построение дерева системы
	set_name("system");
	cl_base* signal_object, * handler_object; // Объект, выдающий сигнал, и целевой объект

	cl_base* current_object = this;
	current_object->set_readiness(1);
	new cl_remote_control(current_object, "remote_control");
	new cl_server(current_object, "server");

	current_object = find_object_by_name("remote_control");
	current_object->set_readiness(1);
	new cl_reader(current_object, "reader");
	new cl_screen(current_object, "screen");

	// Связываем систему с ридером
	signal_object = this;
	handler_object = find_object_by_name("reader");
	handler_object->set_readiness(1);
	signal_object->set_connection(SIGNAL_D(cl_application::emit_build_signal_to_reader), handler_object, HANDLER_D(cl_reader::handle_signal));
	signal_object->set_connection(SIGNAL_D(cl_application::emit_command_signal_to_reader), handler_object, HANDLER_D(cl_reader::handle_signal));

	// Связываем ридер с сервером и системой
	signal_object = find_object_by_name("reader");
	handler_object = this;
	signal_object->set_connection(SIGNAL_D(cl_reader::emit_signal_to_system), handler_object, HANDLER_D(cl_application::handler_method));
	handler_object = find_object_by_name("server");
	handler_object->set_readiness(1);
	signal_object->set_connection(SIGNAL_D(cl_reader::emit_signal_to_server), handler_object, HANDLER_D(cl_server::handle_signal_from_reader));

	signal_object = this;
	string text;
	signal_object->emit_signal(SIGNAL_D(cl_application::emit_build_signal_to_reader), text);

	cl_safe* ptr = (cl_safe*)find_object_by_name("safe");
	ptr->fill_safe();

	// Установка всех связей системы
	signal_object = find_object_by_name("remote_control");
	handler_object = find_object_by_name("reader");
	signal_object->set_connection(SIGNAL_D(cl_remote_control::emit_signal_to_reader), handler_object, HANDLER_D(cl_reader::handle_signal));

	handler_object = find_object_by_name("safe");
	signal_object->set_connection(SIGNAL_D(cl_remote_control::emit_signal_to_safe), handler_object, HANDLER_D(cl_safe::handle_signal_from_remote_control));

	handler_object = find_object_by_name("system");
	signal_object->set_connection(SIGNAL_D(cl_remote_control::emit_signal_to_system), handler_object, HANDLER_D(cl_application::handle_signal_from_remote_control));

	handler_object = find_object_by_name("server");
	signal_object->set_connection(SIGNAL_D(cl_remote_control::emit_signal_to_server), handler_object, HANDLER_D(cl_server::handle_signal_from_remote_control));

	signal_object = find_object_by_name("safe");
	handler_object = find_object_by_name("remote_control");
	signal_object->set_connection(SIGNAL_D(cl_safe::emit_signal_to_remote_control), handler_object, HANDLER_D(cl_remote_control::handle_signal_from_safe));

	signal_object = find_object_by_name("server");
	signal_object->set_connection(SIGNAL_D(cl_server::emit_signal_to_remote_control), handler_object, HANDLER_D(cl_remote_control::handle_signal_from_server));

	signal_object = find_object_by_name("system");
	handler_object = find_object_by_name("screen");
	handler_object->set_readiness(1);
	signal_object->set_connection(SIGNAL_D(cl_application::emit_signal_to_screen), handler_object, HANDLER_D(cl_screen::handle_signal_from_system));

	signal_object = find_object_by_name("remote_control");
	signal_object->set_connection(SIGNAL_D(cl_remote_control::emit_signal_to_screen), handler_object, HANDLER_D(cl_screen::handle_signal_from_remote_control));

	signal_object = find_object_by_name("reader");
	handler_object = find_object_by_name("remote_control");
	signal_object->set_connection(SIGNAL_D(cl_reader::emit_signal_to_remote_control), handler_object, HANDLER_D(cl_remote_control::handle_signal_from_reader));

	emit_signal(SIGNAL_D(cl_application::emit_signal_to_screen), text); // Вывод первого сообщения в консоль (ГОТОВ К РАБОТЕ)
}

// Метод запуска приложения
int cl_application::exec_app() {
	set_readiness_for_all(1); // Установка готовности всем, учитывая разные готовности
	cl_base* signal_object = find_object_by_name("remote_control");
	cl_base* handler_object = find_object_by_name("reader");
	string text;
	// Такты
	while (system_indicator) {
		emit_signal(SIGNAL_D(cl_application::emit_command_signal_to_reader), command);
	}
	return 0;
}

// Метод сигнала
void cl_application::emit_build_signal_to_reader(string& text) {
	text = get_name();
}

void cl_application::emit_command_signal_to_reader(string& text) {
	text = "";
}

// Метод обработчика
void cl_application::handler_method(string input) {
	if (input.substr(0, input.find(' ')) == "command") {
		input = input.substr(input.find(' ') + 1, input.length());
		command = input;
		return;
	}
	int first_value, second_value;

	first_value = stoi(input.substr(0, input.find(' ')));
	input = input.substr(input.find(' ') + 1, input.length());
	second_value = stoi(input);
	new cl_safe(this, first_value, second_value, "safe");
	cl_base* current_object = find_object_by_name("safe");
	string safe_box_name;
	for (int i = 0; i < (first_value * second_value); i++) {
		int test = i + 1;
		safe_box_name = "safe_box_";
		safe_box_name += to_string(test);
		new cl_safe_box(current_object, i + 1, safe_box_name);
	}
}

// Получение метода сигнала нужного класса
//cl_base::TYPE_SIGNAL cl_application::get_signal_method(cl_base* pointer) {
	//return SIGNAL_D(cl_application::signal_method);
	/*if (pointer->get_class_number() == 1) return SIGNAL_D(cl_application::signal_method);
	else if (pointer->get_class_number() == 2) return SIGNAL_D(cl_remote_control::signal_method);
	else if (pointer->get_class_number() == 3) return SIGNAL_D(cl_safe::signal_method);
	else if (pointer->get_class_number() == 4) return SIGNAL_D(cl_safe_box::signal_method);
	else if (pointer->get_class_number() == 5) return SIGNAL_D(cl_server::signal_method);
	else if (pointer->get_class_number() == 6) return SIGNAL_D(cl_screen::signal_method);
	else return SIGNAL_D(cl_reader::signal_method);*/
//}

// Получение метода обработчика нужного класса
//cl_base::TYPE_HANDLER cl_application::get_handler_method(cl_base* pointer) {
	//return HANDLER_D(cl_application::handler_method);
	/*if (pointer->get_class_number() == 1) return HANDLER_D(cl_application::handler_method);
	else if (pointer->get_class_number() == 2) return HANDLER_D(cl_remote_control::handler_method);
	else if (pointer->get_class_number() == 3) return HANDLER_D(cl_safe::handler_method);
	else if (pointer->get_class_number() == 4) return HANDLER_D(cl_safe_box::handler_method);
	else if (pointer->get_class_number() == 5) return HANDLER_D(cl_server::handler_method);
	else if (pointer->get_class_number() == 6) return HANDLER_D(cl_screen::handler_method);
	else return HANDLER_D(cl_reader::handler_method);*/
//}

void cl_application::handle_signal_from_remote_control(string text) {
	if (text == "turn_off") {
		system_indicator = false;
	}
	else if (text == "show_tree") {
		print_readiness_tree(4);
		system_indicator = false;
	}
}

void cl_application::emit_signal_to_screen(string& text) {
	text = "Ready to work";
}