/*
    Given an array of length N
    The elements are strictly positive and unique.
    The elements are arranged in strictly increasing manner.

    Your task is to find out maximum subsequece length that forms a ARITHMETIC PROGESSION

    1 <= N <= 10000
    1 <= A[i] <= 10000

*/

#include <iostream>
#include <vector>
#include <unordered_map>

std::vector<int> initialize_sequence(const int &size) {
    std::vector<int> sequence(size);

    std::cout << "\nKeep entering the elements : ";
    for (int i=0; i<size; i++)
        std::cin >> sequence.at(i);
    
    return sequence;
}

void show_sequence(const std::vector<int> &sequence) {
    std::cout << std::endl;
    for (const int &ele : sequence)
        std::cout << ele << " ";
    std::cout << std::endl;
    return;
}

unsigned long long get_compressed_state(
    const int &current_index,
    const int &previous_index,
    const int &common_difference
)

{
    const unsigned long long BASE = 10001;
    unsigned long long state = (unsigned long long)current_index;
    state = state*BASE + (unsigned long long)previous_index;
    state = state*BASE + (unsigned long long)common_difference;

    return state;
}

std::unordered_map<unsigned long long, int> initialize_memory() {
    std::unordered_map<unsigned long long, int> memory;
    return memory;
}

int find_longest_arithmetic_progression_length(
    const std::vector<int> &sequence,
    const int &size,
    std::unordered_map<unsigned long long, int> memory,
    const int current_index=0,
    const int previous_index=-1,
    const int common_difference=0
)

{
    // NO MORE ELEMENTS TO LOOK FOR
    if (current_index >= size)
        return 0;

    // CALCULATE THE COMPRESSED STATE
    unsigned long long compressed_state = get_compressed_state(current_index, previous_index+1, common_difference);

    // CHECK IF THIS STATE HAS ALREADY BEEN PRECOMPUTED
    if (memory.find(compressed_state) != memory.end())
        return memory.at(compressed_state);
    
    // NOW THE REAL GAME BEGINS
    int option1=INT_MIN, option2=INT_MIN;

    // CASE 1: NO ELEMENTS WERE TAKEN PRIOR TO THAT ELEMENT
    if (previous_index == -1) {
        // CASE 1: WE CAN ASSUME THAT WE ARE STARTING OUR AP WITH THIS ELEMENT
        option1 = 1 + find_longest_arithmetic_progression_length(sequence, size, memory, current_index+1, current_index, common_difference);

        // CASE 2: WE CAN SKIP THIS ELEMENT
        option2 = find_longest_arithmetic_progression_length(sequence, size, memory, current_index+1, previous_index, common_difference);
    }

    // CASE 2: ONLY 1 ELEMENT WAS TAKEN PRIOR TO THAT ELEMENT
    else if (previous_index != -1 and common_difference == 0) {
        // CASE 1: WE CAN FINALLY START OUR ARITHMATIC PROGRESSION
        option1 = 1 + find_longest_arithmetic_progression_length(sequence, size, memory, current_index+1, current_index, sequence.at(current_index)-sequence.at(previous_index));

        // CASE 2: WE CAN AGAIN SKIP TO GET A DIFFERENT PROGRSSION WITH A DIFFERENT COMMON DIFFERENCE
        option2 = find_longest_arithmetic_progression_length(sequence, size, memory, current_index+1, previous_index, common_difference);
    }

    // CASE 3: NOW ATLEAST TWO ELEMENTS AR THERE. SO EITHER THIS ELEMENT FITS IN THE PROGRESSION OR IT DOES NOT
    else {
        // CASE 1: THIS ELEMENT FITS IN THE CURRENT PROGRESSION
        if (sequence.at(current_index) - sequence.at(previous_index) == common_difference)
            return memory[compressed_state] = 1 + find_longest_arithmetic_progression_length(sequence, size, memory, current_index+1, current_index, common_difference);
        
        // CASE 2: THIS ELEMENT DOES NOT FIT THE PRGRESSION WITH CURRENT COMMON DIFFERENCE
        else
            return memory[compressed_state] = find_longest_arithmetic_progression_length(sequence, size, memory, current_index+1, previous_index, common_difference);
    }

    return memory[compressed_state] = std::max(option1, option2);
    
}

int main() {
    int size;
    std::cout << "\nEnter the lngth of the sequence : ";
    std::cin >> size;

    const std::vector<int> sequence = initialize_sequence(size);
    std::unordered_map<unsigned long long, int> memory = initialize_memory();

    const int result = find_longest_arithmetic_progression_length(sequence, size, memory);

    std::cout << "\nThe longest arithmetic progression is of length : " << result << std::endl << std::endl;

    return 0;
}