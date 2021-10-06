// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

Tour::Tour()
{
    // TODO: write this member
}

Tour::Tour(Point a, Point b, Point c, Point d)
{

    Node* node1 = new Node(a, nullptr);
    Node* node2 = new Node(b, nullptr);
    Node* node3 = new Node(c, nullptr);
    Node* node4 = new Node(d, nullptr);

    delete node1;
    node1 = new Node(a, node2);
    delete node2;
    node2 = new Node(b, node3);
    delete node3;
    node3 = new Node(c, node4);
    delete node4;
    node4 = new Node(d, node1);

    first_Node = node1;
}

Tour::~Tour()
{
    // TODO: write this member
}

void Tour::show()
{
    Node* node = first_Node;

    for (int i = 0; i < 4; i++) {
        cout << node->toString() << endl;
        node = node->next;
    }

    // TODO: write this member
}

void Tour::draw(QGraphicsScene *scene)
{
    // TODO: write this member
}

int Tour::size()
{
    // TODO: write this member
}

double Tour::distance()
{
    // TODO: write this member
}

void Tour::insertNearest(Point p)
{
    // TODO: write this member
}

void Tour::insertSmallest(Point p)
{
    // TODO: write this member
}
