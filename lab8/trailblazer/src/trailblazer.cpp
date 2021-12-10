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

        for (Vertex* neighbour : graph.getNeighbors(currentVertex)) {
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
    Vertex* current;
    double altCost;
    double inf = numeric_limits<double>::infinity();

    for (Vertex* vertex : graph.getNodeSet()) {
        if (vertex != start) {
            vertex->cost = inf;
        }
    }
    pq.enqueue(start, start->cost);
    start->setColor(YELLOW);

    while (!pq.isEmpty()) {
        current = pq.dequeue();
        current->setColor(GREEN);

        if(current == end) {
            return current;
        }

        for (Vertex* neighbour : graph.getNeighbors(current)) {
            altCost = current->cost + graph.getEdge(current, neighbour)->cost;

            if (altCost < neighbour->cost) {
                neighbour->cost = altCost;
                neighbour->previous = current;
                pq.enqueue(neighbour, altCost);
                neighbour->setColor(YELLOW);
            }
        }
    }
    return nullptr;
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
    Vertex* current;
    double altCost;
    double bestGuess;
    double inf = numeric_limits<double>::infinity();
    PriorityQueue<Vertex*> pq;

    for (Vertex* vertex : graph.getNodeSet()) {
        if (vertex != start) {
            vertex->cost = inf;
        }
    }
    pq.enqueue(start, start->heuristic(end));
    start->setColor(YELLOW);
    start->visited = true;

    while (!pq.isEmpty()) {
        current = pq.dequeue();
        current->visited = false;
        current->setColor(GREEN);

        if (current == end) {
            return current;
        }

        for (Vertex* neighbour : graph.getNeighbors(current)) {
            altCost = current->cost + graph.getEdge(current, neighbour)->cost;
            if (altCost < neighbour->cost) {
                neighbour->previous = current;
                neighbour->cost = altCost;
                bestGuess = altCost + neighbour->heuristic(end);

                if (!neighbour->visited) {
                    pq.enqueue(neighbour, bestGuess);
                    neighbour->setColor(YELLOW);
                    neighbour->visited = true;
                }
            }
        }

    }
    return nullptr;
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
