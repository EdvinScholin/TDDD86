/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 *
 * This assignment was made by Wilmer Segerstedt (wilse150) and Edvin Schölin (edvsc779).
 * This file contains the code implementation of the Junk class.
 * See Junk.h for comments about each member.
 */

#include "Junk.h"
#include "constants.h"

void Junk::moveTowards(const Unit &u) {}

Junk* Junk::clone() const{
    return new Junk{ *this };
}

bool Junk::canMove() const {
    return false;
}

void Junk::doCrash() {}

bool Junk::justCrashed() const {
    return false;
}

void Junk::draw(QGraphicsScene *scene) const {
    Point corner = asPoint();
    scene->addEllipse(QRectF(corner.x * UNIT_WIDTH, corner.y * UNIT_HEIGHT,
                             JUNK_RADIUS, JUNK_RADIUS), QPen(), QBrush(JUNK_COLOR));
}
