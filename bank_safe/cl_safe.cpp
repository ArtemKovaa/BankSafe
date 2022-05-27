#include "cl_safe.h"

// ����

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
	// ���������� ������� �����
	for (int i = 0; i < rows_count - 1; i++) {
		for (int j = 0; j < columns_count - 1; j++) {
			safe_boxes[i][j] = children[i * columns_count + j];
		}
	}
}

// ����� ������ � ����� �� �� ������
cl_base* cl_safe::find_safe_box(int number) {
	return safe_boxes[(number / rows_count)][(number / columns_count) - 1];
}

void cl_safe::emit_signal_to_remote_control(string& text) {

}

void cl_safe::handle_signal_from_remote_control(string text) {
	int choice = stoi(text.substr(0, text.find(' ')));
	text = text.substr(text.find(' ') + 1, text.length());
	int number;
	switch (choice) {
	case 1:
		number = stoi(text);
		for (int i = 0; i < rows_count - 1; i++) {
			for (int j = 0; j < columns_count - 1; j++) {
				if (safe_boxes[i][j]->get_number() =);
			}
		}
		break;
	case 2:

		break;
	case 3:

		break;
	case 4:

		break;
	}
}