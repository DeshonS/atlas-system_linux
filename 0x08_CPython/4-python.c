#include <Python.h>

void print_python_string(PyObject *p);

void print_python_string(PyObject *p)
{
	if (!PyUnicode_Check(p))
	{
		printf("[.] string object info\n");
		printf("  [ERROR] Invalid String Object\n");
		return;
	}
	char value = ((PyUnicodeObject *)p)->AsUTF8;
	int size = ((PyUnicodeObject *)p)->length;
	printf("[.] string object info\n");
	/*printf("  type: %s\n", type);*/
	printf("  length: %ld\n", size);
	printf("  value: %s\n", value);
}