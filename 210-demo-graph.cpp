#include <iostream>
#include <vector>
using namespace std;
//I decided that I wanted to create an emergency exit for a building with 12 floors

const int SIZE = 13;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;  // Creates alias 'Pair' for the pair<int,int> data type

class Graph {
public:
    // a vector of vectors of Pairs to represent an adjacency list
    vector<vector<Pair>> adjList;

    // Graph Constructor
    Graph(vector<Edge> const &edges) {
        // resize the vector to hold SIZE elements of type vector<Edge>
        adjList.resize(SIZE);

        // add edges to the directed graph
        for (auto &edge: edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            // insert at the end
            adjList[src].push_back(make_pair(dest, weight));
            // for an undirected graph, add an edge from dest to src also
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    // Print the graph's adjacency list
    void printGraph() {
        cout << "Graph's adjacency list:" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }

    void Depth(int d, vector<bool>&visited){ //DFS goes through each of the path until it reaches the end and then it moves back and visit others unlike BFS 
        visited[d] = true;
        cout << d << " ";

        for (auto &edge: adjList[d]){ //this goes through the vertex's neighbors and then if it's not visited, we recall the depth first search to the next vertix
            int next = edge.first;
            if (!visited[next]){
                Depth(next, visited);
            }
        }
    }
    void DFS(int v){
        vector<bool> visited(SIZE, false);
        Depth(v, visited); //this is used to call the Depth function
    }
    void BFS(int b){
        vector<bool> visited(SIZE, false);
        vector<int>v; //I created this so that we know how many verticies we have to go through
        visited[b] = true; //after going through each of the vertex, it is marked true so that you won't repeat the visit
        v.push_back(b);
        while (!v.empty()) {
            int l = b.front();
            v.erase(v.begin());
            cout << l << " ";
            for (auto &edge : adjList[l]) {
                int next = edge.first;
                if (!visited[next]) {
                    visited[next] = true;
                    v.push_back(next);
                }
            }
        }
    }
};

int main() {
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        //vertex 0
        {0,1,12},{0,2,8},{0,3,21},
        //vertex 1
        {1,7,2}
        //vertex 2
        {2,3,6},{2,6,2},
        //vertex 4
        {4,5,9}, {4,10,9},
        //vertex 6
        {6,9,20},
        //vertex 7
        {7,8,10},
        //vertex 8
        {8,9,90},
        //vertex 9
        {9,11,19},
        //vertex 10
        {10,12,24},
        //vertex 11
        {11,12,32},

    };

    // Creates graph
    Graph graph(edges);

    // Prints adjacency list representation of graph
    graph.printGraph();
    //both of these are going to start from vertex 0
    graph.DFS(0);
    graph.BFS(0);

    return 0;
}
