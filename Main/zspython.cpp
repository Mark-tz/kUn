#include <boost/python.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/numpy.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include "Environment/environment.h"
#include <iostream>
using namespace boost::python;
// struct PluginWrapper : ZSPlugin, boost::python::wrapper<ZSPlugin>{
// 	PluginWrapper() {}
// 	void run(){ this->get_override("run")(); }
// };
std::vector<double> ndarray_convert2vector(numpy::ndarray axis){
	int n = axis.shape(0);
    std::vector<double> arr(n);
    for (int i = 0; i < n; ++i){
    	arr[i] = extract<double>(axis[i]);
    }
	return arr;
}
BOOST_PYTHON_MODULE(zss_kun){
	numpy::initialize();
	class_<std::vector<double> >("DoubleVector")
        .def(vector_indexing_suite<std::vector<double>>());
	def("np2v",ndarray_convert2vector);
	class_<FeedBack>("FeedBack")
		.def_readwrite("state",&FeedBack::state)
		.def_readwrite("reward",&FeedBack::reward)
		.def_readwrite("done",&FeedBack::done);
	class_<Environment>("Environment")
		.def(init<int>())
		.def("step",&Environment::step)
		.def("reset",&Environment::reset)
		.def("start_all",&Environment::start_all);
	// class_<PluginWrapper, boost::noncopyable>("ZSPlugin",no_init)
	// 	.def("link",&ZSPlugin::link)
	// 	.def("run",pure_virtual(&ZSPlugin::run));
	// 	.def<>("publish",)	
	// 	.def("publish",)
	// 	.def("receive",)
	// 	.def("receive",)
	// 	.def("try_receive",&ZSPlugin::try_receive)
	// 	.def("store",)
	// 	.def("store",)
	// 	.def("declare_receive",)
	// 	.def("declare_publish",)
	// class_<VisionPlugin,bases<ZSPlugin> >("VisionPlugin");
	// class_<SSLWorld,bases<ZSPlugin>, boost::noncopyable >("SSLWorld",no_init)
	// 	.def("instance",&SSLWorld::instance,return_value_policy<reference_existing_object>())
	// 	.staticmethod("instance");
	
}