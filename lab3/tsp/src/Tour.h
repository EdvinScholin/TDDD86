/*
 * This assignment was made by Wilmer Segerstedt (wilse150) and Edvin Schölin (edvsc779).
 * This file contains declaration of the Tour class.
 * See Tour.cpp for code implementation of each member.
 */

#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"

/*
 * The tour class represents the circular linked list made by multiple
 * nodes.
 */
class Tour {
public:
    /*
     * Default constructor.
     */
    Tour();

    /*
     * Constructs a tour with four points for testing purposes.
     */
    Tour(Point const& a, Point const& b, Point const& c, Point const& d);

    /*
     * Default destructor.
     */
    ~Tour();

    /*
     * Prints all nodes in the linked list to the console, using Node class' method
     * toString().
     */
    void show() const;

    /*
     * Shows the linked list as lines connecting all the nodes.
     */
    void draw(QGraphicsScene* scene) const;

    /*
     * Counts all nodes in the linked list and returns the value.
     */
    int size() const;

    /*
     * Calculates the total distance between the points of the nodes.
     */
    double distance() const;

    /*
     * Inserts node using nearest point heuristic.
     */
    void insertNearest(Point const& p);

    /*
     * Inserts node using smallest distance increase heuristic.
     */
    void insertSmallest(Point const& p);

private:
    Node* first_Node; // A pointer to the first node in the linked list
};

#endif // END TOUR_H
