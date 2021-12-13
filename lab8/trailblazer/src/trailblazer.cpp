/*
 * This assignment was made by Edvin Schölin (edvsc779) and Wilmer Segerstedt (wilse150).
 * The file contains four implementations of various search algorithms in a graph.
 */

#include "costs.h"
#include "trailblazer.h"
#include "pqueue.h"
#include <stack>
#include <queue>
#include <limits>

using namespace std;

/*
 * Backtracks from end vertex to start vertex.
 */
vector<Node*> makePath(Vertex* vertex, Vertex* start) {
    vector<Vertex*> path = {};
    stack<Vertex*> vertexStack;

    if (vertex == nullptr) {
        return path;
    }

    while (vertex != start) {
        vertexStack.push(vertex);
        vertex = vertex->previous;
    }

    vertexStack.push(start);

    while (!vertexStack.empty()) { // This flips the order of the path since the stack contains the reverse order of the path.
        path.push_back(vertexStack.top());
        vertexStack.pop();
    }

    return path;
}

/*
 * Helper function which contains algorithm for depth first search.
 */
bool dfsHelper(BasicGraph& graph, Vertex* start, Vertex* end, stack<Vertex*> stack1, vector<Vertex*>& path) {
    start->visited = true;
    start->setColor(GREEN);
    stack1.push(start); // Add start node to stack

    if (start == end) {
        stack<Vertex*> new_stack;
        while (!stack1.empty()) {
            new_stack.push(stack1.top());
            stack1.pop();
        }
        while (!new_stack.empty()) { // Flips the order of the path
            path.push_back(new_stack.top());
            new_stack.pop();
        }
        return true;
    }

    for (Vertex *vertex : graph.getNeighbors(start)) { // Iterates over all neighbours to given node
        if (!vertex->visited) {
            vertex->visited = true;

            if (dfsHelper(graph, vertex, end, stack1, path)) {
                return true; // We have found a path
            }
            vertex->setColor(GRAY); // Vertex has been checked but not chosen in the final path.
        }
    }

    stack1.pop(); // The node didn't lead anywhere
    return false;
}

/*
 * Main function for depth first search.
 */
vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    stack<Vertex*> stack;
    vector<Vertex*> path = {};
    dfsHelper(graph, start, end, stack, path);
    return path;
}

/*
 * Helper function which contains algorithm for breadth first search.
 */
Vertex* bfsHelper(BasicGraph& graph, Vertex* start, Vertex* end, queue<Vertex*> q) {
    Vertex* currentVertex;

    q.push(start);
    start->visited = true;
    start->setColor(YELLOW); // In process

    while (!q.empty()) {
        currentVertex = q.front();
        currentVertex->setColor(GREEN); // Is path of the final path
        q.pop();

        if (currentVertex == end) { // We have found the end node and it will backtrack the path trough node->previous
            return currentVertex;
        }

        for (Vertex* neighbour : graph.getNeighbors(currentVertex)) { // Iterates over all neighbours to given node
            if (!neighbour->visited) {
                neighbour->previous = currentVertex; // This is what tracks the path back to the start node
                neighbour->setColor(YELLOW); // In process
                neighbour->visited = true;
                q.push(neighbour);
            }
        }
    }
    return nullptr;
}

/*
 * Main function for breadth first search
 */
vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    queue<Vertex*> q;
    Vertex* vertex = bfsHelper(graph, start, end, q);

    return makePath(vertex, start);
}

/*
 * Helper function which contains algorithm for Djisktra search.
 */
Vertex* dijsktraHelper(BasicGraph& graph, Vertex* start, Vertex* end) {
    PriorityQueue<Vertex*> pq;
    Vertex* current;
    double altCost;
    double inf = numeric_limits<double>::infinity();

    for (Vertex* vertex : graph.getNodeSet()) { // Set all node inital costs to infinty
        if (vertex != start) {
            vertex->cost = inf;
        }
    }

    pq.enqueue(start, start->cost);
    start->setColor(YELLOW);

    while (!pq.isEmpty()) {
        current = pq.dequeue(); // We want to check the node with highest priority (lowest cost)
        current->setColor(GREEN);

        if (current == end) { // We have found the end node and it will backtrack the path trough node->previous
            return current;
        }

        for (Vertex* neighbour : graph.getNeighbors(current)) {
            altCost = current->cost + graph.getEdge(current, neighbour)->cost; // Calculate cost from start to neighbour

            if (altCost < neighbour->cost) { // Which neighbour has the cheapest route?
                neighbour->cost = altCost; // The new cost of the neighbour
                neighbour->previous = current; // This is what tracks the path back to the start node
                pq.enqueue(neighbour, altCost); // Add neighbour with the accurate cost to the prio queue
                neighbour->setColor(YELLOW);
            }
        }
    }
    return nullptr;
}

/*
 * Main function for Djisktra algorithm.
 */
vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    Vertex* vertex = dijsktraHelper(graph, start, end);

    return makePath(vertex, start);
}

/*
 * Helper function which contains algorithm for aStar search.
 */
Vertex* aStarHelp(BasicGraph& graph, Vertex* start, Vertex* end) {
    Vertex* current;
    double altCost;
    double bestGuess;
    double inf = numeric_limits<double>::infinity();
    PriorityQueue<Vertex*> pq;

    for (Vertex* vertex : graph.getNodeSet()) { // Set all node inital costs to infinty
        if (vertex != start) {
            vertex->cost = inf;
        }
    }
    pq.enqueue(start, start->heuristic(end)); // Enqueues the start node with the estimated cost to reach the end
    start->setColor(YELLOW);
    start->visited = true;

    while (!pq.isEmpty()) {
        current = pq.dequeue(); // We want to check the node with highest priority (lowest estimated cost to reach the end)
        current->visited = false;
        current->setColor(GREEN);

        if (current == end) { // We have found the end node and it will backtrack the path trough node->previous
            return current;
        }

        for (Vertex* neighbour : graph.getNeighbors(current)) {
            altCost = current->cost + graph.getEdge(current, neighbour)->cost; // Calculate cost from start to neighbour
            if (altCost < neighbour->cost) { // Which neighbour has the cheapest route?
                neighbour->previous = current;
                neighbour->cost = altCost;
                bestGuess = altCost + neighbour->heuristic(end); // Current best guess of the cheapest path cost
                                                                 // from start to end
                if (!neighbour->visited) { // Is node already in prio queue? If not, add it
                    pq.enqueue(neighbour, bestGuess); // Enqueue node with the best estimated cost
                    neighbour->setColor(YELLOW);
                    neighbour->visited = true;
                }
            }
        }

    }
    return nullptr;
}

/*
 * Main function for aStar search.
 */
vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    Vertex* vertex = aStarHelp(graph, start, end);

    return makePath(vertex, start);
}
