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
	const char *value = PyUnicode_AsUTF8(p);
	size = PyUnicode_GET_SIZE(p);
	printf("[.] string object info\n");
	/*printf("  type: %s\n", type);*/
	printf("  length: %d\n", size);
	printf("  value: %s\n", value);
}