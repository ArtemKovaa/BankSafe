#include "cl_remote_control.h"

// Пульт управления

cl_remote_control::cl_remote_control(cl_base* parent, string name) :cl_base(parent, name) {
	this->class_number = 2;
	this->current_safe_box_number = 0;
}

void cl_remote_control::emit_signal_to_reader(string& text) {}

void cl_remote_control::handle_signal_from_reader(string text) {
	int number;
	string command = (text.substr(0, text.find(' '))); // Получаем команду для выполнения
	text = text.substr(text.find(' ') + 1, text.length());

	if (command == "BOX") {
		command = "1 "; // Возможно можно убрать, добавлено для множественного выбора в сейфе
		command += text;
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_safe), command);
	}
	else if (command == "CLIENT_KEY") {
		command = "1 "; // Костыль для работы с множественным выбором на сервере
		command += to_string(current_safe_box_number); // Номер открываемой ячейки
		command += " ";
		command += text; // Клиентский ключ
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_server), command); // Идем на сервер
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
		current_safe_box_number = stoi(text.substr(0, text.find(' '))); // Запоминаем, какую ячейку мы открываем
		text = text.substr(text.find(' ') + 1, text.length()); 
		// Если закрыта, продолжаем наш забег
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_screen), text); // Выводим на экран сообщение о вводе клиентского ключа
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_reader), text); // Считываем следующую команду
	}
	else {
		// Если она уже открыта
		text = "1";
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_screen), text);
	}
}

void cl_remote_control::emit_signal_to_server(string& text) {

}

void cl_remote_control::handle_signal_from_server(string text) {
	// Верные данные
	if (text == "1") {
		// Переходим к вводу банковского ключа
		text = "Enter the bank code"; 
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_screen), text);
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_reader), text);
	}
	// Неверные данные
	else {
		text = "The client is key is incorrect";
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_screen), text); // Уведомляем об ошибке
		text = "0"; // Индикатор для ввода клиентского пароля
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_screen), text); // Выводим на экран сообщение о вводе клиентского ключа
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_reader), text); // Считываем следующую команду
	}
}

void cl_remote_control::emit_signal_to_system() {

}

void cl_remote_control::emit_signal_to_screen() {

}