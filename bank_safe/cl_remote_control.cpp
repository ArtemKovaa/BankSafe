#include "cl_remote_control.h"

// ����� ����������

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
	string command = (text.substr(0, text.find(' '))); // �������� ������� ��� ����������
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
			command = "client "; // ������� ��� ������ � ������������� ������� �� �������
			command += to_string(current_safe_box_number); // ����� ����������� ������
			command += " ";
			command += text; // ���������� ����
			emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_server), command); // ���� �� ������
			if (correctness == "correct") {
				command = "find ";
				command += to_string(current_safe_box_number);
				emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_safe), command);
			}
		}
		else {
			text = "error";
			emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_screen), text); // ������� �� ����� ��������� � ����� ����������� �����
		}
	}
	else if (command == "BANK_KEY") {
		if (stage == 3) {
			command = "bank "; // ������� ��� ������ � ������������� ������� �� �������
			command += to_string(current_safe_box_number); // ����� ����������� ������
			command += " ";
			command += text; // ���������� ����
			emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_server), command); // ���� �� ������
			if (correctness == "correct") {
				command = "find "; // �������� ����� ������, ��������� ��� �������������� ������ � �����
				command += to_string(current_safe_box_number);
				emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_safe), command);
			}
		}
		else {
			text = "error";
			emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_screen), text); // ������� �� ����� ��������� � ����� ����������� �����
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
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_screen), text); // ������� �� ����� ��������� � ����� ����������� �����
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
			emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_screen), text); // ������� �� ����� ��������� � ����� ����������� �����
		}
		else {
			current_safe_box_number = stoi(text.substr(0, text.find(' '))); // ����������, ����� ������ �� ���������
			text = text.substr(text.find(' ') + 1, text.length());
			if (text == "needs_client_key") stage = 2;
			else if (text == "needs_bank_key") stage = 3;
			// ���� �������, ���������� ��� �����
			emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_screen), text); // ������� �� ����� ��������� � ����� ����������� �����
		}
		
	}
	else {
		// ���� ��� ��� �������
		text = "is_open";
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_screen), text);
	}
}

void cl_remote_control::emit_signal_to_server(string& text) {

}

void cl_remote_control::handle_signal_from_server(string text) {
	// ������� ���� �������
	if (text == "1") {
		// ��������� � ����� ����������� �����
		text = "1"; 
		correctness = "correct";
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_screen), text);
	}
	// ������� ���� �����
	else if (text == "2") {
		text = "now_open " + to_string(current_safe_box_number);
		correctness = "correct";
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_screen), text);
		text = "open " + to_string(current_safe_box_number);
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_safe), text);
		stage = 0;
	}
	// �������� ������
	else if (text == "3") {
		text = "client_incorrect";
		correctness = "incorrect";
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_screen), text); // ���������� �� ������
	}
	else if (text == "4") {
		text = "bank_incorrect";
		correctness = "incorrect";
		emit_signal(SIGNAL_D(cl_remote_control::emit_signal_to_screen), text); // ���������� �� ������
	}
}

void cl_remote_control::emit_signal_to_system(string& text) {
	if (!(text == "turn_off")) text = "command";
}

void cl_remote_control::emit_signal_to_screen(string& text) {

}