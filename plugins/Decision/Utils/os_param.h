#ifndef _FILE_PARAM_H_
#define _FILE_PARAM_H_
#include <string>
#ifdef _WIN32
namespace Param{
	namespace File{
		const std::string DataDir = "data\\";
		const char* const ParamDir = "params\\";
		const std::string RobotPosFilterDir = "vision\\Robot_Param\\Pos\\";
		const std::string RobotRotFilterDir = "vision\\Robot_Param\\Rotation\\";
		const std::string BallFilterDir = "vision\\Ball_Param\\";
        const std::string PlayBookPath = "play_books\\";
        const std::string CBayesReader_SCRIPT_PATH = "params\\GameFilterParam\\";
        const std::string OppConfigPath = "defence_config\\";
	}
}
#else // not windows
namespace Param{
    namespace File{
        const std::string DataDir = "data/";
        const char* const ParamDir = "params/";
        const std::string RobotPosFilterDir = "vision/Robot_Param/Pos/";
        const std::string RobotRotFilterDir = "vision/Robot_Param/Rotation/";
        const std::string BallFilterDir = "vision/Ball_Param/";
        const std::string PlayBookPath = "play_books/";
        const std::string CBayesReader_SCRIPT_PATH = "params/GameFilterParam/";
        const std::string OppConfigPath = "defence_config/";
    }
}
#endif
#endif // _FILE_PARAM_H_
