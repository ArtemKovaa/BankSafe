#include "cl_safe_box.h"

// ������ ����������� �����

cl_safe_box::cl_safe_box(cl_base* parent, int number, string name) :cl_base(parent, name) {
	this->class_number = 4;
	this->number = number;
}

int cl_safe_box::get_number() {
	return number;
}

// ����� �������
void cl_safe_box::signal_method(string& text) {
	cout << "\nSignal from " << get_absolute_path();
	text += " (class: 4)";
}

// ����� �����������
void cl_safe_box::handler_method(string text) {
	cout << "\nSignal to " << get_absolute_path() << " Text: " << text;
}