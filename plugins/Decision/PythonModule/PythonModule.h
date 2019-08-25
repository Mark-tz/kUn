// mark 26/12/2018
#ifdef USE_PYTHON_MODULE
#ifndef __PYTHON_MODULE_H__
#define __PYTHON_MODULE_H__
#include <boost/python.hpp>
#include <string>
#include "singleton.hpp"
class CPythonModule{
public:
    CPythonModule();
    virtual ~CPythonModule();
    void run();
private:
    boost::python::object main_namespace;
    std::string code;
};
typedef Singleton<CPythonModule> PythonModule;
#endif //__PYTHON_MODULE_H__
#endif // USE_PYTHON_MODULE