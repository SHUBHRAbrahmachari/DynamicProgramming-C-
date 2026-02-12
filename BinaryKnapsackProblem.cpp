/*
    We are given `n` items of different weights (integer)
    Each item holds a particular value (integer)
    We are also given a bag of a particular weight capacity (integer)
    We need to fill the bag with items such that => `total weights of selected items <= weight capacity of the bag`
    We need to collect as much as possible value.
    We can either select an item or not select the item, we can't break it to have partial value.
    What is the maximum value we can gather?
*/

#include <iostream>
#include <vector>

void show_items(int* weights, int* values, const int n) {
    std::cout << "\n\n";
    for (int i=0; i<n; i++) {
        std::cout << "\n\t\t\t\t\t\t\tItem number - (" << (i+1) << ") : weight : " << weights[i] << ", value : " << values[i] << ";";
    }
    std::cout << "\n\n";
}

std::pair<int*, int*> initialize_items(const int n) {

    int* weights = new int[n];
    int* values = new int[n];

    for (int i=0; i<n; i++) {
        std::cout << "\nEnter the weight and corresponding value for item number - (" << (i+1) << ") respectively : ";
        std::cin >> weights[i] >> values[i];
    }

    show_items(weights, values, n);

    return {weights, values};

}

int find_maximum_wealth(int* &weights, int* &values, const int n, int remaining_capacity, std::vector<std::vector<int>>* &memory, int index=0) {

    // items finished
    if (index >= n or remaining_capacity == 0) {
        return 0;
    }

    // if we have already checked this condition
    if (memory->at(index).at(remaining_capacity) != -1) {
        return memory->at(index).at(remaining_capacity);
    }

    // if weight of current item is less than or equal to remaining capacity, then we can either select the item, or we can just leave => we have these 2 options
    if (weights[index] <= remaining_capacity) {

        // case 1 : leave the item and go to next item
        int result1 = find_maximum_wealth(weights, values, n, remaining_capacity, memory, index+1);

        // case 2 : collect the item, gather the value and move to next item
        int updated_capacity = remaining_capacity - weights[index];
        int result2 = values[index] + (weights, values, n, updated_capacity, memory, index+1);

        // now get the maximum of it

        return memory->at(index).at(remaining_capacity) = std::max(result1, result2);

    }
    
    // if weight of current item is actually greater than remaining capacity then we have only one option of leaving the item and go to next item
    else {
        int result = find_maximum_wealth(weights, values, n, remaining_capacity, memory, index+1);

        return memory->at(index).at(remaining_capacity) = result;
    }
}

int main() {
    int n;
    std::cout << "\nEnter the number of items you want (should be greater than zero!) : ";
    std::cin >> n;

    std::pair<int*, int*> items = initialize_items(n);

    int capacity;
    std::cout << "\nEnter the capacity of the knapsack : ";
    std::cin >> capacity;

    std::vector<std::vector<int>>* memory = new std::vector<std::vector<int>>(n+1, std::vector<int>(capacity+1, -1));

    int res = find_maximum_wealth(items.first, items.second, n, capacity, memory);

    std::cout << "\n\t\t\t\t\t\tMaximum value that can be collected is : " << res  << "\n\n";

    return 0;
}