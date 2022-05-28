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

// Метод вывода наименований объектов в дереве иерархии
void cl_base::print_tree(int recursion_level) {
	if (recursion_level == 4) {
		cout << "Object tree\n";
		cout << get_name(); // Вывод имени корневого объекта
	}
	// Проход вниз по иерархии с выводом имен подчиненных объектов
	for (int i = 0; i < children.size(); i++) {
		cout << '\n' << setw(recursion_level) << ' ' << children[i]->get_name();
		children[i]->print_tree(recursion_level + 4); // Рекурсивный вызов метода для подчиненных объектов
	}
}

// Метод переопределения головного объекта
void cl_base::set_parent(cl_base* new_parent) {
	// Проверка на корневой объект и правильность значения параметра new_parent
	if (parent != nullptr && new_parent != nullptr) {
		for (int i = 0; i < parent->children.size(); i++) {
			// Если указатель на текущий объект есть в массиве, то он удаляется
			if (parent->children[i] == this) {
				parent->children.erase(parent->children.begin() + i);
				break;
			}
		}
		// Добавляем указатель на текущей объект в конец массива
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

// Метод поиска объекта на дереве иерархии по имени
cl_base* cl_base::find_object_by_name(string name) {
	// Проверка текущего объекта
	if (this->name == name) {
		return this;
	}
	// Проход по именам подчиненных текущего объекта
	for (int i = 0; i < children.size(); i++) {
		// Если имя подчиненного объекта равно искомому, то возвращается его имя
		if (children[i]->get_name() == name) {
			return children[i];
		}
	}
	// Проход вниз по иерархии объектов
	for (int i = 0; i < children.size(); i++) {
		cl_base* temp_pointer = children[i]->find_object_by_name(name); // Рекурсивный вызов метода для подчиненных объектов
		// Если найден нужный объект, то он возвращается
		if (temp_pointer != nullptr) {
			return temp_pointer;
		}
	}
	// Не найден - возврат нулевого указателя
	return nullptr;
}

// Метод вывода дерева иерархии объектов и отметок их готовности
void cl_base::print_readiness_tree(int recursion_level) {
	if (recursion_level == 4) {
		cout << "\nThe tree of objects and their readiness\n";
		cout << get_name(); // Вывод имени корневого объекта
	}
	if (state != 0) {
		cout << " is ready";
	}
	else {
		cout << " is not ready";
	}
	// Проход вниз по иерархии с выводом имен подчиненных объектов
	for (int i = 0; i < children.size(); i++) {
		cout << '\n' << setw(recursion_level) << ' ' << children[i]->get_name();
		children[i]->print_readiness_tree(recursion_level + 4); // Рекурсивный вызов метода для подчиненных объектов
	}
}

// Метод установки готовности объекта
void cl_base::set_readiness(int state) {
	// Если объект отключен, то отключаются все объекты, стоящие ниже его по ветке иерархии
	if (state == 0) {
		for (int i = 0; i < children.size(); i++) {
			children[i]->set_readiness(0);
		}
		this->state = state;
	}
	// Если объект не корневой, то поднимаемся вверх по иерархии до корневого, проверяя их отметки готовности
	else if (parent != nullptr) {
		cl_base* temp_pointer = parent;
		do {
			// Если отметка готовности нулевая, то установка готовности игнорируется
			if (temp_pointer->state == 0) {
				return;
			}
			temp_pointer = temp_pointer->get_parent();
		} while (temp_pointer != nullptr);
		this->state = state;
	}
	else {
		this->state = state; // установка готовности, если объект корневой
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

// Установление связи между сигнало текущего объекта и обработчиком целевого объекта
void cl_base::set_connection(TYPE_SIGNAL signal_method, cl_base* handler, TYPE_HANDLER handler_method) {
	// Если уже существуют связи
	if (connections.size() != 0) {
		for (int i = 0; i < connections.size(); i++) {
			// Если добавляемая связь уже существует
			if (connections[i]->signal_method == signal_method && connections[i]->handler == handler &&
				connections[i]->handler_method == handler_method) return;
		}
	}
	// Создание новой связи
	connection_struct* connection = new connection_struct();
	connection->signal_method = signal_method;
	connection->handler = handler;
	connection->handler_method = handler_method;
	connections.push_back(connection);
}

// Удаление связи между сигналом текущего объекта и обработчиком целевого объекта
void cl_base::delete_connection(TYPE_SIGNAL signal_method, cl_base* handler, TYPE_HANDLER handler_method) {
	for (int i = 0; i < connections.size(); i++) {
		// Поиск искомой связи
		if (connections[i]->signal_method == signal_method && connections[i]->handler == handler &&
			connections[i]->handler_method == handler_method) {
			connections.erase(connections.begin() + i); // Удаление искомой связи
			return;
		}
	}
}

// Выдача сигнала от текущего объекта
void cl_base::emit_signal(TYPE_SIGNAL signal_method, string& text) {
	if (this->get_readiness() == 0) return;

	(this->*signal_method)(text);

	// Если связей нет
	if (connections.empty()) return;

	// Проходимся по контейнеру связей
	for (int i = 0; i < connections.size(); i++) {
		// Поиск нужной связи
		if (connections[i]->signal_method == signal_method && connections[i]->handler->get_readiness() != 0) {
			// Если объект-обработчик включен, то выполняется обработка сигнала
			(connections[i]->handler->*(connections[i]->handler_method))(text);
		}
	}
}

// Определение абсолютного пути до текущего объекта
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

// Установка готовности для всех объектов
void cl_base::set_readiness_for_all(int state) {
	this->set_readiness(state); // Установка готовности корневому объекту
	// Рекурсивный вызов метода для всех подчиненных объектов
	for (int i = 0; i < children.size(); i++) children[i]->set_readiness_for_all(state);
}