/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 *
 * This assignment was made by Wilmer Segerstedt (wilse150) and Edvin Schölin (edvsc779).
 * This file contains declaration of the Robot class.
 * See Robot.cpp for code implementation of each member.
 */

#ifndef ROBOT_H
#define ROBOT_H

#include "Unit.h"
#include <QGraphicsScene>

class Robot : public Unit {
    bool crashed = false;

public:
    /*
     * Default constructor
     */
    Robot();

    /*
     * Robot constructor
     */
    Robot(const Point& p): Unit(p){}

    /*
     * Clone method using return statement of this object
     */

    virtual Robot* clone() const ;

    /*
     * did not crash yet
     */
    virtual bool canMove() const;

    /*
     * Crashes and remembers it
     */
    virtual void doCrash();

    /*
     * Return whether the robot crashed
     */
    virtual bool justCrashed() const;


    /*
    * Draws this robot onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene* scene) const;


};

#endif // ROBOT_H
