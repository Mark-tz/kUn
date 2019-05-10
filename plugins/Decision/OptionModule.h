#ifndef _OPTION_MODULE_H_
#define _OPTION_MODULE_H_
/**
* COptionModule.
* 一些初始化参数
*/
class COptionModule{
public:
    COptionModule(bool isYellow,bool isRight);
	~COptionModule();
    int MySide() const { return _side; }
	int MyColor() const { return _color; }
private:
    int _side; // 比赛中所在的边
	int _color; // 我方颜色,RefereeBox用到
};
#endif
