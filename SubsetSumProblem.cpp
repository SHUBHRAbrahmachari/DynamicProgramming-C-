/*
    Given an array arr[] of non-negative integers and a value sum.
    The task is to check if there is a subset of the given array whose sum is equal to the given sum. 

    Examples: 

        Input: arr[] = [3, 34, 4, 12, 5, 2], sum = 9
        Output: True
        Explanation: There is a subset (4, 5) with sum 9.

        Input: arr[] = [3, 34, 4, 12, 5, 2], sum = 30
        Output: False
        Explanation: There is no subset that add up to 30.
*/

#include <iostream>
#include <vector>

std::vector<int>* initialize_set() {
    int n;
    std::cout << "\nEnter the size of the set : ";
    std::cin >> n;

    std::vector<int>* numbers = new std::vector<int>(n);

    std::cout << "\nKeep entering the numbers (unique numbers only): ";

    for (int i=0; i<n; i++)
        std::cin >> numbers->at(i);
    
    return numbers;

}

bool is_target_sum_present(std::vector<int>* &numbers, const int size, const int target_sum, std::vector<std::vector<int>>* &memory, const int current_index = 0) {

    // not possible anymore
    if (target_sum < 0)
        return false;

    // you have successfully found the subsequence
    if (target_sum == 0)
        return true;
    
    // you cannot find target_sum further as well
    if (current_index >= size and target_sum > 0)
        return false;

    // you already pre-computed this result
    if (memory->at(current_index).at(target_sum) != -1) {
        return memory->at(current_index).at(target_sum);
    }
    
    // case 1 : considering current element
    const int new_target_sum = target_sum - numbers->at(current_index);
    bool with_considering_current_index = is_target_sum_present(numbers, size, new_target_sum, memory, current_index+1);

    // case 2 : without considering current element
    if (not with_considering_current_index) {
        bool without_considering_current_index = is_target_sum_present(numbers, size, target_sum, memory, current_index+1);
        return memory->at(current_index).at(target_sum) = with_considering_current_index or without_considering_current_index;
    }

    return memory->at(current_index).at(target_sum) = with_considering_current_index;
    
}

int main() {

    // initialize unique numbers
    std::vector<int>* numbers = initialize_set();
    const int size = numbers->size();

    // inputting the target sum
    int target_sum;
    std::cout << "\nEnter the target sum : ";
    std::cin >> target_sum;

    // initializing memory
    std::vector<std::vector<int>>* memory = new std::vector<std::vector<int>>(size+1, std::vector<int>(target_sum+1, -1));

    bool result = is_target_sum_present(numbers, size, target_sum, memory);
    std::cout << result;

    if(result)
        std::cout << "\nSubset is present!\n\n";
    else
        std::cout << "\nSubset is not present!\n\n";

    delete numbers;
    delete memory;
    return 0;

}