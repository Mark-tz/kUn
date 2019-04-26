/*
** Lua binding: zeus
** Generated automatically by tolua++-1.0.93 on Fri Apr 26 14:43:22 2019.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_zeus_open (lua_State* tolua_S);

#include <iostream>
#include <iomanip>
#include <cmath>
#include <geometry.h>
#include "Global.h"
#include <geometry.h>
#include "WorldDefine.h"
#include <param.h>
#include <WorldDefine.h>
#include <PlayerCommand.h>
#include "BallPredictor.h"
#include "RobotPredictor.h"
#include <game_state.h>
#include <ServerInterface.h>
#include <OptionModule.h>
#include "utils.h"
#include <VisionModule.h>
#include <singleton.h>
#include <geometry.h>
#include <queue>
#include "GDebugEngine.h"
#include "OptionModule.h"
#include "VisionModule.h"
#include <singleton.h>
#include "defence/EnemySituation.h"
#include "WorldModel.h"
#include <param.h>
#include <singleton.h>
#include "KickStatus.h"
#include <singleton.h>
#include <geometry.h>
#include <param.h>
#include <skill/PlayerTask.h>
#include "utils.h"
#include "TaskMediator.h"
#include "referee_commands.h"
#include "game_state.h"
#include <param.h>
#include <geometry.h>
#include <singleton.h>
#include <DribbleStatus.h>
#include <geometry.h>
#include <param.h>
#include "rolematch/munkres.h"
#include "KickDirection.h"
#include "DefendUtils.h"
#include <fstream>
#include <MultiThread.h>
#include <singleton.h>
#include "VisionModule.h"
#include "geometry.h"
#include "gpuBestAlgThread.h"
#include "DefPos2015.h"
#include "TandemPos.h"
#include <geometry.h>
#include <VisionModule.h>
#include <param.h>
#include "BestPlayer.h"
#include "defence/DefenceInfo.h"
#include "NormalPlayUtils.h"
#include "gpuBestAlgThread.h"
#include "TaskMediator.h"
#include "IndirectDefender.h"
#include "SupportPos.h"
#include "AssistPoint.h"
#include "VisionModule.h"
#include "singleton.h"
#include "WorldModel.h"
#include "messidecision.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_CGPUBestAlgThread (lua_State* tolua_S)
{
 CGPUBestAlgThread* self = (CGPUBestAlgThread*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CIndirectDefender (lua_State* tolua_S)
{
 CIndirectDefender* self = (CIndirectDefender*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CBestPlayer (lua_State* tolua_S)
{
 CBestPlayer* self = (CBestPlayer*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CKickDirection (lua_State* tolua_S)
{
 CKickDirection* self = (CKickDirection*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CDefenceInfo (lua_State* tolua_S)
{
 CDefenceInfo* self = (CDefenceInfo*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CSupportPos (lua_State* tolua_S)
{
 CSupportPos* self = (CSupportPos*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CVector (lua_State* tolua_S)
{
 CVector* self = (CVector*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_TwoKickPos (lua_State* tolua_S)
{
 TwoKickPos* self = (TwoKickPos*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CMessiDecision (lua_State* tolua_S)
{
 CMessiDecision* self = (CMessiDecision*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CTandemPos (lua_State* tolua_S)
{
 CTandemPos* self = (CTandemPos*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_PlayerPoseT (lua_State* tolua_S)
{
 PlayerPoseT* self = (PlayerPoseT*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CGeoLineRectangleIntersection (lua_State* tolua_S)
{
 CGeoLineRectangleIntersection* self = (CGeoLineRectangleIntersection*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CGeoLine (lua_State* tolua_S)
{
 CGeoLine* self = (CGeoLine*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CGeoSegment (lua_State* tolua_S)
{
 CGeoSegment* self = (CGeoSegment*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CDefPos2015 (lua_State* tolua_S)
{
 CDefPos2015* self = (CDefPos2015*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CTaskMediator (lua_State* tolua_S)
{
 CTaskMediator* self = (CTaskMediator*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CAssistPoint (lua_State* tolua_S)
{
 CAssistPoint* self = (CAssistPoint*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CKickStatus (lua_State* tolua_S)
{
 CKickStatus* self = (CKickStatus*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CVisionModule (lua_State* tolua_S)
{
 CVisionModule* self = (CVisionModule*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Munkres (lua_State* tolua_S)
{
 Munkres* self = (Munkres*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Matrix_double_ (lua_State* tolua_S)
{
 Matrix<double>* self = (Matrix<double>*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CGeoPoint (lua_State* tolua_S)
{
 CGeoPoint* self = (CGeoPoint*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_GameState (lua_State* tolua_S)
{
 GameState* self = (GameState*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_ObjectPoseT (lua_State* tolua_S)
{
 ObjectPoseT* self = (ObjectPoseT*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CDribbleStatus (lua_State* tolua_S)
{
 CDribbleStatus* self = (CDribbleStatus*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Defend2015 (lua_State* tolua_S)
{
 Defend2015* self = (Defend2015*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CGeoLineLineIntersection (lua_State* tolua_S)
{
 CGeoLineLineIntersection* self = (CGeoLineLineIntersection*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CWorldModel (lua_State* tolua_S)
{
 CWorldModel* self = (CWorldModel*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CGDebugEngine (lua_State* tolua_S)
{
 CGDebugEngine* self = (CGDebugEngine*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CGeoRectangle (lua_State* tolua_S)
{
 CGeoRectangle* self = (CGeoRectangle*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CBestPlayer");
 tolua_usertype(tolua_S,"CAttributeSet");
 tolua_usertype(tolua_S,"CDefenceInfo");
 tolua_usertype(tolua_S,"CVector");
 tolua_usertype(tolua_S,"PlayerCapabilityT");
 tolua_usertype(tolua_S,"CMessiDecision");
 tolua_usertype(tolua_S,"PlayerPoseT");
 tolua_usertype(tolua_S,"CGeoLineRectangleIntersection");
 tolua_usertype(tolua_S,"CWorldModel");
 tolua_usertype(tolua_S,"CGeoSegment");
 tolua_usertype(tolua_S,"VisionObjectT");
 tolua_usertype(tolua_S,"CAssistPoint");
 tolua_usertype(tolua_S,"CKickStatus");
 tolua_usertype(tolua_S,"GameState");
 tolua_usertype(tolua_S,"CKickDirection");
 tolua_usertype(tolua_S,"CDribbleStatus");
 tolua_usertype(tolua_S,"CGeoLineLineIntersection");
 tolua_usertype(tolua_S,"CGeoRectangle");
 tolua_usertype(tolua_S,"CGPUBestAlgThread");
 tolua_usertype(tolua_S,"PlayerTypeT");
 tolua_usertype(tolua_S,"CSupportPos");
 tolua_usertype(tolua_S,"CIndirectDefender");
 tolua_usertype(tolua_S,"CPlayerCommand");
 tolua_usertype(tolua_S,"ReCalModeT");
 tolua_usertype(tolua_S,"TwoKickPos");
 tolua_usertype(tolua_S,"CGeoLine");
 tolua_usertype(tolua_S,"Matrix<double>");
 tolua_usertype(tolua_S,"CDefPos2015");
 tolua_usertype(tolua_S,"CPlayerTask");
 tolua_usertype(tolua_S,"Defend2015");
 tolua_usertype(tolua_S,"CServerInterface::VisualInfo");
 tolua_usertype(tolua_S,"RobotRawVisionData");
 tolua_usertype(tolua_S,"vector<CGeoPoint>");
 tolua_usertype(tolua_S,"KickOffArea");
 tolua_usertype(tolua_S,"CGeoPoint");
 tolua_usertype(tolua_S,"CTandemPos");
 tolua_usertype(tolua_S,"ObjectPoseT");
 tolua_usertype(tolua_S,"Munkres");
 tolua_usertype(tolua_S,"MobileVisionT");
 tolua_usertype(tolua_S,"CGDebugEngine");
 tolua_usertype(tolua_S,"PlayerVisionT");
 tolua_usertype(tolua_S,"CTaskMediator");
 tolua_usertype(tolua_S,"CVisionModule");
}

/* method: new of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector_new00
static int tolua_zeus_CVector_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CVector* tolua_ret = (CVector*)  Mtolua_new((CVector)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CVector");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector_new00_local
static int tolua_zeus_CVector_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CVector* tolua_ret = (CVector*)  Mtolua_new((CVector)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector_delete00
static int tolua_zeus_CVector_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CVector* self = (CVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector_new01
static int tolua_zeus_CVector_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  double tolua_var_1 = ((double)  tolua_tonumber(tolua_S,2,0));
  double tolua_var_2 = ((double)  tolua_tonumber(tolua_S,3,0));
  {
   CVector* tolua_ret = (CVector*)  Mtolua_new((CVector)(tolua_var_1,tolua_var_2));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CVector");
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CVector_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector_new01_local
static int tolua_zeus_CVector_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  double tolua_var_1 = ((double)  tolua_tonumber(tolua_S,2,0));
  double tolua_var_2 = ((double)  tolua_tonumber(tolua_S,3,0));
  {
   CVector* tolua_ret = (CVector*)  Mtolua_new((CVector)(tolua_var_1,tolua_var_2));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CVector_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector_new02
static int tolua_zeus_CVector_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CVector",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CVector* tolua_var_3 = ((const CVector*)  tolua_tousertype(tolua_S,2,0));
  {
   CVector* tolua_ret = (CVector*)  Mtolua_new((CVector)(*tolua_var_3));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CVector");
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CVector_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector_new02_local
static int tolua_zeus_CVector_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CVector",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CVector* tolua_var_3 = ((const CVector*)  tolua_tousertype(tolua_S,2,0));
  {
   CVector* tolua_ret = (CVector*)  Mtolua_new((CVector)(*tolua_var_3));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CVector_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: mod of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector_mod00
static int tolua_zeus_CVector_mod00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVector* self = (const CVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'mod'", NULL);
#endif
  {
   double tolua_ret = (double)  self->mod();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mod'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: mod2 of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector_mod200
static int tolua_zeus_CVector_mod200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVector* self = (const CVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'mod2'", NULL);
#endif
  {
   double tolua_ret = (double)  self->mod2();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mod2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dir of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector_dir00
static int tolua_zeus_CVector_dir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVector* self = (const CVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dir'", NULL);
#endif
  {
   double tolua_ret = (double)  self->dir();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: x of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector_x00
static int tolua_zeus_CVector_x00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVector* self = (const CVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'x'", NULL);
#endif
  {
   double tolua_ret = (double)  self->x();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'x'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: y of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector_y00
static int tolua_zeus_CVector_y00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVector* self = (const CVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'y'", NULL);
#endif
  {
   double tolua_ret = (double)  self->y();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'y'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: value of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector_value00
static int tolua_zeus_CVector_value00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVector* self = (const CVector*)  tolua_tousertype(tolua_S,1,0);
  double tolua_var_4 = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'value'", NULL);
#endif
  {
   double tolua_ret = (double)  self->value(tolua_var_4);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'value'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector__add00
static int tolua_zeus_CVector__add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVector",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVector* self = (const CVector*)  tolua_tousertype(tolua_S,1,0);
  const CVector* tolua_var_5 = ((const CVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   CVector tolua_ret = (CVector)  self->operator+(*tolua_var_5);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CVector)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CVector));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector__sub00
static int tolua_zeus_CVector__sub00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVector",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVector* self = (const CVector*)  tolua_tousertype(tolua_S,1,0);
  const CVector* tolua_var_6 = ((const CVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   CVector tolua_ret = (CVector)  self->operator-(*tolua_var_6);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CVector)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CVector));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.sub'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector__mul00
static int tolua_zeus_CVector__mul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVector* self = (const CVector*)  tolua_tousertype(tolua_S,1,0);
  double tolua_var_7 = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'", NULL);
#endif
  {
   CVector tolua_ret = (CVector)  self->operator*(tolua_var_7);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CVector)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CVector));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.mul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator/ of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector__div00
static int tolua_zeus_CVector__div00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVector* self = (const CVector*)  tolua_tousertype(tolua_S,1,0);
  double tolua_var_8 = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator/'", NULL);
#endif
  {
   CVector tolua_ret = (CVector)  self->operator/(tolua_var_8);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CVector)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CVector));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.div'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector__sub01
static int tolua_zeus_CVector__sub01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CVector* self = (const CVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   CVector tolua_ret = (CVector)  self->operator-();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CVector)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CVector));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CVector__sub00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: rotate of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector_rotate00
static int tolua_zeus_CVector_rotate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVector* self = (const CVector*)  tolua_tousertype(tolua_S,1,0);
  double tolua_var_9 = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rotate'", NULL);
#endif
  {
   CVector tolua_ret = (CVector)  self->rotate(tolua_var_9);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CVector)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CVector));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rotate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint_new00
static int tolua_zeus_CGeoPoint_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoPoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGeoPoint* tolua_ret = (CGeoPoint*)  Mtolua_new((CGeoPoint)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint_new00_local
static int tolua_zeus_CGeoPoint_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoPoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGeoPoint* tolua_ret = (CGeoPoint*)  Mtolua_new((CGeoPoint)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint_delete00
static int tolua_zeus_CGeoPoint_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGeoPoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoPoint* self = (CGeoPoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint_new01
static int tolua_zeus_CGeoPoint_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoPoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
  double y = ((double)  tolua_tonumber(tolua_S,3,0));
  {
   CGeoPoint* tolua_ret = (CGeoPoint*)  Mtolua_new((CGeoPoint)(x,y));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoPoint");
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CGeoPoint_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint_new01_local
static int tolua_zeus_CGeoPoint_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoPoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
  double y = ((double)  tolua_tonumber(tolua_S,3,0));
  {
   CGeoPoint* tolua_ret = (CGeoPoint*)  Mtolua_new((CGeoPoint)(x,y));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CGeoPoint_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint_new02
static int tolua_zeus_CGeoPoint_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoPoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  {
   CGeoPoint* tolua_ret = (CGeoPoint*)  Mtolua_new((CGeoPoint)(*p));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoPoint");
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CGeoPoint_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint_new02_local
static int tolua_zeus_CGeoPoint_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoPoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  {
   CGeoPoint* tolua_ret = (CGeoPoint*)  Mtolua_new((CGeoPoint)(*p));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CGeoPoint_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint__eq00
static int tolua_zeus_CGeoPoint__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGeoPoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoPoint* self = (CGeoPoint*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* rhs = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*rhs);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: x of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint_x00
static int tolua_zeus_CGeoPoint_x00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* self = (const CGeoPoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'x'", NULL);
#endif
  {
   double tolua_ret = (double)  self->x();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'x'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: y of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint_y00
static int tolua_zeus_CGeoPoint_y00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* self = (const CGeoPoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'y'", NULL);
#endif
  {
   double tolua_ret = (double)  self->y();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'y'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dist of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint_dist00
static int tolua_zeus_CGeoPoint_dist00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* self = (const CGeoPoint*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dist'", NULL);
#endif
  {
   double tolua_ret = (double)  self->dist(*p);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dist'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dist2 of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint_dist200
static int tolua_zeus_CGeoPoint_dist200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* self = (const CGeoPoint*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dist2'", NULL);
#endif
  {
   double tolua_ret = (double)  self->dist2(*p);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dist2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint__add00
static int tolua_zeus_CGeoPoint__add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* self = (const CGeoPoint*)  tolua_tousertype(tolua_S,1,0);
  const CVector* v = ((const CVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->operator+(*v);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint__mul00
static int tolua_zeus_CGeoPoint__mul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* self = (const CGeoPoint*)  tolua_tousertype(tolua_S,1,0);
  const double a = ((const double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->operator*(a);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
   tolua_pushnumber(tolua_S,(lua_Number)a);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.mul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint__sub00
static int tolua_zeus_CGeoPoint__sub00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* self = (const CGeoPoint*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   CVector tolua_ret = (CVector)  self->operator-(*p);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CVector)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CVector));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.sub'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGeoLine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLine_new00
static int tolua_zeus_CGeoLine_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoLine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGeoLine* tolua_ret = (CGeoLine*)  Mtolua_new((CGeoLine)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoLine");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGeoLine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLine_new00_local
static int tolua_zeus_CGeoLine_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoLine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGeoLine* tolua_ret = (CGeoLine*)  Mtolua_new((CGeoLine)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoLine");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGeoLine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLine_new01
static int tolua_zeus_CGeoLine_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoLine",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CGeoPoint* p1 = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  const CGeoPoint* p2 = ((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  {
   CGeoLine* tolua_ret = (CGeoLine*)  Mtolua_new((CGeoLine)(*p1,*p2));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoLine");
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CGeoLine_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGeoLine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLine_new01_local
static int tolua_zeus_CGeoLine_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoLine",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CGeoPoint* p1 = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  const CGeoPoint* p2 = ((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  {
   CGeoLine* tolua_ret = (CGeoLine*)  Mtolua_new((CGeoLine)(*p1,*p2));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoLine");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CGeoLine_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGeoLine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLine_new02
static int tolua_zeus_CGeoLine_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoLine",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  double angle = ((double)  tolua_tonumber(tolua_S,3,0));
  {
   CGeoLine* tolua_ret = (CGeoLine*)  Mtolua_new((CGeoLine)(*p,angle));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoLine");
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CGeoLine_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGeoLine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLine_new02_local
static int tolua_zeus_CGeoLine_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoLine",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  double angle = ((double)  tolua_tonumber(tolua_S,3,0));
  {
   CGeoLine* tolua_ret = (CGeoLine*)  Mtolua_new((CGeoLine)(*p,angle));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoLine");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CGeoLine_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: calABC of class  CGeoLine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLine_calABC00
static int tolua_zeus_CGeoLine_calABC00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGeoLine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoLine* self = (CGeoLine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'calABC'", NULL);
#endif
  {
   self->calABC();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'calABC'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: projection of class  CGeoLine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLine_projection00
static int tolua_zeus_CGeoLine_projection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoLine",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLine* self = (const CGeoLine*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'projection'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->projection(*p);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'projection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: point1 of class  CGeoLine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLine_point100
static int tolua_zeus_CGeoLine_point100(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoLine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLine* self = (const CGeoLine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'point1'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->point1();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'point1'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: point2 of class  CGeoLine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLine_point200
static int tolua_zeus_CGeoLine_point200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoLine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLine* self = (const CGeoLine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'point2'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->point2();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'point2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  CGeoLine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLine__eq00
static int tolua_zeus_CGeoLine__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGeoLine",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoLine",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoLine* self = (CGeoLine*)  tolua_tousertype(tolua_S,1,0);
  const CGeoLine* rhs = ((const CGeoLine*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*rhs);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: a of class  CGeoLine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLine_a00
static int tolua_zeus_CGeoLine_a00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoLine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLine* self = (const CGeoLine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'a'", NULL);
#endif
  {
   const double tolua_ret = (const double)  self->a();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'a'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: b of class  CGeoLine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLine_b00
static int tolua_zeus_CGeoLine_b00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoLine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLine* self = (const CGeoLine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'b'", NULL);
#endif
  {
   const double tolua_ret = (const double)  self->b();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'b'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: c of class  CGeoLine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLine_c00
static int tolua_zeus_CGeoLine_c00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoLine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLine* self = (const CGeoLine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'c'", NULL);
#endif
  {
   const double tolua_ret = (const double)  self->c();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'c'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGeoSegment */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoSegment_new00
static int tolua_zeus_CGeoSegment_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoSegment",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGeoSegment* tolua_ret = (CGeoSegment*)  Mtolua_new((CGeoSegment)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoSegment");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGeoSegment */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoSegment_new00_local
static int tolua_zeus_CGeoSegment_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoSegment",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGeoSegment* tolua_ret = (CGeoSegment*)  Mtolua_new((CGeoSegment)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoSegment");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGeoSegment */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoSegment_new01
static int tolua_zeus_CGeoSegment_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoSegment",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CGeoPoint* p1 = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  const CGeoPoint* p2 = ((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  {
   CGeoSegment* tolua_ret = (CGeoSegment*)  Mtolua_new((CGeoSegment)(*p1,*p2));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoSegment");
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CGeoSegment_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGeoSegment */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoSegment_new01_local
static int tolua_zeus_CGeoSegment_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoSegment",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CGeoPoint* p1 = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  const CGeoPoint* p2 = ((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  {
   CGeoSegment* tolua_ret = (CGeoSegment*)  Mtolua_new((CGeoSegment)(*p1,*p2));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoSegment");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CGeoSegment_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsPointOnLineOnSegment of class  CGeoSegment */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoSegment_IsPointOnLineOnSegment00
static int tolua_zeus_CGeoSegment_IsPointOnLineOnSegment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoSegment",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoSegment* self = (const CGeoSegment*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsPointOnLineOnSegment'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsPointOnLineOnSegment(*p);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsPointOnLineOnSegment'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: start of class  CGeoSegment */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoSegment_start00
static int tolua_zeus_CGeoSegment_start00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoSegment",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoSegment* self = (const CGeoSegment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'start'", NULL);
#endif
  {
   const CGeoPoint& tolua_ret = (const CGeoPoint&)  self->start();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'start'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: end of class  CGeoSegment */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoSegment_end00
static int tolua_zeus_CGeoSegment_end00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoSegment",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoSegment* self = (const CGeoSegment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'end'", NULL);
#endif
  {
   const CGeoPoint& tolua_ret = (const CGeoPoint&)  self->end();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'end'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGeoLineLineIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLineLineIntersection_new00
static int tolua_zeus_CGeoLineLineIntersection_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoLineLineIntersection",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoLine",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoLine",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLine* line_1 = ((const CGeoLine*)  tolua_tousertype(tolua_S,2,0));
  const CGeoLine* line_2 = ((const CGeoLine*)  tolua_tousertype(tolua_S,3,0));
  {
   CGeoLineLineIntersection* tolua_ret = (CGeoLineLineIntersection*)  Mtolua_new((CGeoLineLineIntersection)(*line_1,*line_2));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoLineLineIntersection");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGeoLineLineIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLineLineIntersection_new00_local
static int tolua_zeus_CGeoLineLineIntersection_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoLineLineIntersection",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoLine",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoLine",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLine* line_1 = ((const CGeoLine*)  tolua_tousertype(tolua_S,2,0));
  const CGeoLine* line_2 = ((const CGeoLine*)  tolua_tousertype(tolua_S,3,0));
  {
   CGeoLineLineIntersection* tolua_ret = (CGeoLineLineIntersection*)  Mtolua_new((CGeoLineLineIntersection)(*line_1,*line_2));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoLineLineIntersection");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Intersectant of class  CGeoLineLineIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLineLineIntersection_Intersectant00
static int tolua_zeus_CGeoLineLineIntersection_Intersectant00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoLineLineIntersection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLineLineIntersection* self = (const CGeoLineLineIntersection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Intersectant'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Intersectant();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Intersectant'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IntersectPoint of class  CGeoLineLineIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLineLineIntersection_IntersectPoint00
static int tolua_zeus_CGeoLineLineIntersection_IntersectPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoLineLineIntersection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLineLineIntersection* self = (const CGeoLineLineIntersection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IntersectPoint'", NULL);
#endif
  {
   const CGeoPoint& tolua_ret = (const CGeoPoint&)  self->IntersectPoint();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IntersectPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGeoRectangle */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoRectangle_new00
static int tolua_zeus_CGeoRectangle_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoRectangle",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* leftTop = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  const CGeoPoint* rightDown = ((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  {
   CGeoRectangle* tolua_ret = (CGeoRectangle*)  Mtolua_new((CGeoRectangle)(*leftTop,*rightDown));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoRectangle");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGeoRectangle */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoRectangle_new00_local
static int tolua_zeus_CGeoRectangle_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoRectangle",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* leftTop = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  const CGeoPoint* rightDown = ((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  {
   CGeoRectangle* tolua_ret = (CGeoRectangle*)  Mtolua_new((CGeoRectangle)(*leftTop,*rightDown));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoRectangle");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGeoLineRectangleIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLineRectangleIntersection_new00
static int tolua_zeus_CGeoLineRectangleIntersection_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoLineRectangleIntersection",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoLine",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoRectangle",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLine* line = ((const CGeoLine*)  tolua_tousertype(tolua_S,2,0));
  const CGeoRectangle* rect = ((const CGeoRectangle*)  tolua_tousertype(tolua_S,3,0));
  {
   CGeoLineRectangleIntersection* tolua_ret = (CGeoLineRectangleIntersection*)  Mtolua_new((CGeoLineRectangleIntersection)(*line,*rect));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoLineRectangleIntersection");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGeoLineRectangleIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLineRectangleIntersection_new00_local
static int tolua_zeus_CGeoLineRectangleIntersection_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoLineRectangleIntersection",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoLine",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoRectangle",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLine* line = ((const CGeoLine*)  tolua_tousertype(tolua_S,2,0));
  const CGeoRectangle* rect = ((const CGeoRectangle*)  tolua_tousertype(tolua_S,3,0));
  {
   CGeoLineRectangleIntersection* tolua_ret = (CGeoLineRectangleIntersection*)  Mtolua_new((CGeoLineRectangleIntersection)(*line,*rect));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoLineRectangleIntersection");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: intersectant of class  CGeoLineRectangleIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLineRectangleIntersection_intersectant00
static int tolua_zeus_CGeoLineRectangleIntersection_intersectant00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGeoLineRectangleIntersection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoLineRectangleIntersection* self = (CGeoLineRectangleIntersection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'intersectant'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->intersectant();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'intersectant'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: point1 of class  CGeoLineRectangleIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLineRectangleIntersection_point100
static int tolua_zeus_CGeoLineRectangleIntersection_point100(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGeoLineRectangleIntersection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoLineRectangleIntersection* self = (CGeoLineRectangleIntersection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'point1'", NULL);
#endif
  {
   const CGeoPoint& tolua_ret = (const CGeoPoint&)  self->point1();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'point1'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: point2 of class  CGeoLineRectangleIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLineRectangleIntersection_point200
static int tolua_zeus_CGeoLineRectangleIntersection_point200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGeoLineRectangleIntersection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoLineRectangleIntersection* self = (CGeoLineRectangleIntersection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'point2'", NULL);
#endif
  {
   const CGeoPoint& tolua_ret = (const CGeoPoint&)  self->point2();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'point2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: vision */
#ifndef TOLUA_DISABLE_tolua_get_vision_ptr
static int tolua_get_vision_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)vision,"CVisionModule");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: vision */
#ifndef TOLUA_DISABLE_tolua_set_vision_ptr
static int tolua_set_vision_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"CVisionModule",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  vision = ((CVisionModule*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: kickStatus */
#ifndef TOLUA_DISABLE_tolua_get_kickStatus_ptr
static int tolua_get_kickStatus_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)kickStatus,"CKickStatus");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: kickStatus */
#ifndef TOLUA_DISABLE_tolua_set_kickStatus_ptr
static int tolua_set_kickStatus_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"CKickStatus",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  kickStatus = ((CKickStatus*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dribbleStatus */
#ifndef TOLUA_DISABLE_tolua_get_dribbleStatus_ptr
static int tolua_get_dribbleStatus_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)dribbleStatus,"CDribbleStatus");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dribbleStatus */
#ifndef TOLUA_DISABLE_tolua_set_dribbleStatus_ptr
static int tolua_set_dribbleStatus_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"CDribbleStatus",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  dribbleStatus = ((CDribbleStatus*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: debugEngine */
#ifndef TOLUA_DISABLE_tolua_get_debugEngine_ptr
static int tolua_get_debugEngine_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)debugEngine,"CGDebugEngine");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: debugEngine */
#ifndef TOLUA_DISABLE_tolua_set_debugEngine_ptr
static int tolua_set_debugEngine_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"CGDebugEngine",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  debugEngine = ((CGDebugEngine*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: world */
#ifndef TOLUA_DISABLE_tolua_get_world_ptr
static int tolua_get_world_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)world,"CWorldModel");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: world */
#ifndef TOLUA_DISABLE_tolua_set_world_ptr
static int tolua_set_world_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"CWorldModel",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  world = ((CWorldModel*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: kickDirection */
#ifndef TOLUA_DISABLE_tolua_get_kickDirection_ptr
static int tolua_get_kickDirection_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)kickDirection,"CKickDirection");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: kickDirection */
#ifndef TOLUA_DISABLE_tolua_set_kickDirection_ptr
static int tolua_set_kickDirection_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"CKickDirection",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  kickDirection = ((CKickDirection*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bestAlg */
#ifndef TOLUA_DISABLE_tolua_get_bestAlg_ptr
static int tolua_get_bestAlg_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)bestAlg,"CGPUBestAlgThread");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bestAlg */
#ifndef TOLUA_DISABLE_tolua_set_bestAlg_ptr
static int tolua_set_bestAlg_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"CGPUBestAlgThread",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  bestAlg = ((CGPUBestAlgThread*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: defPos2015 */
#ifndef TOLUA_DISABLE_tolua_get_defPos2015_ptr
static int tolua_get_defPos2015_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)defPos2015,"CDefPos2015");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: defPos2015 */
#ifndef TOLUA_DISABLE_tolua_set_defPos2015_ptr
static int tolua_set_defPos2015_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"CDefPos2015",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  defPos2015 = ((CDefPos2015*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: supportPos */
#ifndef TOLUA_DISABLE_tolua_get_supportPos_ptr
static int tolua_get_supportPos_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)supportPos,"CSupportPos");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: supportPos */
#ifndef TOLUA_DISABLE_tolua_set_supportPos_ptr
static int tolua_set_supportPos_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"CSupportPos",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  supportPos = ((CSupportPos*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: tandemPos */
#ifndef TOLUA_DISABLE_tolua_get_tandemPos_ptr
static int tolua_get_tandemPos_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)tandemPos,"CTandemPos");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: tandemPos */
#ifndef TOLUA_DISABLE_tolua_set_tandemPos_ptr
static int tolua_set_tandemPos_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"CTandemPos",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  tandemPos = ((CTandemPos*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bestPlayer */
#ifndef TOLUA_DISABLE_tolua_get_bestPlayer_ptr
static int tolua_get_bestPlayer_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)bestPlayer,"CBestPlayer");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bestPlayer */
#ifndef TOLUA_DISABLE_tolua_set_bestPlayer_ptr
static int tolua_set_bestPlayer_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"CBestPlayer",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  bestPlayer = ((CBestPlayer*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: defenceInfo */
#ifndef TOLUA_DISABLE_tolua_get_defenceInfo_ptr
static int tolua_get_defenceInfo_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)defenceInfo,"CDefenceInfo");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: defenceInfo */
#ifndef TOLUA_DISABLE_tolua_set_defenceInfo_ptr
static int tolua_set_defenceInfo_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"CDefenceInfo",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  defenceInfo = ((CDefenceInfo*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: indirectDefender */
#ifndef TOLUA_DISABLE_tolua_get_indirectDefender_ptr
static int tolua_get_indirectDefender_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)indirectDefender,"CIndirectDefender");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: indirectDefender */
#ifndef TOLUA_DISABLE_tolua_set_indirectDefender_ptr
static int tolua_set_indirectDefender_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"CIndirectDefender",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  indirectDefender = ((CIndirectDefender*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: assistPoint */
#ifndef TOLUA_DISABLE_tolua_get_assistPoint_ptr
static int tolua_get_assistPoint_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)assistPoint,"CAssistPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: assistPoint */
#ifndef TOLUA_DISABLE_tolua_set_assistPoint_ptr
static int tolua_set_assistPoint_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"CAssistPoint",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  assistPoint = ((CAssistPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: messi */
#ifndef TOLUA_DISABLE_tolua_get_messi_ptr
static int tolua_get_messi_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)messi,"CMessiDecision");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: messi */
#ifndef TOLUA_DISABLE_tolua_set_messi_ptr
static int tolua_set_messi_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"CMessiDecision",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  messi = ((CMessiDecision*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ObjectPoseT */
#ifndef TOLUA_DISABLE_tolua_zeus_ObjectPoseT_new00
static int tolua_zeus_ObjectPoseT_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ObjectPoseT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ObjectPoseT* tolua_ret = (ObjectPoseT*)  Mtolua_new((ObjectPoseT)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ObjectPoseT");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ObjectPoseT */
#ifndef TOLUA_DISABLE_tolua_zeus_ObjectPoseT_new00_local
static int tolua_zeus_ObjectPoseT_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ObjectPoseT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ObjectPoseT* tolua_ret = (ObjectPoseT*)  Mtolua_new((ObjectPoseT)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ObjectPoseT");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Pos of class  ObjectPoseT */
#ifndef TOLUA_DISABLE_tolua_zeus_ObjectPoseT_Pos00
static int tolua_zeus_ObjectPoseT_Pos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ObjectPoseT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ObjectPoseT* self = (const ObjectPoseT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Pos'", NULL);
#endif
  {
   const CGeoPoint& tolua_ret = (const CGeoPoint&)  self->Pos();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Pos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPos of class  ObjectPoseT */
#ifndef TOLUA_DISABLE_tolua_zeus_ObjectPoseT_SetPos00
static int tolua_zeus_ObjectPoseT_SetPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ObjectPoseT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ObjectPoseT* self = (ObjectPoseT*)  tolua_tousertype(tolua_S,1,0);
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
  double y = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPos'", NULL);
#endif
  {
   self->SetPos(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPos of class  ObjectPoseT */
#ifndef TOLUA_DISABLE_tolua_zeus_ObjectPoseT_SetPos01
static int tolua_zeus_ObjectPoseT_SetPos01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ObjectPoseT",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  ObjectPoseT* self = (ObjectPoseT*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* pos = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPos'", NULL);
#endif
  {
   self->SetPos(*pos);
  }
 }
 return 0;
tolua_lerror:
 return tolua_zeus_ObjectPoseT_SetPos00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: X of class  ObjectPoseT */
#ifndef TOLUA_DISABLE_tolua_zeus_ObjectPoseT_X00
static int tolua_zeus_ObjectPoseT_X00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ObjectPoseT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ObjectPoseT* self = (const ObjectPoseT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'X'", NULL);
#endif
  {
   double tolua_ret = (double)  self->X();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'X'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Y of class  ObjectPoseT */
#ifndef TOLUA_DISABLE_tolua_zeus_ObjectPoseT_Y00
static int tolua_zeus_ObjectPoseT_Y00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ObjectPoseT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ObjectPoseT* self = (const ObjectPoseT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Y'", NULL);
#endif
  {
   double tolua_ret = (double)  self->Y();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Y'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetVel of class  ObjectPoseT */
#ifndef TOLUA_DISABLE_tolua_zeus_ObjectPoseT_SetVel00
static int tolua_zeus_ObjectPoseT_SetVel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ObjectPoseT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ObjectPoseT* self = (ObjectPoseT*)  tolua_tousertype(tolua_S,1,0);
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
  double y = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetVel'", NULL);
#endif
  {
   self->SetVel(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetVel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetVel of class  ObjectPoseT */
#ifndef TOLUA_DISABLE_tolua_zeus_ObjectPoseT_SetVel01
static int tolua_zeus_ObjectPoseT_SetVel01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ObjectPoseT",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  ObjectPoseT* self = (ObjectPoseT*)  tolua_tousertype(tolua_S,1,0);
  const CVector* vel = ((const CVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetVel'", NULL);
#endif
  {
   self->SetVel(*vel);
  }
 }
 return 0;
tolua_lerror:
 return tolua_zeus_ObjectPoseT_SetVel00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Vel of class  ObjectPoseT */
#ifndef TOLUA_DISABLE_tolua_zeus_ObjectPoseT_Vel00
static int tolua_zeus_ObjectPoseT_Vel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ObjectPoseT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ObjectPoseT* self = (const ObjectPoseT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Vel'", NULL);
#endif
  {
   const CVector& tolua_ret = (const CVector&)  self->Vel();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CVector");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Vel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: VelX of class  ObjectPoseT */
#ifndef TOLUA_DISABLE_tolua_zeus_ObjectPoseT_VelX00
static int tolua_zeus_ObjectPoseT_VelX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ObjectPoseT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ObjectPoseT* self = (const ObjectPoseT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'VelX'", NULL);
#endif
  {
   double tolua_ret = (double)  self->VelX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'VelX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: VelY of class  ObjectPoseT */
#ifndef TOLUA_DISABLE_tolua_zeus_ObjectPoseT_VelY00
static int tolua_zeus_ObjectPoseT_VelY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ObjectPoseT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ObjectPoseT* self = (const ObjectPoseT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'VelY'", NULL);
#endif
  {
   double tolua_ret = (double)  self->VelY();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'VelY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetValid of class  ObjectPoseT */
#ifndef TOLUA_DISABLE_tolua_zeus_ObjectPoseT_SetValid00
static int tolua_zeus_ObjectPoseT_SetValid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ObjectPoseT",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ObjectPoseT* self = (ObjectPoseT*)  tolua_tousertype(tolua_S,1,0);
  bool v = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetValid'", NULL);
#endif
  {
   self->SetValid(v);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetValid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Valid of class  ObjectPoseT */
#ifndef TOLUA_DISABLE_tolua_zeus_ObjectPoseT_Valid00
static int tolua_zeus_ObjectPoseT_Valid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ObjectPoseT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ObjectPoseT* self = (const ObjectPoseT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Valid'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Valid();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Valid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RawPos of class  VisionObjectT */
#ifndef TOLUA_DISABLE_tolua_zeus_VisionObjectT_RawPos00
static int tolua_zeus_VisionObjectT_RawPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const VisionObjectT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const VisionObjectT* self = (const VisionObjectT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RawPos'", NULL);
#endif
  {
   const CGeoPoint& tolua_ret = (const CGeoPoint&)  self->RawPos();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RawPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRawPos of class  VisionObjectT */
#ifndef TOLUA_DISABLE_tolua_zeus_VisionObjectT_SetRawPos00
static int tolua_zeus_VisionObjectT_SetRawPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VisionObjectT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VisionObjectT* self = (VisionObjectT*)  tolua_tousertype(tolua_S,1,0);
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
  double y = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRawPos'", NULL);
#endif
  {
   self->SetRawPos(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRawPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRawPos of class  VisionObjectT */
#ifndef TOLUA_DISABLE_tolua_zeus_VisionObjectT_SetRawPos01
static int tolua_zeus_VisionObjectT_SetRawPos01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VisionObjectT",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  VisionObjectT* self = (VisionObjectT*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* pos = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRawPos'", NULL);
#endif
  {
   self->SetRawPos(*pos);
  }
 }
 return 0;
tolua_lerror:
 return tolua_zeus_VisionObjectT_SetRawPos00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __VisionObjectT__ of class  MobileVisionT */
#ifndef TOLUA_DISABLE_tolua_get_MobileVisionT___VisionObjectT__
static int tolua_get_MobileVisionT___VisionObjectT__(lua_State* tolua_S)
{
  MobileVisionT* self = (MobileVisionT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__VisionObjectT__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<VisionObjectT*>(self), "VisionObjectT");
#else
   tolua_pushusertype(tolua_S,(void*)((VisionObjectT*)self), "VisionObjectT");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  PlayerPoseT */
#ifndef TOLUA_DISABLE_tolua_zeus_PlayerPoseT_new00
static int tolua_zeus_PlayerPoseT_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlayerPoseT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   PlayerPoseT* tolua_ret = (PlayerPoseT*)  Mtolua_new((PlayerPoseT)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PlayerPoseT");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  PlayerPoseT */
#ifndef TOLUA_DISABLE_tolua_zeus_PlayerPoseT_new00_local
static int tolua_zeus_PlayerPoseT_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlayerPoseT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   PlayerPoseT* tolua_ret = (PlayerPoseT*)  Mtolua_new((PlayerPoseT)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PlayerPoseT");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Dir of class  PlayerPoseT */
#ifndef TOLUA_DISABLE_tolua_zeus_PlayerPoseT_Dir00
static int tolua_zeus_PlayerPoseT_Dir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PlayerPoseT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PlayerPoseT* self = (const PlayerPoseT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Dir'", NULL);
#endif
  {
   double tolua_ret = (double)  self->Dir();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Dir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDir of class  PlayerPoseT */
#ifndef TOLUA_DISABLE_tolua_zeus_PlayerPoseT_SetDir00
static int tolua_zeus_PlayerPoseT_SetDir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerPoseT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerPoseT* self = (PlayerPoseT*)  tolua_tousertype(tolua_S,1,0);
  double d = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDir'", NULL);
#endif
  {
   self->SetDir(d);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RotVel of class  PlayerPoseT */
#ifndef TOLUA_DISABLE_tolua_zeus_PlayerPoseT_RotVel00
static int tolua_zeus_PlayerPoseT_RotVel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PlayerPoseT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PlayerPoseT* self = (const PlayerPoseT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RotVel'", NULL);
#endif
  {
   double tolua_ret = (double)  self->RotVel();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RotVel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRotVel of class  PlayerPoseT */
#ifndef TOLUA_DISABLE_tolua_zeus_PlayerPoseT_SetRotVel00
static int tolua_zeus_PlayerPoseT_SetRotVel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerPoseT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerPoseT* self = (PlayerPoseT*)  tolua_tousertype(tolua_S,1,0);
  double d = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRotVel'", NULL);
#endif
  {
   self->SetRotVel(d);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRotVel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetType of class  PlayerTypeT */
#ifndef TOLUA_DISABLE_tolua_zeus_PlayerTypeT_SetType00
static int tolua_zeus_PlayerTypeT_SetType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerTypeT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerTypeT* self = (PlayerTypeT*)  tolua_tousertype(tolua_S,1,0);
  int t = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetType'", NULL);
#endif
  {
   self->SetType(t);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Type of class  PlayerTypeT */
#ifndef TOLUA_DISABLE_tolua_zeus_PlayerTypeT_Type00
static int tolua_zeus_PlayerTypeT_Type00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PlayerTypeT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PlayerTypeT* self = (const PlayerTypeT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Type'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Type();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Type'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __VisionObjectT__ of class  PlayerVisionT */
#ifndef TOLUA_DISABLE_tolua_get_PlayerVisionT___VisionObjectT__
static int tolua_get_PlayerVisionT___VisionObjectT__(lua_State* tolua_S)
{
  PlayerVisionT* self = (PlayerVisionT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__VisionObjectT__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<VisionObjectT*>(self), "VisionObjectT");
#else
   tolua_pushusertype(tolua_S,(void*)((VisionObjectT*)self), "VisionObjectT");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __PlayerTypeT__ of class  PlayerVisionT */
#ifndef TOLUA_DISABLE_tolua_get_PlayerVisionT___PlayerTypeT__
static int tolua_get_PlayerVisionT___PlayerTypeT__(lua_State* tolua_S)
{
  PlayerVisionT* self = (PlayerVisionT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__PlayerTypeT__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<PlayerTypeT*>(self), "PlayerTypeT");
#else
   tolua_pushusertype(tolua_S,(void*)((PlayerTypeT*)self), "PlayerTypeT");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: maxAccel of class  PlayerCapabilityT */
#ifndef TOLUA_DISABLE_tolua_get_PlayerCapabilityT_maxAccel
static int tolua_get_PlayerCapabilityT_maxAccel(lua_State* tolua_S)
{
  PlayerCapabilityT* self = (PlayerCapabilityT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxAccel'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->maxAccel);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: maxAccel of class  PlayerCapabilityT */
#ifndef TOLUA_DISABLE_tolua_set_PlayerCapabilityT_maxAccel
static int tolua_set_PlayerCapabilityT_maxAccel(lua_State* tolua_S)
{
  PlayerCapabilityT* self = (PlayerCapabilityT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxAccel'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->maxAccel = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: maxSpeed of class  PlayerCapabilityT */
#ifndef TOLUA_DISABLE_tolua_get_PlayerCapabilityT_maxSpeed
static int tolua_get_PlayerCapabilityT_maxSpeed(lua_State* tolua_S)
{
  PlayerCapabilityT* self = (PlayerCapabilityT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxSpeed'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->maxSpeed);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: maxSpeed of class  PlayerCapabilityT */
#ifndef TOLUA_DISABLE_tolua_set_PlayerCapabilityT_maxSpeed
static int tolua_set_PlayerCapabilityT_maxSpeed(lua_State* tolua_S)
{
  PlayerCapabilityT* self = (PlayerCapabilityT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxSpeed'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->maxSpeed = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: maxAngularAccel of class  PlayerCapabilityT */
#ifndef TOLUA_DISABLE_tolua_get_PlayerCapabilityT_maxAngularAccel
static int tolua_get_PlayerCapabilityT_maxAngularAccel(lua_State* tolua_S)
{
  PlayerCapabilityT* self = (PlayerCapabilityT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxAngularAccel'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->maxAngularAccel);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: maxAngularAccel of class  PlayerCapabilityT */
#ifndef TOLUA_DISABLE_tolua_set_PlayerCapabilityT_maxAngularAccel
static int tolua_set_PlayerCapabilityT_maxAngularAccel(lua_State* tolua_S)
{
  PlayerCapabilityT* self = (PlayerCapabilityT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxAngularAccel'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->maxAngularAccel = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: maxAngularSpeed of class  PlayerCapabilityT */
#ifndef TOLUA_DISABLE_tolua_get_PlayerCapabilityT_maxAngularSpeed
static int tolua_get_PlayerCapabilityT_maxAngularSpeed(lua_State* tolua_S)
{
  PlayerCapabilityT* self = (PlayerCapabilityT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxAngularSpeed'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->maxAngularSpeed);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: maxAngularSpeed of class  PlayerCapabilityT */
#ifndef TOLUA_DISABLE_tolua_set_PlayerCapabilityT_maxAngularSpeed
static int tolua_set_PlayerCapabilityT_maxAngularSpeed(lua_State* tolua_S)
{
  PlayerCapabilityT* self = (PlayerCapabilityT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxAngularSpeed'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->maxAngularSpeed = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: maxDec of class  PlayerCapabilityT */
#ifndef TOLUA_DISABLE_tolua_get_PlayerCapabilityT_maxDec
static int tolua_get_PlayerCapabilityT_maxDec(lua_State* tolua_S)
{
  PlayerCapabilityT* self = (PlayerCapabilityT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxDec'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->maxDec);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: maxDec of class  PlayerCapabilityT */
#ifndef TOLUA_DISABLE_tolua_set_PlayerCapabilityT_maxDec
static int tolua_set_PlayerCapabilityT_maxDec(lua_State* tolua_S)
{
  PlayerCapabilityT* self = (PlayerCapabilityT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxDec'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->maxDec = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: maxAngularDec of class  PlayerCapabilityT */
#ifndef TOLUA_DISABLE_tolua_get_PlayerCapabilityT_maxAngularDec
static int tolua_get_PlayerCapabilityT_maxAngularDec(lua_State* tolua_S)
{
  PlayerCapabilityT* self = (PlayerCapabilityT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxAngularDec'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->maxAngularDec);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: maxAngularDec of class  PlayerCapabilityT */
#ifndef TOLUA_DISABLE_tolua_set_PlayerCapabilityT_maxAngularDec
static int tolua_set_PlayerCapabilityT_maxAngularDec(lua_State* tolua_S)
{
  PlayerCapabilityT* self = (PlayerCapabilityT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxAngularDec'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->maxAngularDec = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_new00
static int tolua_zeus_CVisionModule_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CVisionModule* tolua_ret = (CVisionModule*)  Mtolua_new((CVisionModule)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CVisionModule");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_new00_local
static int tolua_zeus_CVisionModule_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CVisionModule* tolua_ret = (CVisionModule*)  Mtolua_new((CVisionModule)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CVisionModule");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_delete00
static int tolua_zeus_CVisionModule_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CVisionModule* self = (CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getValidNum of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_getValidNum00
static int tolua_zeus_CVisionModule_getValidNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getValidNum'", NULL);
#endif
  {
   const int tolua_ret = (const int)  self->getValidNum();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getValidNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTheirValidNum of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_getTheirValidNum00
static int tolua_zeus_CVisionModule_getTheirValidNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTheirValidNum'", NULL);
#endif
  {
   const int tolua_ret = (const int)  self->getTheirValidNum();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTheirValidNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetNewVision of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_SetNewVision00
static int tolua_zeus_CVisionModule_SetNewVision00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CVisionModule",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CServerInterface::VisualInfo",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CVisionModule* self = (CVisionModule*)  tolua_tousertype(tolua_S,1,0);
  const CServerInterface::VisualInfo* vInfo = ((const CServerInterface::VisualInfo*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetNewVision'", NULL);
#endif
  {
   self->SetNewVision(*vInfo);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetNewVision'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AllPlayer of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_AllPlayer00
static int tolua_zeus_CVisionModule_AllPlayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AllPlayer'", NULL);
#endif
  {
   const PlayerVisionT& tolua_ret = (const PlayerVisionT&)  self->AllPlayer(num);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const PlayerVisionT");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AllPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OurPlayer of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_OurPlayer00
static int tolua_zeus_CVisionModule_OurPlayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OurPlayer'", NULL);
#endif
  {
   const PlayerVisionT& tolua_ret = (const PlayerVisionT&)  self->OurPlayer(num);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const PlayerVisionT");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OurPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TheirPlayer of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_TheirPlayer00
static int tolua_zeus_CVisionModule_TheirPlayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TheirPlayer'", NULL);
#endif
  {
   const PlayerVisionT& tolua_ret = (const PlayerVisionT&)  self->TheirPlayer(num);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const PlayerVisionT");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TheirPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Ball of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_Ball00
static int tolua_zeus_CVisionModule_Ball00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Ball'", NULL);
#endif
  {
   const MobileVisionT& tolua_ret = (const MobileVisionT&)  self->Ball();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const MobileVisionT");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Ball'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OurPlayer of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_OurPlayer01
static int tolua_zeus_CVisionModule_OurPlayer01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
  int cycle = ((int)  tolua_tonumber(tolua_S,2,0));
  int num = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OurPlayer'", NULL);
#endif
  {
   const PlayerVisionT& tolua_ret = (const PlayerVisionT&)  self->OurPlayer(cycle,num);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const PlayerVisionT");
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CVisionModule_OurPlayer00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: TheirPlayer of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_TheirPlayer01
static int tolua_zeus_CVisionModule_TheirPlayer01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
  int cycle = ((int)  tolua_tonumber(tolua_S,2,0));
  int num = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TheirPlayer'", NULL);
#endif
  {
   const PlayerVisionT& tolua_ret = (const PlayerVisionT&)  self->TheirPlayer(cycle,num);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const PlayerVisionT");
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CVisionModule_TheirPlayer00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Ball of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_Ball01
static int tolua_zeus_CVisionModule_Ball01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
  int cycle = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Ball'", NULL);
#endif
  {
   const MobileVisionT& tolua_ret = (const MobileVisionT&)  self->Ball(cycle);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const MobileVisionT");
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CVisionModule_Ball00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: RawBall of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_RawBall00
static int tolua_zeus_CVisionModule_RawBall00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RawBall'", NULL);
#endif
  {
   const ObjectPoseT& tolua_ret = (const ObjectPoseT&)  self->RawBall();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const ObjectPoseT");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RawBall'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBallPlacementPosition of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_getBallPlacementPosition00
static int tolua_zeus_CVisionModule_getBallPlacementPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBallPlacementPosition'", NULL);
#endif
  {
   const CGeoPoint tolua_ret = (const CGeoPoint)  self->getBallPlacementPosition();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"const CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(const CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"const CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBallPlacementPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OurRawPlayer of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_OurRawPlayer00
static int tolua_zeus_CVisionModule_OurRawPlayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OurRawPlayer'", NULL);
#endif
  {
   const RobotRawVisionData& tolua_ret = (const RobotRawVisionData&)  self->OurRawPlayer(num);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const RobotRawVisionData");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OurRawPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TheirRawPlayer of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_TheirRawPlayer00
static int tolua_zeus_CVisionModule_TheirRawPlayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TheirRawPlayer'", NULL);
#endif
  {
   const RobotRawVisionData& tolua_ret = (const RobotRawVisionData&)  self->TheirRawPlayer(num);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const RobotRawVisionData");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TheirRawPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPlayerCommand of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_SetPlayerCommand00
static int tolua_zeus_CVisionModule_SetPlayerCommand00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const CPlayerCommand",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CVisionModule* self = (CVisionModule*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
  const CPlayerCommand* pCmd = ((const CPlayerCommand*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPlayerCommand'", NULL);
#endif
  {
   self->SetPlayerCommand(num,pCmd);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPlayerCommand'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: gameState of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_gameState00
static int tolua_zeus_CVisionModule_gameState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gameState'", NULL);
#endif
  {
   const GameState& tolua_ret = (const GameState&)  self->gameState();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const GameState");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gameState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PlayerLostTime of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_PlayerLostTime00
static int tolua_zeus_CVisionModule_PlayerLostTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
  const int number = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PlayerLostTime'", NULL);
#endif
  {
   int tolua_ret = (int)  self->PlayerLostTime(number);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PlayerLostTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCurrentRefereeMsg of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_GetCurrentRefereeMsg00
static int tolua_zeus_CVisionModule_GetCurrentRefereeMsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCurrentRefereeMsg'", NULL);
#endif
  {
   const string tolua_ret = (const string)  self->GetCurrentRefereeMsg();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCurrentRefereeMsg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Cycle of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_Cycle00
static int tolua_zeus_CVisionModule_Cycle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Cycle'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Cycle();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Cycle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LastCycle of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_LastCycle00
static int tolua_zeus_CVisionModule_LastCycle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LastCycle'", NULL);
#endif
  {
   int tolua_ret = (int)  self->LastCycle();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LastCycle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Side of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_Side00
static int tolua_zeus_CVisionModule_Side00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Side'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Side();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Side'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OurGoal of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_OurGoal00
static int tolua_zeus_CVisionModule_OurGoal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CVisionModule* self = (CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OurGoal'", NULL);
#endif
  {
   int tolua_ret = (int)  self->OurGoal();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OurGoal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TheirGoal of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_TheirGoal00
static int tolua_zeus_CVisionModule_TheirGoal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CVisionModule* self = (CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TheirGoal'", NULL);
#endif
  {
   int tolua_ret = (int)  self->TheirGoal();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TheirGoal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TimeRemain of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_TimeRemain00
static int tolua_zeus_CVisionModule_TimeRemain00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CVisionModule* self = (CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TimeRemain'", NULL);
#endif
  {
   int tolua_ret = (int)  self->TimeRemain();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TimeRemain'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBallVelStable of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_getBallVelStable00
static int tolua_zeus_CVisionModule_getBallVelStable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CVisionModule* self = (CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBallVelStable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getBallVelStable();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBallVelStable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ballVelValid of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_ballVelValid00
static int tolua_zeus_CVisionModule_ballVelValid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CVisionModule* self = (CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ballVelValid'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ballVelValid();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ballVelValid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGDebugEngine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGDebugEngine_new00
static int tolua_zeus_CGDebugEngine_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGDebugEngine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGDebugEngine* tolua_ret = (CGDebugEngine*)  Mtolua_new((CGDebugEngine)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGDebugEngine");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGDebugEngine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGDebugEngine_new00_local
static int tolua_zeus_CGDebugEngine_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGDebugEngine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGDebugEngine* tolua_ret = (CGDebugEngine*)  Mtolua_new((CGDebugEngine)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGDebugEngine");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CGDebugEngine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGDebugEngine_delete00
static int tolua_zeus_CGDebugEngine_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGDebugEngine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGDebugEngine* self = (CGDebugEngine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: gui_debug_x of class  CGDebugEngine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGDebugEngine_gui_debug_x00
static int tolua_zeus_CGDebugEngine_gui_debug_x00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGDebugEngine",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGDebugEngine* self = (CGDebugEngine*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  char debug_color = ((char)  tolua_tonumber(tolua_S,3,1));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gui_debug_x'", NULL);
#endif
  {
   self->gui_debug_x(*p,debug_color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gui_debug_x'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: gui_debug_line of class  CGDebugEngine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGDebugEngine_gui_debug_line00
static int tolua_zeus_CGDebugEngine_gui_debug_line00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGDebugEngine",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGDebugEngine* self = (CGDebugEngine*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* p1 = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  const CGeoPoint* p2 = ((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  char debug_color = ((char)  tolua_tonumber(tolua_S,4,1));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gui_debug_line'", NULL);
#endif
  {
   self->gui_debug_line(*p1,*p2,debug_color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gui_debug_line'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: gui_debug_arc of class  CGDebugEngine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGDebugEngine_gui_debug_arc00
static int tolua_zeus_CGDebugEngine_gui_debug_arc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGDebugEngine",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGDebugEngine* self = (CGDebugEngine*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  double r = ((double)  tolua_tonumber(tolua_S,3,0));
  double start_angle = ((double)  tolua_tonumber(tolua_S,4,0));
  double span_angle = ((double)  tolua_tonumber(tolua_S,5,0));
  char debug_color = ((char)  tolua_tonumber(tolua_S,6,1));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gui_debug_arc'", NULL);
#endif
  {
   self->gui_debug_arc(*p,r,start_angle,span_angle,debug_color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gui_debug_arc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: gui_debug_triangle of class  CGDebugEngine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGDebugEngine_gui_debug_triangle00
static int tolua_zeus_CGDebugEngine_gui_debug_triangle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGDebugEngine",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGDebugEngine* self = (CGDebugEngine*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* p1 = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  const CGeoPoint* p2 = ((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  const CGeoPoint* p3 = ((const CGeoPoint*)  tolua_tousertype(tolua_S,4,0));
  char debug_color = ((char)  tolua_tonumber(tolua_S,5,1));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gui_debug_triangle'", NULL);
#endif
  {
   self->gui_debug_triangle(*p1,*p2,*p3,debug_color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gui_debug_triangle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: gui_debug_robot of class  CGDebugEngine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGDebugEngine_gui_debug_robot00
static int tolua_zeus_CGDebugEngine_gui_debug_robot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGDebugEngine",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGDebugEngine* self = (CGDebugEngine*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  double robot_dir = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gui_debug_robot'", NULL);
#endif
  {
   self->gui_debug_robot(*p,robot_dir);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gui_debug_robot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: gui_debug_msg of class  CGDebugEngine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGDebugEngine_gui_debug_msg00
static int tolua_zeus_CGDebugEngine_gui_debug_msg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGDebugEngine",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGDebugEngine* self = (CGDebugEngine*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  const char* msgstr = ((const char*)  tolua_tostring(tolua_S,3,0));
  char debug_color = ((char)  tolua_tonumber(tolua_S,4,1));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gui_debug_msg'", NULL);
#endif
  {
   self->gui_debug_msg(*p,msgstr,debug_color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gui_debug_msg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: gui_debug_curve of class  CGDebugEngine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGDebugEngine_gui_debug_curve00
static int tolua_zeus_CGDebugEngine_gui_debug_curve00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGDebugEngine",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGDebugEngine* self = (CGDebugEngine*)  tolua_tousertype(tolua_S,1,0);
  const double num = ((const double)  tolua_tonumber(tolua_S,2,0));
  const double maxLimit = ((const double)  tolua_tonumber(tolua_S,3,0));
  const double minLimit = ((const double)  tolua_tonumber(tolua_S,4,0));
  char debug_color = ((char)  tolua_tonumber(tolua_S,5,1));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gui_debug_curve'", NULL);
#endif
  {
   self->gui_debug_curve(num,maxLimit,minLimit,debug_color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gui_debug_curve'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_new00
static int tolua_zeus_CWorldModel_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CWorldModel* tolua_ret = (CWorldModel*)  Mtolua_new((CWorldModel)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CWorldModel");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_new00_local
static int tolua_zeus_CWorldModel_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CWorldModel* tolua_ret = (CWorldModel*)  Mtolua_new((CWorldModel)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CWorldModel");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: vision of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_vision00
static int tolua_zeus_CWorldModel_vision00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'vision'", NULL);
#endif
  {
   const CVisionModule* tolua_ret = (const CVisionModule*)  self->vision();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"const CVisionModule");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'vision'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OurRobotNum of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_OurRobotNum00
static int tolua_zeus_CWorldModel_OurRobotNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OurRobotNum'", NULL);
#endif
  {
   int tolua_ret = (int)  self->OurRobotNum();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OurRobotNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRealNum of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_GetRealNum00
static int tolua_zeus_CWorldModel_GetRealNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int tolua_var_10 = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRealNum'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetRealNum(tolua_var_10);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRealNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTacticNum of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_GetTacticNum00
static int tolua_zeus_CWorldModel_GetTacticNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int tolua_var_11 = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTacticNum'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetTacticNum(tolua_var_11);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTacticNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: KickDirArrived of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_KickDirArrived00
static int tolua_zeus_CWorldModel_KickDirArrived00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int tolua_var_12 = ((int)  tolua_tonumber(tolua_S,2,0));
  double tolua_var_13 = ((double)  tolua_tonumber(tolua_S,3,0));
  double tolua_var_14 = ((double)  tolua_tonumber(tolua_S,4,0));
  int tolua_var_15 = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'KickDirArrived'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->KickDirArrived(tolua_var_12,tolua_var_13,tolua_var_14,tolua_var_15);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'KickDirArrived'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsBallKicked of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_IsBallKicked00
static int tolua_zeus_CWorldModel_IsBallKicked00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int tolua_var_16 = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsBallKicked'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsBallKicked(tolua_var_16);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsBallKicked'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsInfraredOn of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_IsInfraredOn00
static int tolua_zeus_CWorldModel_IsInfraredOn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int tolua_var_17 = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsInfraredOn'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsInfraredOn(tolua_var_17);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsInfraredOn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SPlayFSMSwitchClearAll of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_SPlayFSMSwitchClearAll00
static int tolua_zeus_CWorldModel_SPlayFSMSwitchClearAll00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  bool clear_flag = ((bool)  tolua_toboolean(tolua_S,2,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SPlayFSMSwitchClearAll'", NULL);
#endif
  {
   self->SPlayFSMSwitchClearAll(clear_flag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SPlayFSMSwitchClearAll'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsBestPlayerChanged of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_IsBestPlayerChanged00
static int tolua_zeus_CWorldModel_IsBestPlayerChanged00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsBestPlayerChanged'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsBestPlayerChanged();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsBestPlayerChanged'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CanDefenceExit of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_CanDefenceExit00
static int tolua_zeus_CWorldModel_CanDefenceExit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CanDefenceExit'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->CanDefenceExit();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CanDefenceExit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: NeedExitAttackDef of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_NeedExitAttackDef00
static int tolua_zeus_CWorldModel_NeedExitAttackDef00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  CGeoPoint leftUp = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  CGeoPoint rightDown = *((CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  int mode = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NeedExitAttackDef'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->NeedExitAttackDef(leftUp,rightDown,mode);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NeedExitAttackDef'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ball2MarkingTouch of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_ball2MarkingTouch00
static int tolua_zeus_CWorldModel_ball2MarkingTouch00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  CGeoPoint leftUp = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  CGeoPoint rightDown = *((CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ball2MarkingTouch'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ball2MarkingTouch(leftUp,rightDown);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ball2MarkingTouch'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isMarkingFrontValid of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_isMarkingFrontValid00
static int tolua_zeus_CWorldModel_isMarkingFrontValid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  CGeoPoint tolua_var_18 = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  double tolua_var_19 = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isMarkingFrontValid'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isMarkingFrontValid(tolua_var_18,tolua_var_19);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isMarkingFrontValid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getEnemyKickOffNum of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_getEnemyKickOffNum00
static int tolua_zeus_CWorldModel_getEnemyKickOffNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getEnemyKickOffNum'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getEnemyKickOffNum();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEnemyKickOffNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMarkingTouchArea of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_getMarkingTouchArea00
static int tolua_zeus_CWorldModel_getMarkingTouchArea00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  CGeoPoint leftPos1 = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  CGeoPoint leftPos2 = *((CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  CGeoPoint rightPos1 = *((CGeoPoint*)  tolua_tousertype(tolua_S,4,0));
  CGeoPoint rightPos2 = *((CGeoPoint*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMarkingTouchArea'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getMarkingTouchArea(leftPos1,leftPos2,rightPos1,rightPos2);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMarkingTouchArea'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: checkEnemyKickOffNumChanged of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_checkEnemyKickOffNumChanged00
static int tolua_zeus_CWorldModel_checkEnemyKickOffNumChanged00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'checkEnemyKickOffNumChanged'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->checkEnemyKickOffNumChanged();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'checkEnemyKickOffNumChanged'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CurrentBayes of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_CurrentBayes00
static int tolua_zeus_CWorldModel_CurrentBayes00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CurrentBayes'", NULL);
#endif
  {
   string tolua_ret = (string)  self->CurrentBayes();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CurrentBayes'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: canProtectBall of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_canProtectBall00
static int tolua_zeus_CWorldModel_canProtectBall00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int current_cycle = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'canProtectBall'", NULL);
#endif
  {
   const bool tolua_ret = (const bool)  self->canProtectBall(current_cycle);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'canProtectBall'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: canShootOnBallPos of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_canShootOnBallPos00
static int tolua_zeus_CWorldModel_canShootOnBallPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int current_cycle = ((int)  tolua_tonumber(tolua_S,2,0));
  int myNum = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'canShootOnBallPos'", NULL);
#endif
  {
   const bool tolua_ret = (const bool)  self->canShootOnBallPos(current_cycle,myNum);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'canShootOnBallPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: canPassOnBallPos of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_canPassOnBallPos00
static int tolua_zeus_CWorldModel_canPassOnBallPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int current_cycle = ((int)  tolua_tonumber(tolua_S,2,0));
  CGeoPoint* passPos = ((CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  CGeoPoint* guisePos = ((CGeoPoint*)  tolua_tousertype(tolua_S,4,0));
  int myNum = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'canPassOnBallPos'", NULL);
#endif
  {
   const bool tolua_ret = (const bool)  self->canPassOnBallPos(current_cycle,*passPos,*guisePos,myNum);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'canPassOnBallPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: canKickAtEnemy of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_canKickAtEnemy00
static int tolua_zeus_CWorldModel_canKickAtEnemy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int current_cycle = ((int)  tolua_tonumber(tolua_S,2,0));
  CGeoPoint* kickDir = ((CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  int myNum = ((int)  tolua_tonumber(tolua_S,4,0));
  int priority = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'canKickAtEnemy'", NULL);
#endif
  {
   const bool tolua_ret = (const bool)  self->canKickAtEnemy(current_cycle,*kickDir,myNum,priority);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'canKickAtEnemy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBallStatus of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_getBallStatus00
static int tolua_zeus_CWorldModel_getBallStatus00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int current_cycle = ((int)  tolua_tonumber(tolua_S,2,0));
  int meNum = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBallStatus'", NULL);
#endif
  {
   const string tolua_ret = (const string)  self->getBallStatus(current_cycle,meNum);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBallStatus'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAttackerAmount of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_getAttackerAmount00
static int tolua_zeus_CWorldModel_getAttackerAmount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int current_cycle = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAttackerAmount'", NULL);
#endif
  {
   const int tolua_ret = (const int)  self->getAttackerAmount(current_cycle);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAttackerAmount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAttackDecision of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_getAttackDecision00
static int tolua_zeus_CWorldModel_getAttackDecision00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int current_cycle = ((int)  tolua_tonumber(tolua_S,2,0));
  int meNum = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAttackDecision'", NULL);
#endif
  {
   const string tolua_ret = (const string)  self->getAttackDecision(current_cycle,meNum);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAttackDecision'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMessiAttackDecision of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_getMessiAttackDecision00
static int tolua_zeus_CWorldModel_getMessiAttackDecision00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int current_cycle = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMessiAttackDecision'", NULL);
#endif
  {
   const bool tolua_ret = (const bool)  self->getMessiAttackDecision(current_cycle);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMessiAttackDecision'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: generateTwoPassPoint of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_generateTwoPassPoint00
static int tolua_zeus_CWorldModel_generateTwoPassPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  CGeoPoint* passOne = ((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  CGeoPoint* passTwo = ((CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'generateTwoPassPoint'", NULL);
#endif
  {
   const bool tolua_ret = (const bool)  self->generateTwoPassPoint(*passOne,*passTwo);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'generateTwoPassPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTandemDir of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_getTandemDir00
static int tolua_zeus_CWorldModel_getTandemDir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int myNum = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTandemDir'", NULL);
#endif
  {
   const double tolua_ret = (const double)  self->getTandemDir(myNum);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTandemDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTandemPos of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_getTandemPos00
static int tolua_zeus_CWorldModel_getTandemPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int myNum = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTandemPos'", NULL);
#endif
  {
   const CGeoPoint tolua_ret = (const CGeoPoint)  self->getTandemPos(myNum);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"const CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(const CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"const CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTandemPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBallToucher of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_getBallToucher00
static int tolua_zeus_CWorldModel_getBallToucher00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBallToucher'", NULL);
#endif
  {
   const int tolua_ret = (const int)  self->getBallToucher();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBallToucher'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLastBallToucher of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_getLastBallToucher00
static int tolua_zeus_CWorldModel_getLastBallToucher00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLastBallToucher'", NULL);
#endif
  {
   const int tolua_ret = (const int)  self->getLastBallToucher();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLastBallToucher'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBallChipLine of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_getBallChipLine00
static int tolua_zeus_CWorldModel_getBallChipLine00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBallChipLine'", NULL);
#endif
  {
   const CGeoLine tolua_ret = (const CGeoLine)  self->getBallChipLine();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoLine)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"const CGeoLine");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(const CGeoLine));
     tolua_pushusertype(tolua_S,tolua_obj,"const CGeoLine");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBallChipLine'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsOurBallByAutoReferee of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_IsOurBallByAutoReferee00
static int tolua_zeus_CWorldModel_IsOurBallByAutoReferee00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsOurBallByAutoReferee'", NULL);
#endif
  {
   const bool tolua_ret = (const bool)  self->IsOurBallByAutoReferee();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsOurBallByAutoReferee'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clearBallStateCouter of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_clearBallStateCouter00
static int tolua_zeus_CWorldModel_clearBallStateCouter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clearBallStateCouter'", NULL);
#endif
  {
   self->clearBallStateCouter();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearBallStateCouter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSuitSider of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_getSuitSider00
static int tolua_zeus_CWorldModel_getSuitSider00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSuitSider'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getSuitSider();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSuitSider'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBallHandler of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_setBallHandler00
static int tolua_zeus_CWorldModel_setBallHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBallHandler'", NULL);
#endif
  {
   self->setBallHandler(num);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBallHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isRecordRunPos of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_isRecordRunPos00
static int tolua_zeus_CWorldModel_isRecordRunPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isRecordRunPos'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isRecordRunPos();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isRecordRunPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isBeingMarked of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_isBeingMarked00
static int tolua_zeus_CWorldModel_isBeingMarked00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int myNum = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isBeingMarked'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isBeingMarked(myNum);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isBeingMarked'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isPassLineBlocked of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_isPassLineBlocked00
static int tolua_zeus_CWorldModel_isPassLineBlocked00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int myNum = ((int)  tolua_tonumber(tolua_S,2,0));
  double allowance = ((double)  tolua_tonumber(tolua_S,3,4.0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isPassLineBlocked'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isPassLineBlocked(myNum,allowance);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isPassLineBlocked'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isShootLineBlocked of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_isShootLineBlocked00
static int tolua_zeus_CWorldModel_isShootLineBlocked00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int myNum = ((int)  tolua_tonumber(tolua_S,2,0));
  double range = ((double)  tolua_tonumber(tolua_S,3,150));
  double allowance = ((double)  tolua_tonumber(tolua_S,4,3.0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isShootLineBlocked'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isShootLineBlocked(myNum,range,allowance);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isShootLineBlocked'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isShootLineBlockedFromPoint of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_isShootLineBlockedFromPoint00
static int tolua_zeus_CWorldModel_isShootLineBlockedFromPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  CGeoPoint pos = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  double range = ((double)  tolua_tonumber(tolua_S,3,150));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isShootLineBlockedFromPoint'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isShootLineBlockedFromPoint(pos,range);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isShootLineBlockedFromPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: drawReflect of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_drawReflect00
static int tolua_zeus_CWorldModel_drawReflect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int myNum = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'drawReflect'", NULL);
#endif
  {
   self->drawReflect(myNum);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'drawReflect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLeftReflectPos of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_getLeftReflectPos00
static int tolua_zeus_CWorldModel_getLeftReflectPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int myNum = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLeftReflectPos'", NULL);
#endif
  {
   const CGeoPoint tolua_ret = (const CGeoPoint)  self->getLeftReflectPos(myNum);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"const CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(const CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"const CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLeftReflectPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRightReflectPos of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_getRightReflectPos00
static int tolua_zeus_CWorldModel_getRightReflectPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int myNum = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRightReflectPos'", NULL);
#endif
  {
   const CGeoPoint tolua_ret = (const CGeoPoint)  self->getRightReflectPos(myNum);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"const CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(const CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"const CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRightReflectPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getReflectPos of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_getReflectPos00
static int tolua_zeus_CWorldModel_getReflectPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int myNum = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getReflectPos'", NULL);
#endif
  {
   const CGeoPoint tolua_ret = (const CGeoPoint)  self->getReflectPos(myNum);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"const CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(const CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"const CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getReflectPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getReflectTouchPos of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_getReflectTouchPos00
static int tolua_zeus_CWorldModel_getReflectTouchPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int myNum = ((int)  tolua_tonumber(tolua_S,2,0));
  double y = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getReflectTouchPos'", NULL);
#endif
  {
   const CGeoPoint tolua_ret = (const CGeoPoint)  self->getReflectTouchPos(myNum,y);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"const CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(const CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"const CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getReflectTouchPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_new00
static int tolua_zeus_CKickStatus_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CKickStatus",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CKickStatus* tolua_ret = (CKickStatus*)  Mtolua_new((CKickStatus)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CKickStatus");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_new00_local
static int tolua_zeus_CKickStatus_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CKickStatus",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CKickStatus* tolua_ret = (CKickStatus*)  Mtolua_new((CKickStatus)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CKickStatus");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setKick of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_setKick00
static int tolua_zeus_CKickStatus_setKick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickStatus* self = (CKickStatus*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
  double power = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setKick'", NULL);
#endif
  {
   self->setKick(num,power);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setKick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setChipKick of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_setChipKick00
static int tolua_zeus_CKickStatus_setChipKick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickStatus* self = (CKickStatus*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
  double power = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setChipKick'", NULL);
#endif
  {
   self->setChipKick(num,power);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setChipKick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBothKick of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_setBothKick00
static int tolua_zeus_CKickStatus_setBothKick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickStatus* self = (CKickStatus*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
  double kick = ((double)  tolua_tonumber(tolua_S,3,0));
  double chip = ((double)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBothKick'", NULL);
#endif
  {
   self->setBothKick(num,kick,chip);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBothKick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAllKick of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_setAllKick00
static int tolua_zeus_CKickStatus_setAllKick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickStatus* self = (CKickStatus*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
  double kick = ((double)  tolua_tonumber(tolua_S,3,0));
  double chip = ((double)  tolua_tonumber(tolua_S,4,0));
  double pass = ((double)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAllKick'", NULL);
#endif
  {
   self->setAllKick(num,kick,chip,pass);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAllKick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: needKick of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_needKick00
static int tolua_zeus_CKickStatus_needKick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CKickStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CKickStatus* self = (const CKickStatus*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'needKick'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->needKick(num);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'needKick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getKickPower of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_getKickPower00
static int tolua_zeus_CKickStatus_getKickPower00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CKickStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CKickStatus* self = (const CKickStatus*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getKickPower'", NULL);
#endif
  {
   double tolua_ret = (double)  self->getKickPower(num);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getKickPower'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getChipKickDist of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_getChipKickDist00
static int tolua_zeus_CKickStatus_getChipKickDist00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CKickStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CKickStatus* self = (const CKickStatus*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getChipKickDist'", NULL);
#endif
  {
   double tolua_ret = (double)  self->getChipKickDist(num);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getChipKickDist'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPassDist of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_getPassDist00
static int tolua_zeus_CKickStatus_getPassDist00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CKickStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CKickStatus* self = (const CKickStatus*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPassDist'", NULL);
#endif
  {
   double tolua_ret = (double)  self->getPassDist(num);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPassDist'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getKiker of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_getKiker00
static int tolua_zeus_CKickStatus_getKiker00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CKickStatus",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CKickStatus* self = (const CKickStatus*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getKiker'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getKiker();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getKiker'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clearAll of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_clearAll00
static int tolua_zeus_CKickStatus_clearAll00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickStatus",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickStatus* self = (CKickStatus*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clearAll'", NULL);
#endif
  {
   self->clearAll();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearAll'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resetKick2ForceClose of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_resetKick2ForceClose00
static int tolua_zeus_CKickStatus_resetKick2ForceClose00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickStatus",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickStatus* self = (CKickStatus*)  tolua_tousertype(tolua_S,1,0);
  bool forceClose = ((bool)  tolua_toboolean(tolua_S,2,false));
  int forceCloseCycle = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resetKick2ForceClose'", NULL);
#endif
  {
   self->resetKick2ForceClose(forceClose,forceCloseCycle);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resetKick2ForceClose'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateForceClose of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_updateForceClose00
static int tolua_zeus_CKickStatus_updateForceClose00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickStatus* self = (CKickStatus*)  tolua_tousertype(tolua_S,1,0);
  int currentCycle = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateForceClose'", NULL);
#endif
  {
   self->updateForceClose(currentCycle);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateForceClose'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isForceClosed of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_isForceClosed00
static int tolua_zeus_CKickStatus_isForceClosed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickStatus",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickStatus* self = (CKickStatus*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isForceClosed'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isForceClosed();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isForceClosed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CTaskMediator */
#ifndef TOLUA_DISABLE_tolua_zeus_CTaskMediator_new00
static int tolua_zeus_CTaskMediator_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CTaskMediator",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CTaskMediator* tolua_ret = (CTaskMediator*)  Mtolua_new((CTaskMediator)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CTaskMediator");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CTaskMediator */
#ifndef TOLUA_DISABLE_tolua_zeus_CTaskMediator_new00_local
static int tolua_zeus_CTaskMediator_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CTaskMediator",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CTaskMediator* tolua_ret = (CTaskMediator*)  Mtolua_new((CTaskMediator)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CTaskMediator");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBallHandler of class  CTaskMediator */
#ifndef TOLUA_DISABLE_tolua_zeus_CTaskMediator_setBallHandler00
static int tolua_zeus_CTaskMediator_setBallHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTaskMediator",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTaskMediator* self = (CTaskMediator*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBallHandler'", NULL);
#endif
  {
   self->setBallHandler(num);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBallHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ballHandler of class  CTaskMediator */
#ifndef TOLUA_DISABLE_tolua_zeus_CTaskMediator_ballHandler00
static int tolua_zeus_CTaskMediator_ballHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CTaskMediator",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CTaskMediator* self = (const CTaskMediator*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ballHandler'", NULL);
#endif
  {
   int tolua_ret = (int)  self->ballHandler();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ballHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: goalie of class  CTaskMediator */
#ifndef TOLUA_DISABLE_tolua_zeus_CTaskMediator_goalie00
static int tolua_zeus_CTaskMediator_goalie00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTaskMediator",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTaskMediator* self = (CTaskMediator*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'goalie'", NULL);
#endif
  {
   int tolua_ret = (int)  self->goalie();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'goalie'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPlayerTask of class  CTaskMediator */
#ifndef TOLUA_DISABLE_tolua_zeus_CTaskMediator_setPlayerTask00
static int tolua_zeus_CTaskMediator_setPlayerTask00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTaskMediator",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CPlayerTask",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTaskMediator* self = (CTaskMediator*)  tolua_tousertype(tolua_S,1,0);
  const int num = ((const int)  tolua_tonumber(tolua_S,2,0));
  CPlayerTask* pTask = ((CPlayerTask*)  tolua_tousertype(tolua_S,3,0));
  const int priority = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPlayerTask'", NULL);
#endif
  {
   self->setPlayerTask(num,pTask,priority);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPlayerTask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPlayerTask of class  CTaskMediator */
#ifndef TOLUA_DISABLE_tolua_zeus_CTaskMediator_getPlayerTask00
static int tolua_zeus_CTaskMediator_getPlayerTask00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CTaskMediator",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CTaskMediator* self = (const CTaskMediator*)  tolua_tousertype(tolua_S,1,0);
  const int num = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPlayerTask'", NULL);
#endif
  {
   CPlayerTask* tolua_ret = (CPlayerTask*)  self->getPlayerTask(num);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CPlayerTask");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPlayerTask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPlayerTaskPriority of class  CTaskMediator */
#ifndef TOLUA_DISABLE_tolua_zeus_CTaskMediator_getPlayerTaskPriority00
static int tolua_zeus_CTaskMediator_getPlayerTaskPriority00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CTaskMediator",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CTaskMediator* self = (const CTaskMediator*)  tolua_tousertype(tolua_S,1,0);
  const int num = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPlayerTaskPriority'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getPlayerTaskPriority(num);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPlayerTaskPriority'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_new00
static int tolua_zeus_GameState_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameState* tolua_ret = (GameState*)  Mtolua_new((GameState)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameState");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_new00_local
static int tolua_zeus_GameState_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameState* tolua_ret = (GameState*)  Mtolua_new((GameState)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameState");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: gameOn of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_gameOn00
static int tolua_zeus_GameState_gameOn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gameOn'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->gameOn();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gameOn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: gameOff of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_gameOff00
static int tolua_zeus_GameState_gameOff00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gameOff'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->gameOff();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gameOff'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: gameOver of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_gameOver00
static int tolua_zeus_GameState_gameOver00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gameOver'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->gameOver();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gameOver'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: restart of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_restart00
static int tolua_zeus_GameState_restart00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'restart'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->restart();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'restart'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ourRestart of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_ourRestart00
static int tolua_zeus_GameState_ourRestart00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ourRestart'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ourRestart();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ourRestart'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: theirRestart of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_theirRestart00
static int tolua_zeus_GameState_theirRestart00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'theirRestart'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->theirRestart();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'theirRestart'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: canKickBall of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_canKickBall00
static int tolua_zeus_GameState_canKickBall00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'canKickBall'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->canKickBall();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'canKickBall'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: canEitherKickBall of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_canEitherKickBall00
static int tolua_zeus_GameState_canEitherKickBall00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'canEitherKickBall'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->canEitherKickBall();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'canEitherKickBall'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CDribbleStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CDribbleStatus_new00
static int tolua_zeus_CDribbleStatus_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CDribbleStatus",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CDribbleStatus* tolua_ret = (CDribbleStatus*)  Mtolua_new((CDribbleStatus)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CDribbleStatus");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CDribbleStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CDribbleStatus_new00_local
static int tolua_zeus_CDribbleStatus_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CDribbleStatus",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CDribbleStatus* tolua_ret = (CDribbleStatus*)  Mtolua_new((CDribbleStatus)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CDribbleStatus");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dribbleOn of class  CDribbleStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CDribbleStatus_dribbleOn00
static int tolua_zeus_CDribbleStatus_dribbleOn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CDribbleStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CDribbleStatus* self = (const CDribbleStatus*)  tolua_tousertype(tolua_S,1,0);
  int number = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dribbleOn'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->dribbleOn(number);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dribbleOn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ballController of class  CDribbleStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CDribbleStatus_ballController00
static int tolua_zeus_CDribbleStatus_ballController00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CDribbleStatus",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CDribbleStatus* self = (const CDribbleStatus*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ballController'", NULL);
#endif
  {
   int tolua_ret = (int)  self->ballController();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ballController'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ballControlled of class  CDribbleStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CDribbleStatus_ballControlled00
static int tolua_zeus_CDribbleStatus_ballControlled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CDribbleStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CDribbleStatus* self = (const CDribbleStatus*)  tolua_tousertype(tolua_S,1,0);
  int number = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ballControlled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ballControlled(number);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ballControlled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dribbleStartPosValid of class  CDribbleStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CDribbleStatus_dribbleStartPosValid00
static int tolua_zeus_CDribbleStatus_dribbleStartPosValid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CDribbleStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CDribbleStatus* self = (const CDribbleStatus*)  tolua_tousertype(tolua_S,1,0);
  int number = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dribbleStartPosValid'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->dribbleStartPosValid(number);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dribbleStartPosValid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: lastBallController of class  CDribbleStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CDribbleStatus_lastBallController00
static int tolua_zeus_CDribbleStatus_lastBallController00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CDribbleStatus",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CDribbleStatus* self = (const CDribbleStatus*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'lastBallController'", NULL);
#endif
  {
   int tolua_ret = (int)  self->lastBallController();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'lastBallController'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: lastBallController of class  CDribbleStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CDribbleStatus_lastBallController01
static int tolua_zeus_CDribbleStatus_lastBallController01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CDribbleStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CDribbleStatus* self = (const CDribbleStatus*)  tolua_tousertype(tolua_S,1,0);
  int number = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'lastBallController'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->lastBallController(number);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CDribbleStatus_lastBallController00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLastBallController of class  CDribbleStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CDribbleStatus_setLastBallController00
static int tolua_zeus_CDribbleStatus_setLastBallController00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDribbleStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDribbleStatus* self = (CDribbleStatus*)  tolua_tousertype(tolua_S,1,0);
  int number = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLastBallController'", NULL);
#endif
  {
   self->setLastBallController(number);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLastBallController'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dribbleStartPos of class  CDribbleStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CDribbleStatus_dribbleStartPos00
static int tolua_zeus_CDribbleStatus_dribbleStartPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CDribbleStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CDribbleStatus* self = (const CDribbleStatus*)  tolua_tousertype(tolua_S,1,0);
  int number = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dribbleStartPos'", NULL);
#endif
  {
   const CGeoPoint& tolua_ret = (const CGeoPoint&)  self->dribbleStartPos(number);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dribbleStartPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dribbleStartCycle of class  CDribbleStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CDribbleStatus_dribbleStartCycle00
static int tolua_zeus_CDribbleStatus_dribbleStartCycle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CDribbleStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CDribbleStatus* self = (const CDribbleStatus*)  tolua_tousertype(tolua_S,1,0);
  int number = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dribbleStartCycle'", NULL);
#endif
  {
   int tolua_ret = (int)  self->dribbleStartCycle(number);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dribbleStartCycle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDribbleOn of class  CDribbleStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CDribbleStatus_setDribbleOn00
static int tolua_zeus_CDribbleStatus_setDribbleOn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDribbleStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDribbleStatus* self = (CDribbleStatus*)  tolua_tousertype(tolua_S,1,0);
  int number = ((int)  tolua_tonumber(tolua_S,2,0));
  int cycle = ((int)  tolua_tonumber(tolua_S,3,0));
  const CGeoPoint* pos = ((const CGeoPoint*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDribbleOn'", NULL);
#endif
  {
   self->setDribbleOn(number,cycle,*pos);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDribbleOn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDribbleOff of class  CDribbleStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CDribbleStatus_setDribbleOff00
static int tolua_zeus_CDribbleStatus_setDribbleOff00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDribbleStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDribbleStatus* self = (CDribbleStatus*)  tolua_tousertype(tolua_S,1,0);
  int number = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDribbleOff'", NULL);
#endif
  {
   self->setDribbleOff(number);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDribbleOff'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDribbleStartPosLost of class  CDribbleStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CDribbleStatus_setDribbleStartPosLost00
static int tolua_zeus_CDribbleStatus_setDribbleStartPosLost00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDribbleStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDribbleStatus* self = (CDribbleStatus*)  tolua_tousertype(tolua_S,1,0);
  int number = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDribbleStartPosLost'", NULL);
#endif
  {
   self->setDribbleStartPosLost(number);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDribbleStartPosLost'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBallControlled of class  CDribbleStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CDribbleStatus_setBallControlled00
static int tolua_zeus_CDribbleStatus_setBallControlled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDribbleStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDribbleStatus* self = (CDribbleStatus*)  tolua_tousertype(tolua_S,1,0);
  int number = ((int)  tolua_tonumber(tolua_S,2,0));
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBallControlled'", NULL);
#endif
  {
   self->setBallControlled(number,*p);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBallControlled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBallLost of class  CDribbleStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CDribbleStatus_setBallLost00
static int tolua_zeus_CDribbleStatus_setBallLost00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDribbleStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDribbleStatus* self = (CDribbleStatus*)  tolua_tousertype(tolua_S,1,0);
  int number = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBallLost'", NULL);
#endif
  {
   self->setBallLost(number);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBallLost'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ballControlStarPos of class  CDribbleStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CDribbleStatus_ballControlStarPos00
static int tolua_zeus_CDribbleStatus_ballControlStarPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CDribbleStatus",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CDribbleStatus* self = (const CDribbleStatus*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ballControlStarPos'", NULL);
#endif
  {
   const CGeoPoint& tolua_ret = (const CGeoPoint&)  self->ballControlStarPos();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ballControlStarPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: needReleaseBall of class  CDribbleStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CDribbleStatus_needReleaseBall00
static int tolua_zeus_CDribbleStatus_needReleaseBall00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CDribbleStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CDribbleStatus* self = (const CDribbleStatus*)  tolua_tousertype(tolua_S,1,0);
  int number = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'needReleaseBall'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->needReleaseBall(number);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'needReleaseBall'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setNeedNotReleaseBall of class  CDribbleStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CDribbleStatus_setNeedNotReleaseBall00
static int tolua_zeus_CDribbleStatus_setNeedNotReleaseBall00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDribbleStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDribbleStatus* self = (CDribbleStatus*)  tolua_tousertype(tolua_S,1,0);
  int number = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setNeedNotReleaseBall'", NULL);
#endif
  {
   self->setNeedNotReleaseBall(number);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setNeedNotReleaseBall'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMayNeedReleaseBall of class  CDribbleStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CDribbleStatus_setMayNeedReleaseBall00
static int tolua_zeus_CDribbleStatus_setMayNeedReleaseBall00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDribbleStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDribbleStatus* self = (CDribbleStatus*)  tolua_tousertype(tolua_S,1,0);
  int number = ((int)  tolua_tonumber(tolua_S,2,0));
  const CGeoPoint* pos = ((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  bool dribbling = ((bool)  tolua_toboolean(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMayNeedReleaseBall'", NULL);
#endif
  {
   self->setMayNeedReleaseBall(number,*pos,dribbling);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMayNeedReleaseBall'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clearDribbleCommand of class  CDribbleStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CDribbleStatus_clearDribbleCommand00
static int tolua_zeus_CDribbleStatus_clearDribbleCommand00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDribbleStatus",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDribbleStatus* self = (CDribbleStatus*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clearDribbleCommand'", NULL);
#endif
  {
   self->clearDribbleCommand();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearDribbleCommand'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDribbleCommand of class  CDribbleStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CDribbleStatus_setDribbleCommand00
static int tolua_zeus_CDribbleStatus_setDribbleCommand00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDribbleStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDribbleStatus* self = (CDribbleStatus*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
  unsigned char power = ((unsigned char)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDribbleCommand'", NULL);
#endif
  {
   self->setDribbleCommand(num,power);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDribbleCommand'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDribbleCommand of class  CDribbleStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CDribbleStatus_getDribbleCommand00
static int tolua_zeus_CDribbleStatus_getDribbleCommand00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDribbleStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDribbleStatus* self = (CDribbleStatus*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDribbleCommand'", NULL);
#endif
  {
   unsigned char tolua_ret = (unsigned char)  self->getDribbleCommand(num);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDribbleCommand'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ballControlled of class  CDribbleStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CDribbleStatus_ballControlled01
static int tolua_zeus_CDribbleStatus_ballControlled01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDribbleStatus",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CDribbleStatus* self = (CDribbleStatus*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ballControlled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ballControlled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CDribbleStatus_ballControlled00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::Normalize */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_Normalize00
static int tolua_zeus_Utils_Normalize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  double angle = ((double)  tolua_tonumber(tolua_S,1,0));
  {
   double tolua_ret = (double)  Utils::Normalize(angle);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Normalize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::Polar2Vector */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_Polar2Vector00
static int tolua_zeus_Utils_Polar2Vector00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  double m = ((double)  tolua_tonumber(tolua_S,1,0));
  double angle = ((double)  tolua_tonumber(tolua_S,2,0));
  {
   CVector tolua_ret = (CVector)  Utils::Polar2Vector(m,angle);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CVector)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CVector));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Polar2Vector'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::VectorDot */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_VectorDot00
static int tolua_zeus_Utils_VectorDot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CVector",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVector* v1 = ((const CVector*)  tolua_tousertype(tolua_S,1,0));
  const CVector* v2 = ((const CVector*)  tolua_tousertype(tolua_S,2,0));
  {
   double tolua_ret = (double)  Utils::VectorDot(*v1,*v2);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'VectorDot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::InBetween */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_InBetween00
static int tolua_zeus_Utils_InBetween00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  const CGeoPoint* p1 = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  const CGeoPoint* p2 = ((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  {
   bool tolua_ret = (bool)  Utils::InBetween(*p,*p1,*p2);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InBetween'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::InBetween */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_InBetween01
static int tolua_zeus_Utils_InBetween01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  double v = ((double)  tolua_tonumber(tolua_S,1,0));
  double v1 = ((double)  tolua_tonumber(tolua_S,2,0));
  double v2 = ((double)  tolua_tonumber(tolua_S,3,0));
  {
   bool tolua_ret = (bool)  Utils::InBetween(v,v1,v2);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_Utils_InBetween00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::AngleBetween */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_AngleBetween00
static int tolua_zeus_Utils_AngleBetween00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  double d = ((double)  tolua_tonumber(tolua_S,1,0));
  double d1 = ((double)  tolua_tonumber(tolua_S,2,0));
  double d2 = ((double)  tolua_tonumber(tolua_S,3,0));
  double buffer = ((double)  tolua_tonumber(tolua_S,4,Param::Math::PI/30));
  {
   bool tolua_ret = (bool)  Utils::AngleBetween(d,d1,d2,buffer);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AngleBetween'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::InBetween */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_InBetween02
static int tolua_zeus_Utils_InBetween02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CVector",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CVector",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CVector",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CVector* v = ((const CVector*)  tolua_tousertype(tolua_S,1,0));
  const CVector* v1 = ((const CVector*)  tolua_tousertype(tolua_S,2,0));
  const CVector* v2 = ((const CVector*)  tolua_tousertype(tolua_S,3,0));
  double buffer = ((double)  tolua_tonumber(tolua_S,4,Param::Math::PI/30));
  {
   bool tolua_ret = (bool)  Utils::InBetween(*v,*v1,*v2,buffer);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_Utils_InBetween01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::Deg2Rad */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_Deg2Rad00
static int tolua_zeus_Utils_Deg2Rad00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  double angle = ((double)  tolua_tonumber(tolua_S,1,0));
  {
   double tolua_ret = (double)  Utils::Deg2Rad(angle);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Deg2Rad'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::Rad2Deg */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_Rad2Deg00
static int tolua_zeus_Utils_Rad2Deg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  double angle = ((double)  tolua_tonumber(tolua_S,1,0));
  {
   double tolua_ret = (double)  Utils::Rad2Deg(angle);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Rad2Deg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::MakeInField */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_MakeInField00
static int tolua_zeus_Utils_MakeInField00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  const double buffer = ((const double)  tolua_tonumber(tolua_S,2,0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  Utils::MakeInField(*p,buffer);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MakeInField'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::OutOfField */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_OutOfField00
static int tolua_zeus_Utils_OutOfField00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  const double buffer = ((const double)  tolua_tonumber(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  Utils::OutOfField(*p,buffer);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OutOfField'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::FieldLeft */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_FieldLeft00
static int tolua_zeus_Utils_FieldLeft00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   double tolua_ret = (double)  Utils::FieldLeft();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FieldLeft'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::FieldRight */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_FieldRight00
static int tolua_zeus_Utils_FieldRight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   double tolua_ret = (double)  Utils::FieldRight();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FieldRight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::FieldTop */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_FieldTop00
static int tolua_zeus_Utils_FieldTop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   double tolua_ret = (double)  Utils::FieldTop();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FieldTop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::FieldBottom */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_FieldBottom00
static int tolua_zeus_Utils_FieldBottom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   double tolua_ret = (double)  Utils::FieldBottom();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FieldBottom'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::LeftTop */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_LeftTop00
static int tolua_zeus_Utils_LeftTop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGeoPoint tolua_ret = (CGeoPoint)  Utils::LeftTop();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LeftTop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::RightBottom */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_RightBottom00
static int tolua_zeus_Utils_RightBottom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGeoPoint tolua_ret = (CGeoPoint)  Utils::RightBottom();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RightBottom'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::Sign */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_Sign00
static int tolua_zeus_Utils_Sign00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  double d = ((double)  tolua_tonumber(tolua_S,1,0));
  {
   int tolua_ret = (int)  Utils::Sign(d);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Sign'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::MakeOutOfOurPenaltyArea */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_MakeOutOfOurPenaltyArea00
static int tolua_zeus_Utils_MakeOutOfOurPenaltyArea00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  const double buffer = ((const double)  tolua_tonumber(tolua_S,2,0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  Utils::MakeOutOfOurPenaltyArea(*p,buffer);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MakeOutOfOurPenaltyArea'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::MakeOutOfCircleAndInField */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_MakeOutOfCircleAndInField00
static int tolua_zeus_Utils_MakeOutOfCircleAndInField00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* center = ((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  const double radius = ((const double)  tolua_tonumber(tolua_S,2,0));
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  const double buffer = ((const double)  tolua_tonumber(tolua_S,4,0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  Utils::MakeOutOfCircleAndInField(*center,radius,*p,buffer);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MakeOutOfCircleAndInField'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::InOurPenaltyArea */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_InOurPenaltyArea00
static int tolua_zeus_Utils_InOurPenaltyArea00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  const double buffer = ((const double)  tolua_tonumber(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  Utils::InOurPenaltyArea(*p,buffer);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InOurPenaltyArea'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::InTheirPenaltyArea */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_InTheirPenaltyArea00
static int tolua_zeus_Utils_InTheirPenaltyArea00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  const double buffer = ((const double)  tolua_tonumber(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  Utils::InTheirPenaltyArea(*p,buffer);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InTheirPenaltyArea'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::PlayerNumValid */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_PlayerNumValid00
static int tolua_zeus_Utils_PlayerNumValid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int num = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  Utils::PlayerNumValid(num);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PlayerNumValid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::canGo */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_canGo00
static int tolua_zeus_Utils_canGo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,1,0));
  const int num = ((const int)  tolua_tonumber(tolua_S,2,0));
  const CGeoPoint* target = ((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  const int flag = ((const int)  tolua_tonumber(tolua_S,4,0));
  const double avoidBuffer = ((const double)  tolua_tonumber(tolua_S,5,0));
  {
   bool tolua_ret = (bool)  Utils::canGo(pVision,num,*target,flag,avoidBuffer);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'canGo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Matrix<double> */
#ifndef TOLUA_DISABLE_tolua_zeus_Matrix_double__new00
static int tolua_zeus_Matrix_double__new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Matrix<double>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Matrix<double>* tolua_ret = (Matrix<double>*)  Mtolua_new((Matrix<double>)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Matrix<double>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Matrix<double> */
#ifndef TOLUA_DISABLE_tolua_zeus_Matrix_double__new00_local
static int tolua_zeus_Matrix_double__new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Matrix<double>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Matrix<double>* tolua_ret = (Matrix<double>*)  Mtolua_new((Matrix<double>)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Matrix<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Matrix<double> */
#ifndef TOLUA_DISABLE_tolua_zeus_Matrix_double__delete00
static int tolua_zeus_Matrix_double__delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Matrix<double>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Matrix<double>* self = (Matrix<double>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Matrix<double> */
#ifndef TOLUA_DISABLE_tolua_zeus_Matrix_double__new01
static int tolua_zeus_Matrix_double__new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Matrix<double>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int rows = ((int)  tolua_tonumber(tolua_S,2,0));
  int columns = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   Matrix<double>* tolua_ret = (Matrix<double>*)  Mtolua_new((Matrix<double>)(rows,columns));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Matrix<double>");
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_Matrix_double__new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Matrix<double> */
#ifndef TOLUA_DISABLE_tolua_zeus_Matrix_double__new01_local
static int tolua_zeus_Matrix_double__new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Matrix<double>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int rows = ((int)  tolua_tonumber(tolua_S,2,0));
  int columns = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   Matrix<double>* tolua_ret = (Matrix<double>*)  Mtolua_new((Matrix<double>)(rows,columns));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Matrix<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_Matrix_double__new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setValue of class  Matrix<double> */
#ifndef TOLUA_DISABLE_tolua_zeus_Matrix_double__setValue00
static int tolua_zeus_Matrix_double__setValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Matrix<double>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Matrix<double>* self = (Matrix<double>*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
  double value = ((double)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setValue'", NULL);
#endif
  {
   self->setValue(x,y,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getValue of class  Matrix<double> */
#ifndef TOLUA_DISABLE_tolua_zeus_Matrix_double__getValue00
static int tolua_zeus_Matrix_double__getValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Matrix<double>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Matrix<double>* self = (Matrix<double>*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getValue'", NULL);
#endif
  {
   double tolua_ret = (double)  self->getValue(x,y);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Munkres */
#ifndef TOLUA_DISABLE_tolua_zeus_Munkres_new00
static int tolua_zeus_Munkres_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Munkres",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Munkres* tolua_ret = (Munkres*)  Mtolua_new((Munkres)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Munkres");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Munkres */
#ifndef TOLUA_DISABLE_tolua_zeus_Munkres_new00_local
static int tolua_zeus_Munkres_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Munkres",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Munkres* tolua_ret = (Munkres*)  Mtolua_new((Munkres)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Munkres");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Munkres */
#ifndef TOLUA_DISABLE_tolua_zeus_Munkres_delete00
static int tolua_zeus_Munkres_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Munkres",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Munkres* self = (Munkres*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: solve of class  Munkres */
#ifndef TOLUA_DISABLE_tolua_zeus_Munkres_solve00
static int tolua_zeus_Munkres_solve00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Munkres",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Matrix<double>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Munkres* self = (Munkres*)  tolua_tousertype(tolua_S,1,0);
  Matrix<double>* tolua_var_20 = ((Matrix<double>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'solve'", NULL);
#endif
  {
   self->solve(*tolua_var_20);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'solve'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CKickDirection */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickDirection_new00
static int tolua_zeus_CKickDirection_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CKickDirection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CKickDirection* tolua_ret = (CKickDirection*)  Mtolua_new((CKickDirection)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CKickDirection");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CKickDirection */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickDirection_new00_local
static int tolua_zeus_CKickDirection_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CKickDirection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CKickDirection* tolua_ret = (CKickDirection*)  Mtolua_new((CKickDirection)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CKickDirection");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GenerateShootDir of class  CKickDirection */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickDirection_GenerateShootDir00
static int tolua_zeus_CKickDirection_GenerateShootDir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickDirection",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickDirection* self = (CKickDirection*)  tolua_tousertype(tolua_S,1,0);
  const int player = ((const int)  tolua_tonumber(tolua_S,2,0));
  const CGeoPoint pos = *((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GenerateShootDir'", NULL);
#endif
  {
   self->GenerateShootDir(player,pos);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GenerateShootDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getKickValid of class  CKickDirection */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickDirection_getKickValid00
static int tolua_zeus_CKickDirection_getKickValid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickDirection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickDirection* self = (CKickDirection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getKickValid'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getKickValid();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getKickValid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCompensate of class  CKickDirection */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickDirection_getCompensate00
static int tolua_zeus_CKickDirection_getCompensate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickDirection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickDirection* self = (CKickDirection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCompensate'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getCompensate();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCompensate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRawKickDir of class  CKickDirection */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickDirection_getRawKickDir00
static int tolua_zeus_CKickDirection_getRawKickDir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickDirection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickDirection* self = (CKickDirection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRawKickDir'", NULL);
#endif
  {
   double tolua_ret = (double)  self->getRawKickDir();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRawKickDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCompensateDir of class  CKickDirection */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickDirection_getCompensateDir00
static int tolua_zeus_CKickDirection_getCompensateDir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickDirection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickDirection* self = (CKickDirection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCompensateDir'", NULL);
#endif
  {
   double tolua_ret = (double)  self->getCompensateDir();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCompensateDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRealKickDir of class  CKickDirection */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickDirection_getRealKickDir00
static int tolua_zeus_CKickDirection_getRealKickDir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickDirection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickDirection* self = (CKickDirection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRealKickDir'", NULL);
#endif
  {
   double tolua_ret = (double)  self->getRealKickDir();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRealKickDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: calCompensate of class  CKickDirection */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickDirection_calCompensate00
static int tolua_zeus_CKickDirection_calCompensate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickDirection",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickDirection* self = (CKickDirection*)  tolua_tousertype(tolua_S,1,0);
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
  double y = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'calCompensate'", NULL);
#endif
  {
   double tolua_ret = (double)  self->calCompensate(x,y);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'calCompensate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::reversePoint */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_reversePoint00
static int tolua_zeus_DefendUtils_reversePoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  DefendUtils::reversePoint(*p);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reversePoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::calcBlockAngle */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_calcBlockAngle00
static int tolua_zeus_DefendUtils_calcBlockAngle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* target = ((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  const CGeoPoint* player = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  {
   double tolua_ret = (double)  DefendUtils::calcBlockAngle(*target,*player);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'calcBlockAngle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::isPosInOurPenaltyArea */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_isPosInOurPenaltyArea00
static int tolua_zeus_DefendUtils_isPosInOurPenaltyArea00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  DefendUtils::isPosInOurPenaltyArea(*p);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isPosInOurPenaltyArea'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::leftCirValid */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_leftCirValid00
static int tolua_zeus_DefendUtils_leftCirValid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  DefendUtils::leftCirValid(*p);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'leftCirValid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::rightCirValid */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_rightCirValid00
static int tolua_zeus_DefendUtils_rightCirValid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  DefendUtils::rightCirValid(*p);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rightCirValid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::getEnemyShooter */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_getEnemyShooter00
static int tolua_zeus_DefendUtils_getEnemyShooter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   int tolua_ret = (int)  DefendUtils::getEnemyShooter();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEnemyShooter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::getPenaltyFronter */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_getPenaltyFronter00
static int tolua_zeus_DefendUtils_getPenaltyFronter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   int tolua_ret = (int)  DefendUtils::getPenaltyFronter();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPenaltyFronter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::getDefenceTargetAndLine */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_getDefenceTargetAndLine00
static int tolua_zeus_DefendUtils_getDefenceTargetAndLine00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoPoint* RdefenceTarget = ((CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  double RdefendDir = ((double)  tolua_tonumber(tolua_S,2,0));
  {
   CGeoLine tolua_ret = (CGeoLine)  DefendUtils::getDefenceTargetAndLine(*RdefenceTarget,RdefendDir);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoLine)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoLine");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoLine));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoLine");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
   tolua_pushnumber(tolua_S,(lua_Number)RdefendDir);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDefenceTargetAndLine'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::calcDefenderPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_calcDefenderPoint00
static int tolua_zeus_DefendUtils_calcDefenderPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint Rtarget = *((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  const double Rdir = ((const double)  tolua_tonumber(tolua_S,2,0));
  const posSide Rside = ((const posSide) (int)  tolua_tonumber(tolua_S,3,0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  DefendUtils::calcDefenderPoint(Rtarget,Rdir,Rside);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'calcDefenderPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::getCornerAreaPos */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_getCornerAreaPos00
static int tolua_zeus_DefendUtils_getCornerAreaPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGeoPoint tolua_ret = (CGeoPoint)  DefendUtils::getCornerAreaPos();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCornerAreaPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::getIndirectDefender */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_getIndirectDefender00
static int tolua_zeus_DefendUtils_getIndirectDefender00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  double radius = ((double)  tolua_tonumber(tolua_S,1,0));
  CGeoPoint leftUp = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  CGeoPoint rightDown = *((CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  int mode = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  DefendUtils::getIndirectDefender(radius,leftUp,rightDown,mode);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIndirectDefender'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::getMiddleDefender */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_getMiddleDefender00
static int tolua_zeus_DefendUtils_getMiddleDefender00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  double bufferX = ((double)  tolua_tonumber(tolua_S,1,0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  DefendUtils::getMiddleDefender(bufferX);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMiddleDefender'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::getDefaultPos */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_getDefaultPos00
static int tolua_zeus_DefendUtils_getDefaultPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int index = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  DefendUtils::getDefaultPos(index);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDefaultPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::calcBalltoOurPenaty */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_calcBalltoOurPenaty00
static int tolua_zeus_DefendUtils_calcBalltoOurPenaty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   double tolua_ret = (double)  DefendUtils::calcBalltoOurPenaty();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'calcBalltoOurPenaty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_new00
static int tolua_zeus_CGPUBestAlgThread_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGPUBestAlgThread* tolua_ret = (CGPUBestAlgThread*)  Mtolua_new((CGPUBestAlgThread)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGPUBestAlgThread");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_new00_local
static int tolua_zeus_CGPUBestAlgThread_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGPUBestAlgThread* tolua_ret = (CGPUBestAlgThread*)  Mtolua_new((CGPUBestAlgThread)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGPUBestAlgThread");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_delete00
static int tolua_zeus_CGPUBestAlgThread_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initialize of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_initialize00
static int tolua_zeus_CGPUBestAlgThread_initialize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
  CVisionModule* _pVision = ((CVisionModule*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initialize'", NULL);
#endif
  {
   self->initialize(_pVision);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initialize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBestPoint of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_getBestPoint00
static int tolua_zeus_CGPUBestAlgThread_getBestPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBestPoint'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getBestPoint();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBestPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBestPoint of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_getBestPoint01
static int tolua_zeus_CGPUBestAlgThread_getBestPoint01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint leftUp = *((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBestPoint'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getBestPoint(leftUp);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CGPUBestAlgThread_getBestPoint00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBestPoint of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_getBestPoint02
static int tolua_zeus_CGPUBestAlgThread_getBestPoint02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint leftUp = *((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  const CGeoPoint rightDown = *((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  const int pointKeeperNum = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBestPoint'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getBestPoint(leftUp,rightDown,pointKeeperNum);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CGPUBestAlgThread_getBestPoint01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBestPoint of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_getBestPoint03
static int tolua_zeus_CGPUBestAlgThread_getBestPoint03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"const ReCalModeT",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint leftUp = *((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  const CGeoPoint rightDown = *((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  const int pointKeeperNum = ((const int)  tolua_tonumber(tolua_S,4,0));
  const ReCalModeT* reCalMode = ((const ReCalModeT*)  tolua_tousertype(tolua_S,5,0));
  bool forceReset = ((bool)  tolua_toboolean(tolua_S,6,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBestPoint'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getBestPoint(leftUp,rightDown,pointKeeperNum,*reCalMode,forceReset);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CGPUBestAlgThread_getBestPoint02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: generatePointValue of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_generatePointValue00
static int tolua_zeus_CGPUBestAlgThread_generatePointValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'generatePointValue'", NULL);
#endif
  {
   self->generatePointValue();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'generatePointValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isLastOneValid of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_isLastOneValid00
static int tolua_zeus_CGPUBestAlgThread_isLastOneValid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isLastOneValid'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isLastOneValid(*p);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isLastOneValid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSendPoint of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_setSendPoint00
static int tolua_zeus_CGPUBestAlgThread_setSendPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint passPoint = *((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSendPoint'", NULL);
#endif
  {
   self->setSendPoint(passPoint);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSendPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPosPotential of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_getPosPotential00
static int tolua_zeus_CGPUBestAlgThread_getPosPotential00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint p = *((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPosPotential'", NULL);
#endif
  {
   double tolua_ret = (double)  self->getPosPotential(p);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPosPotential'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: bestPointForCornerKicks of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_bestPointForCornerKicks00
static int tolua_zeus_CGPUBestAlgThread_bestPointForCornerKicks00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
  bool isChip = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'bestPointForCornerKicks'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->bestPointForCornerKicks(isChip);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'bestPointForCornerKicks'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: bestPointForFrontKicks of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_bestPointForFrontKicks00
static int tolua_zeus_CGPUBestAlgThread_bestPointForFrontKicks00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'bestPointForFrontKicks'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->bestPointForFrontKicks();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'bestPointForFrontKicks'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: bestPointForBackKicks of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_bestPointForBackKicks00
static int tolua_zeus_CGPUBestAlgThread_bestPointForBackKicks00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'bestPointForBackKicks'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->bestPointForBackKicks();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'bestPointForBackKicks'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isChip of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_isChip00
static int tolua_zeus_CGPUBestAlgThread_isChip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isChip'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isChip();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isChip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isChip of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_isChip01
static int tolua_zeus_CGPUBestAlgThread_isChip01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
  const int robotnum = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isChip'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isChip(robotnum);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CGPUBestAlgThread_isChip00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: isChip of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_isChip02
static int tolua_zeus_CGPUBestAlgThread_isChip02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint passPoint = *((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isChip'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isChip(passPoint);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CGPUBestAlgThread_isChip01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getChipPower of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_getChipPower00
static int tolua_zeus_CGPUBestAlgThread_getChipPower00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getChipPower'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getChipPower();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getChipPower'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFixBuf of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_getFixBuf00
static int tolua_zeus_CGPUBestAlgThread_getFixBuf00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFixBuf'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getFixBuf();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFixBuf'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: numberReceive of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_numberReceive00
static int tolua_zeus_CGPUBestAlgThread_numberReceive00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,10,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
  int first = ((int)  tolua_tonumber(tolua_S,2,0));
  int second = ((int)  tolua_tonumber(tolua_S,3,0));
  int third = ((int)  tolua_tonumber(tolua_S,4,0));
  int fourth = ((int)  tolua_tonumber(tolua_S,5,0));
  int fifth = ((int)  tolua_tonumber(tolua_S,6,0));
  int sixth = ((int)  tolua_tonumber(tolua_S,7,0));
  int assister = ((int)  tolua_tonumber(tolua_S,8,0));
  int goalie = ((int)  tolua_tonumber(tolua_S,9,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'numberReceive'", NULL);
#endif
  {
   self->numberReceive(first,second,third,fourth,fifth,sixth,assister,goalie);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'numberReceive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: receiveOwnPos of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_receiveOwnPos00
static int tolua_zeus_CGPUBestAlgThread_receiveOwnPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"vector<CGeoPoint>",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
  vector<CGeoPoint> myPos = *((vector<CGeoPoint>*)  tolua_tousertype(tolua_S,2,0));
  int number = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'receiveOwnPos'", NULL);
#endif
  {
   self->receiveOwnPos(myPos,number);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'receiveOwnPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: detectModule of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_detectModule00
static int tolua_zeus_CGPUBestAlgThread_detectModule00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
  bool generatePos = ((bool)  tolua_toboolean(tolua_S,2,0));
  double detectDist = ((double)  tolua_tonumber(tolua_S,3,0));
  int detectCycle = ((int)  tolua_tonumber(tolua_S,4,0));
  bool useGoalie = ((bool)  tolua_toboolean(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'detectModule'", NULL);
#endif
  {
   self->detectModule(generatePos,detectDist,detectCycle,useGoalie);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'detectModule'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: detectDefendKickedModule of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_detectDefendKickedModule00
static int tolua_zeus_CGPUBestAlgThread_detectDefendKickedModule00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
  int checkAttepmts = ((int)  tolua_tonumber(tolua_S,2,0));
  int defendKickCycle = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'detectDefendKickedModule'", NULL);
#endif
  {
   self->detectDefendKickedModule(checkAttepmts,defendKickCycle);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'detectDefendKickedModule'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scanModule of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_scanModule00
static int tolua_zeus_CGPUBestAlgThread_scanModule00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scanModule'", NULL);
#endif
  {
   self->scanModule();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'scanModule'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: fakePosComputeModule of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_fakePosComputeModule00
static int tolua_zeus_CGPUBestAlgThread_fakePosComputeModule00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'fakePosComputeModule'", NULL);
#endif
  {
   self->fakePosComputeModule();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'fakePosComputeModule'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPosForFirstVehicle of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_getPosForFirstVehicle00
static int tolua_zeus_CGPUBestAlgThread_getPosForFirstVehicle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPosForFirstVehicle'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getPosForFirstVehicle();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPosForFirstVehicle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPosForSecondVehicle of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_getPosForSecondVehicle00
static int tolua_zeus_CGPUBestAlgThread_getPosForSecondVehicle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPosForSecondVehicle'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getPosForSecondVehicle();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPosForSecondVehicle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPosForThirdVehicle of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_getPosForThirdVehicle00
static int tolua_zeus_CGPUBestAlgThread_getPosForThirdVehicle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPosForThirdVehicle'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getPosForThirdVehicle();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPosForThirdVehicle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPosForFourthVehicle of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_getPosForFourthVehicle00
static int tolua_zeus_CGPUBestAlgThread_getPosForFourthVehicle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPosForFourthVehicle'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getPosForFourthVehicle();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPosForFourthVehicle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPosForFifthVehicle of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_getPosForFifthVehicle00
static int tolua_zeus_CGPUBestAlgThread_getPosForFifthVehicle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPosForFifthVehicle'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getPosForFifthVehicle();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPosForFifthVehicle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPosForSixthVehicle of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_getPosForSixthVehicle00
static int tolua_zeus_CGPUBestAlgThread_getPosForSixthVehicle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPosForSixthVehicle'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getPosForSixthVehicle();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPosForSixthVehicle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPosForAssister of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_getPosForAssister00
static int tolua_zeus_CGPUBestAlgThread_getPosForAssister00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPosForAssister'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getPosForAssister();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPosForAssister'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPosForGoalie of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_getPosForGoalie00
static int tolua_zeus_CGPUBestAlgThread_getPosForGoalie00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPosForGoalie'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getPosForGoalie();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPosForGoalie'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPosForShoot of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_getPosForShoot00
static int tolua_zeus_CGPUBestAlgThread_getPosForShoot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPosForShoot'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getPosForShoot();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPosForShoot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: generateJamPos of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_generateJamPos00
static int tolua_zeus_CGPUBestAlgThread_generateJamPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'generateJamPos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->generateJamPos();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'generateJamPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: detectMarkedOver of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_detectMarkedOver00
static int tolua_zeus_CGPUBestAlgThread_detectMarkedOver00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'detectMarkedOver'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->detectMarkedOver();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'detectMarkedOver'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: detectDefendKickedOver of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_detectDefendKickedOver00
static int tolua_zeus_CGPUBestAlgThread_detectDefendKickedOver00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'detectDefendKickedOver'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->detectDefendKickedOver();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'detectDefendKickedOver'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: detectAgain of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_detectAgain00
static int tolua_zeus_CGPUBestAlgThread_detectAgain00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'detectAgain'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->detectAgain();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'detectAgain'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scanOver of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_scanOver00
static int tolua_zeus_CGPUBestAlgThread_scanOver00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scanOver'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->scanOver();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'scanOver'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: canPass of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_canPass00
static int tolua_zeus_CGPUBestAlgThread_canPass00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'canPass'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->canPass();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'canPass'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isDefendedHead of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_isDefendedHead00
static int tolua_zeus_CGPUBestAlgThread_isDefendedHead00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isDefendedHead'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isDefendedHead();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isDefendedHead'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: allMarked of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_allMarked00
static int tolua_zeus_CGPUBestAlgThread_allMarked00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'allMarked'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->allMarked();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'allMarked'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isMarked of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_isMarked00
static int tolua_zeus_CGPUBestAlgThread_isMarked00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
  int number = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isMarked'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isMarked(number);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isMarked'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: changeLeaderOver of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_changeLeaderOver00
static int tolua_zeus_CGPUBestAlgThread_changeLeaderOver00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
  bool finishFlag = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'changeLeaderOver'", NULL);
#endif
  {
   self->changeLeaderOver(finishFlag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'changeLeaderOver'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: confirmPosForFirstVehicle of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_confirmPosForFirstVehicle00
static int tolua_zeus_CGPUBestAlgThread_confirmPosForFirstVehicle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'confirmPosForFirstVehicle'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->confirmPosForFirstVehicle();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'confirmPosForFirstVehicle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: confirmPosForSecondVehicle of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_confirmPosForSecondVehicle00
static int tolua_zeus_CGPUBestAlgThread_confirmPosForSecondVehicle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'confirmPosForSecondVehicle'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->confirmPosForSecondVehicle();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'confirmPosForSecondVehicle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: confirmPosForThirdVehicle of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_confirmPosForThirdVehicle00
static int tolua_zeus_CGPUBestAlgThread_confirmPosForThirdVehicle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'confirmPosForThirdVehicle'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->confirmPosForThirdVehicle();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'confirmPosForThirdVehicle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: confirmPosForFourthVehicle of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_confirmPosForFourthVehicle00
static int tolua_zeus_CGPUBestAlgThread_confirmPosForFourthVehicle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'confirmPosForFourthVehicle'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->confirmPosForFourthVehicle();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'confirmPosForFourthVehicle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: changeLeader of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_changeLeader00
static int tolua_zeus_CGPUBestAlgThread_changeLeader00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'changeLeader'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->changeLeader();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'changeLeader'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: leftD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_get_Defend2015_leftD
static int tolua_get_Defend2015_leftD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'leftD'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->leftD,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: leftD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_set_Defend2015_leftD
static int tolua_set_Defend2015_leftD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'leftD'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->leftD = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: rightD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_get_Defend2015_rightD
static int tolua_get_Defend2015_rightD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rightD'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->rightD,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: rightD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_set_Defend2015_rightD
static int tolua_set_Defend2015_rightD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rightD'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->rightD = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: middleD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_get_Defend2015_middleD
static int tolua_get_Defend2015_middleD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'middleD'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->middleD,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: middleD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_set_Defend2015_middleD
static int tolua_set_Defend2015_middleD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'middleD'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->middleD = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: singleD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_get_Defend2015_singleD
static int tolua_get_Defend2015_singleD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'singleD'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->singleD,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: singleD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_set_Defend2015_singleD
static int tolua_set_Defend2015_singleD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'singleD'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->singleD = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: goalieD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_get_Defend2015_goalieD
static int tolua_get_Defend2015_goalieD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'goalieD'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->goalieD,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: goalieD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_set_Defend2015_goalieD
static int tolua_set_Defend2015_goalieD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'goalieD'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->goalieD = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: sideD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_get_Defend2015_sideD
static int tolua_get_Defend2015_sideD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sideD'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->sideD,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: sideD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_set_Defend2015_sideD
static int tolua_set_Defend2015_sideD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sideD'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->sideD = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSidePos of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_zeus_Defend2015_getSidePos00
static int tolua_zeus_Defend2015_getSidePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Defend2015",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSidePos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getSidePos();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSidePos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLeftPos of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_zeus_Defend2015_getLeftPos00
static int tolua_zeus_Defend2015_getLeftPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Defend2015",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLeftPos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getLeftPos();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLeftPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRightPos of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_zeus_Defend2015_getRightPos00
static int tolua_zeus_Defend2015_getRightPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Defend2015",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRightPos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getRightPos();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRightPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMiddlePos of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_zeus_Defend2015_getMiddlePos00
static int tolua_zeus_Defend2015_getMiddlePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Defend2015",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMiddlePos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getMiddlePos();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMiddlePos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSinglePos of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_zeus_Defend2015_getSinglePos00
static int tolua_zeus_Defend2015_getSinglePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Defend2015",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSinglePos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getSinglePos();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSinglePos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getGoaliePos of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_zeus_Defend2015_getGoaliePos00
static int tolua_zeus_Defend2015_getGoaliePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Defend2015",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getGoaliePos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getGoaliePos();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getGoaliePos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CDefPos2015 */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefPos2015_new00
static int tolua_zeus_CDefPos2015_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CDefPos2015",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CDefPos2015* tolua_ret = (CDefPos2015*)  Mtolua_new((CDefPos2015)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CDefPos2015");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CDefPos2015 */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefPos2015_new00_local
static int tolua_zeus_CDefPos2015_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CDefPos2015",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CDefPos2015* tolua_ret = (CDefPos2015*)  Mtolua_new((CDefPos2015)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CDefPos2015");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CDefPos2015 */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefPos2015_delete00
static int tolua_zeus_CDefPos2015_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefPos2015",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefPos2015* self = (CDefPos2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: generatePos of class  CDefPos2015 */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefPos2015_generatePos00
static int tolua_zeus_CDefPos2015_generatePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefPos2015",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefPos2015* self = (CDefPos2015*)  tolua_tousertype(tolua_S,1,0);
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'generatePos'", NULL);
#endif
  {
   self->generatePos(pVision);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'generatePos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDefPos2015 of class  CDefPos2015 */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefPos2015_getDefPos201500
static int tolua_zeus_CDefPos2015_getDefPos201500(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefPos2015",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefPos2015* self = (CDefPos2015*)  tolua_tousertype(tolua_S,1,0);
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDefPos2015'", NULL);
#endif
  {
   Defend2015 tolua_ret = (Defend2015)  self->getDefPos2015(pVision);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Defend2015)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Defend2015");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Defend2015));
     tolua_pushusertype(tolua_S,tolua_obj,"Defend2015");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDefPos2015'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CTandemPos */
#ifndef TOLUA_DISABLE_tolua_zeus_CTandemPos_new00
static int tolua_zeus_CTandemPos_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CTandemPos",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CTandemPos* tolua_ret = (CTandemPos*)  Mtolua_new((CTandemPos)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CTandemPos");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CTandemPos */
#ifndef TOLUA_DISABLE_tolua_zeus_CTandemPos_new00_local
static int tolua_zeus_CTandemPos_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CTandemPos",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CTandemPos* tolua_ret = (CTandemPos*)  Mtolua_new((CTandemPos)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CTandemPos");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CTandemPos */
#ifndef TOLUA_DISABLE_tolua_zeus_CTandemPos_delete00
static int tolua_zeus_CTandemPos_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTandemPos",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTandemPos* self = (CTandemPos*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: generatePos of class  CTandemPos */
#ifndef TOLUA_DISABLE_tolua_zeus_CTandemPos_generatePos00
static int tolua_zeus_CTandemPos_generatePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTandemPos",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTandemPos* self = (CTandemPos*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'generatePos'", NULL);
#endif
  {
   self->generatePos();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'generatePos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTandemPos of class  CTandemPos */
#ifndef TOLUA_DISABLE_tolua_zeus_CTandemPos_getTandemPos00
static int tolua_zeus_CTandemPos_getTandemPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTandemPos",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTandemPos* self = (CTandemPos*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTandemPos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getTandemPos();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTandemPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CBestPlayer */
#ifndef TOLUA_DISABLE_tolua_zeus_CBestPlayer_new00
static int tolua_zeus_CBestPlayer_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CBestPlayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CBestPlayer* tolua_ret = (CBestPlayer*)  Mtolua_new((CBestPlayer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CBestPlayer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CBestPlayer */
#ifndef TOLUA_DISABLE_tolua_zeus_CBestPlayer_new00_local
static int tolua_zeus_CBestPlayer_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CBestPlayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CBestPlayer* tolua_ret = (CBestPlayer*)  Mtolua_new((CBestPlayer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CBestPlayer");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CBestPlayer */
#ifndef TOLUA_DISABLE_tolua_zeus_CBestPlayer_delete00
static int tolua_zeus_CBestPlayer_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CBestPlayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CBestPlayer* self = (CBestPlayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getOurBestPlayer of class  CBestPlayer */
#ifndef TOLUA_DISABLE_tolua_zeus_CBestPlayer_getOurBestPlayer00
static int tolua_zeus_CBestPlayer_getOurBestPlayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CBestPlayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CBestPlayer* self = (CBestPlayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getOurBestPlayer'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getOurBestPlayer();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getOurBestPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTheirBestPlayer of class  CBestPlayer */
#ifndef TOLUA_DISABLE_tolua_zeus_CBestPlayer_getTheirBestPlayer00
static int tolua_zeus_CBestPlayer_getTheirBestPlayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CBestPlayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CBestPlayer* self = (CBestPlayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTheirBestPlayer'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getTheirBestPlayer();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTheirBestPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTheirGoalie of class  CBestPlayer */
#ifndef TOLUA_DISABLE_tolua_zeus_CBestPlayer_getTheirGoalie00
static int tolua_zeus_CBestPlayer_getTheirGoalie00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CBestPlayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CBestPlayer* self = (CBestPlayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTheirGoalie'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getTheirGoalie();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTheirGoalie'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_new00
static int tolua_zeus_CDefenceInfo_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CDefenceInfo* tolua_ret = (CDefenceInfo*)  Mtolua_new((CDefenceInfo)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CDefenceInfo");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_new00_local
static int tolua_zeus_CDefenceInfo_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CDefenceInfo* tolua_ret = (CDefenceInfo*)  Mtolua_new((CDefenceInfo)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CDefenceInfo");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_delete00
static int tolua_zeus_CDefenceInfo_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initialization of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_initialization00
static int tolua_zeus_CDefenceInfo_initialization00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initialization'", NULL);
#endif
  {
   self->initialization();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initialization'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateDefenceInfo of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_updateDefenceInfo00
static int tolua_zeus_CDefenceInfo_updateDefenceInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateDefenceInfo'", NULL);
#endif
  {
   self->updateDefenceInfo(pVision);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateDefenceInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: changeAttrSet of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_changeAttrSet00
static int tolua_zeus_CDefenceInfo_changeAttrSet00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CAttributeSet",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
  CAttributeSet* as = ((CAttributeSet*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'changeAttrSet'", NULL);
#endif
  {
   self->changeAttrSet(*as);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'changeAttrSet'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAttackNum of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_getAttackNum00
static int tolua_zeus_CDefenceInfo_getAttackNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAttackNum'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getAttackNum();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAttackNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAttackOppNumByPri of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_getAttackOppNumByPri00
static int tolua_zeus_CDefenceInfo_getAttackOppNumByPri00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAttackOppNumByPri'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getAttackOppNumByPri(i);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAttackOppNumByPri'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSteadyAttackOppNumByPri of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_getSteadyAttackOppNumByPri00
static int tolua_zeus_CDefenceInfo_getSteadyAttackOppNumByPri00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSteadyAttackOppNumByPri'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getSteadyAttackOppNumByPri(i);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSteadyAttackOppNumByPri'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: queryMarked of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_queryMarked00
static int tolua_zeus_CDefenceInfo_queryMarked00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'queryMarked'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->queryMarked(i);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'queryMarked'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getOurMarkDenfender of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_getOurMarkDenfender00
static int tolua_zeus_CDefenceInfo_getOurMarkDenfender00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
  const int enemyNum = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getOurMarkDenfender'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getOurMarkDenfender(enemyNum);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getOurMarkDenfender'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTriggerState of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_getTriggerState00
static int tolua_zeus_CDefenceInfo_getTriggerState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTriggerState'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getTriggerState();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTriggerState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMarkList of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_setMarkList00
static int tolua_zeus_CDefenceInfo_setMarkList00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,2,0));
  int myNum = ((int)  tolua_tonumber(tolua_S,3,0));
  int enemyNum = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMarkList'", NULL);
#endif
  {
   self->setMarkList(pVision,myNum,enemyNum);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMarkList'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setNoMarkingField of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_setNoMarkingField00
static int tolua_zeus_CDefenceInfo_setNoMarkingField00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
  CGeoPoint upLeft = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  CGeoPoint downRight = *((CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setNoMarkingField'", NULL);
#endif
  {
   self->setNoMarkingField(upLeft,downRight);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setNoMarkingField'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clearNoMarkingField of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_clearNoMarkingField00
static int tolua_zeus_CDefenceInfo_clearNoMarkingField00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
  CGeoPoint upLeft = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  CGeoPoint downRight = *((CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clearNoMarkingField'", NULL);
#endif
  {
   self->clearNoMarkingField(upLeft,downRight);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearNoMarkingField'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clearAll of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_clearAll00
static int tolua_zeus_CDefenceInfo_clearAll00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clearAll'", NULL);
#endif
  {
   self->clearAll();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearAll'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setNoChangeFlag of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_setNoChangeFlag00
static int tolua_zeus_CDefenceInfo_setNoChangeFlag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setNoChangeFlag'", NULL);
#endif
  {
   self->setNoChangeFlag();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setNoChangeFlag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clearNoChangeFlag of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_clearNoChangeFlag00
static int tolua_zeus_CDefenceInfo_clearNoChangeFlag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clearNoChangeFlag'", NULL);
#endif
  {
   self->clearNoChangeFlag();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearNoChangeFlag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resetMarkingInfo of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_resetMarkingInfo00
static int tolua_zeus_CDefenceInfo_resetMarkingInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resetMarkingInfo'", NULL);
#endif
  {
   self->resetMarkingInfo();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resetMarkingInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NormalPlayUtils::generateTwoPassPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_NormalPlayUtils_generateTwoPassPoint00
static int tolua_zeus_NormalPlayUtils_generateTwoPassPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoPoint ball = *((CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  CGeoPoint* passPosOne = ((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  CGeoPoint* passPosTwo = ((CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  {
   bool tolua_ret = (bool)  NormalPlayUtils::generateTwoPassPoint(ball,*passPosOne,*passPosTwo);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'generateTwoPassPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NormalPlayUtils::isEnemyBlockShootLine */
#ifndef TOLUA_DISABLE_tolua_zeus_NormalPlayUtils_isEnemyBlockShootLine00
static int tolua_zeus_NormalPlayUtils_isEnemyBlockShootLine00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoPoint ball = *((CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  double shootDir = ((double)  tolua_tonumber(tolua_S,2,0));
  double range = ((double)  tolua_tonumber(tolua_S,3,0));
  {
   bool tolua_ret = (bool)  NormalPlayUtils::isEnemyBlockShootLine(ball,shootDir,range);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isEnemyBlockShootLine'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: onePos of class  TwoKickPos */
#ifndef TOLUA_DISABLE_tolua_get_TwoKickPos_onePos
static int tolua_get_TwoKickPos_onePos(lua_State* tolua_S)
{
  TwoKickPos* self = (TwoKickPos*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'onePos'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->onePos,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: onePos of class  TwoKickPos */
#ifndef TOLUA_DISABLE_tolua_set_TwoKickPos_onePos
static int tolua_set_TwoKickPos_onePos(lua_State* tolua_S)
{
  TwoKickPos* self = (TwoKickPos*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'onePos'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->onePos = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: anotherPos of class  TwoKickPos */
#ifndef TOLUA_DISABLE_tolua_get_TwoKickPos_anotherPos
static int tolua_get_TwoKickPos_anotherPos(lua_State* tolua_S)
{
  TwoKickPos* self = (TwoKickPos*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'anotherPos'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->anotherPos,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: anotherPos of class  TwoKickPos */
#ifndef TOLUA_DISABLE_tolua_set_TwoKickPos_anotherPos
static int tolua_set_TwoKickPos_anotherPos(lua_State* tolua_S)
{
  TwoKickPos* self = (TwoKickPos*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'anotherPos'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->anotherPos = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getOnePos of class  TwoKickPos */
#ifndef TOLUA_DISABLE_tolua_zeus_TwoKickPos_getOnePos00
static int tolua_zeus_TwoKickPos_getOnePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TwoKickPos",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TwoKickPos* self = (TwoKickPos*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getOnePos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getOnePos();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getOnePos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnotherPos of class  TwoKickPos */
#ifndef TOLUA_DISABLE_tolua_zeus_TwoKickPos_getAnotherPos00
static int tolua_zeus_TwoKickPos_getAnotherPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TwoKickPos",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TwoKickPos* self = (TwoKickPos*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAnotherPos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getAnotherPos();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAnotherPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: _Left of class  KickOffArea */
#ifndef TOLUA_DISABLE_tolua_get_KickOffArea__Left
static int tolua_get_KickOffArea__Left(lua_State* tolua_S)
{
  KickOffArea* self = (KickOffArea*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_Left'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->_Left,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: _Left of class  KickOffArea */
#ifndef TOLUA_DISABLE_tolua_set_KickOffArea__Left
static int tolua_set_KickOffArea__Left(lua_State* tolua_S)
{
  KickOffArea* self = (KickOffArea*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_Left'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->_Left = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: _Right of class  KickOffArea */
#ifndef TOLUA_DISABLE_tolua_get_KickOffArea__Right
static int tolua_get_KickOffArea__Right(lua_State* tolua_S)
{
  KickOffArea* self = (KickOffArea*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_Right'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->_Right,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: _Right of class  KickOffArea */
#ifndef TOLUA_DISABLE_tolua_set_KickOffArea__Right
static int tolua_set_KickOffArea__Right(lua_State* tolua_S)
{
  KickOffArea* self = (KickOffArea*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_Right'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->_Right = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: baseDir of class  KickOffArea */
#ifndef TOLUA_DISABLE_tolua_get_KickOffArea_baseDir
static int tolua_get_KickOffArea_baseDir(lua_State* tolua_S)
{
  KickOffArea* self = (KickOffArea*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseDir'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->baseDir);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: baseDir of class  KickOffArea */
#ifndef TOLUA_DISABLE_tolua_set_KickOffArea_baseDir
static int tolua_set_KickOffArea_baseDir(lua_State* tolua_S)
{
  KickOffArea* self = (KickOffArea*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseDir'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->baseDir = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: radius of class  KickOffArea */
#ifndef TOLUA_DISABLE_tolua_get_KickOffArea_radius
static int tolua_get_KickOffArea_radius(lua_State* tolua_S)
{
  KickOffArea* self = (KickOffArea*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'radius'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->radius);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: radius of class  KickOffArea */
#ifndef TOLUA_DISABLE_tolua_set_KickOffArea_radius
static int tolua_set_KickOffArea_radius(lua_State* tolua_S)
{
  KickOffArea* self = (KickOffArea*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'radius'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->radius = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CIndirectDefender */
#ifndef TOLUA_DISABLE_tolua_zeus_CIndirectDefender_new00
static int tolua_zeus_CIndirectDefender_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CIndirectDefender",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CIndirectDefender* tolua_ret = (CIndirectDefender*)  Mtolua_new((CIndirectDefender)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CIndirectDefender");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CIndirectDefender */
#ifndef TOLUA_DISABLE_tolua_zeus_CIndirectDefender_new00_local
static int tolua_zeus_CIndirectDefender_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CIndirectDefender",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CIndirectDefender* tolua_ret = (CIndirectDefender*)  Mtolua_new((CIndirectDefender)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CIndirectDefender");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CIndirectDefender */
#ifndef TOLUA_DISABLE_tolua_zeus_CIndirectDefender_delete00
static int tolua_zeus_CIndirectDefender_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CIndirectDefender",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CIndirectDefender* self = (CIndirectDefender*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTwoDefPos of class  CIndirectDefender */
#ifndef TOLUA_DISABLE_tolua_zeus_CIndirectDefender_getTwoDefPos00
static int tolua_zeus_CIndirectDefender_getTwoDefPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CIndirectDefender",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,7,&tolua_err) || !tolua_isusertype(tolua_S,7,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,8,&tolua_err) || !tolua_isusertype(tolua_S,8,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,9,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CIndirectDefender* self = (CIndirectDefender*)  tolua_tousertype(tolua_S,1,0);
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,2,0));
  double radius1 = ((double)  tolua_tonumber(tolua_S,3,0));
  CGeoPoint left1 = *((CGeoPoint*)  tolua_tousertype(tolua_S,4,0));
  CGeoPoint right1 = *((CGeoPoint*)  tolua_tousertype(tolua_S,5,0));
  double radius2 = ((double)  tolua_tonumber(tolua_S,6,0));
  CGeoPoint left2 = *((CGeoPoint*)  tolua_tousertype(tolua_S,7,0));
  CGeoPoint right2 = *((CGeoPoint*)  tolua_tousertype(tolua_S,8,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTwoDefPos'", NULL);
#endif
  {
   TwoKickPos tolua_ret = (TwoKickPos)  self->getTwoDefPos(pVision,radius1,left1,right1,radius2,left2,right2);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((TwoKickPos)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"TwoKickPos");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(TwoKickPos));
     tolua_pushusertype(tolua_S,tolua_obj,"TwoKickPos");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTwoDefPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CSupportPos */
#ifndef TOLUA_DISABLE_tolua_zeus_CSupportPos_new00
static int tolua_zeus_CSupportPos_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CSupportPos",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CSupportPos* tolua_ret = (CSupportPos*)  Mtolua_new((CSupportPos)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CSupportPos");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CSupportPos */
#ifndef TOLUA_DISABLE_tolua_zeus_CSupportPos_new00_local
static int tolua_zeus_CSupportPos_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CSupportPos",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CSupportPos* tolua_ret = (CSupportPos*)  Mtolua_new((CSupportPos)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CSupportPos");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CSupportPos */
#ifndef TOLUA_DISABLE_tolua_zeus_CSupportPos_delete00
static int tolua_zeus_CSupportPos_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSupportPos",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSupportPos* self = (CSupportPos*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: generatePos of class  CSupportPos */
#ifndef TOLUA_DISABLE_tolua_zeus_CSupportPos_generatePos00
static int tolua_zeus_CSupportPos_generatePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSupportPos",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSupportPos* self = (CSupportPos*)  tolua_tousertype(tolua_S,1,0);
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,2,0));
  int num = ((int)  tolua_tonumber(tolua_S,3,0));
  int num2 = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'generatePos'", NULL);
#endif
  {
   self->generatePos(pVision,num,num2);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'generatePos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSupPos of class  CSupportPos */
#ifndef TOLUA_DISABLE_tolua_zeus_CSupportPos_getSupPos00
static int tolua_zeus_CSupportPos_getSupPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSupportPos",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSupportPos* self = (CSupportPos*)  tolua_tousertype(tolua_S,1,0);
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,2,0));
  int num = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSupPos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getSupPos(pVision,num);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSupPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSupPosNew of class  CSupportPos */
#ifndef TOLUA_DISABLE_tolua_zeus_CSupportPos_getSupPosNew00
static int tolua_zeus_CSupportPos_getSupPosNew00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSupportPos",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSupportPos* self = (CSupportPos*)  tolua_tousertype(tolua_S,1,0);
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,2,0));
  int num1 = ((int)  tolua_tonumber(tolua_S,3,0));
  int num2 = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSupPosNew'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getSupPosNew(pVision,num1,num2);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSupPosNew'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CAssistPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CAssistPoint_new00
static int tolua_zeus_CAssistPoint_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CAssistPoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CAssistPoint* tolua_ret = (CAssistPoint*)  Mtolua_new((CAssistPoint)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CAssistPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CAssistPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CAssistPoint_new00_local
static int tolua_zeus_CAssistPoint_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CAssistPoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CAssistPoint* tolua_ret = (CAssistPoint*)  Mtolua_new((CAssistPoint)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CAssistPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CAssistPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CAssistPoint_delete00
static int tolua_zeus_CAssistPoint_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CAssistPoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CAssistPoint* self = (CAssistPoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBestAssistPoint of class  CAssistPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CAssistPoint_getBestAssistPoint00
static int tolua_zeus_CAssistPoint_getBestAssistPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CAssistPoint",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CAssistPoint* self = (CAssistPoint*)  tolua_tousertype(tolua_S,1,0);
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,2,0));
  int leaderNum = ((int)  tolua_tonumber(tolua_S,3,0));
  int assistNum = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBestAssistPoint'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getBestAssistPoint(pVision,leaderNum,assistNum);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBestAssistPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: generateBestPoint of class  CAssistPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CAssistPoint_generateBestPoint00
static int tolua_zeus_CAssistPoint_generateBestPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CAssistPoint",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CAssistPoint* self = (CAssistPoint*)  tolua_tousertype(tolua_S,1,0);
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,2,0));
  int leadNum = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'generateBestPoint'", NULL);
#endif
  {
   self->generateBestPoint(pVision,leadNum);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'generateBestPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CMessiDecision */
#ifndef TOLUA_DISABLE_tolua_zeus_CMessiDecision_new00
static int tolua_zeus_CMessiDecision_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMessiDecision",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CMessiDecision* tolua_ret = (CMessiDecision*)  Mtolua_new((CMessiDecision)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMessiDecision");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CMessiDecision */
#ifndef TOLUA_DISABLE_tolua_zeus_CMessiDecision_new00_local
static int tolua_zeus_CMessiDecision_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMessiDecision",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CMessiDecision* tolua_ret = (CMessiDecision*)  Mtolua_new((CMessiDecision)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMessiDecision");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: messiRun of class  CMessiDecision */
#ifndef TOLUA_DISABLE_tolua_zeus_CMessiDecision_messiRun00
static int tolua_zeus_CMessiDecision_messiRun00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMessiDecision",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMessiDecision* self = (CMessiDecision*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'messiRun'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->messiRun();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'messiRun'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: nextState of class  CMessiDecision */
#ifndef TOLUA_DISABLE_tolua_zeus_CMessiDecision_nextState00
static int tolua_zeus_CMessiDecision_nextState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMessiDecision",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMessiDecision* self = (CMessiDecision*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'nextState'", NULL);
#endif
  {
   string tolua_ret = (string)  self->nextState();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'nextState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: leaderNum of class  CMessiDecision */
#ifndef TOLUA_DISABLE_tolua_zeus_CMessiDecision_leaderNum00
static int tolua_zeus_CMessiDecision_leaderNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMessiDecision",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMessiDecision* self = (CMessiDecision*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'leaderNum'", NULL);
#endif
  {
   int tolua_ret = (int)  self->leaderNum();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'leaderNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: receiverNum of class  CMessiDecision */
#ifndef TOLUA_DISABLE_tolua_zeus_CMessiDecision_receiverNum00
static int tolua_zeus_CMessiDecision_receiverNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMessiDecision",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMessiDecision* self = (CMessiDecision*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'receiverNum'", NULL);
#endif
  {
   int tolua_ret = (int)  self->receiverNum();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'receiverNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: attackerAmount of class  CMessiDecision */
#ifndef TOLUA_DISABLE_tolua_zeus_CMessiDecision_attackerAmount00
static int tolua_zeus_CMessiDecision_attackerAmount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMessiDecision",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMessiDecision* self = (CMessiDecision*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'attackerAmount'", NULL);
#endif
  {
   int tolua_ret = (int)  self->attackerAmount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'attackerAmount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: passPos of class  CMessiDecision */
#ifndef TOLUA_DISABLE_tolua_zeus_CMessiDecision_passPos00
static int tolua_zeus_CMessiDecision_passPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMessiDecision",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMessiDecision* self = (CMessiDecision*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'passPos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->passPos();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'passPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: receiverPos of class  CMessiDecision */
#ifndef TOLUA_DISABLE_tolua_zeus_CMessiDecision_receiverPos00
static int tolua_zeus_CMessiDecision_receiverPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMessiDecision",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMessiDecision* self = (CMessiDecision*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'receiverPos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->receiverPos();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'receiverPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: leaderPos of class  CMessiDecision */
#ifndef TOLUA_DISABLE_tolua_zeus_CMessiDecision_leaderPos00
static int tolua_zeus_CMessiDecision_leaderPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMessiDecision",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMessiDecision* self = (CMessiDecision*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'leaderPos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->leaderPos();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'leaderPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: otherPos of class  CMessiDecision */
#ifndef TOLUA_DISABLE_tolua_zeus_CMessiDecision_otherPos00
static int tolua_zeus_CMessiDecision_otherPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMessiDecision",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMessiDecision* self = (CMessiDecision*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'otherPos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->otherPos(i);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'otherPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: goaliePassPos of class  CMessiDecision */
#ifndef TOLUA_DISABLE_tolua_zeus_CMessiDecision_goaliePassPos00
static int tolua_zeus_CMessiDecision_goaliePassPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMessiDecision",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMessiDecision* self = (CMessiDecision*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'goaliePassPos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->goaliePassPos();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'goaliePassPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMessiRun of class  CMessiDecision */
#ifndef TOLUA_DISABLE_tolua_zeus_CMessiDecision_setMessiRun00
static int tolua_zeus_CMessiDecision_setMessiRun00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMessiDecision",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMessiDecision* self = (CMessiDecision*)  tolua_tousertype(tolua_S,1,0);
  bool lMessiRun = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMessiRun'", NULL);
#endif
  {
   self->setMessiRun(lMessiRun);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMessiRun'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isFlat of class  CMessiDecision */
#ifndef TOLUA_DISABLE_tolua_zeus_CMessiDecision_isFlat00
static int tolua_zeus_CMessiDecision_isFlat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMessiDecision",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMessiDecision* self = (CMessiDecision*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isFlat'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isFlat();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isFlat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: passVel of class  CMessiDecision */
#ifndef TOLUA_DISABLE_tolua_zeus_CMessiDecision_passVel00
static int tolua_zeus_CMessiDecision_passVel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMessiDecision",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMessiDecision* self = (CMessiDecision*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'passVel'", NULL);
#endif
  {
   double tolua_ret = (double)  self->passVel();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'passVel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_zeus_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,1);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CVector","CVector","",tolua_collect_CVector);
  #else
  tolua_cclass(tolua_S,"CVector","CVector","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CVector");
   tolua_function(tolua_S,"new",tolua_zeus_CVector_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CVector_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CVector_new00_local);
   tolua_function(tolua_S,"delete",tolua_zeus_CVector_delete00);
   tolua_function(tolua_S,"new",tolua_zeus_CVector_new01);
   tolua_function(tolua_S,"new_local",tolua_zeus_CVector_new01_local);
   tolua_function(tolua_S,".call",tolua_zeus_CVector_new01_local);
   tolua_function(tolua_S,"new",tolua_zeus_CVector_new02);
   tolua_function(tolua_S,"new_local",tolua_zeus_CVector_new02_local);
   tolua_function(tolua_S,".call",tolua_zeus_CVector_new02_local);
   tolua_function(tolua_S,"mod",tolua_zeus_CVector_mod00);
   tolua_function(tolua_S,"mod2",tolua_zeus_CVector_mod200);
   tolua_function(tolua_S,"dir",tolua_zeus_CVector_dir00);
   tolua_function(tolua_S,"x",tolua_zeus_CVector_x00);
   tolua_function(tolua_S,"y",tolua_zeus_CVector_y00);
   tolua_function(tolua_S,"value",tolua_zeus_CVector_value00);
   tolua_function(tolua_S,".add",tolua_zeus_CVector__add00);
   tolua_function(tolua_S,".sub",tolua_zeus_CVector__sub00);
   tolua_function(tolua_S,".mul",tolua_zeus_CVector__mul00);
   tolua_function(tolua_S,".div",tolua_zeus_CVector__div00);
   tolua_function(tolua_S,".sub",tolua_zeus_CVector__sub01);
   tolua_function(tolua_S,"rotate",tolua_zeus_CVector_rotate00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CGeoPoint","CGeoPoint","",tolua_collect_CGeoPoint);
  #else
  tolua_cclass(tolua_S,"CGeoPoint","CGeoPoint","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CGeoPoint");
   tolua_function(tolua_S,"new",tolua_zeus_CGeoPoint_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGeoPoint_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGeoPoint_new00_local);
   tolua_function(tolua_S,"delete",tolua_zeus_CGeoPoint_delete00);
   tolua_function(tolua_S,"new",tolua_zeus_CGeoPoint_new01);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGeoPoint_new01_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGeoPoint_new01_local);
   tolua_function(tolua_S,"new",tolua_zeus_CGeoPoint_new02);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGeoPoint_new02_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGeoPoint_new02_local);
   tolua_function(tolua_S,".eq",tolua_zeus_CGeoPoint__eq00);
   tolua_function(tolua_S,"x",tolua_zeus_CGeoPoint_x00);
   tolua_function(tolua_S,"y",tolua_zeus_CGeoPoint_y00);
   tolua_function(tolua_S,"dist",tolua_zeus_CGeoPoint_dist00);
   tolua_function(tolua_S,"dist2",tolua_zeus_CGeoPoint_dist200);
   tolua_function(tolua_S,".add",tolua_zeus_CGeoPoint__add00);
   tolua_function(tolua_S,".mul",tolua_zeus_CGeoPoint__mul00);
   tolua_function(tolua_S,".sub",tolua_zeus_CGeoPoint__sub00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CGeoLine","CGeoLine","",tolua_collect_CGeoLine);
  #else
  tolua_cclass(tolua_S,"CGeoLine","CGeoLine","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CGeoLine");
   tolua_function(tolua_S,"new",tolua_zeus_CGeoLine_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGeoLine_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGeoLine_new00_local);
   tolua_function(tolua_S,"new",tolua_zeus_CGeoLine_new01);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGeoLine_new01_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGeoLine_new01_local);
   tolua_function(tolua_S,"new",tolua_zeus_CGeoLine_new02);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGeoLine_new02_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGeoLine_new02_local);
   tolua_function(tolua_S,"calABC",tolua_zeus_CGeoLine_calABC00);
   tolua_function(tolua_S,"projection",tolua_zeus_CGeoLine_projection00);
   tolua_function(tolua_S,"point1",tolua_zeus_CGeoLine_point100);
   tolua_function(tolua_S,"point2",tolua_zeus_CGeoLine_point200);
   tolua_function(tolua_S,".eq",tolua_zeus_CGeoLine__eq00);
   tolua_function(tolua_S,"a",tolua_zeus_CGeoLine_a00);
   tolua_function(tolua_S,"b",tolua_zeus_CGeoLine_b00);
   tolua_function(tolua_S,"c",tolua_zeus_CGeoLine_c00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CGeoSegment","CGeoSegment","CGeoLine",tolua_collect_CGeoSegment);
  #else
  tolua_cclass(tolua_S,"CGeoSegment","CGeoSegment","CGeoLine",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CGeoSegment");
   tolua_function(tolua_S,"new",tolua_zeus_CGeoSegment_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGeoSegment_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGeoSegment_new00_local);
   tolua_function(tolua_S,"new",tolua_zeus_CGeoSegment_new01);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGeoSegment_new01_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGeoSegment_new01_local);
   tolua_function(tolua_S,"IsPointOnLineOnSegment",tolua_zeus_CGeoSegment_IsPointOnLineOnSegment00);
   tolua_function(tolua_S,"start",tolua_zeus_CGeoSegment_start00);
   tolua_function(tolua_S,"end",tolua_zeus_CGeoSegment_end00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CGeoLineLineIntersection","CGeoLineLineIntersection","",tolua_collect_CGeoLineLineIntersection);
  #else
  tolua_cclass(tolua_S,"CGeoLineLineIntersection","CGeoLineLineIntersection","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CGeoLineLineIntersection");
   tolua_function(tolua_S,"new",tolua_zeus_CGeoLineLineIntersection_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGeoLineLineIntersection_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGeoLineLineIntersection_new00_local);
   tolua_function(tolua_S,"Intersectant",tolua_zeus_CGeoLineLineIntersection_Intersectant00);
   tolua_function(tolua_S,"IntersectPoint",tolua_zeus_CGeoLineLineIntersection_IntersectPoint00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CGeoRectangle","CGeoRectangle","",tolua_collect_CGeoRectangle);
  #else
  tolua_cclass(tolua_S,"CGeoRectangle","CGeoRectangle","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CGeoRectangle");
   tolua_function(tolua_S,"new",tolua_zeus_CGeoRectangle_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGeoRectangle_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGeoRectangle_new00_local);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CGeoLineRectangleIntersection","CGeoLineRectangleIntersection","",tolua_collect_CGeoLineRectangleIntersection);
  #else
  tolua_cclass(tolua_S,"CGeoLineRectangleIntersection","CGeoLineRectangleIntersection","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CGeoLineRectangleIntersection");
   tolua_function(tolua_S,"new",tolua_zeus_CGeoLineRectangleIntersection_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGeoLineRectangleIntersection_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGeoLineRectangleIntersection_new00_local);
   tolua_function(tolua_S,"intersectant",tolua_zeus_CGeoLineRectangleIntersection_intersectant00);
   tolua_function(tolua_S,"point1",tolua_zeus_CGeoLineRectangleIntersection_point100);
   tolua_function(tolua_S,"point2",tolua_zeus_CGeoLineRectangleIntersection_point200);
  tolua_endmodule(tolua_S);
  tolua_variable(tolua_S,"vision",tolua_get_vision_ptr,tolua_set_vision_ptr);
  tolua_variable(tolua_S,"kickStatus",tolua_get_kickStatus_ptr,tolua_set_kickStatus_ptr);
  tolua_variable(tolua_S,"dribbleStatus",tolua_get_dribbleStatus_ptr,tolua_set_dribbleStatus_ptr);
  tolua_variable(tolua_S,"debugEngine",tolua_get_debugEngine_ptr,tolua_set_debugEngine_ptr);
  tolua_variable(tolua_S,"world",tolua_get_world_ptr,tolua_set_world_ptr);
  tolua_variable(tolua_S,"kickDirection",tolua_get_kickDirection_ptr,tolua_set_kickDirection_ptr);
  tolua_variable(tolua_S,"bestAlg",tolua_get_bestAlg_ptr,tolua_set_bestAlg_ptr);
  tolua_variable(tolua_S,"defPos2015",tolua_get_defPos2015_ptr,tolua_set_defPos2015_ptr);
  tolua_variable(tolua_S,"supportPos",tolua_get_supportPos_ptr,tolua_set_supportPos_ptr);
  tolua_variable(tolua_S,"tandemPos",tolua_get_tandemPos_ptr,tolua_set_tandemPos_ptr);
  tolua_variable(tolua_S,"bestPlayer",tolua_get_bestPlayer_ptr,tolua_set_bestPlayer_ptr);
  tolua_variable(tolua_S,"defenceInfo",tolua_get_defenceInfo_ptr,tolua_set_defenceInfo_ptr);
  tolua_variable(tolua_S,"indirectDefender",tolua_get_indirectDefender_ptr,tolua_set_indirectDefender_ptr);
  tolua_variable(tolua_S,"assistPoint",tolua_get_assistPoint_ptr,tolua_set_assistPoint_ptr);
  tolua_variable(tolua_S,"messi",tolua_get_messi_ptr,tolua_set_messi_ptr);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ObjectPoseT","ObjectPoseT","",tolua_collect_ObjectPoseT);
  #else
  tolua_cclass(tolua_S,"ObjectPoseT","ObjectPoseT","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ObjectPoseT");
   tolua_function(tolua_S,"new",tolua_zeus_ObjectPoseT_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_ObjectPoseT_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_ObjectPoseT_new00_local);
   tolua_function(tolua_S,"Pos",tolua_zeus_ObjectPoseT_Pos00);
   tolua_function(tolua_S,"SetPos",tolua_zeus_ObjectPoseT_SetPos00);
   tolua_function(tolua_S,"SetPos",tolua_zeus_ObjectPoseT_SetPos01);
   tolua_function(tolua_S,"X",tolua_zeus_ObjectPoseT_X00);
   tolua_function(tolua_S,"Y",tolua_zeus_ObjectPoseT_Y00);
   tolua_function(tolua_S,"SetVel",tolua_zeus_ObjectPoseT_SetVel00);
   tolua_function(tolua_S,"SetVel",tolua_zeus_ObjectPoseT_SetVel01);
   tolua_function(tolua_S,"Vel",tolua_zeus_ObjectPoseT_Vel00);
   tolua_function(tolua_S,"VelX",tolua_zeus_ObjectPoseT_VelX00);
   tolua_function(tolua_S,"VelY",tolua_zeus_ObjectPoseT_VelY00);
   tolua_function(tolua_S,"SetValid",tolua_zeus_ObjectPoseT_SetValid00);
   tolua_function(tolua_S,"Valid",tolua_zeus_ObjectPoseT_Valid00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"VisionObjectT","VisionObjectT","",NULL);
  tolua_beginmodule(tolua_S,"VisionObjectT");
   tolua_function(tolua_S,"RawPos",tolua_zeus_VisionObjectT_RawPos00);
   tolua_function(tolua_S,"SetRawPos",tolua_zeus_VisionObjectT_SetRawPos00);
   tolua_function(tolua_S,"SetRawPos",tolua_zeus_VisionObjectT_SetRawPos01);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"MobileVisionT","MobileVisionT","ObjectPoseT",NULL);
  tolua_beginmodule(tolua_S,"MobileVisionT");
   tolua_variable(tolua_S,"__VisionObjectT__",tolua_get_MobileVisionT___VisionObjectT__,NULL);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"PlayerPoseT","PlayerPoseT","ObjectPoseT",tolua_collect_PlayerPoseT);
  #else
  tolua_cclass(tolua_S,"PlayerPoseT","PlayerPoseT","ObjectPoseT",NULL);
  #endif
  tolua_beginmodule(tolua_S,"PlayerPoseT");
   tolua_function(tolua_S,"new",tolua_zeus_PlayerPoseT_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_PlayerPoseT_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_PlayerPoseT_new00_local);
   tolua_function(tolua_S,"Dir",tolua_zeus_PlayerPoseT_Dir00);
   tolua_function(tolua_S,"SetDir",tolua_zeus_PlayerPoseT_SetDir00);
   tolua_function(tolua_S,"RotVel",tolua_zeus_PlayerPoseT_RotVel00);
   tolua_function(tolua_S,"SetRotVel",tolua_zeus_PlayerPoseT_SetRotVel00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"PlayerTypeT","PlayerTypeT","",NULL);
  tolua_beginmodule(tolua_S,"PlayerTypeT");
   tolua_function(tolua_S,"SetType",tolua_zeus_PlayerTypeT_SetType00);
   tolua_function(tolua_S,"Type",tolua_zeus_PlayerTypeT_Type00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"PlayerVisionT","PlayerVisionT","PlayerPoseT",NULL);
  tolua_beginmodule(tolua_S,"PlayerVisionT");
   tolua_variable(tolua_S,"__VisionObjectT__",tolua_get_PlayerVisionT___VisionObjectT__,NULL);
   tolua_variable(tolua_S,"__PlayerTypeT__",tolua_get_PlayerVisionT___PlayerTypeT__,NULL);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"PlayerCapabilityT","PlayerCapabilityT","",NULL);
  tolua_beginmodule(tolua_S,"PlayerCapabilityT");
   tolua_variable(tolua_S,"maxAccel",tolua_get_PlayerCapabilityT_maxAccel,tolua_set_PlayerCapabilityT_maxAccel);
   tolua_variable(tolua_S,"maxSpeed",tolua_get_PlayerCapabilityT_maxSpeed,tolua_set_PlayerCapabilityT_maxSpeed);
   tolua_variable(tolua_S,"maxAngularAccel",tolua_get_PlayerCapabilityT_maxAngularAccel,tolua_set_PlayerCapabilityT_maxAngularAccel);
   tolua_variable(tolua_S,"maxAngularSpeed",tolua_get_PlayerCapabilityT_maxAngularSpeed,tolua_set_PlayerCapabilityT_maxAngularSpeed);
   tolua_variable(tolua_S,"maxDec",tolua_get_PlayerCapabilityT_maxDec,tolua_set_PlayerCapabilityT_maxDec);
   tolua_variable(tolua_S,"maxAngularDec",tolua_get_PlayerCapabilityT_maxAngularDec,tolua_set_PlayerCapabilityT_maxAngularDec);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CVisionModule","CVisionModule","",tolua_collect_CVisionModule);
  #else
  tolua_cclass(tolua_S,"CVisionModule","CVisionModule","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CVisionModule");
   tolua_function(tolua_S,"new",tolua_zeus_CVisionModule_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CVisionModule_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CVisionModule_new00_local);
   tolua_function(tolua_S,"delete",tolua_zeus_CVisionModule_delete00);
   tolua_function(tolua_S,"getValidNum",tolua_zeus_CVisionModule_getValidNum00);
   tolua_function(tolua_S,"getTheirValidNum",tolua_zeus_CVisionModule_getTheirValidNum00);
   tolua_function(tolua_S,"SetNewVision",tolua_zeus_CVisionModule_SetNewVision00);
   tolua_function(tolua_S,"AllPlayer",tolua_zeus_CVisionModule_AllPlayer00);
   tolua_function(tolua_S,"OurPlayer",tolua_zeus_CVisionModule_OurPlayer00);
   tolua_function(tolua_S,"TheirPlayer",tolua_zeus_CVisionModule_TheirPlayer00);
   tolua_function(tolua_S,"Ball",tolua_zeus_CVisionModule_Ball00);
   tolua_function(tolua_S,"OurPlayer",tolua_zeus_CVisionModule_OurPlayer01);
   tolua_function(tolua_S,"TheirPlayer",tolua_zeus_CVisionModule_TheirPlayer01);
   tolua_function(tolua_S,"Ball",tolua_zeus_CVisionModule_Ball01);
   tolua_function(tolua_S,"RawBall",tolua_zeus_CVisionModule_RawBall00);
   tolua_function(tolua_S,"getBallPlacementPosition",tolua_zeus_CVisionModule_getBallPlacementPosition00);
   tolua_function(tolua_S,"OurRawPlayer",tolua_zeus_CVisionModule_OurRawPlayer00);
   tolua_function(tolua_S,"TheirRawPlayer",tolua_zeus_CVisionModule_TheirRawPlayer00);
   tolua_function(tolua_S,"SetPlayerCommand",tolua_zeus_CVisionModule_SetPlayerCommand00);
   tolua_function(tolua_S,"gameState",tolua_zeus_CVisionModule_gameState00);
   tolua_function(tolua_S,"PlayerLostTime",tolua_zeus_CVisionModule_PlayerLostTime00);
   tolua_function(tolua_S,"GetCurrentRefereeMsg",tolua_zeus_CVisionModule_GetCurrentRefereeMsg00);
   tolua_function(tolua_S,"Cycle",tolua_zeus_CVisionModule_Cycle00);
   tolua_function(tolua_S,"LastCycle",tolua_zeus_CVisionModule_LastCycle00);
   tolua_function(tolua_S,"Side",tolua_zeus_CVisionModule_Side00);
   tolua_function(tolua_S,"OurGoal",tolua_zeus_CVisionModule_OurGoal00);
   tolua_function(tolua_S,"TheirGoal",tolua_zeus_CVisionModule_TheirGoal00);
   tolua_function(tolua_S,"TimeRemain",tolua_zeus_CVisionModule_TimeRemain00);
   tolua_function(tolua_S,"getBallVelStable",tolua_zeus_CVisionModule_getBallVelStable00);
   tolua_function(tolua_S,"ballVelValid",tolua_zeus_CVisionModule_ballVelValid00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CGDebugEngine","CGDebugEngine","",tolua_collect_CGDebugEngine);
  #else
  tolua_cclass(tolua_S,"CGDebugEngine","CGDebugEngine","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CGDebugEngine");
   tolua_function(tolua_S,"new",tolua_zeus_CGDebugEngine_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGDebugEngine_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGDebugEngine_new00_local);
   tolua_function(tolua_S,"delete",tolua_zeus_CGDebugEngine_delete00);
   tolua_function(tolua_S,"gui_debug_x",tolua_zeus_CGDebugEngine_gui_debug_x00);
   tolua_function(tolua_S,"gui_debug_line",tolua_zeus_CGDebugEngine_gui_debug_line00);
   tolua_function(tolua_S,"gui_debug_arc",tolua_zeus_CGDebugEngine_gui_debug_arc00);
   tolua_function(tolua_S,"gui_debug_triangle",tolua_zeus_CGDebugEngine_gui_debug_triangle00);
   tolua_function(tolua_S,"gui_debug_robot",tolua_zeus_CGDebugEngine_gui_debug_robot00);
   tolua_function(tolua_S,"gui_debug_msg",tolua_zeus_CGDebugEngine_gui_debug_msg00);
   tolua_function(tolua_S,"gui_debug_curve",tolua_zeus_CGDebugEngine_gui_debug_curve00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CWorldModel","CWorldModel","",tolua_collect_CWorldModel);
  #else
  tolua_cclass(tolua_S,"CWorldModel","CWorldModel","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CWorldModel");
   tolua_function(tolua_S,"new",tolua_zeus_CWorldModel_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CWorldModel_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CWorldModel_new00_local);
   tolua_function(tolua_S,"vision",tolua_zeus_CWorldModel_vision00);
   tolua_function(tolua_S,"OurRobotNum",tolua_zeus_CWorldModel_OurRobotNum00);
   tolua_function(tolua_S,"GetRealNum",tolua_zeus_CWorldModel_GetRealNum00);
   tolua_function(tolua_S,"GetTacticNum",tolua_zeus_CWorldModel_GetTacticNum00);
   tolua_function(tolua_S,"KickDirArrived",tolua_zeus_CWorldModel_KickDirArrived00);
   tolua_function(tolua_S,"IsBallKicked",tolua_zeus_CWorldModel_IsBallKicked00);
   tolua_function(tolua_S,"IsInfraredOn",tolua_zeus_CWorldModel_IsInfraredOn00);
   tolua_function(tolua_S,"SPlayFSMSwitchClearAll",tolua_zeus_CWorldModel_SPlayFSMSwitchClearAll00);
   tolua_function(tolua_S,"IsBestPlayerChanged",tolua_zeus_CWorldModel_IsBestPlayerChanged00);
   tolua_function(tolua_S,"CanDefenceExit",tolua_zeus_CWorldModel_CanDefenceExit00);
   tolua_function(tolua_S,"NeedExitAttackDef",tolua_zeus_CWorldModel_NeedExitAttackDef00);
   tolua_function(tolua_S,"ball2MarkingTouch",tolua_zeus_CWorldModel_ball2MarkingTouch00);
   tolua_function(tolua_S,"isMarkingFrontValid",tolua_zeus_CWorldModel_isMarkingFrontValid00);
   tolua_function(tolua_S,"getEnemyKickOffNum",tolua_zeus_CWorldModel_getEnemyKickOffNum00);
   tolua_function(tolua_S,"getMarkingTouchArea",tolua_zeus_CWorldModel_getMarkingTouchArea00);
   tolua_function(tolua_S,"checkEnemyKickOffNumChanged",tolua_zeus_CWorldModel_checkEnemyKickOffNumChanged00);
   tolua_function(tolua_S,"CurrentBayes",tolua_zeus_CWorldModel_CurrentBayes00);
   tolua_function(tolua_S,"canProtectBall",tolua_zeus_CWorldModel_canProtectBall00);
   tolua_function(tolua_S,"canShootOnBallPos",tolua_zeus_CWorldModel_canShootOnBallPos00);
   tolua_function(tolua_S,"canPassOnBallPos",tolua_zeus_CWorldModel_canPassOnBallPos00);
   tolua_function(tolua_S,"canKickAtEnemy",tolua_zeus_CWorldModel_canKickAtEnemy00);
   tolua_function(tolua_S,"getBallStatus",tolua_zeus_CWorldModel_getBallStatus00);
   tolua_function(tolua_S,"getAttackerAmount",tolua_zeus_CWorldModel_getAttackerAmount00);
   tolua_function(tolua_S,"getAttackDecision",tolua_zeus_CWorldModel_getAttackDecision00);
   tolua_function(tolua_S,"getMessiAttackDecision",tolua_zeus_CWorldModel_getMessiAttackDecision00);
   tolua_function(tolua_S,"generateTwoPassPoint",tolua_zeus_CWorldModel_generateTwoPassPoint00);
   tolua_function(tolua_S,"getTandemDir",tolua_zeus_CWorldModel_getTandemDir00);
   tolua_function(tolua_S,"getTandemPos",tolua_zeus_CWorldModel_getTandemPos00);
   tolua_function(tolua_S,"getBallToucher",tolua_zeus_CWorldModel_getBallToucher00);
   tolua_function(tolua_S,"getLastBallToucher",tolua_zeus_CWorldModel_getLastBallToucher00);
   tolua_function(tolua_S,"getBallChipLine",tolua_zeus_CWorldModel_getBallChipLine00);
   tolua_function(tolua_S,"IsOurBallByAutoReferee",tolua_zeus_CWorldModel_IsOurBallByAutoReferee00);
   tolua_function(tolua_S,"clearBallStateCouter",tolua_zeus_CWorldModel_clearBallStateCouter00);
   tolua_function(tolua_S,"getSuitSider",tolua_zeus_CWorldModel_getSuitSider00);
   tolua_function(tolua_S,"setBallHandler",tolua_zeus_CWorldModel_setBallHandler00);
   tolua_function(tolua_S,"isRecordRunPos",tolua_zeus_CWorldModel_isRecordRunPos00);
   tolua_function(tolua_S,"isBeingMarked",tolua_zeus_CWorldModel_isBeingMarked00);
   tolua_function(tolua_S,"isPassLineBlocked",tolua_zeus_CWorldModel_isPassLineBlocked00);
   tolua_function(tolua_S,"isShootLineBlocked",tolua_zeus_CWorldModel_isShootLineBlocked00);
   tolua_function(tolua_S,"isShootLineBlockedFromPoint",tolua_zeus_CWorldModel_isShootLineBlockedFromPoint00);
   tolua_function(tolua_S,"drawReflect",tolua_zeus_CWorldModel_drawReflect00);
   tolua_function(tolua_S,"getLeftReflectPos",tolua_zeus_CWorldModel_getLeftReflectPos00);
   tolua_function(tolua_S,"getRightReflectPos",tolua_zeus_CWorldModel_getRightReflectPos00);
   tolua_function(tolua_S,"getReflectPos",tolua_zeus_CWorldModel_getReflectPos00);
   tolua_function(tolua_S,"getReflectTouchPos",tolua_zeus_CWorldModel_getReflectTouchPos00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CKickStatus","CKickStatus","",tolua_collect_CKickStatus);
  #else
  tolua_cclass(tolua_S,"CKickStatus","CKickStatus","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CKickStatus");
   tolua_function(tolua_S,"new",tolua_zeus_CKickStatus_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CKickStatus_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CKickStatus_new00_local);
   tolua_function(tolua_S,"setKick",tolua_zeus_CKickStatus_setKick00);
   tolua_function(tolua_S,"setChipKick",tolua_zeus_CKickStatus_setChipKick00);
   tolua_function(tolua_S,"setBothKick",tolua_zeus_CKickStatus_setBothKick00);
   tolua_function(tolua_S,"setAllKick",tolua_zeus_CKickStatus_setAllKick00);
   tolua_function(tolua_S,"needKick",tolua_zeus_CKickStatus_needKick00);
   tolua_function(tolua_S,"getKickPower",tolua_zeus_CKickStatus_getKickPower00);
   tolua_function(tolua_S,"getChipKickDist",tolua_zeus_CKickStatus_getChipKickDist00);
   tolua_function(tolua_S,"getPassDist",tolua_zeus_CKickStatus_getPassDist00);
   tolua_function(tolua_S,"getKiker",tolua_zeus_CKickStatus_getKiker00);
   tolua_function(tolua_S,"clearAll",tolua_zeus_CKickStatus_clearAll00);
   tolua_function(tolua_S,"resetKick2ForceClose",tolua_zeus_CKickStatus_resetKick2ForceClose00);
   tolua_function(tolua_S,"updateForceClose",tolua_zeus_CKickStatus_updateForceClose00);
   tolua_function(tolua_S,"isForceClosed",tolua_zeus_CKickStatus_isForceClosed00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CTaskMediator","CTaskMediator","",tolua_collect_CTaskMediator);
  #else
  tolua_cclass(tolua_S,"CTaskMediator","CTaskMediator","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CTaskMediator");
   tolua_function(tolua_S,"new",tolua_zeus_CTaskMediator_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CTaskMediator_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CTaskMediator_new00_local);
   tolua_function(tolua_S,"setBallHandler",tolua_zeus_CTaskMediator_setBallHandler00);
   tolua_function(tolua_S,"ballHandler",tolua_zeus_CTaskMediator_ballHandler00);
   tolua_function(tolua_S,"goalie",tolua_zeus_CTaskMediator_goalie00);
   tolua_function(tolua_S,"setPlayerTask",tolua_zeus_CTaskMediator_setPlayerTask00);
   tolua_function(tolua_S,"getPlayerTask",tolua_zeus_CTaskMediator_getPlayerTask00);
   tolua_function(tolua_S,"getPlayerTaskPriority",tolua_zeus_CTaskMediator_getPlayerTaskPriority00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"GameState","GameState","",tolua_collect_GameState);
  #else
  tolua_cclass(tolua_S,"GameState","GameState","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"GameState");
   tolua_function(tolua_S,"new",tolua_zeus_GameState_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_GameState_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_GameState_new00_local);
   tolua_function(tolua_S,"gameOn",tolua_zeus_GameState_gameOn00);
   tolua_function(tolua_S,"gameOff",tolua_zeus_GameState_gameOff00);
   tolua_function(tolua_S,"gameOver",tolua_zeus_GameState_gameOver00);
   tolua_function(tolua_S,"restart",tolua_zeus_GameState_restart00);
   tolua_function(tolua_S,"ourRestart",tolua_zeus_GameState_ourRestart00);
   tolua_function(tolua_S,"theirRestart",tolua_zeus_GameState_theirRestart00);
   tolua_function(tolua_S,"canKickBall",tolua_zeus_GameState_canKickBall00);
   tolua_function(tolua_S,"canEitherKickBall",tolua_zeus_GameState_canEitherKickBall00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CDribbleStatus","CDribbleStatus","",tolua_collect_CDribbleStatus);
  #else
  tolua_cclass(tolua_S,"CDribbleStatus","CDribbleStatus","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CDribbleStatus");
   tolua_function(tolua_S,"new",tolua_zeus_CDribbleStatus_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CDribbleStatus_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CDribbleStatus_new00_local);
   tolua_function(tolua_S,"dribbleOn",tolua_zeus_CDribbleStatus_dribbleOn00);
   tolua_function(tolua_S,"ballController",tolua_zeus_CDribbleStatus_ballController00);
   tolua_function(tolua_S,"ballControlled",tolua_zeus_CDribbleStatus_ballControlled00);
   tolua_function(tolua_S,"dribbleStartPosValid",tolua_zeus_CDribbleStatus_dribbleStartPosValid00);
   tolua_function(tolua_S,"lastBallController",tolua_zeus_CDribbleStatus_lastBallController00);
   tolua_function(tolua_S,"lastBallController",tolua_zeus_CDribbleStatus_lastBallController01);
   tolua_function(tolua_S,"setLastBallController",tolua_zeus_CDribbleStatus_setLastBallController00);
   tolua_function(tolua_S,"dribbleStartPos",tolua_zeus_CDribbleStatus_dribbleStartPos00);
   tolua_function(tolua_S,"dribbleStartCycle",tolua_zeus_CDribbleStatus_dribbleStartCycle00);
   tolua_function(tolua_S,"setDribbleOn",tolua_zeus_CDribbleStatus_setDribbleOn00);
   tolua_function(tolua_S,"setDribbleOff",tolua_zeus_CDribbleStatus_setDribbleOff00);
   tolua_function(tolua_S,"setDribbleStartPosLost",tolua_zeus_CDribbleStatus_setDribbleStartPosLost00);
   tolua_function(tolua_S,"setBallControlled",tolua_zeus_CDribbleStatus_setBallControlled00);
   tolua_function(tolua_S,"setBallLost",tolua_zeus_CDribbleStatus_setBallLost00);
   tolua_function(tolua_S,"ballControlStarPos",tolua_zeus_CDribbleStatus_ballControlStarPos00);
   tolua_function(tolua_S,"needReleaseBall",tolua_zeus_CDribbleStatus_needReleaseBall00);
   tolua_function(tolua_S,"setNeedNotReleaseBall",tolua_zeus_CDribbleStatus_setNeedNotReleaseBall00);
   tolua_function(tolua_S,"setMayNeedReleaseBall",tolua_zeus_CDribbleStatus_setMayNeedReleaseBall00);
   tolua_function(tolua_S,"clearDribbleCommand",tolua_zeus_CDribbleStatus_clearDribbleCommand00);
   tolua_function(tolua_S,"setDribbleCommand",tolua_zeus_CDribbleStatus_setDribbleCommand00);
   tolua_function(tolua_S,"getDribbleCommand",tolua_zeus_CDribbleStatus_getDribbleCommand00);
   tolua_function(tolua_S,"ballControlled",tolua_zeus_CDribbleStatus_ballControlled01);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"Utils",0);
  tolua_beginmodule(tolua_S,"Utils");
   tolua_function(tolua_S,"Normalize",tolua_zeus_Utils_Normalize00);
   tolua_function(tolua_S,"Polar2Vector",tolua_zeus_Utils_Polar2Vector00);
   tolua_function(tolua_S,"VectorDot",tolua_zeus_Utils_VectorDot00);
   tolua_function(tolua_S,"InBetween",tolua_zeus_Utils_InBetween00);
   tolua_function(tolua_S,"InBetween",tolua_zeus_Utils_InBetween01);
   tolua_function(tolua_S,"AngleBetween",tolua_zeus_Utils_AngleBetween00);
   tolua_function(tolua_S,"InBetween",tolua_zeus_Utils_InBetween02);
   tolua_function(tolua_S,"Deg2Rad",tolua_zeus_Utils_Deg2Rad00);
   tolua_function(tolua_S,"Rad2Deg",tolua_zeus_Utils_Rad2Deg00);
   tolua_function(tolua_S,"MakeInField",tolua_zeus_Utils_MakeInField00);
   tolua_function(tolua_S,"OutOfField",tolua_zeus_Utils_OutOfField00);
   tolua_function(tolua_S,"FieldLeft",tolua_zeus_Utils_FieldLeft00);
   tolua_function(tolua_S,"FieldRight",tolua_zeus_Utils_FieldRight00);
   tolua_function(tolua_S,"FieldTop",tolua_zeus_Utils_FieldTop00);
   tolua_function(tolua_S,"FieldBottom",tolua_zeus_Utils_FieldBottom00);
   tolua_function(tolua_S,"LeftTop",tolua_zeus_Utils_LeftTop00);
   tolua_function(tolua_S,"RightBottom",tolua_zeus_Utils_RightBottom00);
   tolua_function(tolua_S,"Sign",tolua_zeus_Utils_Sign00);
   tolua_function(tolua_S,"MakeOutOfOurPenaltyArea",tolua_zeus_Utils_MakeOutOfOurPenaltyArea00);
   tolua_function(tolua_S,"MakeOutOfCircleAndInField",tolua_zeus_Utils_MakeOutOfCircleAndInField00);
   tolua_function(tolua_S,"InOurPenaltyArea",tolua_zeus_Utils_InOurPenaltyArea00);
   tolua_function(tolua_S,"InTheirPenaltyArea",tolua_zeus_Utils_InTheirPenaltyArea00);
   tolua_function(tolua_S,"PlayerNumValid",tolua_zeus_Utils_PlayerNumValid00);
   tolua_function(tolua_S,"canGo",tolua_zeus_Utils_canGo00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Matrix_double_","Matrix<double>","",tolua_collect_Matrix_double_);
  #else
  tolua_cclass(tolua_S,"Matrix_double_","Matrix<double>","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Matrix_double_");
   tolua_function(tolua_S,"new",tolua_zeus_Matrix_double__new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_Matrix_double__new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_Matrix_double__new00_local);
   tolua_function(tolua_S,"delete",tolua_zeus_Matrix_double__delete00);
   tolua_function(tolua_S,"new",tolua_zeus_Matrix_double__new01);
   tolua_function(tolua_S,"new_local",tolua_zeus_Matrix_double__new01_local);
   tolua_function(tolua_S,".call",tolua_zeus_Matrix_double__new01_local);
   tolua_function(tolua_S,"setValue",tolua_zeus_Matrix_double__setValue00);
   tolua_function(tolua_S,"getValue",tolua_zeus_Matrix_double__getValue00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Munkres","Munkres","",tolua_collect_Munkres);
  #else
  tolua_cclass(tolua_S,"Munkres","Munkres","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Munkres");
   tolua_function(tolua_S,"new",tolua_zeus_Munkres_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_Munkres_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_Munkres_new00_local);
   tolua_function(tolua_S,"delete",tolua_zeus_Munkres_delete00);
   tolua_function(tolua_S,"solve",tolua_zeus_Munkres_solve00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CKickDirection","CKickDirection","",tolua_collect_CKickDirection);
  #else
  tolua_cclass(tolua_S,"CKickDirection","CKickDirection","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CKickDirection");
   tolua_function(tolua_S,"new",tolua_zeus_CKickDirection_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CKickDirection_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CKickDirection_new00_local);
   tolua_function(tolua_S,"GenerateShootDir",tolua_zeus_CKickDirection_GenerateShootDir00);
   tolua_function(tolua_S,"getKickValid",tolua_zeus_CKickDirection_getKickValid00);
   tolua_function(tolua_S,"getCompensate",tolua_zeus_CKickDirection_getCompensate00);
   tolua_function(tolua_S,"getRawKickDir",tolua_zeus_CKickDirection_getRawKickDir00);
   tolua_function(tolua_S,"getCompensateDir",tolua_zeus_CKickDirection_getCompensateDir00);
   tolua_function(tolua_S,"getRealKickDir",tolua_zeus_CKickDirection_getRealKickDir00);
   tolua_function(tolua_S,"calCompensate",tolua_zeus_CKickDirection_calCompensate00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"POS_SIDE_LEFT",POS_SIDE_LEFT);
  tolua_constant(tolua_S,"POS_SIDE_RIGHT",POS_SIDE_RIGHT);
  tolua_constant(tolua_S,"POS_SIDE_MIDDLE",POS_SIDE_MIDDLE);
  tolua_module(tolua_S,"DefendUtils",0);
  tolua_beginmodule(tolua_S,"DefendUtils");
   tolua_function(tolua_S,"reversePoint",tolua_zeus_DefendUtils_reversePoint00);
   tolua_function(tolua_S,"calcBlockAngle",tolua_zeus_DefendUtils_calcBlockAngle00);
   tolua_function(tolua_S,"isPosInOurPenaltyArea",tolua_zeus_DefendUtils_isPosInOurPenaltyArea00);
   tolua_function(tolua_S,"leftCirValid",tolua_zeus_DefendUtils_leftCirValid00);
   tolua_function(tolua_S,"rightCirValid",tolua_zeus_DefendUtils_rightCirValid00);
   tolua_function(tolua_S,"getEnemyShooter",tolua_zeus_DefendUtils_getEnemyShooter00);
   tolua_function(tolua_S,"getPenaltyFronter",tolua_zeus_DefendUtils_getPenaltyFronter00);
   tolua_function(tolua_S,"getDefenceTargetAndLine",tolua_zeus_DefendUtils_getDefenceTargetAndLine00);
   tolua_function(tolua_S,"calcDefenderPoint",tolua_zeus_DefendUtils_calcDefenderPoint00);
   tolua_function(tolua_S,"getCornerAreaPos",tolua_zeus_DefendUtils_getCornerAreaPos00);
   tolua_function(tolua_S,"getIndirectDefender",tolua_zeus_DefendUtils_getIndirectDefender00);
   tolua_function(tolua_S,"getMiddleDefender",tolua_zeus_DefendUtils_getMiddleDefender00);
   tolua_function(tolua_S,"getDefaultPos",tolua_zeus_DefendUtils_getDefaultPos00);
   tolua_function(tolua_S,"calcBalltoOurPenaty",tolua_zeus_DefendUtils_calcBalltoOurPenaty00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"CIRCLE_MODE",CIRCLE_MODE);
  tolua_constant(tolua_S,"RECT_MODE",RECT_MODE);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CGPUBestAlgThread","CGPUBestAlgThread","",tolua_collect_CGPUBestAlgThread);
  #else
  tolua_cclass(tolua_S,"CGPUBestAlgThread","CGPUBestAlgThread","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CGPUBestAlgThread");
   tolua_function(tolua_S,"new",tolua_zeus_CGPUBestAlgThread_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGPUBestAlgThread_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGPUBestAlgThread_new00_local);
   tolua_function(tolua_S,"delete",tolua_zeus_CGPUBestAlgThread_delete00);
   tolua_function(tolua_S,"initialize",tolua_zeus_CGPUBestAlgThread_initialize00);
   tolua_function(tolua_S,"getBestPoint",tolua_zeus_CGPUBestAlgThread_getBestPoint00);
   tolua_function(tolua_S,"getBestPoint",tolua_zeus_CGPUBestAlgThread_getBestPoint01);
   tolua_function(tolua_S,"getBestPoint",tolua_zeus_CGPUBestAlgThread_getBestPoint02);
   tolua_function(tolua_S,"getBestPoint",tolua_zeus_CGPUBestAlgThread_getBestPoint03);
   tolua_function(tolua_S,"generatePointValue",tolua_zeus_CGPUBestAlgThread_generatePointValue00);
   tolua_function(tolua_S,"isLastOneValid",tolua_zeus_CGPUBestAlgThread_isLastOneValid00);
   tolua_function(tolua_S,"setSendPoint",tolua_zeus_CGPUBestAlgThread_setSendPoint00);
   tolua_function(tolua_S,"getPosPotential",tolua_zeus_CGPUBestAlgThread_getPosPotential00);
   tolua_function(tolua_S,"bestPointForCornerKicks",tolua_zeus_CGPUBestAlgThread_bestPointForCornerKicks00);
   tolua_function(tolua_S,"bestPointForFrontKicks",tolua_zeus_CGPUBestAlgThread_bestPointForFrontKicks00);
   tolua_function(tolua_S,"bestPointForBackKicks",tolua_zeus_CGPUBestAlgThread_bestPointForBackKicks00);
   tolua_function(tolua_S,"isChip",tolua_zeus_CGPUBestAlgThread_isChip00);
   tolua_function(tolua_S,"isChip",tolua_zeus_CGPUBestAlgThread_isChip01);
   tolua_function(tolua_S,"isChip",tolua_zeus_CGPUBestAlgThread_isChip02);
   tolua_function(tolua_S,"getChipPower",tolua_zeus_CGPUBestAlgThread_getChipPower00);
   tolua_function(tolua_S,"getFixBuf",tolua_zeus_CGPUBestAlgThread_getFixBuf00);
   tolua_function(tolua_S,"numberReceive",tolua_zeus_CGPUBestAlgThread_numberReceive00);
   tolua_function(tolua_S,"receiveOwnPos",tolua_zeus_CGPUBestAlgThread_receiveOwnPos00);
   tolua_function(tolua_S,"detectModule",tolua_zeus_CGPUBestAlgThread_detectModule00);
   tolua_function(tolua_S,"detectDefendKickedModule",tolua_zeus_CGPUBestAlgThread_detectDefendKickedModule00);
   tolua_function(tolua_S,"scanModule",tolua_zeus_CGPUBestAlgThread_scanModule00);
   tolua_function(tolua_S,"fakePosComputeModule",tolua_zeus_CGPUBestAlgThread_fakePosComputeModule00);
   tolua_function(tolua_S,"getPosForFirstVehicle",tolua_zeus_CGPUBestAlgThread_getPosForFirstVehicle00);
   tolua_function(tolua_S,"getPosForSecondVehicle",tolua_zeus_CGPUBestAlgThread_getPosForSecondVehicle00);
   tolua_function(tolua_S,"getPosForThirdVehicle",tolua_zeus_CGPUBestAlgThread_getPosForThirdVehicle00);
   tolua_function(tolua_S,"getPosForFourthVehicle",tolua_zeus_CGPUBestAlgThread_getPosForFourthVehicle00);
   tolua_function(tolua_S,"getPosForFifthVehicle",tolua_zeus_CGPUBestAlgThread_getPosForFifthVehicle00);
   tolua_function(tolua_S,"getPosForSixthVehicle",tolua_zeus_CGPUBestAlgThread_getPosForSixthVehicle00);
   tolua_function(tolua_S,"getPosForAssister",tolua_zeus_CGPUBestAlgThread_getPosForAssister00);
   tolua_function(tolua_S,"getPosForGoalie",tolua_zeus_CGPUBestAlgThread_getPosForGoalie00);
   tolua_function(tolua_S,"getPosForShoot",tolua_zeus_CGPUBestAlgThread_getPosForShoot00);
   tolua_function(tolua_S,"generateJamPos",tolua_zeus_CGPUBestAlgThread_generateJamPos00);
   tolua_function(tolua_S,"detectMarkedOver",tolua_zeus_CGPUBestAlgThread_detectMarkedOver00);
   tolua_function(tolua_S,"detectDefendKickedOver",tolua_zeus_CGPUBestAlgThread_detectDefendKickedOver00);
   tolua_function(tolua_S,"detectAgain",tolua_zeus_CGPUBestAlgThread_detectAgain00);
   tolua_function(tolua_S,"scanOver",tolua_zeus_CGPUBestAlgThread_scanOver00);
   tolua_function(tolua_S,"canPass",tolua_zeus_CGPUBestAlgThread_canPass00);
   tolua_function(tolua_S,"isDefendedHead",tolua_zeus_CGPUBestAlgThread_isDefendedHead00);
   tolua_function(tolua_S,"allMarked",tolua_zeus_CGPUBestAlgThread_allMarked00);
   tolua_function(tolua_S,"isMarked",tolua_zeus_CGPUBestAlgThread_isMarked00);
   tolua_function(tolua_S,"changeLeaderOver",tolua_zeus_CGPUBestAlgThread_changeLeaderOver00);
   tolua_function(tolua_S,"confirmPosForFirstVehicle",tolua_zeus_CGPUBestAlgThread_confirmPosForFirstVehicle00);
   tolua_function(tolua_S,"confirmPosForSecondVehicle",tolua_zeus_CGPUBestAlgThread_confirmPosForSecondVehicle00);
   tolua_function(tolua_S,"confirmPosForThirdVehicle",tolua_zeus_CGPUBestAlgThread_confirmPosForThirdVehicle00);
   tolua_function(tolua_S,"confirmPosForFourthVehicle",tolua_zeus_CGPUBestAlgThread_confirmPosForFourthVehicle00);
   tolua_function(tolua_S,"changeLeader",tolua_zeus_CGPUBestAlgThread_changeLeader00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Defend2015","Defend2015","",tolua_collect_Defend2015);
  #else
  tolua_cclass(tolua_S,"Defend2015","Defend2015","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Defend2015");
   tolua_variable(tolua_S,"leftD",tolua_get_Defend2015_leftD,tolua_set_Defend2015_leftD);
   tolua_variable(tolua_S,"rightD",tolua_get_Defend2015_rightD,tolua_set_Defend2015_rightD);
   tolua_variable(tolua_S,"middleD",tolua_get_Defend2015_middleD,tolua_set_Defend2015_middleD);
   tolua_variable(tolua_S,"singleD",tolua_get_Defend2015_singleD,tolua_set_Defend2015_singleD);
   tolua_variable(tolua_S,"goalieD",tolua_get_Defend2015_goalieD,tolua_set_Defend2015_goalieD);
   tolua_variable(tolua_S,"sideD",tolua_get_Defend2015_sideD,tolua_set_Defend2015_sideD);
   tolua_function(tolua_S,"getSidePos",tolua_zeus_Defend2015_getSidePos00);
   tolua_function(tolua_S,"getLeftPos",tolua_zeus_Defend2015_getLeftPos00);
   tolua_function(tolua_S,"getRightPos",tolua_zeus_Defend2015_getRightPos00);
   tolua_function(tolua_S,"getMiddlePos",tolua_zeus_Defend2015_getMiddlePos00);
   tolua_function(tolua_S,"getSinglePos",tolua_zeus_Defend2015_getSinglePos00);
   tolua_function(tolua_S,"getGoaliePos",tolua_zeus_Defend2015_getGoaliePos00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CDefPos2015","CDefPos2015","",tolua_collect_CDefPos2015);
  #else
  tolua_cclass(tolua_S,"CDefPos2015","CDefPos2015","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CDefPos2015");
   tolua_function(tolua_S,"new",tolua_zeus_CDefPos2015_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CDefPos2015_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CDefPos2015_new00_local);
   tolua_function(tolua_S,"delete",tolua_zeus_CDefPos2015_delete00);
   tolua_function(tolua_S,"generatePos",tolua_zeus_CDefPos2015_generatePos00);
   tolua_function(tolua_S,"getDefPos2015",tolua_zeus_CDefPos2015_getDefPos201500);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CTandemPos","CTandemPos","",tolua_collect_CTandemPos);
  #else
  tolua_cclass(tolua_S,"CTandemPos","CTandemPos","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CTandemPos");
   tolua_function(tolua_S,"new",tolua_zeus_CTandemPos_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CTandemPos_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CTandemPos_new00_local);
   tolua_function(tolua_S,"delete",tolua_zeus_CTandemPos_delete00);
   tolua_function(tolua_S,"generatePos",tolua_zeus_CTandemPos_generatePos00);
   tolua_function(tolua_S,"getTandemPos",tolua_zeus_CTandemPos_getTandemPos00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CBestPlayer","CBestPlayer","",tolua_collect_CBestPlayer);
  #else
  tolua_cclass(tolua_S,"CBestPlayer","CBestPlayer","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CBestPlayer");
   tolua_function(tolua_S,"new",tolua_zeus_CBestPlayer_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CBestPlayer_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CBestPlayer_new00_local);
   tolua_function(tolua_S,"delete",tolua_zeus_CBestPlayer_delete00);
   tolua_function(tolua_S,"getOurBestPlayer",tolua_zeus_CBestPlayer_getOurBestPlayer00);
   tolua_function(tolua_S,"getTheirBestPlayer",tolua_zeus_CBestPlayer_getTheirBestPlayer00);
   tolua_function(tolua_S,"getTheirGoalie",tolua_zeus_CBestPlayer_getTheirGoalie00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CDefenceInfo","CDefenceInfo","",tolua_collect_CDefenceInfo);
  #else
  tolua_cclass(tolua_S,"CDefenceInfo","CDefenceInfo","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CDefenceInfo");
   tolua_function(tolua_S,"new",tolua_zeus_CDefenceInfo_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CDefenceInfo_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CDefenceInfo_new00_local);
   tolua_function(tolua_S,"delete",tolua_zeus_CDefenceInfo_delete00);
   tolua_function(tolua_S,"initialization",tolua_zeus_CDefenceInfo_initialization00);
   tolua_function(tolua_S,"updateDefenceInfo",tolua_zeus_CDefenceInfo_updateDefenceInfo00);
   tolua_function(tolua_S,"changeAttrSet",tolua_zeus_CDefenceInfo_changeAttrSet00);
   tolua_function(tolua_S,"getAttackNum",tolua_zeus_CDefenceInfo_getAttackNum00);
   tolua_function(tolua_S,"getAttackOppNumByPri",tolua_zeus_CDefenceInfo_getAttackOppNumByPri00);
   tolua_function(tolua_S,"getSteadyAttackOppNumByPri",tolua_zeus_CDefenceInfo_getSteadyAttackOppNumByPri00);
   tolua_function(tolua_S,"queryMarked",tolua_zeus_CDefenceInfo_queryMarked00);
   tolua_function(tolua_S,"getOurMarkDenfender",tolua_zeus_CDefenceInfo_getOurMarkDenfender00);
   tolua_function(tolua_S,"getTriggerState",tolua_zeus_CDefenceInfo_getTriggerState00);
   tolua_function(tolua_S,"setMarkList",tolua_zeus_CDefenceInfo_setMarkList00);
   tolua_function(tolua_S,"setNoMarkingField",tolua_zeus_CDefenceInfo_setNoMarkingField00);
   tolua_function(tolua_S,"clearNoMarkingField",tolua_zeus_CDefenceInfo_clearNoMarkingField00);
   tolua_function(tolua_S,"clearAll",tolua_zeus_CDefenceInfo_clearAll00);
   tolua_function(tolua_S,"setNoChangeFlag",tolua_zeus_CDefenceInfo_setNoChangeFlag00);
   tolua_function(tolua_S,"clearNoChangeFlag",tolua_zeus_CDefenceInfo_clearNoChangeFlag00);
   tolua_function(tolua_S,"resetMarkingInfo",tolua_zeus_CDefenceInfo_resetMarkingInfo00);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"NormalPlayUtils",0);
  tolua_beginmodule(tolua_S,"NormalPlayUtils");
   tolua_function(tolua_S,"generateTwoPassPoint",tolua_zeus_NormalPlayUtils_generateTwoPassPoint00);
   tolua_function(tolua_S,"isEnemyBlockShootLine",tolua_zeus_NormalPlayUtils_isEnemyBlockShootLine00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"TwoKickPos","TwoKickPos","",tolua_collect_TwoKickPos);
  #else
  tolua_cclass(tolua_S,"TwoKickPos","TwoKickPos","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"TwoKickPos");
   tolua_variable(tolua_S,"onePos",tolua_get_TwoKickPos_onePos,tolua_set_TwoKickPos_onePos);
   tolua_variable(tolua_S,"anotherPos",tolua_get_TwoKickPos_anotherPos,tolua_set_TwoKickPos_anotherPos);
   tolua_function(tolua_S,"getOnePos",tolua_zeus_TwoKickPos_getOnePos00);
   tolua_function(tolua_S,"getAnotherPos",tolua_zeus_TwoKickPos_getAnotherPos00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"KickOffArea","KickOffArea","",NULL);
  tolua_beginmodule(tolua_S,"KickOffArea");
   tolua_variable(tolua_S,"_Left",tolua_get_KickOffArea__Left,tolua_set_KickOffArea__Left);
   tolua_variable(tolua_S,"_Right",tolua_get_KickOffArea__Right,tolua_set_KickOffArea__Right);
   tolua_variable(tolua_S,"baseDir",tolua_get_KickOffArea_baseDir,tolua_set_KickOffArea_baseDir);
   tolua_variable(tolua_S,"radius",tolua_get_KickOffArea_radius,tolua_set_KickOffArea_radius);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CIndirectDefender","CIndirectDefender","",tolua_collect_CIndirectDefender);
  #else
  tolua_cclass(tolua_S,"CIndirectDefender","CIndirectDefender","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CIndirectDefender");
   tolua_function(tolua_S,"new",tolua_zeus_CIndirectDefender_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CIndirectDefender_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CIndirectDefender_new00_local);
   tolua_function(tolua_S,"delete",tolua_zeus_CIndirectDefender_delete00);
   tolua_function(tolua_S,"getTwoDefPos",tolua_zeus_CIndirectDefender_getTwoDefPos00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CSupportPos","CSupportPos","",tolua_collect_CSupportPos);
  #else
  tolua_cclass(tolua_S,"CSupportPos","CSupportPos","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CSupportPos");
   tolua_function(tolua_S,"new",tolua_zeus_CSupportPos_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CSupportPos_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CSupportPos_new00_local);
   tolua_function(tolua_S,"delete",tolua_zeus_CSupportPos_delete00);
   tolua_function(tolua_S,"generatePos",tolua_zeus_CSupportPos_generatePos00);
   tolua_function(tolua_S,"getSupPos",tolua_zeus_CSupportPos_getSupPos00);
   tolua_function(tolua_S,"getSupPosNew",tolua_zeus_CSupportPos_getSupPosNew00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CAssistPoint","CAssistPoint","",tolua_collect_CAssistPoint);
  #else
  tolua_cclass(tolua_S,"CAssistPoint","CAssistPoint","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CAssistPoint");
   tolua_function(tolua_S,"new",tolua_zeus_CAssistPoint_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CAssistPoint_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CAssistPoint_new00_local);
   tolua_function(tolua_S,"delete",tolua_zeus_CAssistPoint_delete00);
   tolua_function(tolua_S,"getBestAssistPoint",tolua_zeus_CAssistPoint_getBestAssistPoint00);
   tolua_function(tolua_S,"generateBestPoint",tolua_zeus_CAssistPoint_generateBestPoint00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CMessiDecision","CMessiDecision","",tolua_collect_CMessiDecision);
  #else
  tolua_cclass(tolua_S,"CMessiDecision","CMessiDecision","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CMessiDecision");
   tolua_function(tolua_S,"new",tolua_zeus_CMessiDecision_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CMessiDecision_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CMessiDecision_new00_local);
   tolua_function(tolua_S,"messiRun",tolua_zeus_CMessiDecision_messiRun00);
   tolua_function(tolua_S,"nextState",tolua_zeus_CMessiDecision_nextState00);
   tolua_function(tolua_S,"leaderNum",tolua_zeus_CMessiDecision_leaderNum00);
   tolua_function(tolua_S,"receiverNum",tolua_zeus_CMessiDecision_receiverNum00);
   tolua_function(tolua_S,"attackerAmount",tolua_zeus_CMessiDecision_attackerAmount00);
   tolua_function(tolua_S,"passPos",tolua_zeus_CMessiDecision_passPos00);
   tolua_function(tolua_S,"receiverPos",tolua_zeus_CMessiDecision_receiverPos00);
   tolua_function(tolua_S,"leaderPos",tolua_zeus_CMessiDecision_leaderPos00);
   tolua_function(tolua_S,"otherPos",tolua_zeus_CMessiDecision_otherPos00);
   tolua_function(tolua_S,"goaliePassPos",tolua_zeus_CMessiDecision_goaliePassPos00);
   tolua_function(tolua_S,"setMessiRun",tolua_zeus_CMessiDecision_setMessiRun00);
   tolua_function(tolua_S,"isFlat",tolua_zeus_CMessiDecision_isFlat00);
   tolua_function(tolua_S,"passVel",tolua_zeus_CMessiDecision_passVel00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_zeus (lua_State* tolua_S) {
 return tolua_zeus_open(tolua_S);
};
#endif

