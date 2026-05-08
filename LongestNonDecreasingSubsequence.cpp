#include <iostream>
#include <vector>
#include <random>

void show_numbers(const std::vector<int> numbers) {
    std::cout << std::endl;
    for (int ele: numbers)
        std::cout << ele << " ";
    std::cout << std::endl << std::endl;
    return;
}

std::vector<int> get_numbers(const int size, const int upper_limit) {

    std::vector<int> numbers;

    for (int i=0; i<size; i++)
        numbers.push_back(rand()%upper_limit);
    
    return numbers;

}

std::vector<std::vector<int>> get_memory(const int size) {
    std::vector<std::vector<int>> memory(size+1, std::vector<int>(size+1, -1));     // size+1 because previous_index can be -1 as well
    return memory;
}



int find_longest_non_decreasing_subsequence_length(
    const std::vector<int> &numbers,
    const int size,
    std::vector<std::vector<int>> &memory,
    int index=0,
    int previous_index=-1
) {

    // list is exhausted
    if (index >= size)
        return 0;
    
    // this state has already been precomputed
    if (memory.at(index).at(previous_index+1) != -1)
        return memory.at(index).at(previous_index+1);

    // NOW ACTUAL WORK STARTS
    int option_1 = -1, option_2 = -1;

    // (1) NO ELEMENT WAS SELECTED PREVIOUSLY
    if (previous_index == -1) {
        // (1) WE CAN EITHER TAKE THIS ELEMENT INTO ACCOUNT
        option_1 = 1 + find_longest_non_decreasing_subsequence_length(numbers, size, memory, index+1, index);

        // (2) WE CAN SKIP THIS NUMBER AND MOVE TO NEXT
        option_2 = find_longest_non_decreasing_subsequence_length(numbers, size, memory, index+1, previous_index);

    }

    // (2) ALTEAST ONE ELEMENT WAS SELECTED EARLIER
    else {
        // (1) THIS ELEMENT DOES NOT FIT INTO THE CURRENT SUBSEQUENCE
        if (numbers.at(index) < numbers.at(previous_index)) {
            return memory.at(index).at(previous_index+1) = find_longest_non_decreasing_subsequence_length(numbers, size, memory, index+1, previous_index);
        }

        // (2) THIS ELEMENT FITS INTO THE CURRENT SUBSEQUENCE
        else {
            // (1) WE CAN EITHER TAKE THIS ELEMENT INTO ACCOUNT
            option_1 = 1 + find_longest_non_decreasing_subsequence_length(numbers, size, memory, index+1, index);

            // (2) WE CAN SKIP THIS NUMBER AND MOVE TO NEXT
            option_2 = find_longest_non_decreasing_subsequence_length(numbers, size, memory, index+1, previous_index);
        }
    }

    return memory.at(index).at(previous_index+1) = std::max(option_1, option_2);

}





int main() {
    int size, upper_limit;

    std::cout << "\nEnter the size of the list : ";
    std::cin >> size;

    std::cout << "\nEnter the upper limit : ";
    std::cin >> upper_limit;

    std::vector<int> numbers = get_numbers(size, upper_limit);
    std::vector<std::vector<int>> memory = get_memory(size);

    show_numbers(numbers);

    int result = find_longest_non_decreasing_subsequence_length(numbers, size, memory);

    std::cout << "\nThe length of longest non-decreasing subsequence is : " << result << std::endl << std::endl;


    return 0;

}