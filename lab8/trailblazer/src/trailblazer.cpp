// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "costs.h"
#include "trailblazer.h"
#include <stack>
#include <set>
#include <algorithm>
#include <queue>
#include <unordered_set>
// TODO: include any other headers you need; remove this comment
using namespace std;

void DFS(BasicGraph& graph, Vertex* start, Vertex* end, stack<Vertex*>& stack, vector<Vertex*>& path) {
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
vector<Vertex*> DFSV2(BasicGraph& graph, Vertex* start, Vertex* end) {
    //TODO: byt variabelnamn och fixa färgerna.
    queue<stack<Vertex*>> q;
    stack<Vertex*> chain_stack;
    chain_stack.push(start);
    q.push(chain_stack);                        //create/add a stack containing {w1} to the queue

    while (!q.empty()) {                        //the queue is not empty
        chain_stack = q.front();
        q.pop();                                //dequeue the partial-chain stack from the front of the queue
        if (chain_stack.top() == end) {          //if the word at the top of the stack is the destinaction word
            vector<Vertex*> path;
            stack<Vertex*> new_stack;
            while (!chain_stack.empty()) {      //output the elements of the stack as the solution
                //chain_stack.top()->setColor(GREEN); //för att visa vägen atm
                new_stack.push(chain_stack.top());
                chain_stack.pop();
            }
            while(!new_stack.empty()) {
                path.push_back(new_stack.top());
                new_stack.pop();

            }
            return path;

        }

        else {
            for (Vertex *neighbour : graph.getNeighbors(chain_stack.top())) {
                if (!neighbour->visited) {   //if that neighbour word has not already been used in a ladder before
                    stack<Vertex*> copy_stack = chain_stack;             //create a copy of the current chain stack
                    neighbour->visited = true;                     //ensure neighbour word is not used again
                    neighbour->setColor(GREEN);
                    copy_stack.push(neighbour);                         //put the neighbour word at the top of the copy stack
                    q.push(copy_stack);                                 //add the copy stack to the end of the queue
                }
                neighbour->setColor(GRAY);
            }
        }
    }
    return {};
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

    //DFS(graph, start, end, stack, path);
    //DFS(graph, start, end, stack, path);

    path = DFSV2(graph, start, end);
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
