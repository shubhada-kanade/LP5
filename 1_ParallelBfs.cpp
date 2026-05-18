#include <iostream>
#include <vector>
#include <queue>
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

    void bfs(int startNode) {

        vector<bool> visited(numNodes, false);

        queue<int> q;

        visited[startNode] = true;
        q.push(startNode);

        while (!q.empty()) {

            int currentNode = q.front();
            q.pop();

            cout << currentNode << " ";

            #pragma omp parallel for
            for (int i = 0; i < (int)children[currentNode].size(); i++) {

                int child = children[currentNode][i];

                #pragma omp critical
                {
                    if (!visited[child]) {

                        visited[child] = true;
                        q.push(child);
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

    cout << "Enter the starting node for BFS: ";
    cin >> startNode;

    cout << "Breadth First Search (BFS): ";

    tree.bfs(startNode);

    cout << endl;

    return 0;
}
