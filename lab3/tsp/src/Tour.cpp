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
        //följande kod fungerar alldeles utmärkt.
        Node* node1 = new Node(a, nullptr);
        Node* node2 = new Node(b, nullptr);
        Node* node3 = new Node(c, nullptr);
        Node* node4 = new Node(d, nullptr);

        node1->next = node2;
        node2->next = node3;
        node3->next = node4;
        node4->next = node1;

        first_Node = node1;



//    Node* node1 = new Node(a, nullptr);
//    Node* node2 = new Node(b, nullptr);
//    Node* node3 = new Node(c, nullptr);
//    Node* node4 = new Node(d, nullptr);

//    node1->next = node2;
//    node2->next = node3;
//    node3->next = node4;
//    node4->next = node1;

//    first_Node = node1;






//    Node* node1 = nullptr; //new Node(a, nullptr);
//    Node* node2 = nullptr;//new Node(b, nullptr);
//    Node* node3 = nullptr; //new Node(c, nullptr);
//    Node* node4 = nullptr; //new Node(d, nullptr);

//    delete node1;
//    node1 = new Node(a, node2);
//    delete node2;
//    node2 = new Node(b, node3);
//    delete node3;
//    node3 = new Node(c, node4);
//    delete node4;
//    node4 = new Node(d, node1);

//    first_Node = node1;
}

Tour::~Tour()
{
    // TODO: write this member
}

void Tour::show()
{
    Node* current = first_Node;
    while (current != nullptr) {
        cout << current->toString() << endl;
        current = current->next; // move to the next node
        if (current == first_Node) {
            break;                      //tror inte dom gillar detta men men
        }

    }


//    Node* node = first_Node;

//    for (int i = 0; i < 4; i++) {
//        cout << node->toString() << endl;
//        node = node->next;
//    }

    // TODO: write this member
}

void Tour::draw(QGraphicsScene *scene)
{
    // TODO: write this member
}

int Tour::size()
{
    Node* current = first_Node;
    int count = 0;
    while (current != nullptr) {
        count++;
        current = current->next; // move to the next node
        if (current == first_Node) {
            break;                      //tror inte dom gillar detta men men
        }
    }
    cout << "Number of points on tour: " << count;



    // TODO: write this member
}

double Tour::distance()
{
    Node* current = first_Node;
    int total_distance = 0;
    while (current != nullptr) {
        total_distance += current->point.distanceTo(current->next->point);
        current = current->next; // move to the next node
        if (current == first_Node) {
            break;                      //tror inte dom gillar detta men men
        }
    }
    cout << "Total distance of tour: " << total_distance;



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
