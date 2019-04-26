#ifndef NEATPOS_H
#define NEATPOS_H
#include <VisionModule.h>
#include "geometry.h"

/*****************************************************************************/
/*                      CNeatPos                                             */
/*****************************************************************************/

class CNeat{
public:
    CNeat();
    ~CNeat(void);

    /*************************************************************************/
    /* @fn void SetActionValues( double delta_x, double delta_y,             */
    /*                           double direction )                          */
    /*                                                                       */
    /* @brief get action values from python script and store                 */
    /*                                                                       */
    /* @author Hanwen Chen                                                   */
    /* @date 2019-3-4                                                        */
    /*                                                                       */
    /* @param delta_x, delta_y  postion                                      */
    /*************************************************************************/
    void SetActionValues( double delta_x, double delta_y,
                          double delta_direction );
//    CGeoPoint SetActionValues( double delta_x, double delta_y,
//                               double direction );

    /*************************************************************************/
    /* @fn     CGeoPoint GetPosition(const CVisionModule *pVision,           */
    /*                               const int num)                          */
    /*                                                                       */
    /* @brief  return as a function                                          */
    /*                                                                       */
    /* @author Hanwen Chen                                                   */
    /* @date   2019-3-4                                                      */
    /*                                                                       */
    /* @param  num - runner index                                            */
    /*************************************************************************/
    CGeoPoint GetPosition(const CVisionModule *pVision, const int num);

    /*************************************************************************/
    /* @fn     double GetDirection()                                         */
    /*                                                                       */
    /* @brief  return param direction to lua script                          */
    /*                                                                       */
    /* @author Hanwen Chen                                                   */
    /* @date   2019-3-4                                                      */
    /*                                                                       */
    /* @param  num - runner index                                            */
    /*************************************************************************/
    double GetDirection(const CVisionModule *pVision, const int num){
        _direction = pVision->OurPlayer(num).Dir() + _delta_direction;
        return _direction;
    }
private:
    CGeoPoint _param_position;
    double _delta_direction;
    double _delta_x;
    double _delta_y;
    double _direction;
    double _x;
    double _y;
};

typedef NormalSingleton< CNeat > Neat;

#endif // NEATPOS_H
