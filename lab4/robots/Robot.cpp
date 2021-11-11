/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 *
 * This assignment was made by Wilmer Segerstedt (wilse150) and Edvin Schölin (edvsc779).
 * This file contains the code implementation of the Robot class.
 * See Robot.h for comments about each member.
 */

#include "Robot.h"
#include "constants.h"

Robot::Robot() {

}

Robot* Robot::clone() const
{
    return new Robot{ *this };
}

bool Robot::canMove() const{
    return !crashed;
}

void Robot::doCrash(){
    crashed = true;
}

bool Robot::justCrashed() const{
    return crashed;
}

void Robot::draw(QGraphicsScene *scene) const {
    Point corner = asPoint();
    scene->addEllipse(QRectF(corner.x * UNIT_WIDTH, corner.y * UNIT_HEIGHT,
                             JUNK_RADIUS, JUNK_RADIUS), QPen(), QBrush(ROBOT_COLOR));
}


