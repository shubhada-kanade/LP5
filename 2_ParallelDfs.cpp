#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

class Tree {
private:
    int numNodes;
    vector<vector<int> > children;

public:
    Tree(int nodes) : numNodes(nodes), children(nodes) {}

    void addChild(int parent, int child) {
        children[parent].push_back(child);
    }

    void viewTree() {
        cout << "Tree:\n";

        for (int i = 0; i < numNodes; i++) {
            cout << "Node " << i << " -> ";

            for (size_t j = 0; j < children[i].size(); j++) {
                cout << children[i][j] << " ";
            }

            cout << endl;
        }
    }

    void dfs(int startNode) {
        vector<bool> visited(numNodes, false);
        stack<int> s;

        visited[startNode] = true;
        s.push(startNode);

        while (!s.empty()) {
            int currentNode = s.top();
            s.pop();

            cout << currentNode << " ";

            #pragma omp parallel for
            for (int i = 0; i < (int)children[currentNode].size(); i++) {

                int child = children[currentNode][i];

                #pragma omp critical
                {
                    if (!visited[child]) {
                        visited[child] = true;
                        s.push(child);
                    }
                }
            }
        }
    }
};

int main() {

    int numNodes;

    cout << "Enter the number of nodes in the tree: ";
    cin >> numNodes;

    Tree tree(numNodes);

    int numEdges;

    cout << "Enter the number of edges in the tree: ";
    cin >> numEdges;

    cout << "Enter the edges (parent child):\n";

    for (int i = 0; i < numEdges; i++) {

        int parent, child;

        cin >> parent >> child;

        tree.addChild(parent, child);
    }

    tree.viewTree();

    int startNode;

    cout << "Enter the starting node for DFS: ";
    cin >> startNode;

    cout << "Depth First Search (DFS): ";

    tree.dfs(startNode);

    cout << endl;

    return 0;
}

// Input/Output:
// Enter the number of nodes in the tree: 6
// Enter the number of edges in the tree: 5
// Enter the edges (parent child):
// 0 1
// 0 2
// 1 3
// 1 4
// 2 5
// Tree:
// Node 0 -> 1 2
// Node 1 -> 3 4
// Node 2 -> 5
// Node 3 ->
// Node 4 ->
// Node 5 ->
// Enter the starting node for DFS: 0
// Depth First Search (DFS): 0 2 5 1 4 3
