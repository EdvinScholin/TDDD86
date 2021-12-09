// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "costs.h"
#include "trailblazer.h"
#include "pqueue.h"
#include <stack>
#include <queue>
#include <limits>
#include <map>
#include <set>

// TODO: include any other headers you need; remove this comment
using namespace std;

bool DFS(BasicGraph& graph, Vertex* start, Vertex* end, stack<Vertex*> stack1, vector<Vertex*>& path) {
    start->visited = true;
    start->setColor(GREEN);
    stack1.push(start);

    if (start == end) {
        stack<Vertex*> new_stack;
        while (!stack1.empty()) {      //output the elements of the stack as the solution
            new_stack.push(stack1.top());
            stack1.pop();
        }
        while (!new_stack.empty()) {
            path.push_back(new_stack.top());
            new_stack.pop();
        }
        return true;
    }

    for (Vertex *vertex : graph.getNeighbors(start)) {
        if (!vertex->visited) {
            vertex->visited = true;
            if (DFS(graph, vertex, end, stack1, path)) {
                return true;
            }
            vertex->setColor(GRAY);
        }
    }

    stack1.pop();
    return false;
}

vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    stack<Vertex*> stack;
    vector<Vertex*> path = {};
    DFS(graph, start, end, stack, path);
    return path;
}


Vertex* BFS(BasicGraph& graph, Vertex* start, Vertex* end, queue<Vertex*> q) {
    Vertex* currentVertex;

    q.push(start);
    start->visited = true;
    start->setColor(YELLOW);

    while (!q.empty()) {
        currentVertex = q.front();
        currentVertex->setColor(GREEN);
        q.pop();

        if (currentVertex == end) {
            return currentVertex;
        }

        for (auto neighbour : graph.getNeighbors(currentVertex)) {
            if (!neighbour->visited) {
                neighbour->previous = currentVertex;
                neighbour->setColor(YELLOW);
                neighbour->visited = true;
                q.push(neighbour);
            }
        }
    }

    return nullptr;
}


vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    queue<Vertex*> q;
    vector<Vertex*> path = {};

    Vertex* vertex = BFS(graph, start, end, q);
    stack<Vertex*> vertexStack;

    while(vertex != start) {
        vertexStack.push(vertex);
        vertex = vertex->previous;
    }

    vertexStack.push(start);

    while(!vertexStack.empty()) {
        path.push_back(vertexStack.top());
        vertexStack.pop();
    }

    return path;
}

Vertex* dijsktraHelp(BasicGraph& graph, Vertex* start, Vertex* end) {
    PriorityQueue<Vertex*> pq;
    Vertex* bestVertex;
    double altCost;

    for (Vertex* vertex : graph.getNodeSet()) {
        if (vertex != start) {
            vertex->cost = numeric_limits<double>::infinity();
            vertex->previous = nullptr;
        }
        pq.enqueue(vertex, vertex->cost);
    }

    while (!pq.isEmpty()) {
        bestVertex = pq.dequeue();
        bestVertex->setColor(GREEN);

        if(bestVertex == end) {
            return bestVertex;
        }

        for (Vertex* neighbour : graph.getNeighbors(bestVertex)) {
            altCost = bestVertex->cost + graph.getEdge(bestVertex, neighbour)->cost;

            if (altCost < neighbour->cost) {
                neighbour->cost = altCost;
                neighbour->previous = bestVertex;
                pq.changePriority(neighbour, altCost);
                neighbour->setColor(YELLOW);
            }
        }
    }
}

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();

    vector<Vertex*> path {};

    Vertex* vertex = dijsktraHelp(graph, start, end);
    stack<Vertex*> vertexStack;

    if (vertex == nullptr) { //kanske
        return path;
    }

    while(vertex != start) {
        vertexStack.push(vertex);
        vertex = vertex->previous;
    }

    vertexStack.push(start);

    while(!vertexStack.empty()) {
        path.push_back(vertexStack.top());
        vertexStack.pop();
    }


    return path;
}

Vertex* aStarHelp(BasicGraph& graph, Vertex* start, Vertex* end) {
    PriorityQueue<Vertex*> pq;
    Vertex* bestVertex;
    double altCost;
    double bestGuessCost;
    map<Vertex*, double> fscore; //fett onödig
    set<Vertex*> openSet;


    for (Vertex* vertex : graph.getNodeSet()) {
        if (vertex != start) {
            vertex->cost = numeric_limits<double>::infinity();
            vertex->previous = nullptr;
        }
//        pq.enqueue(vertex, vertex->cost);
//        openSet.insert(vertex);
    }

    pq.enqueue(start, start->cost);
    openSet.insert(start);


    while (!pq.isEmpty()) {
        bestVertex = pq.dequeue();
        openSet.erase(bestVertex);
        bestVertex->setColor(GREEN);

        if(bestVertex == end) {
            return bestVertex;
        }

        for (Vertex* neighbour : graph.getNeighbors(bestVertex)) {
            altCost = bestVertex->cost + graph.getEdge(bestVertex, neighbour)->cost;


            if (altCost < neighbour->cost) {
                neighbour->cost = altCost;
                neighbour->previous = bestVertex;

                bestGuessCost = altCost + bestVertex->heuristic(neighbour);


                if(openSet.find(neighbour) == openSet.end()){
                    pq.enqueue(neighbour, bestGuessCost);
                    neighbour->setColor(YELLOW);
                }



            }
        }
    }
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();

    vector<Vertex*> path {};

    Vertex* vertex = aStarHelp(graph, start, end);
    stack<Vertex*> vertexStack;

    if (vertex == nullptr) { //kanske
        return path;
    }

    while(vertex != start) {
        vertexStack.push(vertex);
        vertex = vertex->previous;
    }

    vertexStack.push(start);

    while(!vertexStack.empty()) {
        path.push_back(vertexStack.top());
        vertexStack.pop();
    }


    return path;
}
