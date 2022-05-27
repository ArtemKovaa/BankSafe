#include "cl_base.h"

cl_base::cl_base(cl_base* parent, string name) {
	this->parent = parent;
	this->name = name;
	if (parent != nullptr) {
		this->parent->children.push_back(this);
	}
}

void cl_base::set_name(string name) {
	this->name = name;
}

string cl_base::get_name() {
	return name;
}

// ����� ������ ������������ �������� � ������ ��������
void cl_base::print_tree(int recursion_level) {
	if (recursion_level == 4) {
		cout << "Object tree\n";
		cout << get_name(); // ����� ����� ��������� �������
	}
	// ������ ���� �� �������� � ������� ���� ����������� ��������
	for (int i = 0; i < children.size(); i++) {
		cout << '\n' << setw(recursion_level) << ' ' << children[i]->get_name();
		children[i]->print_tree(recursion_level + 4); // ����������� ����� ������ ��� ����������� ��������
	}
}

// ����� ��������������� ��������� �������
void cl_base::set_parent(cl_base* new_parent) {
	// �������� �� �������� ������ � ������������ �������� ��������� new_parent
	if (parent != nullptr && new_parent != nullptr) {
		for (int i = 0; i < parent->children.size(); i++) {
			// ���� ��������� �� ������� ������ ���� � �������, �� �� ���������
			if (parent->children[i] == this) {
				parent->children.erase(parent->children.begin() + i);
				break;
			}
		}
		// ��������� ��������� �� ������� ������ � ����� �������
		parent = new_parent;
		parent->children.push_back(this);
	}

}

cl_base* cl_base::get_parent() {
	return parent;
}

cl_base::~cl_base() {
	for (int i = 0; i < children.size(); i++) {
		delete children[i];
	}
}

// ����� ������ ������� �� ������ �������� �� �����
cl_base* cl_base::find_object_by_name(string name) {
	// �������� �������� �������
	if (this->name == name) {
		return this;
	}
	// ������ �� ������ ����������� �������� �������
	for (int i = 0; i < children.size(); i++) {
		// ���� ��� ������������ ������� ����� ��������, �� ������������ ��� ���
		if (children[i]->get_name() == name) {
			return children[i];
		}
	}
	// ������ ���� �� �������� ��������
	for (int i = 0; i < children.size(); i++) {
		cl_base* temp_pointer = children[i]->find_object_by_name(name); // ����������� ����� ������ ��� ����������� ��������
		// ���� ������ ������ ������, �� �� ������������
		if (temp_pointer != nullptr) {
			return temp_pointer;
		}
	}
	// �� ������ - ������� �������� ���������
	return nullptr;
}

// ����� ������ ������ �������� �������� � ������� �� ����������
void cl_base::print_readiness_tree(int recursion_level) {
	if (recursion_level == 4) {
		cout << "\nThe tree of objects and their readiness\n";
		cout << get_name(); // ����� ����� ��������� �������
	}
	if (state != 0) {
		cout << " is ready";
	}
	else {
		cout << " is not ready";
	}
	// ������ ���� �� �������� � ������� ���� ����������� ��������
	for (int i = 0; i < children.size(); i++) {
		cout << '\n' << setw(recursion_level) << ' ' << children[i]->get_name();
		children[i]->print_readiness_tree(recursion_level + 4); // ����������� ����� ������ ��� ����������� ��������
	}
}

// ����� ��������� ���������� �������
void cl_base::set_readiness(int state) {
	// ���� ������ ��������, �� ����������� ��� �������, ������� ���� ��� �� ����� ��������
	if (state == 0) {
		for (int i = 0; i < children.size(); i++) {
			children[i]->set_readiness(0);
		}
		this->state = state;
	}
	// ���� ������ �� ��������, �� ����������� ����� �� �������� �� ���������, �������� �� ������� ����������
	else if (parent != nullptr) {
		cl_base* temp_pointer = parent;
		do {
			// ���� ������� ���������� �������, �� ��������� ���������� ������������
			if (temp_pointer->state == 0) {
				return;
			}
			temp_pointer = temp_pointer->get_parent();
		} while (temp_pointer != nullptr);
		this->state = state;
	}
	else {
		this->state = state; // ��������� ����������, ���� ������ ��������
	}
}

cl_base* cl_base::find_object_by_path(string path) {
	if (path.find("//") == 0) {
		if (parent == nullptr) return this->find_object_by_name(path.erase(0, 2));
		else return parent->find_object_by_path(path);
	}
	else if (path[0] == '/' && path.size() == 1) {
		if (parent == nullptr) return this;
		else return parent->find_object_by_path("/");
	}
	else if (path[0] == '/') {
		if (parent == nullptr) return this->find_object_by_path(path.erase(0, 1));
		else return parent->find_object_by_path(path);
	}
	else if (path.find("/") != -1 && path.find("/") != 0) {
		string push = path, object_name;
		for (int i = 0; i < path.find("/"); i++) {
			object_name.push_back(path[i]);
			push.erase(0, 1);
		}
		for (int i = 0; i < children.size(); i++) {
			if (children[i]->get_name() == object_name) return children[i]->find_object_by_path(push.erase(0, 1));
		}
	}
	else if (path == ".") return this;
	else {
		for (int i = 0; i < children.size(); i++) {
			if (children[i]->get_name() == path) return children[i];
		}
	}
	return nullptr;
}

// ������������ ����� ����� ������� �������� ������� � ������������ �������� �������
void cl_base::set_connection(TYPE_SIGNAL signal_method, cl_base* handler, TYPE_HANDLER handler_method) {
	// ���� ��� ���������� �����
	if (connections.size() != 0) {
		for (int i = 0; i < connections.size(); i++) {
			// ���� ����������� ����� ��� ����������
			if (connections[i]->signal_method == signal_method && connections[i]->handler == handler &&
				connections[i]->handler_method == handler_method) return;
		}
	}
	// �������� ����� �����
	connection_struct* connection = new connection_struct();
	connection->signal_method = signal_method;
	connection->handler = handler;
	connection->handler_method = handler_method;
	connections.push_back(connection);
}

// �������� ����� ����� �������� �������� ������� � ������������ �������� �������
void cl_base::delete_connection(TYPE_SIGNAL signal_method, cl_base* handler, TYPE_HANDLER handler_method) {
	for (int i = 0; i < connections.size(); i++) {
		// ����� ������� �����
		if (connections[i]->signal_method == signal_method && connections[i]->handler == handler &&
			connections[i]->handler_method == handler_method) {
			connections.erase(connections.begin() + i); // �������� ������� �����
			return;
		}
	}
}

// ������ ������� �� �������� �������
void cl_base::emit_signal(TYPE_SIGNAL signal_method, string& text) {
	if (this->get_readiness() == 0) return;

	(this->*signal_method)(text);

	// ���� ������ ���
	if (connections.empty()) return;

	// ���������� �� ���������� ������
	for (int i = 0; i < connections.size(); i++) {
		// ����� ������ �����
		if (connections[i]->signal_method == signal_method && connections[i]->handler->get_readiness() != 0) {
			// ���� ������-���������� �������, �� ����������� ��������� �������
			(connections[i]->handler->*(connections[i]->handler_method))(text);
		}
	}
}

// ����������� ����������� ���� �� �������� �������
string cl_base::get_absolute_path(string absolute_path) {
	if (parent == nullptr) return "/";
	return parent->get_absolute_path("/") + name + absolute_path;
}

int cl_base::get_class_number() {
	return class_number;
}

int cl_base::get_readiness() {
	return state;
}

// ��������� ���������� ��� ���� ��������
void cl_base::set_readiness_for_all(int state) {
	this->set_readiness(state); // ��������� ���������� ��������� �������
	// ����������� ����� ������ ��� ���� ����������� ��������
	for (int i = 0; i < children.size(); i++) children[i]->set_readiness_for_all(state);
}