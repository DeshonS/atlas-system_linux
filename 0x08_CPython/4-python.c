#include <Python.h>

void print_python_string(PyObject *p);

void print_python_string(PyObject *p)
{
	if (!PyString_Check(p))
	{
		printf("[.] string object info\n");
		printf("  [ERROR] Invalid String Object\n");
		return;
	}
	char value = ((PyStringObject *)p)->tp_name;
	int size = ((PyStringObject *)p)->ob_size;
	printf("[.] string object info\n");
	/*printf("  type: %s\n");*/
	printf("  length: %d\n" size);
	printf("  value: %s\n", value);
}