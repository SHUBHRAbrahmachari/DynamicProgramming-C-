/*
    Given an integer array arr[],
    find the length of the longest subsequence such that the absolute difference between adjacent elements is 1.

    1 ≤ arr.size() ≤ 1000
    1 ≤ arr[i] ≤ 1000

*/

#include <iostream>
#include <vector>
#include <random>

std::vector<int> initialize_sequence(const int size){

    std::vector<int> sequence;

    for (int i=0; i<size; i++)
        sequence.emplace_back((rand()%1000) + 1);
    
    return sequence;

}

void show_sequence(const std::vector<int> &sequence) {
    std::cout << std::endl;
    for (int ele: sequence)
        std::cout << ele << " ";
    std::cout << std::endl << std::endl;
    return;
}

std::vector<std::vector<int>> initialize_memory(const int size) {
    std::vector<std::vector<int>> memory(size, std::vector<int>(size+1, -1));       // -1 can be the previous index as well
    return memory;
}

int find_maximum_good_sequence_length(
    const std::vector<int> &sequence,
    const int size,
    std::vector<std::vector<int>> &memory,
    int index=0,
    int previous_index=-1
)

{
    // sequence is exhausted
    if (index >= size)
        return 0;
    
    // this particular state has been already precomputed
    if (memory.at(index).at(previous_index+1) != -1)
        return memory.at(index).at(previous_index+1);

    // NOW ACTION STARTS
    int option_1 = -1, option_2 = -1;

    // CASE 1: NO ELEMENT WAS SELECTED BEFORE THAT
    if (previous_index == -1) {
        // CASE 1: WE WON'T TAKE THAT ELEMENT INTO ACCOUNT
        option_1 = find_maximum_good_sequence_length(sequence, size, memory, index+1, previous_index);

        // CASE 2: WE WILL TAKE THAT ELEMENT WITH US ALONG
        option_2 = 1 + find_maximum_good_sequence_length(sequence, size, memory, index+1, index);
    }

    // CASE 2: ATLEAST ONE ELEMENT WAS SELECTED BEFORE THIS ONE
    else {
        // CASE 1: THIS ELEMENT DOES NOT FIT HERE
        if (std::abs(sequence.at(index) - sequence.at(previous_index)) != 1) {
            return memory.at(index).at(previous_index+1) = find_maximum_good_sequence_length(sequence, size, memory, index+1, previous_index);
        }

        // CASE 2: THIS ELEMENT FITS IN THE SEQUENE
        else {
            // CASE 1: WE WON'T TAKE THAT ELEMENT INTO ACCOUNT
            option_1 = find_maximum_good_sequence_length(sequence, size, memory, index+1, previous_index);

            // CASE 2: WE WILL TAKE THAT ELEMENT WITH US ALONG
            option_2 = 1 + find_maximum_good_sequence_length(sequence, size, memory, index+1, index);
        }
    }

    return memory.at(index).at(previous_index+1) = std::max(option_1, option_2);
}

int main() {

    int size;

    std::cout << "\nEnter the size between 1 and 1000 : ";
    std::cin >> size;


    std::vector<int> sequence = initialize_sequence(size);
    show_sequence(sequence);

    std::vector<std::vector<int>> memory = initialize_memory(size);

    int result = find_maximum_good_sequence_length(sequence, size, memory);

    std::cout << "\nThe maximum such subsequence length is : " << result << "\n";


    return 0;

}