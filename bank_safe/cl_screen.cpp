#include "cl_screen.h"

// ����� ������ ����������

cl_screen::cl_screen(cl_base* parent, string name) :cl_base(parent, name) {
	this->class_number = 6;
}

// ����� �������
void cl_screen::signal_method(string& text) {
	cout << "\nSignal from " << get_absolute_path();
	text += " (class: 6)";
}

// ����� �����������
void cl_screen::handler_method(string text) {
	cout << "\nSignal to " << get_absolute_path() << " Text: " << text;
}