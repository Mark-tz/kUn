#include "OptionModule.h"
#include <param.h>
#include <weerror.h>
#include "WorldModel.h"
#include "parammanager.h"

COptionModule::COptionModule(bool isYellow,bool isRight)
    : _side(isRight ? Param::Field::POS_SIDE_RIGHT : Param::Field::POS_SIDE_LEFT)
    , _color(isYellow ? TEAM_YELLOW : TEAM_BLUE)
{
	std::cout << "Side : " << ((_side == Param::Field::POS_SIDE_LEFT) ? "left" : "right")
			  << ", Color : " << ((_color == TEAM_YELLOW) ? "yellow" : "blue") << " is running..." << std::endl;
	WorldModel::Instance()->registerOption(this);
}
COptionModule::~COptionModule(void) {}
