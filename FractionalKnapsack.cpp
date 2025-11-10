#include <iostream>
#include <vector>
#include <algorithm> // Required for sort()

using namespace std;

// Simple struct to hold item data
struct Item {
    int value;
    int weight;
    double ratio; // To store value-per-weight
};

// Comparison function to sort items by ratio in descending order
bool compareItems(Item a, Item b) {
    return a.ratio > b.ratio;
}

int main() {
    int n, capacity;
    cout << "Enter number of items: ";
    cin >> n;
    cout << "Enter knapsack capacity: ";
    cin >> capacity;
    cout << endl;

    vector<Item> items(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter value and weight for Item " << i + 1 << ": ";
        cin >> items[i].value >> items[i].weight;
        items[i].ratio = (double)items[i].value / items[i].weight;
    }

    // Sort items based on value-per-weight ratio (descending)
    sort(items.begin(), items.end(), compareItems);

    double totalValue = 0.0;
    int currentWeight = 0;

    cout << "\n--- Fractional Knapsack (Greedy) ---" << endl;

    for (int i = 0; i < n; i++) {
        // If the item fits completely, take all of it
        if (currentWeight + items[i].weight <= capacity) {
            currentWeight += items[i].weight;
            totalValue += items[i].value;
            cout << "Took 100% of Item (V:" << items[i].value << ", W:" << items[i].weight << ")" << endl;
        }
        // If the item doesn't fit completely, take a fraction
        else {
            int remainingCapacity = capacity - currentWeight;
            double fraction = (double)remainingCapacity / items[i].weight;
            totalValue += items[i].value * fraction;
            cout << "Took " << (fraction * 100) << "% of Item (V:" << items[i].value << ", W:" << items[i].weight << ")" << endl;
            break; // Knapsack is now full
        }
    }

    cout << "\nTotal Value (Fractional): " << totalValue << endl;

    return 0;
}