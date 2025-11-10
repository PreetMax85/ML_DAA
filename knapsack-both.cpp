#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to store item details
struct Item {
    int value, weight;
};

// Function for Fractional Knapsack (Greedy)
double fractionalKnapsack(vector<Item> items, int capacity) {
    // Sort items by value/weight ratio
    sort(items.begin(), items.end(), [](Item a, Item b) {
        return (double)a.value / a.weight > (double)b.value / b.weight;
    });

    double totalValue = 0.0;
    int currentWeight = 0;

    for (auto &item : items) {
        if (currentWeight + item.weight <= capacity) {
            currentWeight += item.weight;
            totalValue += item.value;
        } else {
            int remain = capacity - currentWeight;
            totalValue += item.value * ((double)remain / item.weight);
            break;
        }
    }
    return totalValue;
}

// Function for 0/1 Knapsack (Dynamic Programming)
int knapsackDP(vector<Item> items, int capacity) {
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (items[i - 1].weight <= w)
                dp[i][w] = max(items[i - 1].value + dp[i - 1][w - items[i - 1].weight],
                               dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    // Display DP table
    cout << "\nDP Table:\n";
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            cout << dp[i][w] << "\t";
        }
        cout << endl;
    }

    return dp[n][capacity];
}

// Main function
int main() {
    int n, capacity;
    cout << "Enter number of items: ";
    cin >> n;
    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    vector<Item> items(n);
    cout << "Enter value and weight of each item:\n";
    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << " (value weight): ";
        cin >> items[i].value >> items[i].weight;
    }

    double greedyResult = fractionalKnapsack(items, capacity);
    int dpResult = knapsackDP(items, capacity);

    cout << "\nFractional Knapsack (Greedy) Result: " << greedyResult;
    cout << "\n0/1 Knapsack (DP) Result: " << dpResult << endl;

    cout << "\nObservation: Greedy method may give higher value (approximate), "
         << "but DP gives the exact optimal result for 0/1 knapsack.\n";

    return 0;
}