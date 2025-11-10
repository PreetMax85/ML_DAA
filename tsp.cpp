#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

// Structure to represent a node in the state-space tree
struct Node {
    vector<int> path;  // current path
    int reducedMatrix[10][10];
    int cost;
    int vertex;
    int level;
};

// Function to copy a matrix
void copyMatrix(int src[10][10], int dest[10][10], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dest[i][j] = src[i][j];
}

// Function to reduce matrix and return the reduction cost
int reduceMatrix(int mat[10][10], int n) {
    int cost = 0;

    // Row reduction
    for (int i = 0; i < n; i++) {
        int rowMin = INT_MAX;
        for (int j = 0; j < n; j++)
            if (mat[i][j] < rowMin)
                rowMin = mat[i][j];
        if (rowMin != INT_MAX && rowMin != 0) {
            cost += rowMin;
            for (int j = 0; j < n; j++)
                if (mat[i][j] != INT_MAX)
                    mat[i][j] -= rowMin;
        }
    }

    // Column reduction
    for (int j = 0; j < n; j++) {
        int colMin = INT_MAX;
        for (int i = 0; i < n; i++)
            if (mat[i][j] < colMin)
                colMin = mat[i][j];
        if (colMin != INT_MAX && colMin != 0) {
            cost += colMin;
            for (int i = 0; i < n; i++)
                if (mat[i][j] != INT_MAX)
                    mat[i][j] -= colMin;
        }
    }

    return cost;
}

// Comparator for priority queue (min-heap)
struct compare {
    bool operator()(const Node* a, const Node* b) const {
        return a->cost > b->cost;
    }
};

// Function to solve TSP using Branch and Bound
void solveTSP(int costMatrix[10][10], int n) {
    priority_queue<Node*, vector<Node*>, compare> pq;

    // Initialize root node
    Node* root = new Node;
    root->path.push_back(0);
    root->level = 0;
    root->vertex = 0;
    copyMatrix(costMatrix, root->reducedMatrix, n);

    // Reduce root matrix and calculate initial cost
    root->cost = reduceMatrix(root->reducedMatrix, n);

    pq.push(root);
    int finalCost = INT_MAX;
    vector<int> finalPath;

    // Process nodes until priority queue is empty
    while (!pq.empty()) {
        Node* minNode = pq.top();
        pq.pop();

        int i = minNode->vertex;

        // If all cities are visited
        if (minNode->level == n - 1) {
            int lastToFirst = costMatrix[i][0];
            if (lastToFirst != INT_MAX &&
                minNode->cost + lastToFirst < finalCost) {
                finalCost = minNode->cost + lastToFirst;
                finalPath = minNode->path;
                finalPath.push_back(0);
            }
            continue;
        }

        // Expand the node
        for (int j = 0; j < n; j++) {
            if (minNode->reducedMatrix[i][j] != INT_MAX) {
                Node* child = new Node;
                copyMatrix(minNode->reducedMatrix, child->reducedMatrix, n);

                // Set outgoing path cost to infinity
                for (int k = 0; k < n; k++) {
                    child->reducedMatrix[i][k] = INT_MAX;
                    child->reducedMatrix[k][j] = INT_MAX;
                }
                child->reducedMatrix[j][0] = INT_MAX;

                child->path = minNode->path;
                child->path.push_back(j);
                child->level = minNode->level + 1;
                child->vertex = j;

                // Calculate cost for child node
                int childCost = minNode->cost + minNode->reducedMatrix[i][j] +
                                reduceMatrix(child->reducedMatrix, n);
                child->cost = childCost;

                pq.push(child);
            }
        }
    }

    // Print final result
    cout << "\nOptimal Path: ";
    for (int i = 0; i < finalPath.size(); i++)
        cout << finalPath[i] << (i == finalPath.size() - 1 ? "" : " -> ");

    cout << "\nMinimum Cost: " << finalCost << endl;
}

// ---------------- MAIN FUNCTION ----------------
int main() {
    int n;
    int costMatrix[10][10];

    cout << "Enter number of cities: ";
    cin >> n;

    cout << "Enter cost matrix (use 999 for infinity):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> costMatrix[i][j];
            if (costMatrix[i][j] == 999)
                costMatrix[i][j] = INT_MAX;
        }
    }

    solveTSP(costMatrix, n);

    cout << "\nTime Complexity: O(n!) in worst case (but reduced using Branch & Bound)\n";

    return 0;
}
