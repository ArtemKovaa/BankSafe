#include "cl_remote_control.h"

// Пульт управления

cl_remote_control::cl_remote_control(cl_base* parent, string name) :cl_base(parent, name) {
	this->class_number = 2;
	this->current_safe_box_number = 0;
}

void cl_remote_control::emit_signal_to_reader(string& text) {}

void cl_remote_control::handle_signal_from_reader(string text) {
	if (text == "Turn off the safe") {
		text = "turn_off";
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_system), text);
		return;
	}
	int number;
	string command = (text.substr(0, text.find(' '))); // Получаем команду для выполнения
	text = text.substr(text.find(' ') + 1, text.length());

	if (command == "BOX") {
		stage = 1;
		command = "find "; 
		command += text;
		command += " first";
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_safe), command);
	}
	else if (command == "CLIENT_KEY") {
		if (stage == 2) {
			command = "client "; // Костыль для работы с множественным выбором на сервере
			command += to_string(current_safe_box_number); // Номер открываемой ячейки
			command += " ";
			command += text; // Клиентский ключ
			emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_server), command); // Идем на сервер
			if (correctness == "correct") {
				command = "find ";
				command += to_string(current_safe_box_number);
				emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_safe), command);
			}
		}
		else {
			text = "error";
			emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_screen), text); // Выводим на экран сообщение о вводе клиентского ключа
		}
	}
	else if (command == "BANK_KEY") {
		if (stage == 3) {
			command = "bank "; // Костыль для работы с множественным выбором на сервере
			command += to_string(current_safe_box_number); // Номер открываемой ячейки
			command += " ";
			command += text; // Клиентский ключ
			emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_server), command); // Идем на сервер
			if (correctness == "correct") {
				command = "find "; // Возможно можно убрать, добавлено для множественного выбора в сейфе
				command += to_string(current_safe_box_number);
				emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_safe), command);
			}
		}
		else {
			text = "error";
			emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_screen), text); // Выводим на экран сообщение о вводе клиентского ключа
		}
		
	}
	else if (command == "CLOSE_BOX") {
		number = stoi(text.substr(0, text.find(' ')));
		command = "close " + text;
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_safe), command);
		text = "next";
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_screen), text);
	}
	else if (command == "CANCEL") {
		stage = 0;
		text = "cancel";
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_screen), text); // Выводим на экран сообщение о вводе клиентского ключа
	}
	else if (command == "SHOWTREE") {

	}
}

void cl_remote_control::emit_signal_to_safe(string& text) {

}

void cl_remote_control::handle_signal_from_safe(string text) {
	if (text.length() > 0) {
		if (text.substr(text.find(' ') + 1, text.length()) == "is_open") {
			string key = text.substr(text.find(' ') + 1, text.length());
			text = text.substr(text.find(' ') + 1, text.length());
			emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_screen), text); // Выводим на экран сообщение о вводе клиентского ключа
		}
		else {
			current_safe_box_number = stoi(text.substr(0, text.find(' '))); // Запоминаем, какую ячейку мы открываем
			text = text.substr(text.find(' ') + 1, text.length());
			if (text == "needs_client_key") stage = 2;
			else if (text == "needs_bank_key") stage = 3;
			// Если закрыта, продолжаем наш забег
			emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_screen), text); // Выводим на экран сообщение о вводе банковского ключа
		}
		
	}
	else {
		// Если она уже открыта
		text = "is_open";
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_screen), text);
	}
}

void cl_remote_control::emit_signal_to_server(string& text) {

}

void cl_remote_control::handle_signal_from_server(string text) {
	// Подошел ключ клиента
	if (text == "1") {
		// Переходим к вводу банковского ключа
		text = "1"; 
		correctness = "correct";
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_screen), text);
	}
	// Подошел ключ банка
	else if (text == "2") {
		text = "now_open " + to_string(current_safe_box_number);
		correctness = "correct";
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_screen), text);
		text = "open " + to_string(current_safe_box_number);
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_safe), text);
		stage = 0;
	}
	// Неверные данные
	else if (text == "3") {
		text = "client_incorrect";
		correctness = "incorrect";
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_screen), text); // Уведомляем об ошибке
	}
	else if (text == "4") {
		text = "bank_incorrect";
		correctness = "incorrect";
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_screen), text); // Уведомляем об ошибке
	}
}

void cl_remote_control::emit_signal_to_system(string& text) {
	if (!(text == "turn_off")) text = "command";
}

void cl_remote_control::emit_signal_to_screen(string& text) {

}