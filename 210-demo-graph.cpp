//Kyawt Thinzar Min
//IDE used: VS code

#include <iostream>
#include <vector>
#include <climits>
#include <queue>
using namespace std;
//I decided that I wanted to create an emergency exit for a building with 12 floors
//Dijkstra's Algorithm: Useful for finding the shortest path from a single source to all other nodes in a graph with non-negative weights. It uses a priority queue to greedily select the next node with the smallest distance, updating its neighbors' distances.
const int SIZE = 13;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;  // Creates alias 'Pair' for the pair<int,int> data type

class Graph {
public:
    // a vector of vectors of Pairs to represent an adjacency list
    vector<vector<Pair>> adjList;
    vector<string> floorNames = {
        "Floor 0", "Floor 1", "Floor 2", "Floor 3", "Floor 4", "Floor 5", "Floor 6", "Floor 7", "Floor 8", "Floor 9", "Floor 10", "Floor 11", "Floor 12 "
    };

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
            cout << floorNames[i] << " connects to:\n";

            for (auto &p : adjList[i]) {
                cout << "  ->" << floorNames[p.first] << " , Difficulty: " << p.second << endl;
            }//the weights became the difficulty, and the vertex are the floors
            cout << endl;
        }
    }

    void Depth(int d, vector<bool>&visited){ //DFS goes through each of the path until it reaches the end and then it moves back and visit others unlike BFS 
        visited[d] = true;
        cout << "\nInspecting " << floorNames[d] << endl;

        for (auto &edge : adjList[d]) {
            int next = edge.first;
            int danger = edge.second;

            if (!visited[next]) {
                cout << "  Intersecting with:  " << floorNames[next]
                     << " , Difficulty: " << danger << endl;

                Depth(next, visited);
            }
        }
    }
    void DFS(int v){
        vector<bool> visited(SIZE, false);
        Depth(v, visited);
    }
    void BFS(int b){
        int f = 0; 
        vector<bool> visited(SIZE, false);
        vector<int>v; //I created this so that we know how many verticies we have to go through
        visited[b] = true; //after going through each of the vertex, it is marked true so that you won't repeat the visit
        v.push_back(b);
        while (f < v.size()) {
            int curr = v[f];
            f++;
            cout << "Closest floor #" << floorNames[curr] << "\n";

            for (auto &edge : adjList[curr]) {
                int next = edge.first;
                int i = edge.second;

                if (!visited[next]) {
                    visited[next] = true;
                    v.push_back(next);

                    cout << "  Next reachable floor: "
                         << floorNames[next]
                         << " , Difficulty: " << i << "\n";
                }
            }

            cout << endl;
        }
    }

    vector<int> dijkstra(int src) {
        vector<int> dist(SIZE, INT_MAX);
        dist[src] = 0; //the distance is initially 0

        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
        pq.push({0, src});

        while(!pq.empty()) { //this is a loop to take out the vertex with the least distance
            int u = pq.top().second;
            int d = pq.top().first;
            pq.pop();

            if(d > dist[u]) continue;
            for(auto &neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;
                if(dist[u] + weight < dist[v]) { //this is to compare the weight
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }
 
        return dist;
    }
    void shortest(int src) { //this is the printing function
        vector<int> dist = dijkstra(src);
        cout << "Shortest path from " << floorNames[src] << ":\n";
        for(int i = 0; i < dist.size(); i++)
            cout << src << " -> " << i << " : " << dist[i] << endl;
    }
    void MST(){
        vector<int> key(SIZE, INT_MAX); 
        vector<bool> included(SIZE, false); //this is to keep track of the vertix that is in the MST
        vector<int> parent(SIZE, -1); //This vector is created to store the minimum spanning tree under parent
        key[0] = 0;

        for (int i=0; i<SIZE-1; i++){
            int u = -1;
            for (int j= 0; j<SIZE; j++){
                if(!included[j] && (u==-1 || key[j] <key[u])){ //if the vertex is not in the span, and it's key is smaller, the u will be changed to j
                    u=j;
                }
            }
            included[u] = true;

            for (auto &edge : adjList[u]) {
                int v = edge.first;
                int weight = edge.second;

                if (!included[v] && weight < key[v]) { //if thee vertex is not yet in the span and it's weight is also less, parent and v is updated
                    parent[v] = u;
                    key[v] = weight;
                }
            }
        }
        for (int i = 0; i <SIZE ; i++){
            if (parent[i] != -1){
                cout << "Intersection from " << parent [i] << " to " << i<< " fits " << key[i] << " people." << endl;
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
        {1,7,2},
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

    int choice = 0;
    while (choice !=  5){
        cout << "[0] Show the full map of the building" << endl;
        cout << "[1] Show the neighboring floors (BFS)" << endl;
        cout << "[2] Show any paths from the intersections (DFS)" << endl;
        cout << "[3] Show the shortest paths" << endl;
        cout << "[4] Show minimum spanning tree" << endl;
        cout << "[5] Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 0){
            graph.printGraph();
        }
        else if (choice == 1){
            cout << "Tracing emergency exits starting from floor 0 or the Ground Floor [BFS]" << endl;
            cout << "To know nearest exit." << endl;
            graph.BFS(0);
            cout << endl;
        }
        else if (choice == 2){
            cout << "Tracing emergency exits starting from floor 0 or the Ground Floor [DFS]" << endl;
            cout << "To be aware of the paths leading from a certain floor" << endl;
            graph.DFS(0);
            cout << endl;
        }
        else if (choice == 3){
            cout << "Printing the shortest routs:" << endl;
            graph.shortest(0);
        }
        else if (choice == 4){
            cout << "The minimum spanning tree:" << endl;
            graph.MST();
        }
        else{
            cout << "Ended the find :)" << endl;
            return 0;
        }
    }
    
    return 0;
}
