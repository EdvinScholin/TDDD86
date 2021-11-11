/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 *
 * This assignment was made by Wilmer Segerstedt (wilse150) and Edvin Schölin (edvsc779).
 * This file contains declaration of the Junk class.
 * See Junk.cpp for code implementation of each member.
 */

#ifndef JUNK_H
#define JUNK_H

#include "Robot.h"
#include <QGraphicsScene>

class Junk : public Robot {
public:
    /*
     * Constructor for Junk
     */
    Junk(const Point& p): Robot(p){}

    /*
     * Clone method for Junk using return statement of this object
     */
    Junk* clone() const override ;

    /*
     * Do not move towards a hero
     */
    void moveTowards(const Unit& u) override;

    /*
     * did not crash yet
     */
    bool canMove() const override;

    /*
     * Crashes and remembers it
     */
    void doCrash() override;

    /*
     * Return whether the robot crashed
     */
    bool justCrashed() const override;

    /*
    * Draws this junk onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene* scene) const override;
};

#endif // JUNK_H
