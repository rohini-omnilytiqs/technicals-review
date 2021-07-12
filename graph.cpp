// Simple undirected graph representation where nodes are ints 
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <stack>
#include <unordered_set>
#include <queue>
#include <tuple>
#include <queue>
#include <functional>

using namespace std;

// typedef tuple<int, char, char> key_t;

// struct key_hash : public unary_function<key_t, size_t>
// {
//  size_t operator()(const key_t& k) const
//  {
//    return get<0>(k) ^ get<1>(k) ^ get<2>(k);
//  }
// };
// typedef std::unordered_map<const key_t,data,key_hash,key_equal> map_t;

class Graph{
    private:
        vector<int> nodes;
        unordered_map<int, vector<int>*> adj;
        unordered_map<tuple<int, int>, int> edgeWeights;
        int getUnexploredNeighborIndex(int node, unordered_set<int> visited);
        int getFirstUnvisitedNodeIndex(unordered_set<int> visited);
        bool Compare(int node1, int node2);

    public: 
        Graph();
        ~Graph(){
            for(const auto &i : adj)
                delete i.second;
        } 
        void addNode(int node); // O(V) (because of checking if the node exists already, otherwise O(1))
        void deleteNode(int node); // O(V) (because of checking if the node exists, otherwise O(1))
        vector<int> getNeighbors(int node); // O(1)
        void addEdge(int node1, int node2, int weight = 0); // O(V) (because of checking if the nodes exist, otherwise O(1))
        int getEdgeWeight(int node1, int node2); // O(E) (because of checking if the edge exists, otherwise O(1))
        void removeEdge(int node1, int node2); // O(V)+O(E) (because of checking if the nodes and edge exists, otherwise O(1))
        bool cycleHelper(int nodeToExplore, int unexploredNeighborIndex, unordered_set<int> visited);
        vector<int> BFS(); // O(V+E)
        vector<int> DFS(bool &hasCycle); // O(V+E)
        // had issues using PQ for dijkstra's. could be implemented without a PQ just so it is done
        // unordered_map<int, int> dijkstra(int sourceNode); // O(V + ElogV) with PQ, otherwise O(V^2). ElogV term comes bc vertex's position in PQ can be updated once for each neighbor.
};

// add node by checking it doesn't already exist and adding an empty list to adjacency list
void Graph::addNode(int node){
    if (find(nodes.begin(), nodes.end(), node) != nodes.end()){
        return;
    }
    nodes.push_back(node);
    vector<int>* newAdj = new vector<int>;
    adj.insert({node, newAdj});
}

// delete node by checking it exists and then deleting it, and removing it from adjacency list
void Graph::deleteNode(int node){
    vector<int>::iterator it  = find(nodes.begin(), nodes.end(), node);
    if (it != nodes.end()){
        nodes.erase(it);
        adj.erase(node);

        for (unordered_map<int, vector<int>*>::iterator mapIt = adj.begin(); mapIt != adj.end(); ++mapIt){
            vector<int>::iterator listIt = find(mapIt->second->begin(), mapIt->second->end(), node);
            if (listIt != mapIt->second->end()) {
                mapIt->second->erase(listIt);
            }
        }
    
    } 
}

// get neighbors with adjacency list  
vector<int> Graph::getNeighbors(int node){
    return *(adj[node]);
}

// add edge by making sure both nodes exist and adding to their respective adjacency lists
// also add non-negative edge weight to map, and if no weight is given, it defaults to 0
void Graph::addEdge(int node1, int node2, int weight){
    vector<int>::iterator it1  = find(nodes.begin(), nodes.end(), node1);
    vector<int>::iterator it2  = find(nodes.begin(), nodes.end(), node2);

    if ((it1 != nodes.end()) && (it2 != nodes.end())){
        adj[node1]->push_back(node2);
        adj[node2]->push_back(node1);
        tuple<int, int> edge = {node1, node2};
        if (weight >= 0){
           edgeWeights.insert({edge, weight}); 
        }
        else{        
            edgeWeights.insert({edge, 0});
        }
    }
}

// gets edge weight by checking if edge exists, and returning the value in the edge weights map
int Graph::getEdgeWeight(int node1, int node2){
    tuple<int, int> edge = {node1, node2};
    if (edgeWeights.find(edge) == edgeWeights.end()) {
        return edgeWeights[edge];
    }
    return -1;
}

// remove edge by making sure both nodes exist and the two nodes exist in each other's adjacency list, and removing them from it
void Graph::removeEdge(int node1, int node2) {
    vector<int>::iterator it1  = find(nodes.begin(), nodes.end(), node1);
    vector<int>::iterator it2  = find(nodes.begin(), nodes.end(), node2);

    if ((it1 != nodes.end()) && (it2 != nodes.end())){
    
        vector<int>::iterator node2Adj = find(adj[node1]->begin(), adj[node1]->end(), node2);
        vector<int>::iterator node1Adj = find(adj[node2]->begin(), adj[node2]->end(), node1);

        if((node2Adj != adj[node1]->end()) && (node1Adj != adj[node2]->end())) {
            adj[node1]->erase(node2Adj);
            adj[node2]->erase(node1Adj);
        }
    }
}

// DEPTH FIRST SEARCH: start at a source and explore it completely before moving on
// also uses hasCycle param to check if a cycle exists by checking if the neighbors of the node being explored has a neighbor visited node
vector<int> Graph::DFS(bool &hasCycle){
    vector<int> traversal; 
    stack<int> toExplore; // uses stack to explore all nodes as deep as possible
    unordered_set<int> visited;
    hasCycle = false;

    if(nodes.empty())
        return traversal;
    
    toExplore.push(nodes[0]);
    traversal.push_back(nodes[0]);
    visited.insert(nodes[0]);

    // continue until all nodes have been explored
    while(traversal.size() != nodes.size()){
        int nodeToExplore = toExplore.top();

        // tries to get unexplored neighbor and adds it to the traversal, marks it as visited, and puts it on the stack
        int unexploredNeighborIndex = getUnexploredNeighborIndex(nodeToExplore, visited); 
        if (unexploredNeighborIndex != -1){
            int neighbor = adj[nodeToExplore]->at(unexploredNeighborIndex);
            toExplore.push(neighbor);
            traversal.push_back(neighbor);
            visited.insert(neighbor);

            // check for cycle by checking if the neighbor has neighbors it has seen before (besides the source)
            if(!hasCycle){
                hasCycle = cycleHelper(nodeToExplore, unexploredNeighborIndex, visited);
            }
        }
        // if there aren't any unexplored neighbors, pop the stack - we've explored all its neighbors
        else{
            toExplore.pop();
        } 

        // this part is to get parts of the graph that are entirely disconnected; essentially starting dfs again from a new source
        if (toExplore.empty()){
            int unvisitedNodeIndex = getFirstUnvisitedNodeIndex(visited);
            if (unvisitedNodeIndex!=-1){
                toExplore.push(nodes[unvisitedNodeIndex]);
            }
        }  
    }
    return traversal;
}

// helper that checks if neighbor has already-visited neighbor (indicating cycle)
bool Graph::cycleHelper(int nodeToExplore, int unexploredNeighborIndex, unordered_set<int> visited) {
    unordered_set<int>::const_iterator neighborOfNeighborIt;
    for (int i=0; i<adj[unexploredNeighborIndex]->size(); i++){
        int neighborOfNeighbor = adj[unexploredNeighborIndex]->at(i);

        if(neighborOfNeighbor != nodeToExplore) {
            neighborOfNeighborIt = visited.find(neighborOfNeighbor);
            if (neighborOfNeighborIt != visited.end()){
                return true;    
            }
        } 
    }
    return false;  
}

// helper that index of unexplored neighbor
int Graph::getUnexploredNeighborIndex(int node, unordered_set<int> visited){
    int unexploredNeighborIndex = -1;

    if (!adj[node]->empty()){
        unordered_set<int>::const_iterator neighborIt;
        for (int i=0; i<adj[node]->size(); i++){
            int neighbor = adj[node]->at(i);
            neighborIt = visited.find(neighbor);
            if (neighborIt == visited.end()){
                unexploredNeighborIndex = i;
                break;
            }
        } 
    }  
    return unexploredNeighborIndex;
}

// helper to get nodes that haven't been seen yet (i.e. separate sources)
int Graph::getFirstUnvisitedNodeIndex(unordered_set<int> visited){
    int unvisitedNodeIndex = -1;

    unordered_set<int>::const_iterator nodeIt;
    for (int i=0; i<nodes.size(); i++){
            nodeIt = visited.find(nodes[i]);
            if (nodeIt == visited.end()){
                unvisitedNodeIndex = i;
                break;
            }
    }    
    return unvisitedNodeIndex;
}

// explores all of a level before moving on to the next
vector<int> Graph::BFS(){
    vector<int> traversal; 
    queue<int> toExplore; // uses queue to explore all nodes that were seen first
    unordered_set<int> visited;

    if(nodes.empty())
        return traversal;
    
    toExplore.push(nodes[0]);
    visited.insert(nodes[0]);

    // bfs ends when all nodes have been explored
    while (traversal.size() != nodes.size()){
        int nodeToExplore = toExplore.front();
        traversal.push_back(nodeToExplore);
        toExplore.pop();

        // get neighbors and add them to queue, marking them as visited
        if (!adj[nodeToExplore]->empty()){
            unordered_set<int>::const_iterator neighborIt;
            for (int i=0; i<adj[nodeToExplore]->size(); i++){
                int neighbor = adj[nodeToExplore]->at(i);
                neighborIt = visited.find(neighbor);
                if (neighborIt == visited.end()){
                    toExplore.push(neighbor);
                    visited.insert(neighbor);
                }
            }
        }

        // this is to help get disinct nodes
        if (toExplore.empty()){
            int unvisitedNodeIndex = getFirstUnvisitedNodeIndex(visited);
            if (unvisitedNodeIndex!=-1){
                toExplore.push(nodes[unvisitedNodeIndex]);
                visited.insert(nodes[unvisitedNodeIndex]);
            }
        } 
    }
    return traversal;
}

// bool Compare(tuple<int,int> pair1, tuple<int, int> pair2)
// {
//     return get<1>(pair1)<get<1>(pair2);
// }

// dijkstra gives a shortest path from source to everywhere
// unordered_map<int, int> Graph::dijkstra(int sourceNode) {
//     vector<int>::iterator it  = find(nodes.begin(), nodes.end(), sourceNode);
//     unordered_map<int, int> distances;
//     unordered_map<int, int> previous;

//     if (it == nodes.end()){
//         return previous;
//     }

//     priority_queue<tuple<int, int>, vector<tuple<int, int>>, function<bool(tuple<int,int> pair1, tuple<int, int> pair2)>> nodesPQ(Compare); // we want this to be sorted by dist from source.
//     bool wasUpdated=true;

//     for (int i=0; i<nodes.size(); i++){
//         if (nodes[i] == sourceNode){
//             tuple<int, int> source = {sourceNode, 0};
//             nodesPQ.push(source); 
//             distances.insert({sourceNode, 0});
//         }
//         else{
//             tuple<int, int> node = {nodes[i], 1000};
//             nodesPQ.push(node);
//             distances.insert({nodes[i], 1000});
//             previous.insert({nodes[i], -1});
//         }
//     }

//     while(wasUpdated){
//         int currNode = get<0>(nodesPQ.top());
//         nodesPQ.pop();
//         vector<int> neighbors = getNeighbors(currNode);
//         wasUpdated = false;

//         for (int i=0; i<neighbors.size(); i++){
//             int neighbor = neighbors[i];
//             int newWeight = getEdgeWeight(currNode, neighbor) + distances[currNode];
//             if (distances[neighbor] > newWeight){
//                 wasUpdated = true;
//                 distances[neighbor] = newWeight;
//                 previous[neighbor] = currNode;
//                 tuple<int, int> nodeData = {nodes[i], newWeight};
//                 nodesPQ.push(nodeData);
//             }
//         }
//     }

//     return previous;

// }

int main() {
    Graph myGraph = Graph();
    myGraph.addNode(0);
    myGraph.addNode(1);
    myGraph.addNode(2);
    myGraph.addNode(3);
    myGraph.addNode(4);
    myGraph.addNode(5);
    myGraph.addNode(6);
    myGraph.addNode(7);
    myGraph.addNode(8);
    myGraph.addNode(9);
    myGraph.addNode(10);
    myGraph.addNode(11);
    myGraph.addNode(12);

    myGraph.addEdge(0,1);
    myGraph.addEdge(1,5);
    myGraph.addEdge(1,6);
    myGraph.addEdge(6,7);
    myGraph.addEdge(6,8);
    myGraph.addEdge(7,8);
    myGraph.addEdge(0,2);
    myGraph.addEdge(2,4);
    myGraph.addEdge(2,3);
    myGraph.addEdge(2,9);
    myGraph.addEdge(3,10);
    myGraph.addEdge(3,9);
    myGraph.addEdge(9,10);
    myGraph.addEdge(11,12);

    bool hasCycle;
    vector<int> DFSTraversal = myGraph.DFS(hasCycle);
    for (int i=0; i<DFSTraversal.size(); i++){
        cout << DFSTraversal[i] << " ";
    }
    cout << endl;

    if (hasCycle){
        cout << "Graph has cycle" << endl;
    }
    vector<int> BFSTraversal = myGraph.BFS();
    for (int i=0; i<BFSTraversal.size(); i++){
        cout << BFSTraversal[i] << " ";
    }
    cout << endl;
    return 0;
}