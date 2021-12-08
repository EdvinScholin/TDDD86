// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "costs.h"
#include "trailblazer.h"
#include <stack>
#include <set>
#include <algorithm>
// TODO: include any other headers you need; remove this comment
using namespace std;

void DFS(BasicGraph& graph, Vertex* start, Vertex* end, stack<Vertex*> stack, vector<Vertex*>& path) {
    start->visited = true;
    stack.push(start);

    if (start == end) {
        Node* node;
        while(!stack.empty()) {
            node = stack.top();
            node->setColor(GREEN);
            stack.pop();
            path.push_back(node); // kanske blir baklänges.
        }

        return;
    }

    for (Vertex *vertex : graph.getNeighbors(start)) {
        if (!vertex->visited) {
            if (!vertex->visited) {
                vertex->visited = true;
                vertex->setColor(YELLOW);
                DFS(graph, vertex, end, stack, path);
            }

            else {
                vertex->setColor(GRAY);
            }
        }
    }

    stack.pop();
}

vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
//    graph.resetData();

//    vector<Vertex*> path = {};
//    stack<Vertex*> stack;
//    Vertex* currentNode;

//    start->visited = true;
//    start->setColor(GREEN);
//    stack.push(start);


//    while (!stack.empty()) {



//       currentNode = stack.top();
//       stack.pop();


//       if (currentNode == end) {
//           while(!stack.empty()) {
//               currentNode = stack.top();
//               stack.pop();
//               path.push_back(currentNode); // kanske blir baklänges.
//           }
//           //reverse(path.begin(), path.end());
//           return path;
//       }

//       for (Vertex *vertex : graph.getNeighbors(currentNode)) {
//           if (!vertex->visited) {
//               stack.push(vertex);
//               vertex->visited = true;
//               vertex->setColor(YELLOW);
//           }
//       }
//    }
//    return path;

    graph.resetData();
    stack<Vertex*> stack;
    vector<Vertex*> path = {};

    DFS(graph, start, end, stack, path);
    return path;

}





vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
    return path;
}

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
    return path;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
    return path;
}
