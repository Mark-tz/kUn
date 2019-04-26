#ifndef ZPASSV2_H
#define ZPASSV2_H
#include <skill/PlayerTask.h>

class CZPassV2 : public CStatedTask {
public:
    virtual void plan( const CVisionModule* pVision );
    virtual bool isEmpty() const { return false; }
    virtual CPlayerCommand* execute ( const CVisionModule* pVision );
protected:
    virtual void toStream( std::ostream& os ) const {
        os << "Skill: ZPassV2\n" << std::endl;
    }
private:
    bool needdribble_ = false;
    bool needkick_ = false;
    bool chip_ = false;
    bool safeMode_ = false;
    int new_status_;
//    int _last_status;
    int getStaticDir(const CVisionModule * pVision, int staticDir);
    CGeoPoint ball_line_projection_;
};

/// @brief return 0: touch, return 1: CmuTurn, return 2: TurnKick
void JudgeMode( const CVisionModule* pVision, int robot_num,
                        CGeoPoint pos);

#endif
