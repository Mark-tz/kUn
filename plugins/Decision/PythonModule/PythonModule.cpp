#ifdef USE_PYTHON_MODULE
#include "PythonModule.h"
#include "VisionModule.h"
#include "SkillUtils.h"
#include "GDebugEngine.h"
#include "geometry.h"
#include "WorldDefine.h"
#include "Neat.h"
#include <string>
#include <fstream>
#include <streambuf>
#include <QtDebug>
using namespace boost::python;
CPythonModule::CPythonModule(){
    std::ifstream t("python_scripts/Medusa.py");
    code = std::string((std::istreambuf_iterator<char>(t)),std::istreambuf_iterator<char>());
    try{
#ifdef _WIN32
        _putenv_s("PYTHONPATH", "python_scripts");
#else
        setenv("PYTHONPATH", "python_scripts", 1);
#endif
        Py_Initialize();
        object main_module((handle<>(borrowed(PyImport_AddModule("__main__")))));
        main_namespace = main_module.attr("__dict__");
        void (PlayerVisionT::*pSetPos)(double, double) = &PlayerVisionT::SetPos;

        // VisionModule
        class_<PlayerVisionT>("PlayerVisionT")
                .def("dir",&PlayerVisionT::Dir)
                .def("x",&PlayerVisionT::X)
                .def("y",&PlayerVisionT::Y)
                .def("velX",&PlayerVisionT::VelX)
                .def("velY",&PlayerVisionT::VelY)
                .def("valid",&PlayerVisionT::Valid)
                .def("setPos", pSetPos, return_value_policy<reference_existing_object>())
                ;
        class_<MobileVisionT>("MobileVision")
                .def("x", &MobileVisionT::X)
                .def("y", &MobileVisionT::Y)
                ;
        const PlayerVisionT& (CVisionModule::*pOurPlayer)(int) const = &CVisionModule::OurPlayer;
        const PlayerVisionT& (CVisionModule::*pTheirPlayer)(int) const = &CVisionModule::TheirPlayer;
        const MobileVisionT& (CVisionModule::*pBall)(void) const = &CVisionModule::Ball;
        class_<CVisionModule>("VisionModule")
                .def("our",pOurPlayer,return_value_policy<reference_existing_object>())
                .def("their",pTheirPlayer,return_value_policy<reference_existing_object>())
                .def("getValidNumber",&CVisionModule::getValidNum)
                .def("getTheirValidNumber",&CVisionModule::getTheirValidNum)
                .def("ball", pBall,return_value_policy<reference_existing_object>())
                .def("cycle", &CVisionModule::Cycle)
                ;
        main_namespace["vision"] = ptr(VisionModule::Instance());

        // SkillUtils
        class_<SkillUtils>("SkillUtils")
                .def("ourBest",&SkillUtils::getOurBestPlayer)
                .def("theirBest",&SkillUtils::getTheirBestPlayer)
                ;
        main_namespace["info"] = ptr(ZSkillUtils::instance());

        // DebugEngine
        main_namespace["Point"] = class_<CGeoPoint>("CGeoPoint")
                .def(init<double,double>())
                .def("x",&CGeoPoint::x)
                .def("y",&CGeoPoint::y)
                .def("x",&CGeoPoint::setX)
                .def("y",&CGeoPoint::setY)
                ;
        class_<CGDebugEngine,boost::noncopyable>("GDebugEngine")
                .def("x",&CGDebugEngine::gui_debug_x)
                .def("line",&CGDebugEngine::gui_debug_line)
                .def("robot",&CGDebugEngine::gui_debug_robot)
                .def("msg",&CGDebugEngine::gui_debug_msg)
                ;
        main_namespace["debug"] = ptr(GDebugEngine::Instance());

        // SendCommand
        class_<CNeat>("Neat")
                .def("set", &CNeat::SetActionValues)
                ;
        main_namespace["send"] = ptr(Neat::Instance());

    }catch(error_already_set){
        qDebug() << "Python Module Error :";PyErr_Print();
    }
}
CPythonModule::~CPythonModule(){
}
void CPythonModule::run(){
    try{
        handle<> ignored((PyRun_String(code.c_str(),Py_file_input,main_namespace.ptr(),main_namespace.ptr())));
    }catch(error_already_set){
        qDebug() << "Python Module Error :";PyErr_Print();
    }
}

#endif // USE_PYTHON_MODULE