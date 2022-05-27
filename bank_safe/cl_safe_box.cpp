#include "cl_safe_box.h"

// Ячейка банковского сейфа

cl_safe_box::cl_safe_box(cl_base* parent, int number, string name) :cl_base(parent, name) {
	this->class_number = 4;
	this->number = number;
}

// Метод сигнала
void cl_safe_box::signal_method(string& text) {
	cout << "\nSignal from " << get_absolute_path();
	text += " (class: 4)";
}

// Метод обработчика
void cl_safe_box::handler_method(string text) {
	cout << "\nSignal to " << get_absolute_path() << " Text: " << text;
}