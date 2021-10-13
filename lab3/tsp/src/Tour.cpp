/*
 * This assignment was made by Wilmer Segerstedt (wilse150) and Edvin Schölin (edvsc779).
 * This file contains the code implementation of the Tour class.
 * See Tour.h for comments about each member.
 */

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

Tour::Tour()
{
    first_Node = nullptr;
}

Tour::Tour(Point const& a, Point const& b, Point const& c, Point const& d)
{
        Node* node1 = new Node(a, nullptr);
        Node* node2 = new Node(b, nullptr);
        Node* node3 = new Node(c, nullptr);
        Node* node4 = new Node(d, nullptr);

        node1->next = node2;
        node2->next = node3;
        node3->next = node4;
        node4->next = node1;

        first_Node = node1;
}

Tour::~Tour()
{

    Node* current = first_Node;
    Node* temp_node = nullptr;

    while (current != nullptr) {
        temp_node = current->next;
        delete current;
        current = temp_node;

        if (current == first_Node) {
            break;
        }
    }
}

void Tour::show() const
{
    Node* current = first_Node;

    while (current != nullptr) {
        cout << current->toString() << endl;
        current = current->next;

        if (current == first_Node) {
            break;
        }
    }
}

void Tour::draw(QGraphicsScene *scene) const
{
    Node* current = first_Node;

    while (current != nullptr) {
        current->point.drawTo(current->next->point, scene);
        current = current->next;

        if (current == first_Node) {
            break;
        }
    }
}

int Tour::size() const
{
    Node* current = first_Node;
    int count = 0;

    while (current != nullptr) {
        count++;
        current = current->next;

        if (current == first_Node) {
            break;
        }
    }

    return count;
}

double Tour::distance() const
{
    Node* current = first_Node;
    double total_distance = 0;
    while (current != nullptr) {
        total_distance += current->point.distanceTo(current->next->point); // Add the distance between current point to next point
        current = current->next;
        if (current == first_Node) {
            break;
        }
    }

    return total_distance;
}

void Tour::insertNearest(Point const& p)
{
    if (first_Node == nullptr) {
        Node* node1 = new Node(p, nullptr);
        node1->next = node1;
        first_Node = node1;
    }
    else
    {
        Node* current = first_Node;
        Node* closestNode = nullptr;
        double closestDistance = numeric_limits<double>::max();

        while (current != nullptr) {
            if (current->point.distanceTo(p) < closestDistance) { // If there is a closer distance, we set a new closest node and closest distance
                closestNode = current;
                closestDistance = current->point.distanceTo(p);
            }
            current = current->next;

            if (current == first_Node)
            {
                break;
            }
        }

        Node* newNode = new Node(p, closestNode->next); // Insert the node at the nearest node
        closestNode->next = newNode;
    }
}

void Tour::insertSmallest(Point const& p)
{
    if(first_Node == nullptr) {
        Node* node1 = new Node(p, nullptr);
        node1->next = node1;
        first_Node = node1;
    }
    else {
        Node* current = first_Node;
        Node* bestNode = nullptr;
        double shortestDistanceIncrease = numeric_limits<double>::max();
        double startingDistance = 0;
        double distanceIncrease = 0;
        double d1 = 0;
        double d2 = 0;

        while (current != nullptr) {
            startingDistance = current->point.distanceTo(current->next->point); // Point A->B starting distance.
            d1 = current->point.distanceTo(p);                                  // distance between point A and P.
            d2 = current->next->point.distanceTo(p);                            // distance between point P and B.
            distanceIncrease = d1 + d2 - startingDistance;

            if (distanceIncrease < shortestDistanceIncrease) {
                shortestDistanceIncrease = distanceIncrease;
                bestNode = current;
            }
            current = current->next;

            if (current == first_Node)
            {
                break;
            }
        }

        Node* newNode = new Node(p, bestNode->next); //insert node that results in shortest tour distance increase.
        bestNode->next = newNode;
    }
}
