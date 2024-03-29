#include <Python.h>

void print_python_list(PyObject *p);
void print_python_bytes(PyObject *p);
void print_python_float(PyObject *p);

/**
 * print_python_list - Prints basic info about Python lists.
 * @p: A PyObject list object.
 */
void print_python_list(PyObject *p)
{
    Py_ssize_t size, alloc, i;
    const char *type;
    PyListObject *list = (PyListObject *)p;
    PyVarObject *var = (PyVarObject *)p;

    size = var->ob_size;
    alloc = list->allocated;

    fflush(stdout);

    printf("[*] Python list info\n");
    if (strncmp(Py_TYPE(p)->tp_name, "list", 4) != 0)
    {
        printf("  [ERROR] Invalid List Object\n");
        return;
    }

    printf("[*] Size of the Python List = %ld\n", size);
    printf("[*] Allocated = %ld\n", alloc);

    for (i = 0; i < size; i++)
    {
        type = Py_TYPE(list->ob_item[i])->tp_name;
        printf("Element %ld: %s\n", i, type);

        if (strncmp(type, "bytes", 5) == 0)
            print_python_bytes(list->ob_item[i]);
        else if (strncmp(type, "float", 5) == 0)
            print_python_float(list->ob_item[i]);
    }
}

/**
 * print_python_bytes - Prints basic info about Python bytes.
 * @p: A PyObject bytes object.
 */
void print_python_bytes(PyObject *p)
{
    Py_ssize_t size, i;
    char *str;

    printf("[.] bytes object info\n");
    if (strncmp(Py_TYPE(p)->tp_name, "bytes", 5) != 0)
    {
        printf("  [ERROR] Invalid Bytes Object\n");
        return;
    }

    size = PyBytes_Size(p);
    printf("  size: %ld\n", size);

    str = PyBytes_AsString(p);
    printf("  trying string: %s\n", str);

    printf("  first 10 bytes: ");
    for (i = 0; i < size && i < 10; i++)
        printf("%02x ", (unsigned char)str[i]);
    printf("\n");
}

/**
 * print_python_float - Prints basic info about Python float.
 * @p: A PyObject float object.
 */
void print_python_float(PyObject *p)
{
    printf("[.] float object info\n");
    if (strncmp(Py_TYPE(p)->tp_name, "float", 5) != 0)
    {
        printf("  [ERROR] Invalid Float Object\n");
        return;
    }

    printf("  value: %f\n", PyFloat_AsDouble(p));
}
