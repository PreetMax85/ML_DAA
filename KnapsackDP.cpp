#include <iostream>
#include <vector>
#include <algorithm> // Required for max()

using namespace std;

int main() {
    int n, capacity;
    cout << "Enter number of items: ";
    cin >> n;
    cout << "Enter knapsack capacity: ";
    cin >> capacity;
    cout << endl;

    vector<int> values(n);
    vector<int> weights(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter value for Item " << i + 1 << ": ";
        cin >> values[i];
        cout << "Enter weight for Item " << i + 1 << ": ";
        cin >> weights[i];
    }

    // Create the DP table: dp[i][w]
    // n+1 rows, capacity+1 columns
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    // Build the table
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            // Get the current item's info (note: i-1 index)
            int currentWeight = weights[i - 1];
            int currentValue = values[i - 1];

            // If the item is too heavy to fit
            if (currentWeight > w) {
                dp[i][w] = dp[i - 1][w];
            }
            // Else, decide to include it or not
            else {
                dp[i][w] = max(
                    dp[i - 1][w], // Don't include item
                    currentValue + dp[i - 1][w - currentWeight] // Include item
                );
            }
        }
    }

    cout << "\n--- 0/1 Knapsack (Dynamic Programming) ---" << endl;

    // Print the DP table
    cout << "DP Table:" << endl;
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            cout << dp[i][w] << "\t";
        }
        cout << endl;
    }

    // The max value is in the bottom-right corner
    int maxValue = dp[n][capacity];
    cout << "\nTotal Value (0/1): " << maxValue << endl;

    // Backtrack to find selected items
    cout << "Selected Items (1-indexed):" << endl;
    int k = capacity; // Start at max capacity
    for (int i = n; i > 0 && maxValue > 0; i--) {
        // If the value is the same as the row above,
        // it means we did NOT include the current item.
        if (dp[i][k] == dp[i - 1][k]) {
            // Item i was not included
        }
        // Otherwise, we DID include this item.
        else {
            // Item i (which is 1-indexed) was included
            cout << "  Item " << i << " (V:" << values[i-1] << ", W:" << weights[i-1] << ")" << endl;
            // Subtract the item's value and weight
            maxValue -= values[i - 1];
            k -= weights[i - 1];
        }
    }

    return 0;
}