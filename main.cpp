#include <Python.h>

#include <boost/python.hpp>

#include <string>
#include <iostream>

void boost_exec_file()
{
    namespace python = boost::python;

    std::string py_filename {"sample_python_code.py"};
    std::string py_func_name {"get_number"};

    Py_Initialize();

    try {
        python::object module = python::import("__main__");
        python::object name_space = module.attr("__dict__");
        exec_file(py_filename.c_str(), name_space, name_space);

        python::object py_func = name_space[py_func_name.c_str()];
        python::object py_res = py_func();
        int res = python::extract<int>(py_res);
        std::cout << "the magic number is: [" << res << "]" << std::endl;
    }
    catch(python::error_already_set& ex) {
        std::cerr << "ERROR: python exception" << std::endl;
        PyErr_Print();
    }
}

int main()
{
    boost_exec_file();
}
