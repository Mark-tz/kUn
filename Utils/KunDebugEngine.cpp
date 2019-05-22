#include "KunDebugEngine.h"
#include <cstring>
#include "zss_debug.pb.h"
#include "staticparams.h"
#include <QString>
namespace{
    Debug_Msgs guiDebugMsgs;
}
KunDebugEngine::KunDebugEngine(){
}
KunDebugEngine::~KunDebugEngine(){
}

void KunDebugEngine::gui_debug_x(const CGeoPoint& p, int debug_color){
	CGeoPoint basePos = p;

	const CGeoPoint p1 = basePos + CVector(5, 5);
	const CGeoPoint p2 = basePos + CVector(-5,-5);
	gui_debug_line(p1, p2, debug_color);

	const CGeoPoint p3 = basePos + CVector(5,-5);
	const CGeoPoint p4 = basePos + CVector(-5, 5);
	gui_debug_line(p3,p4, debug_color);
}
void KunDebugEngine::gui_debug_points(const std::vector<CGeoPoint> points, int debug_color){
    debugMutex.lock();
    Debug_Msg* msg = guiDebugMsgs.add_msgs();
    msg->set_type(Debug_Msg::Debug_Type::Debug_Msg_Debug_Type_Points);
    msg->set_color(Debug_Msg_Color(debug_color));
    Debug_Points* debugPoints = msg->mutable_points();
    for (int i=0; i < points.size(); i++) {
        Point* point = debugPoints->add_point();
        point->set_x(points[i].x());
        point->set_y(points[i].y());
    }
//    qDebug() << "point size: " << points.size();
    debugMutex.unlock();
}
void KunDebugEngine::gui_debug_line(const CGeoPoint& p1, const CGeoPoint& p2, int debug_color){
    debugMutex.lock();
    Debug_Msg* msg = guiDebugMsgs.add_msgs();
    msg->set_type(Debug_Msg::Debug_Type::Debug_Msg_Debug_Type_LINE);
    msg->set_color(Debug_Msg_Color(debug_color));
    Debug_Line* line = msg->mutable_line();
    Point *pos1 = line->mutable_start(), *pos2 = line->mutable_end();
    pos1->set_x(p1.x());
    pos1->set_y(p1.y());
    pos2->set_x(p2.x());
    pos2->set_y(p2.y());
	line->set_back(false);
    line->set_forward(false);
    debugMutex.unlock();
}
void KunDebugEngine::gui_debug_arc(const CGeoPoint& p, double r, double start_angle, double span_angle, int debug_color){
    debugMutex.lock();
    Debug_Msg* msg = guiDebugMsgs.add_msgs();
    msg->set_type(Debug_Msg::Debug_Type::Debug_Msg_Debug_Type_ARC);
    msg->set_color(Debug_Msg_Color(debug_color));
    Debug_Arc* arc = msg->mutable_arc();
	arc->set_start(start_angle);
	arc->set_end(span_angle);
	arc->set_fill(false);
    Rectangle* rec = arc->mutable_rectangle();
    Point *p1 = rec->mutable_point1(), *p2 = rec->mutable_point2();
    PosT center;
    center.x = p.x();
    center.y = p.y();
	p1->set_x(center.x - r);
	p1->set_y(center.y - r);
	p2->set_x(center.x + r);
    p2->set_y(center.y + r);
    debugMutex.unlock();
}
void KunDebugEngine::gui_debug_triangle(const CGeoPoint& p1, const CGeoPoint& p2, const CGeoPoint& p3, int debug_color){
    debugMutex.lock();
    Debug_Msg* msg = guiDebugMsgs.add_msgs();
    msg->set_type(Debug_Msg::Debug_Type::Debug_Msg_Debug_Type_POLYGON);
    msg->set_color(Debug_Msg_Color(debug_color));
    Debug_Polygon* tri = msg->mutable_polygon();
    Point* pos1 = tri->add_vertex();
    Point* pos2 = tri->add_vertex();
    Point* pos3 = tri->add_vertex();
    pos1->set_x(p1.x());
    pos1->set_y(p1.y());
    pos2->set_x(p2.x());
    pos2->set_y(p2.y());
    pos3->set_x(p3.x());
    pos3->set_y(p3.y());
    debugMutex.unlock();
}
void KunDebugEngine::gui_debug_robot(const CGeoPoint& p, double robot_dir){
    debugMutex.lock();
    Debug_Msg* msg = guiDebugMsgs.add_msgs();
    msg->set_type(Debug_Msg::Debug_Type::Debug_Msg_Debug_Type_ROBOT);
    msg->set_color(Debug_Msg_Color(0));
    Debug_Robot* robot = msg->mutable_robot();

	float rdir;
    rdir = robot_dir*180/M_PI; // 转成角度
	robot->set_dir(rdir);

    Point* robot_pos = robot->mutable_pos();

    robot_pos->set_x(p.x());
    robot_pos->set_y(p.y());
    debugMutex.unlock();
}
void KunDebugEngine::gui_debug_msg(const CGeoPoint& p, const char* msgstr, int debug_color)
{
    debugMutex.lock();
    Debug_Msg* msg = guiDebugMsgs.add_msgs();
    msg->set_type(Debug_Msg::Debug_Type::Debug_Msg_Debug_Type_TEXT);
    msg->set_color(Debug_Msg_Color(debug_color));
    Debug_Text* text = msg->mutable_text();
    Point* center = text->mutable_pos();
    center->set_x(p.x());
    center->set_y(p.y());
    text->set_text(msgstr);
    debugMutex.unlock();
}
void KunDebugEngine::gui_debug_curve(const double num, const double maxLimit, const double minLimit, int debug_color)
{
    debugMutex.lock();
    Debug_Msg* msg = guiDebugMsgs.add_msgs();
    msg->set_type(Debug_Msg::Debug_Type::Debug_Msg_Debug_Type_CURVE);
    msg->set_color(Debug_Msg_Color(debug_color));
    Debug_Curve_* curve = msg->mutable_curve();
	curve->set_num(num);
	curve->set_minlimit(minLimit);
	curve->set_maxlimit(maxLimit);
    debugMutex.unlock();
}
void KunDebugEngine::send(bool teamIsBlue){
    static QByteArray data;
    debugMutex.lock();
    int size = guiDebugMsgs.ByteSize();
    data.resize(size);
    guiDebugMsgs.SerializeToArray(data.data(),size);
    debugMutex.unlock();
    int sent_size = 0;
    if(teamIsBlue){
        sent_size = sendSocket.writeDatagram(data,data.size(),QHostAddress(QString::fromStdString(ZSS::LOCAL_ADDRESS)),ZSS::Medusa::DEBUG_MSG_SEND[0]);
    } else {
        sent_size = sendSocket.writeDatagram(data,data.size(),QHostAddress(QString::fromStdString(ZSS::LOCAL_ADDRESS)),ZSS::Medusa::DEBUG_MSG_SEND[1]);
    }
//    std::cout << "size: " << data.size() << ' ' << sent_size << std::endl;
    guiDebugMsgs.clear_msgs();
}
