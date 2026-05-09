/*
    Given a list of n integers.
    Our task is to find out the minimum sum of those non-decreasing subsequences with length k.

    1 ≤ N, K ≤ 1000
    1 ≤ arr[i] ≤ 100000
*/

#include <iostream>
#include <vector>
#include <limits>

#define MAX std::numeric_limits<int>::max() / 3     // imagining infinity with `MAX`

std::vector<int> initialize_sequence(const int &size) {
    std::vector<int> sequence;
    std::cout << "\nKeep entering the values : \n\n";

    for (int i=0; i<size; i++) {
        int ele;
        std::cin >> ele;
        sequence.emplace_back(ele);
    }
    
    return sequence;
}

void show_sequence(const std::vector<int> &sequence) {
    std::cout << std::endl;
    for (int ele: sequence)
        std::cout << ele << " ";
    
    std::cout << std::endl << std::endl;
    return;
}


std::vector<std::vector<std::vector<int>>> initilize_memory(const int size, const int count_of_numbers) {
    std::vector<std::vector<std::vector<int>>> memory(size, std::vector<std::vector<int>>(size+1, std::vector<int>(count_of_numbers+1, -1)));
    return memory;
}


int find_minimum_sequence_sum(
    const std::vector<int> &sequence,
    const int &size,
    const int &remaining_count_of_numbers,
    std::vector<std::vector<std::vector<int>>> &memory,
    const int index=0,
    const int previous_index=-1
) 

{

    // exactly desired number of elements have been added successfully
    if (remaining_count_of_numbers == 0)
        return 0;

    // failed search
    if (index >= size)
        return MAX;
    
    // this state has already been precomputed
    if (memory.at(index).at(previous_index+1).at(remaining_count_of_numbers) != -1)
        return memory.at(index).at(previous_index+1).at(remaining_count_of_numbers);

    // NOW GAME BEGINS
    int option_1=0, option_2=0;

    // CASE 1: NO PREVIOUS ELEMENT WAS THERE
    if (previous_index == -1) {
        // CASE 1: TAKE THAT ELEMENT
        option_1 = sequence.at(index) + find_minimum_sequence_sum(sequence, size, remaining_count_of_numbers-1, memory, index+1, index);

        // CASE 2: SKIP THAT ELEMENT
        option_2 = find_minimum_sequence_sum(sequence, size, remaining_count_of_numbers, memory, index+1, previous_index);
    }
    
    // CASE 2: ATLEAST ONE ELEMENT WAS HERE BEFORE IT
    else {
        // CASE 1: IT DOES NOT FOLLOW SUBSEQUENCE
        if (sequence.at(index) < sequence.at(previous_index)){
            return memory.at(index).at(previous_index+1).at(remaining_count_of_numbers) = find_minimum_sequence_sum(sequence, size, remaining_count_of_numbers, memory, index+1, previous_index);
        }

        // CASE 2: IT DOES FOLLOW THE SUBSEQUENCE RULE
        else {
            // CASE 1: TAKE THAT ELEMENT
            option_1 = sequence.at(index) + find_minimum_sequence_sum(sequence, size, remaining_count_of_numbers-1, memory, index+1, index);

            // CASE 2: SKIP THAT ELEMENT
            option_2 = find_minimum_sequence_sum(sequence, size, remaining_count_of_numbers, memory, index+1, previous_index);
        }
    }

    return memory.at(index).at(previous_index+1).at(remaining_count_of_numbers) = std::min(option_1, option_2);
    
}

int main() {
    int size;
    std::cout << "\nEnter the size of the sequence, between 1 to 1000 : ";
    std::cin >> size;

    int count_of_numbers;
    std::cout << "\nEnter the number of elements in the subsequence : ";
    std::cin >> count_of_numbers;

    std::vector<int> sequence = initialize_sequence(size);

    show_sequence(sequence);

    std::vector<std::vector<std::vector<int>>> memory = initilize_memory(size, count_of_numbers);

    int result = find_minimum_sequence_sum(sequence, size, count_of_numbers, memory);

    if (result >= MAX)
        std::cout << "\nNo such subsequence exists!\n";
    else
        std::cout << "\nThe minimum such summation is : " << result << std::endl;

    return 0;
}
