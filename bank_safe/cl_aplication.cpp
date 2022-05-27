#include "cl_application.h"

cl_application::cl_application(cl_base* parent) :cl_base(parent) {
	this->class_number = 1;
}

void cl_application::build_tree_objects() {
	set_name("system");
	cl_base* signal_object, * handler_object; // Объект, выдающий сигнал, и целевой объект

	cl_base* current_object = this;
	new cl_remote_control(current_object, "remote_control");
	new cl_server(current_object, "server");

	current_object = find_object_by_name("remote_control");
	new cl_reader(current_object, "reader");
	new cl_screen(current_object, "screen");

	// Связываем систему с ридером
	signal_object = this;
	handler_object = find_object_by_name("reader");
	signal_object->set_connection(SIGNAL_D(cl_application::signal_method), handler_object, HANDLER_D(cl_reader::handler_method));

	// Связываем ридер с сервером и системой
	signal_object = find_object_by_name("reader");
	handler_object = this;
	signal_object->set_connection(SIGNAL_D(cl_reader::emit_signal_to_system), handler_object, HANDLER_D(cl_application::handler_method));
	handler_object = find_object_by_name("server");;
	signal_object->set_connection(SIGNAL_D(cl_reader::emit_signal_to_server), handler_object, HANDLER_D(cl_server::handle_signal_from_reader));

	signal_object = this;
	string text = "";
	signal_object->emit_signal(get_signal_method(signal_object), text);

	cl_safe* ptr = (cl_safe*)find_object_by_name("safe");
	ptr->fill_safe();

	current_object = find_object_by_name("system");
	cl_server* ptr1 = (cl_server*)find_object_by_name("server");
	ptr1->show_inf();


	string signal_object_path, handler_object_path; // Пути выдающего сигнал и целевого объекта


	while (cin >> signal_object_path) {
		// Условие завершения построения связей
		if (signal_object_path == "end_of_connections") {
			break;
		}
		cin >> handler_object_path;

		signal_object = find_object_by_path(signal_object_path);

		// Если объект, выдающий сигнал, не найден
		if (signal_object == nullptr) {
			cout << "\nObject " << signal_object_path << " not found";
			continue;
		}

		handler_object = find_object_by_path(handler_object_path);

		// Если объект-обработчик не найден
		if (handler_object == nullptr) {
			cout << "\nHandler object " << handler_object_path << " not found";
			continue;
		}

		signal_object->set_connection(get_signal_method(signal_object), handler_object, get_handler_method(handler_object));
	}
}

// Метод запуска приложения
int cl_application::exec_app() {
	print_tree(4); // Вывод на консоль иерархического дерева объектов системы

	set_readiness_for_all(1); // Установка всем объектам состояния готовности

	string signal_object_path, handler_object_path; // Пути выдающего сигнал и целевого объекта
	cl_base* signal_object, * handler_object; // Объект, выдающий сигнал, и целевой объект
	string text, operation;
	int state; // Состояние готовности

	while (cin >> operation) {
		// Команда END
		if (operation == "END") {
			break;
		}
		// Команда EMIT
		else if (operation == "EMIT") {
			cin >> signal_object_path;
			getline(cin, text);

			signal_object = find_object_by_path(signal_object_path);
			// Если объект, выдающий сигнал, не найден
			if (signal_object == nullptr) {
				cout << "\nObject " << signal_object_path << " not found";
				continue;
			}
			// Выдача сигнала
			signal_object->emit_signal(get_signal_method(signal_object), text);
		}
		// Команда SET_CONNECT
		else if (operation == "SET_CONNECT") {
			cin >> signal_object_path >> handler_object_path;

			signal_object = find_object_by_path(signal_object_path);
			// Если объект, выдающий сигнал, не найден
			if (signal_object == nullptr) {
				cout << "\nObject " << signal_object_path << " not found";
				continue;
			}

			handler_object = find_object_by_path(handler_object_path);
			// Если объект-обработчик не найден
			if (handler_object == nullptr) {
				cout << "\nHandler object " << handler_object_path << " not found";
				continue;
			}
			// Установка связи
			signal_object->set_connection(get_signal_method(signal_object), handler_object, get_handler_method(handler_object));
		}
		// Команда DELETE_CONNECT
		else if (operation == "DELETE_CONNECT") {
			cin >> signal_object_path >> handler_object_path;

			signal_object = find_object_by_path(signal_object_path);
			// Если объект, выдающий сигнал, не найден
			if (signal_object == nullptr) {
				cout << "\nObject " << signal_object_path << " not found";
				continue;
			}

			handler_object = find_object_by_path(handler_object_path);
			// Если объект-обработчик не найден
			if (handler_object == nullptr) {
				cout << "\nHandler object " << handler_object_path << " not found";
				continue;
			}
			// Удаление связи
			signal_object->delete_connection(get_signal_method(signal_object), handler_object, get_handler_method(handler_object));
		}
		// Команда SET_CONDITION
		else {
			cin >> signal_object_path >> state;

			signal_object = find_object_by_path(signal_object_path);
			// Если объект, которому нужно установить состояние, не найден
			if (signal_object == nullptr) {
				cout << "\nObject " << signal_object_path << " not found";
				continue;
			}

			signal_object->set_readiness(state); // Установка готовности
		}
	}
	return 0;
}

// Метод сигнала
void cl_application::signal_method(string& text) {
	text = get_name();
}

// Метод обработчика
void cl_application::handler_method(string input) {
	int first_value, second_value;

	first_value = stoi(input.substr(0, input.find(' ')));
	input = input.substr(input.find(' ') + 1, input.length());
	second_value = stoi(input);
	new cl_safe(this, first_value, second_value, "safe");
	cl_base* current_object = find_object_by_name("safe");
	string safe_box_name;
	for (int i = 0; i < (first_value * second_value); i++) {
		int test = i + 1;
		safe_box_name = "safe_box ";
		safe_box_name += to_string(test);
		new cl_safe_box(current_object, i + 1, safe_box_name);
	}
}

// Получение метода сигнала нужного класса
cl_base::TYPE_SIGNAL cl_application::get_signal_method(cl_base* pointer) {
	return SIGNAL_D(cl_application::signal_method);
	/*if (pointer->get_class_number() == 1) return SIGNAL_D(cl_application::signal_method);
	else if (pointer->get_class_number() == 2) return SIGNAL_D(cl_remote_control::signal_method);
	else if (pointer->get_class_number() == 3) return SIGNAL_D(cl_safe::signal_method);
	else if (pointer->get_class_number() == 4) return SIGNAL_D(cl_safe_box::signal_method);
	else if (pointer->get_class_number() == 5) return SIGNAL_D(cl_server::signal_method);
	else if (pointer->get_class_number() == 6) return SIGNAL_D(cl_screen::signal_method);
	else return SIGNAL_D(cl_reader::signal_method);*/
}

// Получение метода обработчика нужного класса
cl_base::TYPE_HANDLER cl_application::get_handler_method(cl_base* pointer) {
	return HANDLER_D(cl_application::handler_method);
	/*if (pointer->get_class_number() == 1) return HANDLER_D(cl_application::handler_method);
	else if (pointer->get_class_number() == 2) return HANDLER_D(cl_remote_control::handler_method);
	else if (pointer->get_class_number() == 3) return HANDLER_D(cl_safe::handler_method);
	else if (pointer->get_class_number() == 4) return HANDLER_D(cl_safe_box::handler_method);
	else if (pointer->get_class_number() == 5) return HANDLER_D(cl_server::handler_method);
	else if (pointer->get_class_number() == 6) return HANDLER_D(cl_screen::handler_method);
	else return HANDLER_D(cl_reader::handler_method);*/
}