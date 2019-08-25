#include "utils.h"
#include "WorldModel.h"
#include "param.h"
#include <GDebugEngine.h>
#include <iostream>

namespace Utils{
    double dirDiff(const CVector& v1, const CVector& v2) { return fabs(Normalize(v1.dir() - v2.dir()));}
	double Normalize(double angle)
	{
		if (fabs(angle) > 10 ){
			cout<<angle<<" Normalize Error!!!!!!!!!!!!!!!!!!!!"<<endl;
			return 0;
		}
		const double M_2PI = Param::Math::PI * 2;
		// 快速粗调整
		angle -= (int)(angle / M_2PI) * M_2PI; 
		
		// 细调整 (-PI,PI]
		while( angle > Param::Math::PI ) {
			angle -= M_2PI;
		}

		while( angle <= -Param::Math::PI ) {
			angle += M_2PI;
		}

		return angle;
	}
	CVector Polar2Vector(double m,double angle)
	{
		return CVector(m*std::cos(angle),m*std::sin(angle));
	}
	double VectorDot(const CVector& v1, const CVector& v2)
	{
		return v1.x()*v2.x() + v1.y()*v2.y();
	}
	bool InBetween(const CGeoPoint& p,const CGeoPoint& p1,const CGeoPoint& p2)
	{
		return p.x() >= (std::min)(p1.x(),p2.x()) && p.x() <= (std::max)(p1.x(),p2.x())
			&& p.y() >= (std::min)(p1.y(),p2.y()) && p.y() <= (std::max)(p1.y(),p2.y());
	}
	bool InBetween(double v,double v1,double v2)
	{
		return (v > v1 && v < v2) || (v < v1 && v > v2);
	}
	bool InBetween(const CVector& v, const CVector& v1, const CVector& v2, double buffer)
	{
		
		double d = v.dir(), d1 = v1.dir(), d2 = v2.dir();
		return AngleBetween(d, d1, d2, buffer);
	}

	bool AngleBetween(double d, double d1, double d2, double buffer)
	{
		using namespace Param::Math;
		// d, d1, d2为向量v, v1, v2的方向弧度

		// 当v和v1或v2的角度相差很小,在buffer允许范围之内时,认为满足条件
		double error = (std::min)(std::fabs(Normalize(d-d1)), std::fabs(Normalize(d-d2)));
		if (error < buffer) {
			return true;
		}

		if (std::fabs(d1 - d2) < PI) {
			// 当直接相减绝对值小于PI时, d应该大于小的,小于大的
			return InBetween(d, d1, d2);
		}
		else {
			// 化为上面那种情况
			return InBetween(Normalize(d+PI), Normalize(d1+PI), Normalize(d2+PI));
		}
	}

	CGeoPoint MakeInField(const CGeoPoint& p,const double buffer)
	{
		if( std::fabs(p.y()) < Param::Field::GOAL_WIDTH/2 ){
			double y = ( std::fabs(p.y()) > Param::Field::GOAL_WIDTH/2 - buffer ) ? Sign(p.y()) * (Param::Field::GOAL_WIDTH/2 - buffer) : p.y();
			const double fLeft = FieldLeft() - Param::Field::GOAL_DEPTH + buffer;
			if( p.x() < fLeft ){
				return CGeoPoint(fLeft,y);
			}
			const double fRight = FieldRight() + Param::Field::GOAL_DEPTH - buffer;
			if( p.x() > fRight ){
				return CGeoPoint(fRight,y);
			}
			return p;
		}
		CGeoPoint result = p;
		if( result.x() < FieldLeft() + buffer ){
			result = CGeoPoint(FieldLeft() + buffer,result.y());
		}else if( result.x() > FieldRight() - buffer){
			result = CGeoPoint(FieldRight() - buffer,result.y());
		}
		if( result.y() < FieldTop() + buffer){
			result = CGeoPoint(result.x(),FieldTop() + buffer);
		}else if( result.y() > FieldBottom() - buffer){
			result = CGeoPoint(result.x(),FieldBottom() - buffer);
		}
		return result;
	}
	//modified by Wang in 2018/3/17
	bool InOurPenaltyArea(const CGeoPoint& p, const double buffer) {
        // rectangle penalty
        return (p.x() < -Param::Field::PITCH_LENGTH / 2 +
                Param::Field::PENALTY_AREA_DEPTH + buffer
                &&
                std::fabs(p.y()) <
                Param::Field::PENALTY_AREA_WIDTH / 2 + buffer);
    }
	//modified by Wang in 2018/3/17
	bool InTheirPenaltyArea(const CGeoPoint& p, const double buffer) {
            // rectanlge penalty
        return (p.x() >
                Param::Field::PITCH_LENGTH / 2 -
                Param::Field::PENALTY_AREA_DEPTH - buffer
                &&
                std::fabs(p.y()) <
                Param::Field::PENALTY_AREA_WIDTH / 2 + buffer);
    }


    bool InTheirPenaltyAreaWithVel(const PlayerVisionT& me, const double buffer) {
        CVector vel = me.Vel();
        CGeoPoint pos = me.Pos();
//        GDebugEngine::Instance()->gui_debug_x(pos + Polar2Vector(pow(vel.mod(), 2) / (2 * 400), vel.dir()));
        if (me.Vel().mod() < 30) return InTheirPenaltyArea(me.Pos(), buffer);
        if (InTheirPenaltyArea(pos + Polar2Vector(pow(vel.mod(), 2) / (2 * 400), vel.dir()), buffer)) {
            return true;
        }
        else return false;
    }

	bool OutOfField(const CGeoPoint& p, const double buffer	)	//buffer为正在场内，负在场外
	{
		return p.x() < FieldLeft() + buffer || p.x() > FieldRight() - buffer 
			|| p.y() < FieldTop() + buffer || p.y() > FieldBottom() - buffer;
	}

	//modified by Wang in 2018/3/21
	CGeoPoint MakeOutOfOurPenaltyArea(const CGeoPoint& p, const double buffer) {
        // rectangle penalty
        //右半禁区点
        if (p.y() > 0) {
            //距离禁区上边近，取上边投影
            if (-Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH - p.x() < Param::Field::PENALTY_AREA_WIDTH / 2 - p.y())
                return CGeoPoint(-Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH + 1.2*buffer, p.y());
            //距离禁区右边近，取右边投影
            else return CGeoPoint(p.x(), Param::Field::PENALTY_AREA_WIDTH / 2 + buffer*1.2);
        }
        //左半禁区点
        else {
            //距离禁区上边近，取上边投影
            if (-Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH - p.x() < p.y() - (-Param::Field::PENALTY_AREA_WIDTH / 2) )
                return CGeoPoint(-Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH + 1.2*buffer, p.y());
            //距离禁区左边近，取左边投影
            else return CGeoPoint(p.x(), -Param::Field::PENALTY_AREA_WIDTH / 2 - 1.2*buffer);
        }
		return p;
	}
	//modified by Wang in 2018/3/17
    CGeoPoint MakeOutOfTheirPenaltyArea(const CGeoPoint& p, const double buffer) {
        // rectangle penalty
        CGeoPoint newPoint = p;
        if(newPoint.x() > Param::Field::PITCH_LENGTH / 2)
            newPoint.setX(200);
        //右半禁区点
        if (newPoint.y() > 0) {
            //距离禁区下边近，取下边投影
            if (newPoint.x() - Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH < Param::Field::PENALTY_AREA_WIDTH / 2 - newPoint.y())
                return CGeoPoint(/*200*/Param::Field::PITCH_LENGTH / 2 - Param::Field::PENALTY_AREA_DEPTH - buffer, newPoint.y());
            //距离禁区右边近，取右边投影
            else return CGeoPoint(newPoint.x(), Param::Field::PENALTY_AREA_WIDTH / 2 + buffer);
        }
        //左半禁区点
        else {
            //距离禁区下边近，取下边投影
            if (newPoint.x() - Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH < Param::Field::PENALTY_AREA_WIDTH / 2 - newPoint.y())
                return CGeoPoint(/*200*/Param::Field::PITCH_LENGTH / 2 - Param::Field::PENALTY_AREA_DEPTH - buffer, newPoint.y());
            //距离禁区左边近，取左边投影
            else return CGeoPoint(newPoint.x(), -Param::Field::PENALTY_AREA_WIDTH / 2 - buffer);
        }
        return p;
	}

    CGeoPoint MakeOutOfCircle(const CGeoPoint& center, const double radius, const CGeoPoint& start, const CGeoPoint& target, const double buffer) {
        CGeoPoint p(target);
        CVector adjustDir = start - target;
        adjustDir = adjustDir / adjustDir.mod();
        double adjustUnit = 0.5;
        while(p.dist(center) < radius + buffer)
            p = p + adjustDir * adjustUnit;
        return p;
    }

    CGeoPoint MakeOutOfLongCircle(const CGeoPoint& seg_start, const CGeoPoint& seg_end, const double radius, const CGeoPoint& start, const CGeoPoint& target, const double buffer) {
        CGeoSegment segment(seg_start, seg_end);
        CGeoPoint p(target);
        CVector adjustDir = start - target;
        adjustDir = adjustDir / adjustDir.mod();
        double adjustUnit = 0.5;
        while(segment.dist2Point(p) < radius + buffer)
            p = p + adjustDir * adjustUnit;
        return p;
    }



	CGeoPoint MakeOutOfCircleAndInField(const CGeoPoint& center,const double radius,const CGeoPoint& p,const double buffer)
	{
		const CVector p2c = p - center;
		const double dist = p2c.mod();
		if( dist > radius + buffer || dist < 0.01 ){ // 不在圆内
			return p;
		}
		CGeoPoint newPos(center + p2c * (radius + buffer) / dist);
		CGeoRectangle fieldRect(FieldLeft() + buffer,FieldTop() + buffer,FieldRight() - buffer,FieldBottom() - buffer);
		if( !fieldRect.HasPoint(newPos) ){ // 在场外,选择距离最近且不在圆内的场内点
			CGeoCirlce avoidCircle(center,radius + buffer);
			std::vector< CGeoPoint > intPoints;
			for(int i=0; i<4; ++i){
				CGeoLine fieldLine(fieldRect._point[i % 4],fieldRect._point[(i+1) % 4]);
				CGeoLineCircleIntersection fieldLineCircleInt(fieldLine,avoidCircle);
				if( fieldLineCircleInt.intersectant() ){
					intPoints.push_back(fieldLineCircleInt.point1());
					intPoints.push_back(fieldLineCircleInt.point2());
				}
			}
			double minDist = 1000.0;
			CGeoPoint minPoint = newPos;
			for( unsigned int i=0; i<intPoints.size(); ++i ){
				double cDist = p.dist(intPoints[i]);
				if( cDist < minDist ){
					minDist = cDist;
					minPoint = intPoints[i];
				}
			}
			return minPoint;
		}

		return newPos; // 圆外距离p最近的点
	}


	bool PlayerNumValid(int num)
	{
		if (num>=1 && num<=Param::Field::MAX_PLAYER){
			return true;
		}
		else{
			return false;
		}
	}
	// 给定一个球门线上的点, 一个方向(角度), 找出一个在禁区外防守该方向的
	// 离禁区线较近的点
	CGeoPoint GetOutSidePenaltyPos(double dir, double delta, const CGeoPoint targetPoint)
	{	
		//double delta = Param::Field::MAX_PLAYER_SIZE + 1.5;
		CGeoPoint pInter = GetInterPos(dir, targetPoint);
		CGeoPoint pDefend = pInter + Polar2Vector(delta, dir);
		return pDefend;
	}

	CGeoPoint GetOutTheirSidePenaltyPos(double dir, double delta, const CGeoPoint& targetPoint) {
        CGeoPoint pInter = GetTheirInterPos(dir, targetPoint);
		return (pInter + Polar2Vector(delta, dir));
	}

	// GetDefendPos的处理细节
	// 给定点和方向求它和禁区线的交点
	//给定点需在禁区内
	//modified by Wang in 2018/3/17
	CGeoPoint GetInterPos(double dir, const CGeoPoint targetPoint) {
		using namespace Param::Field;
        if ( IF_USE_ELLIPSE ){
            // ellipse penalty
            // 禁区的两段圆弧,用圆来表示
            CGeoCirlce c1(CGeoPoint(-PITCH_LENGTH/2,  PENALTY_AREA_L/2), PENALTY_AREA_R);
            CGeoCirlce c2(CGeoPoint(-PITCH_LENGTH/2, -PENALTY_AREA_L/2), PENALTY_AREA_R);
            CGeoPoint targetPointInstead = targetPoint;
            if (dir >= Param::Math::PI/2 - 5/180*Param::Math::PI && dir <= Param::Math::PI)
        return CGeoPoint(-PITCH_LENGTH/2,PENALTY_AREA_L/2+PENALTY_AREA_R);
            else if (dir <= -Param::Math::PI/2 + 5/180*Param::Math::PI && dir >= -Param::Math::PI)
                return CGeoPoint(-PITCH_LENGTH/2,-PENALTY_AREA_L/2-PENALTY_AREA_R);

            // 连接两段圆弧的直线(pLine),用直线来表示
            CGeoPoint pend1(-PITCH_LENGTH/2+PENALTY_AREA_R,  PENALTY_AREA_L/2);
            CGeoPoint pend2(-PITCH_LENGTH/2+PENALTY_AREA_R, -PENALTY_AREA_L/2);
            CGeoLine pLine(pend1, pend2);
            // 过给定的点和方向, 作一条直线
            CGeoLine dirLine(targetPointInstead, dir);

            // 求该直线和c1的交点
            if (targetPoint.y() == c1.Center().y())
            {
                if (dir>=0 && dir<Param::Math::PI/2)
                {
                    CGeoPoint p = c1.Center()+Polar2Vector(PENALTY_AREA_R,dir);
                    return p;
                }
            }
            else{
                CGeoLineCircleIntersection dirLine_c1_inter(dirLine, c1);
                if (dirLine_c1_inter.intersectant())
                {
                    CGeoPoint p1 = dirLine_c1_inter.point1();
                    CGeoPoint p2 = dirLine_c1_inter.point2();
                    double dir1 = Normalize((p1-c1.Center()).dir());
                    double dir2 = Normalize((p2-c1.Center()).dir());
                    if (dir1>=0 && dir1<=Param::Math::PI/2)
                    {
                        return p1;

                    }
                    else if (dir2>=0 && dir2<=Param::Math::PI/2)
                    {
                        return p2;

                    }
                }
            }

            // 求该直线和c2的交点
            if (targetPoint.y() == c2.Center().y())
            {
                if ( dir<=0 && dir>(-Param::Math::PI/2))
                {
                    CGeoPoint p = c2.Center()+Polar2Vector(PENALTY_AREA_R,dir);
                    return p;
                }
            }
            else{
                CGeoLineCircleIntersection dirLine_c2_inter(dirLine, c2);
                if (dirLine_c2_inter.intersectant())
                {
                    CGeoPoint p1 = dirLine_c2_inter.point1();
                    CGeoPoint p2 = dirLine_c2_inter.point2();
                    double dir1 = Normalize((p1-c2.Center()).dir());
                    double dir2 = Normalize((p2-c2.Center()).dir());
                    if (dir1>=(-Param::Math::PI/2) && dir1<=0)
                    {
                        return p1;

                    }
                    else if (dir2>=(-Param::Math::PI/2) && dir2<=0)
                    {
                        return p2;

                    }
                }
            }
            // 求该直线和连接两条圆弧的线段pLine的交点
            CGeoLineLineIntersection pline_dirline_inter(pLine, dirLine);
            if (pline_dirline_inter.Intersectant())
            {
                CGeoPoint p = pline_dirline_inter.IntersectPoint();
                if (p.y() <= pend1.y() && p.y() >= pend2.y())
                {
                    return p;

                }
            }
            //// 返回一个默认点,禁区顶部的中点
//            std::cout<<"our default pos!!"<<std::endl;
            return CGeoPoint(-PITCH_LENGTH/2+PENALTY_AREA_R, 0);
        }
        else {
            // rectangle penalty
            CGeoPoint p1(-PITCH_LENGTH / 2, -PENALTY_AREA_WIDTH / 2);//禁区左下
            CGeoPoint p2(-PITCH_LENGTH / 2 + PENALTY_AREA_DEPTH, -PENALTY_AREA_WIDTH / 2);//禁区左上
            CGeoPoint p3(-PITCH_LENGTH / 2 + PENALTY_AREA_DEPTH, PENALTY_AREA_WIDTH / 2);//禁区右上
            CGeoPoint p4(-PITCH_LENGTH / 2, PENALTY_AREA_WIDTH / 2);//禁区右下
            CGeoLine line1(p1, p2);//禁区左边线
            CGeoLine line2(p2, p3);//禁区前边线
            CGeoLine line3(p3, p4);//禁区右边线
            CGeoLine dirLine(targetPoint, dir);

            CGeoLineLineIntersection inter1(line1, dirLine);
            CGeoLineLineIntersection inter2(line2, dirLine);
            CGeoLineLineIntersection inter3(line3, dirLine);

            CGeoPoint inter_p1 = inter1.IntersectPoint();
            GDebugEngine::Instance()->gui_debug_x(inter_p1, 3);//黄
            CGeoPoint inter_p2 = inter2.IntersectPoint();
            GDebugEngine::Instance()->gui_debug_x(inter_p2, 4);//绿
            CGeoPoint inter_p3 = inter3.IntersectPoint();
            GDebugEngine::Instance()->gui_debug_x(inter_p3, 9);//黑
            CGeoPoint returnPoint = targetPoint;//返回值

            //if (targetPoint.x() >= -PITCH_LENGTH / 2 + PENALTY_AREA_DEPTH) {
            if (targetPoint.y() <= 0) {//case 1
                if (InOurPenaltyArea(inter_p1, 10)) returnPoint = inter_p1;
                else returnPoint = inter_p2;
            }
            else {//case 2
                if (InOurPenaltyArea(inter_p3, 10)) returnPoint = inter_p3;
                else returnPoint = inter_p2;//随便选的
            }
            GDebugEngine::Instance()->gui_debug_x(returnPoint, 0);
            CGeoPoint p0(-PITCH_LENGTH / 2, 0);
            GDebugEngine::Instance()->gui_debug_line(returnPoint, p0, 0);
            return returnPoint;
        }
		//}
		/*
		else if (std::fabs(targetPoint.y()) <= PENALTY_AREA_WIDTH / 2) {//case 3
			if (InOurPenaltyArea(inter_p2, 0)) return inter_p2;
			else return p2;//随便选的
		}
		else {
			if (targetPoint.y() <= 0) {//case 4
				if (InOurPenaltyArea(inter_p1, 0)) return inter_p1;
				else if (InOurPenaltyArea(inter_p2, 0)) return inter_p2;
				else return p2;//随便选的
			}
			else {//case 5
				if (InOurPenaltyArea(inter_p2, 0)) return inter_p2;
				else if (InOurPenaltyArea(inter_p3, 0)) return inter_p3;
				else return p3;//随便选的
			}
		}
		*/
	}
	//modified by Wang in 2018/3/17
    CGeoPoint GetTheirInterPos(double dir, const CGeoPoint& targetPoint) {
        using namespace Param::Field;
        if ( IF_USE_ELLIPSE ){
            // ellipse penalty
            // 禁区的两段圆弧,用圆来表示
            CGeoCirlce c1(CGeoPoint(-PITCH_LENGTH/2,  PENALTY_AREA_L/2), PENALTY_AREA_R);
            CGeoCirlce c2(CGeoPoint(-PITCH_LENGTH/2, -PENALTY_AREA_L/2), PENALTY_AREA_R);
            CGeoPoint targetPointInstead = targetPoint;
            if (dir >= Param::Math::PI/2 - 5/180*Param::Math::PI && dir <= Param::Math::PI)
                return CGeoPoint(-PITCH_LENGTH/2,PENALTY_AREA_L/2+PENALTY_AREA_R);
            else if (dir <= -Param::Math::PI/2 + 5/180*Param::Math::PI && dir >= -Param::Math::PI)
                return CGeoPoint(-PITCH_LENGTH/2,-PENALTY_AREA_L/2-PENALTY_AREA_R);

            // 连接两段圆弧的直线(pLine),用直线来表示
            CGeoPoint pend1(-PITCH_LENGTH/2+PENALTY_AREA_R,  PENALTY_AREA_L/2);
            CGeoPoint pend2(-PITCH_LENGTH/2+PENALTY_AREA_R, -PENALTY_AREA_L/2);
            CGeoLine pLine(pend1, pend2);
            // 过给定的点和方向, 作一条直线
            CGeoLine dirLine(targetPointInstead, dir);

            // 求该直线和c1的交点
            if (targetPoint.y() == c1.Center().y())
            {
                if (dir>=0 && dir<Param::Math::PI/2)
                {
                    CGeoPoint p = c1.Center()+Polar2Vector(PENALTY_AREA_R,dir);
                    return p;
                }
            }
            else{
                CGeoLineCircleIntersection dirLine_c1_inter(dirLine, c1);
                if (dirLine_c1_inter.intersectant())
                {
                    CGeoPoint p1 = dirLine_c1_inter.point1();
                    CGeoPoint p2 = dirLine_c1_inter.point2();
                    double dir1 = Normalize((p1-c1.Center()).dir());
                    double dir2 = Normalize((p2-c1.Center()).dir());
                    if (dir1>=0 && dir1<=Param::Math::PI/2)
                    {
                        return p1;

                    }
                    else if (dir2>=0 && dir2<=Param::Math::PI/2)
                    {
                        return p2;

                    }
                }
            }

            // 求该直线和c2的交点
            if (targetPoint.y() == c2.Center().y())
            {
                if ( dir<=0 && dir>(-Param::Math::PI/2))
                {
                    CGeoPoint p = c2.Center()+Polar2Vector(PENALTY_AREA_R,dir);
                    return p;
                }
            }
            else{
                CGeoLineCircleIntersection dirLine_c2_inter(dirLine, c2);
                if (dirLine_c2_inter.intersectant())
                {
                    CGeoPoint p1 = dirLine_c2_inter.point1();
                    CGeoPoint p2 = dirLine_c2_inter.point2();
                    double dir1 = Normalize((p1-c2.Center()).dir());
                    double dir2 = Normalize((p2-c2.Center()).dir());
                    if (dir1>=(-Param::Math::PI/2) && dir1<=0)
                    {
                        return p1;

                    }
                    else if (dir2>=(-Param::Math::PI/2) && dir2<=0)
                    {
                        return p2;

                    }
                }
            }
            // 求该直线和连接两条圆弧的线段pLine的交点
            CGeoLineLineIntersection pline_dirline_inter(pLine, dirLine);
            if (pline_dirline_inter.Intersectant())
            {
                CGeoPoint p = pline_dirline_inter.IntersectPoint();
                if (p.y() <= pend1.y() && p.y() >= pend2.y())
                {
                    return p;

                }
            }
            //// 返回一个默认点,禁区顶部的中点
//            std::cout<<"our default pos!!"<<std::endl;
            return CGeoPoint(-PITCH_LENGTH/2+PENALTY_AREA_R, 0);
        }
        else{
            // rectangle penalty
            CGeoPoint p1(PITCH_LENGTH / 2, -PENALTY_AREA_WIDTH / 2);//禁区左上
            CGeoPoint p2(PITCH_LENGTH / 2 - PENALTY_AREA_DEPTH, -PENALTY_AREA_WIDTH / 2);//禁区左下
            CGeoPoint p3(PITCH_LENGTH / 2 - PENALTY_AREA_DEPTH, PENALTY_AREA_WIDTH / 2);//禁区右下
            CGeoPoint p4(PITCH_LENGTH / 2, PENALTY_AREA_WIDTH / 2);//禁区右上
            CGeoLine line1(p1, p2);//禁区左边线
            CGeoLine line2(p2, p3);//禁区下边线
            CGeoLine line3(p3, p4);//禁区右边线
            CGeoLine dirLine(targetPoint, dir);

            CGeoLineLineIntersection inter1(line1, dirLine);
            CGeoLineLineIntersection inter2(line2, dirLine);
            CGeoLineLineIntersection inter3(line3, dirLine);

            CGeoPoint inter_p1 = inter1.IntersectPoint();
            CGeoPoint inter_p2 = inter2.IntersectPoint();
            CGeoPoint inter_p3 = inter3.IntersectPoint();
            CGeoPoint returnPoint = targetPoint;//返回值

            if (targetPoint.x() >= PITCH_LENGTH / 2 - PENALTY_AREA_DEPTH) {
                if (targetPoint.y() <= 0) {//case 1
                    if (InOurPenaltyArea(inter_p1, 0)) return inter_p1;
                    else return p2;//随便选的
                }
                else {//case 2
                    if (InOurPenaltyArea(inter_p3, 0)) return inter_p3;
                    else return p3;//随便选的
                }
            }
            else if (std::fabs(targetPoint.y()) <= PENALTY_AREA_WIDTH / 2) {//case 3
                if (InOurPenaltyArea(inter_p2, 0)) return inter_p2;
                else return p2;//随便选的
            }
            else {
                if (targetPoint.y() <= 0) {//case 4
                    if (InOurPenaltyArea(inter_p1, 0)) return inter_p1;
                    else if (InOurPenaltyArea(inter_p2, 0)) return inter_p2;
                    else return p2;//随便选的
                }
                else {//case 5
                    if (InOurPenaltyArea(inter_p2, 0)) return inter_p2;
                    else if (InOurPenaltyArea(inter_p3, 0)) return inter_p3;
                    else return p3;//随便选的
                }
            }
        }
	}
	/*
	CGeoPoint GetInterPos(double dir, const CGeoPoint targetPoint)
	{
		using namespace Param::Field;
		if (Param::Rule::Version == 2008)
		{
			// 禁区的两段圆弧,用圆来表示
			CGeoCirlce c1(CGeoPoint(-PITCH_LENGTH/2,  PENALTY_AREA_L/2), PENALTY_AREA_R); 
			CGeoCirlce c2(CGeoPoint(-PITCH_LENGTH/2, -PENALTY_AREA_L/2), PENALTY_AREA_R);
			CGeoPoint targetPointInstead = targetPoint;
			if (dir >= Param::Math::PI/2 - 5/180*Param::Math::PI && dir <= Param::Math::PI)
        return CGeoPoint(-PITCH_LENGTH/2,PENALTY_AREA_L/2+PENALTY_AREA_R);
			else if (dir <= -Param::Math::PI/2 + 5/180*Param::Math::PI && dir >= -Param::Math::PI)
				return CGeoPoint(-PITCH_LENGTH/2,-PENALTY_AREA_L/2-PENALTY_AREA_R);

			// 连接两段圆弧的直线(pLine),用直线来表示
			CGeoPoint pend1(-PITCH_LENGTH/2+PENALTY_AREA_R,  PENALTY_AREA_L/2);
			CGeoPoint pend2(-PITCH_LENGTH/2+PENALTY_AREA_R, -PENALTY_AREA_L/2);
			CGeoLine pLine(pend1, pend2);
			// 过给定的点和方向, 作一条直线
			CGeoLine dirLine(targetPointInstead, dir);

			// 求该直线和c1的交点
			if (targetPoint.y() == c1.Center().y())
			{
				if (dir>=0 && dir<Param::Math::PI/2)
				{
					CGeoPoint p = c1.Center()+Polar2Vector(PENALTY_AREA_R,dir);
					return p;
				}         
			}
			else{
				CGeoLineCircleIntersection dirLine_c1_inter(dirLine, c1);
				if (dirLine_c1_inter.intersectant())
				{
					CGeoPoint p1 = dirLine_c1_inter.point1();
					CGeoPoint p2 = dirLine_c1_inter.point2();
					double dir1 = Normalize((p1-c1.Center()).dir());
					double dir2 = Normalize((p2-c1.Center()).dir());
					if (dir1>=0 && dir1<=Param::Math::PI/2)
					{ 
						return p1;

					} 
					else if (dir2>=0 && dir2<=Param::Math::PI/2)
					{
						return p2;

					}
				}
			}
			
			// 求该直线和c2的交点
			if (targetPoint.y() == c2.Center().y())
			{
				if ( dir<=0 && dir>(-Param::Math::PI/2))
				{
					CGeoPoint p = c2.Center()+Polar2Vector(PENALTY_AREA_R,dir);
					return p;
				}	
			}
			else{
				CGeoLineCircleIntersection dirLine_c2_inter(dirLine, c2);
				if (dirLine_c2_inter.intersectant())
				{
					CGeoPoint p1 = dirLine_c2_inter.point1();
					CGeoPoint p2 = dirLine_c2_inter.point2();
					double dir1 = Normalize((p1-c2.Center()).dir());
					double dir2 = Normalize((p2-c2.Center()).dir());
					if (dir1>=(-Param::Math::PI/2) && dir1<=0)
					{
						return p1;

					} 
					else if (dir2>=(-Param::Math::PI/2) && dir2<=0)
					{
						return p2;

					}
				}
			}
			// 求该直线和连接两条圆弧的线段pLine的交点
			CGeoLineLineIntersection pline_dirline_inter(pLine, dirLine);
			if (pline_dirline_inter.Intersectant())
			{
				CGeoPoint p = pline_dirline_inter.IntersectPoint();
				if (p.y() <= pend1.y() && p.y() >= pend2.y())
				{
					return p;

				}
			}
			//// 返回一个默认点,禁区顶部的中点
			std::cout<<"our default pos!!"<<std::endl;
			return CGeoPoint(-PITCH_LENGTH/2+PENALTY_AREA_R, 0);
    }
		else if (Param::Rule::Version == 2004)
		{
			CGeoCirlce penaltyCircle(CGeoPoint(-PITCH_LENGTH/2, 0),PENALTY_AREA_WIDTH/2);
			CGeoLine dirLine(targetPoint,dir);
			CGeoLineCircleIntersection dirLine_penaltyCircle(dirLine,penaltyCircle);
			if (dirLine_penaltyCircle.intersectant())
			{
				CGeoPoint p = Utils::OutOfField(dirLine_penaltyCircle.point1())?dirLine_penaltyCircle.point2():dirLine_penaltyCircle.point1();
				return p;
			}		
		}			
		return CGeoPoint(-PITCH_LENGTH/2+PENALTY_AREA_WIDTH/2, 0);
	}

	CGeoPoint GetTheirInterPos(double dir, const CGeoPoint& targetPoint) {
		using namespace Param::Field;
		// 禁区的两段圆弧,用圆来表示
		CGeoCirlce c1(CGeoPoint(PITCH_LENGTH/2, PENALTY_AREA_L/2), PENALTY_AREA_R); 
		CGeoCirlce c2(CGeoPoint(PITCH_LENGTH/2, -PENALTY_AREA_L/2), PENALTY_AREA_R);
		if (dir <= Param::Math::PI/2 + 5/180*Param::Math::PI && dir >= 0)
			return CGeoPoint(PITCH_LENGTH/2, PENALTY_AREA_L/2 + PENALTY_AREA_R);
		else if	 (dir >= -Param::Math::PI - 5/180*Param::Math::PI	&& dir <= 0)
			return CGeoPoint(PITCH_LENGTH/2, -(PENALTY_AREA_L/2 + PENALTY_AREA_R));

		// 连接两段圆弧的直线(pLine),用直线来表示
		CGeoPoint pend1(PITCH_LENGTH/2 - PENALTY_AREA_R, PENALTY_AREA_L/2);
		CGeoPoint pend2(PITCH_LENGTH/2 - PENALTY_AREA_R, -PENALTY_AREA_L/2);
		CGeoLine pLine(pend1, pend2);
		// 过给定的点和方向, 作一条直线
		CGeoLine dirLine(targetPoint, dir);

		// 求该直线和c1的交点
		if (abs(targetPoint.y() - c1.Center().y()) < 0.0001) {
			if (dir > Param::Math::PI/2 && dir < Param::Math::PI) {
				CGeoPoint p = c1.Center() + Polar2Vector(PENALTY_AREA_R, dir);
				return p;
			}
		} else {
			CGeoLineCircleIntersection dirLine_c1_inter(dirLine, c1);
			if (dirLine_c1_inter.intersectant()) {
				CGeoPoint p1 = dirLine_c1_inter.point1();
				CGeoPoint p2 = dirLine_c1_inter.point2();
				double dir1 = Normalize((p1-c1.Center()).dir());
				double dir2 = Normalize((p2-c1.Center()).dir());
				if (dir1 >= Param::Math::PI / 2 && dir1 <= Param::Math::PI)
					return p1;
				else if (dir2 >= Param::Math::PI / 2 && dir2 <= Param::Math::PI)
					return p2;
			}
		}
		// 求该直线和c2的交点
		if (abs(targetPoint.y() - c2.Center().y()) < 0.0001) {
			if (dir < -Param::Math::PI/2 && dir > -Param::Math::PI) {
				CGeoPoint p = c2.Center() + Polar2Vector(PENALTY_AREA_R, dir);
				return p;
			}
		} else {
			CGeoLineCircleIntersection dirLine_c2_inter(dirLine, c2);
			if (dirLine_c2_inter.intersectant()) {
				CGeoPoint p1 = dirLine_c2_inter.point1();
				CGeoPoint p2 = dirLine_c2_inter.point2();
				double dir1 = Normalize((p1-c2.Center()).dir());
				double dir2 = Normalize((p2-c2.Center()).dir());
				if (dir1 <= -Param::Math::PI/2 && dir1 >= -Param::Math::PI)
					return p1;
				else if (dir2 <= -Param::Math::PI/2 && dir2 >= -Param::Math::PI)
					return p2;
			}
		}
		// 求该直线和连接两条圆弧的线段pLine的交点
		CGeoLineLineIntersection pline_dirline_inter(pLine, dirLine);
		if (pline_dirline_inter.Intersectant()) {
			CGeoPoint p = pline_dirline_inter.IntersectPoint();
			if (p.y() <= pend1.y() && p.y() >= pend2.y())
				return p;
		}
		//// 返回一个默认点,禁区顶部的中点
		std::cout<<"our default pos!!"<<std::endl;
		return CGeoPoint(PITCH_LENGTH / 2 - PENALTY_AREA_R, 0);
	}
	*/
	float SquareRootFloat(float number) {
		long i;
		float x, y;
		const float f = 1.5F;

		x = number * 0.5F;
		y  = number;
		i  = * ( long * ) &y;
		i  = 0x5f3759df - ( i >> 1 );
		y  = * ( float * ) &i;
		y  = y * ( f - ( x * y * y ) );
		y  = y * ( f - ( x * y * y ) );
		return number * y;
	}
	bool canGo(const CVisionModule* pVision, const int vecNumber, const CGeoPoint& target, const int flags, const double avoidBuffer)//判断是否可以直接到达目标点
	{
		static bool _canGo = true;
		const CGeoPoint& vecPos = pVision->OurPlayer(vecNumber).Pos();
		CGeoSegment moving_seg(vecPos, target);
		const double minBlockDist2 = (Param::Field::MAX_PLAYER_SIZE/2 + avoidBuffer) * (Param::Field::MAX_PLAYER_SIZE/2 + avoidBuffer);
		for( int i=1; i<=Param::Field::MAX_PLAYER * 2; ++i ){ // 看路线上有没有人
			if( i == vecNumber || !pVision->AllPlayer(i).Valid()){
				continue;
			}
			const CGeoPoint& obs_pos = pVision->AllPlayer(i).Pos();
			if( (obs_pos - target).mod2() < minBlockDist2 ){
				_canGo = false;
				return _canGo;
			}
			CGeoPoint prj_point = moving_seg.projection(obs_pos);
			if( moving_seg.IsPointOnLineOnSegment(prj_point) ){
				const double blockedDist2 = (obs_pos - prj_point).mod2();
				if( blockedDist2 < minBlockDist2 && blockedDist2 < (obs_pos - vecPos).mod2()){
					_canGo = false;
					return _canGo;
				}
			}
		}
		if( _canGo && (flags & PlayerStatus::DODGE_BALL) ){ // 躲避球
			const CGeoPoint& obs_pos = pVision->Ball().Pos();
			CGeoPoint prj_point = moving_seg.projection(obs_pos);
			if( obs_pos.dist(prj_point) < avoidBuffer + Param::Field::BALL_SIZE && moving_seg.IsPointOnLineOnSegment(prj_point) ){
				_canGo = false;
				return _canGo;
			}
		}
		if( _canGo && (flags & PlayerStatus::DODGE_OUR_DEFENSE_BOX) ){ // 避免进入本方禁区
			if( Param::Rule::Version == 2003 ){	// 2003年的规则禁区是矩形
				CGeoRectangle defenseBox(-Param::Field::PITCH_LENGTH/2, -Param::Field::PENALTY_AREA_WIDTH/2 - avoidBuffer, -Param::Field::PITCH_LENGTH/2 + Param::Field::PENALTY_AREA_WIDTH + avoidBuffer, Param::Field::PENALTY_AREA_WIDTH/2 + avoidBuffer);
				CGeoLineRectangleIntersection intersection(moving_seg, defenseBox);
				if( intersection.intersectant() ){
					if( moving_seg.IsPointOnLineOnSegment(intersection.point1()) || moving_seg.IsPointOnLineOnSegment(intersection.point2())){
						_canGo = false; // 要经过禁区
						return _canGo;
					}
				}
			}else if (Param::Rule::Version == 2004) { // 2004年的规则禁区是半圆形
				CGeoCirlce defenseBox(CGeoPoint(-Param::Field::PITCH_LENGTH/2, 0), Param::Field::PENALTY_AREA_WIDTH/2 + avoidBuffer);
				CGeoLineCircleIntersection intersection(moving_seg, defenseBox);
				if( intersection.intersectant() ){
					if( moving_seg.IsPointOnLineOnSegment(intersection.point1()) || moving_seg.IsPointOnLineOnSegment(intersection.point2())){
						_canGo = false; // 要经过禁区
						return _canGo;
					}
				}
			}
            // 2019, china open, ellipse penalty
            else if (Param::Rule::Version == 2019 &&
                     Param::Field::IF_USE_ELLIPSE) {
                CGeoCirlce c1(CGeoPoint(-Param::Field::PITCH_LENGTH/2,
                                        Param::Field::PENALTY_AREA_L/2),
                              Param::Field::PENALTY_AREA_R + avoidBuffer);
                CGeoCirlce c2(CGeoPoint(-Param::Field::PITCH_LENGTH/2,
                                        -Param::Field::PENALTY_AREA_L/2),
                              Param::Field::PENALTY_AREA_R + avoidBuffer);
                CGeoRectangle defenseBox(
                            -Param::Field::PITCH_LENGTH / 2 +
                            Param::Field::PENALTY_AREA_R +
                            avoidBuffer,
                            -Param::Field::PENALTY_AREA_L / 2,
                            -Param::Field::PITCH_LENGTH / 2,
                            Param::Field::PENALTY_AREA_L/ 2);
                CGeoLineCircleIntersection intersection1(moving_seg, c1);
                CGeoLineCircleIntersection intersection2(moving_seg, c2);
                CGeoLineRectangleIntersection intersection3(moving_seg,
                                                           defenseBox);
                if (intersection1.intersectant() ||
                        intersection2.intersectant() ||
                        intersection3.intersectant()) {
                    if (moving_seg.IsPointOnLineOnSegment(intersection1.point1()) ||
                            moving_seg.IsPointOnLineOnSegment(intersection1.point2())||
                            moving_seg.IsPointOnLineOnSegment(intersection2.point1())||
                            moving_seg.IsPointOnLineOnSegment(intersection2.point2())||
                            moving_seg.IsPointOnLineOnSegment(intersection3.point1())||
                            moving_seg.IsPointOnLineOnSegment(intersection3.point2())) {
                        _canGo = false; // 要经过禁区
                        return _canGo;
                    }
                }

            }
            else {// 2018年的规则禁区是矩形
				CGeoRectangle defenseBox(-Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH + avoidBuffer, -Param::Field::PENALTY_AREA_WIDTH / 2 - avoidBuffer, -Param::Field::PITCH_LENGTH / 2, Param::Field::PENALTY_AREA_WIDTH / 2 + avoidBuffer);
				CGeoLineRectangleIntersection intersection(moving_seg, defenseBox);
				if (intersection.intersectant()) {
					if (moving_seg.IsPointOnLineOnSegment(intersection.point1()) || moving_seg.IsPointOnLineOnSegment(intersection.point2())) {
						_canGo = false; // 要经过禁区
						return _canGo;
					}
				}
			}
		}
		return _canGo;
	}
}

