#include "cl_safe.h"

// Сейф

cl_safe::cl_safe(cl_base* parent, int rows_count, int columns_count, string name) :cl_base(parent, name) {
	this->class_number = 3;
	this->rows_count = rows_count;
	this->columns_count = columns_count;
	this->safe_boxes_count = rows_count * columns_count;
	safe_boxes = new cl_safe_box** [rows_count];
	for (int i = 0; i < rows_count; i++) {
		safe_boxes[i] = new cl_safe_box* [columns_count];
	}
}

void cl_safe::fill_safe() {
	// Заполнение матрицы сейфа
	for (int i = 0; i < rows_count; i++) {
		for (int j = 0; j < columns_count; j++) {
			safe_boxes[i][j] = (cl_safe_box*)children[(i * columns_count) + j];
		}
	}
}

// Поиск ячейки в сейфе по ее номеру
cl_base* cl_safe::find_safe_box(int number) {
	return safe_boxes[(number / rows_count)][(number / columns_count) - 1];
}

void cl_safe::emit_signal_to_remote_control(string& text) {

}

void cl_safe::handle_signal_from_remote_control(string text) {
	string choice = text.substr(0, text.find(' '));
	text = text.substr(text.find(' ') + 1, text.length());
	int number = stoi(text.substr(0, text.find(' '))); // Номер ячейки
	text = text.substr(text.find(' ') + 1, text.length());
	if (choice == "find") {
		// Проход по всем ячейкам и поиск нужной
		for (int i = 0; i < rows_count; i++) {
			for (int j = 0; j < columns_count; j++) {
				if (safe_boxes[i][j]->get_number() == number) {
					// Проверка на то, что она закрыта
					if (text == "first") {
						if (safe_boxes[i][j]->get_readiness() == 3) {
							text = "";
							emit_signal(SIGNAL_D(cl_safe::emit_signal_to_remote_control), text);
							return;
						}
						safe_boxes[i][j]->set_readiness(1);
						text = to_string(number);
						text += " needs_client_key"; 
						emit_signal(SIGNAL_D(cl_safe::emit_signal_to_remote_control), text); // Передаем пульту номер ячейки
						return;
					}
					else if (safe_boxes[i][j]->get_readiness() == 1) {
						safe_boxes[i][j]->set_readiness(2);
						text = to_string(number);
						text += " needs_bank_key"; 
						emit_signal(SIGNAL_D(cl_safe::emit_signal_to_remote_control), text); // Передаем пульту номер ячейки
						return;
					}
				}
			}
		}
	}
	else if (choice == "open") {
		for (int i = 0; i < rows_count; i++) {
			for (int j = 0; j < columns_count; j++) {
				if (safe_boxes[i][j]->get_number() == number) {
					safe_boxes[i][j]->set_readiness(3); // открываем ячейку
				}
			}
		}
	}
	else if (choice == "close") {
		for (int i = 0; i < rows_count; i++) {
			for (int j = 0; j < columns_count; j++) {
				if (safe_boxes[i][j]->get_number() == number) {
					safe_boxes[i][j]->set_readiness(1); // закрываем ячейку
				}
			}
		}
	}
}