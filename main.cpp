#include <Python.h>

#include <boost/python.hpp>

#include <string>
#include <iostream>
#include <cstdlib>

namespace bp = boost::python;

void boost_exec_file()
{
    std::string py_filename {"sample_python_code.py"};
    std::string py_func_name {"get_number"};

    try {
        bp::object module = bp::import("__main__");
        bp::object name_space = module.attr("__dict__");
        bp::exec_file(py_filename.c_str(), name_space, name_space);

        bp::object py_func = name_space[py_func_name.c_str()];
        bp::object py_res = py_func();
        int res = bp::extract<int>(py_res);
        std::cout << "the magic number is: [" << res << "]" << std::endl;
    }
    catch(bp::error_already_set& ex) {
        std::cerr << "ERROR: python exception" << std::endl;
        PyErr_Print();
    }
}

void boost_exec()
{
    std::string py_filename {"sample_python_code.py"};
    std::string py_func_name {"get_number"};

    try {
        bp::object module = bp::import("__main__");
        bp::object name_space = module.attr("__dict__");
        bp::exec("print('hello from python in c++')", name_space, name_space);
    }
    catch(bp::error_already_set& ex) {
        std::cerr << "ERROR: python exception" << std::endl;
        PyErr_Print();
    }
}

void boost_exec_run_py_func()
{
    std::string py_filename {"sample_python_code.py"};
    std::string py_func_name {"get_number"};

    try {
        bp::object module = bp::import("__main__");
        bp::object name_space = module.attr("__dict__");
        bp::exec("from sample_python_code import get_number", name_space, name_space);
        bp::exec("get_number", name_space, name_space);
    }
    catch(bp::error_already_set& ex) {
        std::cerr << "ERROR: python exception" << std::endl;
        PyErr_Print();
    }
}

void boost_import_custom_module()
{
    std::string py_module_name {"sample_python_code"};
    std::string py_func_name {"get_number"};

    try {
        // >>> import the module from disk
        bp::object module = bp::import(py_module_name.c_str());
        auto numb = module.attr(py_func_name.c_str())();

        int res = bp::extract<int>(numb);
        std::cout << "the magic number is: [" << res << "]" << std::endl;
    }
    catch(bp::error_already_set& ex) {
        std::cerr << "ERROR: python exception" << std::endl;
        PyErr_Print();
    }
}

// A simle example with boost::python::exec():
// https://stackoverflow.com/questions/50154064/call-a-python-function-from-c-using-boost-python
// A nice example of boost python:
// https://stackoverflow.com/questions/38620134/how-to-import-a-function-from-python-file-by-boost-python
int main()
{
    // Allow Python to load modules from the current directory.
    setenv("PYTHONPATH", ".", 1); // must be called before Py_Initialize().
    Py_Initialize();

    std::cout << ">> boost_exec_file():" << std::endl;
    boost_exec_file();

    std::cout << ">> boost_exec():" << std::endl;
    boost_exec();

    std::cout << ">> boost_exec_run_py_func():" << std::endl;
    boost_exec_run_py_func();

    std::cout << ">> boost_import_custom_module():" << std::endl;
    boost_import_custom_module();
}
