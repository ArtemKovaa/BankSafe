#include "cl_safe.h"

// Сейф

cl_safe::cl_safe(cl_base* parent, int rows_count, int columns_count, string name) :cl_base(parent, name) {
	this->class_number = 3;
	this->rows_count = rows_count;
	this->columns_count = columns_count;
	this->safe_boxes_count = rows_count * columns_count;
	safe_boxes = new cl_base** [rows_count];
	for (int i = 0; i < rows_count; i++) {
		safe_boxes[i] = new cl_base * [columns_count];
	}
}

void cl_safe::fill_safe() {
	// Заполнение матрицы сейфа
	for (int i = 0; i < rows_count - 1; i++) {
		for (int j = 0; j < columns_count - 1; j++) {
			safe_boxes[i][j] = children[i * columns_count + j];
		}
	}
}

// Метод сигнала
void cl_safe::signal_method(string& text) {
	cout << "\nSignal from " << get_absolute_path();
	text += " (class: 3)";
}

// Метод обработчика
void cl_safe::handler_method(string text) {
	cout << "\nSignal to " << get_absolute_path() << " Text: " << text;
}

// Поиск ячейки в сейфе по ее номеру
cl_base* cl_safe::find_safe_box(int number) {
	return safe_boxes[(number / rows_count)][(number / columns_count) - 1];
}