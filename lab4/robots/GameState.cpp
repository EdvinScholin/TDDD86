/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 * Updated for TDDD86, 2021.
 *
 * This assignment was made by Wilmer Segerstedt (wilse150) and Edvin Schölin (edvsc779).
 * This file contains the code implementation of the GameState class.
 * See GameState.h for comments about each member.
 */

#include "GameState.h"
#include "utilities.h"
#include "constants.h"
#include <iostream>

GameState::GameState(int numberOfRobots) {
   for (int i = 0; i < numberOfRobots; i++) {
       Robot* robot = new Robot();
       while(!isEmpty(*robot)) {
           delete robot;
           robot = new Robot();
       }
       robots.push_back(robot);
    }
    teleportHero();
}

GameState::~GameState() {
    while (!robots.empty()){
        Robot* robot = robots.back();
        robots.pop_back();
        delete robot;
    }
}

GameState::GameState(const GameState& gameState) {
    for (int i = 0; i < gameState.robots.size(); i++) {
        robots.push_back(gameState.robots[i]->clone());
    }

    Hero hero = gameState.hero;
}

GameState& GameState::operator=(const GameState &gs) {
    if(this != &gs) {
        while (!robots.empty()){
            Robot* robot = robots.back();
            robots.pop_back();
            delete robot;
        }

        for (int i = 0; i < gs.robots.size(); i++) {
            robots.push_back(gs.robots[i]->clone());
        }

        this->hero = gs.hero;
    }

    return *this;
}

void GameState::draw(QGraphicsScene *scene) const {
    scene->clear();
    hero.draw(scene);
    for (const auto& robot: robots) {
        robot->draw(scene);

    }
}

void GameState::teleportHero() {
    do hero.teleport();
    while (!isEmpty(hero));
}

void GameState::moveRobots() {
    for(auto& robot: robots)
        robot->moveTowards(hero);
}


void GameState::updateCrashes() {
    for(unsigned i=0; i < robots.size(); ++i){
        for(unsigned o=i+1; o < robots.size(); ++o){
              if(robots[i]->at(*robots[o])){
                robots[i]->doCrash();
                robots[o]->doCrash();
            }
        }
    }
}

int GameState::countJustCrashed()const{
    int numberDestroyed = 0;
    for(unsigned i=0; i < robots.size(); ++i)
        if(robots[i]->justCrashed())
            numberDestroyed++;
    return numberDestroyed;
}

void GameState::junkTheCrashed(){
    for(unsigned i=0; i < robots.size(); ++i){
        if (robots[i]->justCrashed()) {
            Junk* new_junk = new Junk(robots[i]->asPoint());
            delete robots[i];
            robots[i] = new_junk;
        }
    }
}

bool GameState::stillLiveRobots() const {
    for(unsigned i=0; i < robots.size(); ++i)
        if(robots[i]->canMove())
            return true;
    return false;
}


bool GameState::heroDead() const {
    for(const auto& robot: robots){
        if(hero.at(*robot)){
            return true;
        }
    }
    return false;
}


void GameState::moveHeroTowards(const Point& dir) {
    hero.moveTowards(dir);
}

Point GameState::getHeroAsPoint() const {return hero.asPoint();}

/*
 * Free of robots and junk
 */
bool GameState::isEmpty(const Unit& unit) const {
    for(const auto& robot: robots)
        if(robot->at(unit))
            return false;
    return true;
}

