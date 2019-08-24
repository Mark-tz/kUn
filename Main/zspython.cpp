#include <boost/python.hpp>
#include "zsplugin.hpp"
#include "Vision/visionmodule.h"
#include "Sim/sslworld.h"
using namespace boost::python;

struct PluginWrapper : ZSPlugin, boost::python::wrapper<ZSPlugin>{
	PluginWrapper() {}
	void run(){ this->get_override("run")(); }
};

BOOST_PYTHON_MODULE(zss_kun){
	class_<PluginWrapper, boost::noncopyable>("ZSPlugin",no_init)
		.def("link",&ZSPlugin::link)
		.def("run",pure_virtual(&ZSPlugin::run));
		// .def<>("publish",)	
		// .def("publish",)
		// .def("receive",)
		// .def("receive",)
		// .def("try_receive",&ZSPlugin::try_receive)
		// .def("store",)
		// .def("store",)
		// .def("declare_receive",)
		// .def("declare_publish",)
	class_<VisionModule,bases<ZSPlugin> >("VisionModule");
	class_<SSLWorld,bases<ZSPlugin>, boost::noncopyable >("SSLWorld",no_init)
		.def("instance",&SSLWorld::instance,return_value_policy<reference_existing_object>())
		.staticmethod("instance");
}