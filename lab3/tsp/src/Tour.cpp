// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"
#include <set>
#include <map>

Tour::Tour()
{
    first_Node = nullptr;

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
}




Tour::~Tour()
{
    Node* current = first_Node;
    set<Node*> set;

    while (current != nullptr) {
        set.insert(current);
        current = current->next;
        if (current == first_Node) {
            break;                      //tror inte dom gillar detta men men
        }
    }

    for (Node* node : set) {
        delete node;
    }


    // TODO: write this member
}

void Tour::show()
{
    Node* current = first_Node;

    while (current != nullptr) {
        cout << current->toString() << endl;
        current = current->next;        // move to the next node

        if (current == first_Node) {
            break;                      //tror inte dom gillar detta men men
        }
    }

    // TODO: write this member
}

void Tour::draw(QGraphicsScene *scene)
{
    Node* current = first_Node;

    while (current != nullptr) {
        current->point.drawTo(current->next->point, scene);
        current = current->next;        // move to the next node

        if (current == first_Node) {
            break;                      //tror inte dom gillar detta men men
        }
    }
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
    //cout << "Number of points on tour: " << count;


    return count;
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
    //cout << "Total distance of tour: " << total_distance;

    return total_distance;


    // TODO: write this member
}

void Tour::insertNearest(Point p)
{
    if(first_Node == nullptr) {
        Node* node1 = new Node(p, nullptr);
        node1->next = node1;
        first_Node = node1;
    }
    else
    {
        Node* current = first_Node;
        Node* closestNode = nullptr;
        int closestDistance = numeric_limits<int>::max();

        while (current != nullptr) {
            if (current->point.distanceTo(p) < closestDistance) {
                closestNode = current; //är rädd att closestnode också ändras när current ändras. Pekare pekar på pekare?
                closestDistance = current->point.distanceTo(p);
            }
            current = current->next;

            if (current == first_Node)
            {
                break;
            }
        }

        Node* newNode = new Node(p, closestNode->next);
        closestNode->next = newNode;

        //cout << "Closest node to p:_ " << closestNode->toString() << endl;;
    }


    // TODO: write this member
}

void Tour::insertSmallest(Point p)
{
    // TODO: write this member
    if(first_Node == nullptr) {
        Node* node1 = new Node(p, nullptr);
        node1->next = node1;
        first_Node = node1;
    }
    else
    {
        Node* current = first_Node->next;
        //Node* closestNode = nullptr;
        map<int, set<Node*>> possibleTours; //map of distance of tour and tours
        set<Node*> currentNodes;

        while(current != first_Node) {      //should make a set containing copies of all nodes.
            Node* node = new Node(current->point, current->next);
            currentNodes.insert(node);
            current = current->next;
        }
        set<Node*> currentNodesCopy = currentNodes;

        //current = first_Node;
        for(int i; i < currentNodesCopy.size(); i++) //to test all possible positions
        {
            current = first_Node;
            for(int ii = 0; ii < i; ii++) {     //move pointer
                current = current->next;
            }
            Node* newNode = new Node(p, current->next);
            current->next = newNode;
            possibleTours.insert({})            //funkar inte ska egentligen skapa ett tour objekt.
        }

    }
}
