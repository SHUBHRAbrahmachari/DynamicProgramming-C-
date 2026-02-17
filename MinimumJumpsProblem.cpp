/*
    You are given an array arr[] of non-negative numbers. Each number tells you the maximum number of steps you can jump forward from that position.

    For example:

    If arr[i] = 3, you can jump to index i + 1, i + 2, or i + 3 from position i.
    If arr[i] = 0, you cannot jump forward from that position.
    Your task is to find the minimum number of jumps needed to move from the first position in the array to the last position.

    Note:  Return -1 if you can't reach the end of the array.

    Examples : 

        Input: arr = [1, 4, 3, 2, 6, 7]
        Output: 2 
        Explanation: First we jump from the 1st to 2nd element and then jump to the last element.

        Input: arr = [0, 10, 20]
        Output: -1
        Explanation: We cannot go anywhere from the 1st element.
*/

#include <iostream>
#include <vector>
#include <limits>

#define MAX std::numeric_limits<int>::max()/2      // imagining infinity using MAX

std::vector<int>* initialize_vector() {
    int n;
    std::cout << "\nEnter the length of the array : ";
    std::cin >> n;

    std::vector<int>* array = new std::vector<int>(n);

    std::cout << "\nKeep entering the array values (non-negative numbers only): ";

    for (int i=0; i<n; i++) {
        std::cin >> array->at(i);
    }

    return array;
}

int find_minimum_jumps(std::vector<int>* &array, const int size, std::vector<int>* &memory, const int current_index=0) {

    // reached the final destination index
    if (current_index >= size-1)
        return 0;
    
    // if this state is already pre-computed so simply return the result
    if (memory->at(current_index) != -1)
        return memory->at(current_index);
    
    const int maximum_jump_length = array->at(current_index);     // that many jumps we need to explore

    int current_best_result = MAX;

    for (int jump_length=1; jump_length <= maximum_jump_length; jump_length++) {
        
        int next_index = current_index + jump_length;
        int current_result = 1 + find_minimum_jumps(array, size, memory, next_index);

        if (current_result < current_best_result)
            current_best_result = current_result;
    }

    return memory->at(current_index) = current_best_result;
}

int main() {

    // getting the jump values
    std::vector<int>* array = initialize_vector();
    
    // collecting the size of the array
    const int size = array->size();

    // initializing DP memory
    std::vector<int>* memory = new std::vector<int>(size+1, -1);

    const int res = find_minimum_jumps(array, size, memory);

    if (res >= MAX)
        std::cout << "\n\t\t\t\tLast index cannot be reached!\n\n";
    else
        std::cout << "\n\t\t\t\tMinimum " << res << " jumps are required!\n\n";
    
    delete array;
    delete memory;
    return 0;

}


