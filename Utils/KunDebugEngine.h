#ifndef __KUN_DEBUG_ENGINE_H__
#define __KUN_DEBUG_ENGINE_H__
#include <singleton.hpp>
#include <geometry.h>
#include <QUdpSocket>
#include <QMutex>
namespace{
    const int COLOR_WHITE = 0;
    const int COLOR_RED = 1;
    const int COLOR_ORANGE = 2;
    const int COLOR_YELLOW = 3;
    const int COLOR_GREEN = 4;
    const int COLOR_CYAN = 5;
    const int COLOR_BLUE = 6;
    const int COLOR_PURPLE = 7;
    const int COLOR_GRAY = 8;
    const int COLOR_BLACK = 9;
}

struct PosT{
    double x;
    double y;
};

class KunDebugEngine{
public:
        KunDebugEngine();
        ~KunDebugEngine();
    void gui_debug_x(const CGeoPoint& p, int debug_color = 1);
    void gui_debug_points(const std::vector<CGeoPoint> points, int debug_color = 1);
    void gui_debug_line(const CGeoPoint& p1, const CGeoPoint& p2, int debug_color = 1);
    void gui_debug_arc(const CGeoPoint& p, double r, double start_angle, double span_angle, int debug_color = 1);
    void gui_debug_triangle(const CGeoPoint& p1, const CGeoPoint& p2, const CGeoPoint& p3, int debug_color = 1);
	void gui_debug_robot(const CGeoPoint& p, double robot_dir);
    void gui_debug_msg(const CGeoPoint& p, const char* msgstr, int debug_color = 1);
    void gui_debug_curve(const double num, const double maxLimit, const double minLimit, int debug_color = 1);
    void send(bool);
private:
    QUdpSocket sendSocket;
    QMutex debugMutex;
};
typedef Singleton < KunDebugEngine > DebugEngine;

#endif // __KUN_DEBUG_ENGINE_H__
