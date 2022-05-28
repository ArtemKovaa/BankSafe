#ifndef CL_BASE_H
#define CL_BASE_H
#define SIGNAL_D(signal_f) (TYPE_SIGNAL) (&signal_f)
#define HANDLER_D(handler_f) (TYPE_HANDLER) (&handler_f)

#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

class cl_base {

public:
	typedef void (cl_base::* TYPE_SIGNAL) (string&);
	typedef void (cl_base::* TYPE_HANDLER) (string);

private:
	string name;
	cl_base* parent = nullptr;
	int state = 0; // Состояние готовности объекта
	struct connection_struct {
		TYPE_SIGNAL signal_method;
		cl_base* handler;
		TYPE_HANDLER handler_method;
	};
	vector<connection_struct*> connections;

protected:
	vector<cl_base*> children;
	int class_number; // Номер класса

public:
	cl_base(cl_base* parent, string name = "Default");
	void set_name(string name);
	string get_name();
	void print_tree(int recursion_level);
	void set_parent(cl_base* parent);
	cl_base* get_parent();
	~cl_base();
	cl_base* find_object_by_name(string name);
	void print_readiness_tree(int recursion_level);
	void set_readiness(int state);
	cl_base* find_object_by_path(string path);
	void set_connection(TYPE_SIGNAL signal_method, cl_base* handler, TYPE_HANDLER handler_method);
	void delete_connection(TYPE_SIGNAL signal_method, cl_base* handler, TYPE_HANDLER handler_method);
	void emit_signal(TYPE_SIGNAL signal_method, string& text);
	string get_absolute_path(string absolute_path = "");
	int get_class_number();
	int get_readiness();
	void set_readiness_for_all(int state);
};

#endif