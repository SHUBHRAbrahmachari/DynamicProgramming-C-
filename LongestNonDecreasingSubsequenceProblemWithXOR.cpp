/*
    You are given an array A of length N and an integer M.
    A subsequence of A is considered GOOD if the following conditions hold:

        1. The elements of the subsequence are non-decreasing.
        2. The bitwise XOR of these elements is at least M.
        3. Them minimum length has to be 1

    Find the length of the longest good subsequence. If it is not possible to choose any subsequence,
    then the answer is 0.

                • 1 ≤ N ≤ 1000
                • 1 ≤ M ≤ 500
                • 1 ≤ A[i] ≤ N

    SO BASICALLY DP STATE BECOMES [current_index][previous_index][current_xor] = [1000][1001][2^k] So we don't know that. Where k = floor(log2(N))+1
    SO BETTR USE DP STATE COMPRESSION: 

    current_index CAN TAKE : 0 TO 999
    previous_index CAN TAKE : 0 TO 1000 (EACH SHIFTED TO RIGHT TO ADJUST -1)
    current_xor CAN TAKE : 0 TO 2^10 (1024) (SINCE K = floor(1000)+1 = 10)

    SO KEEP BASE = 1025

*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>

#define MIN std::numeric_limits<int>::min()/2     // to define invalid case

std::vector<int> initialize_sequence(const int &size) {
    std::vector<int> sequence(size);
    std::cout << "\nKeep entering the values : ";
    for (int i=0; i<size; i++)
        std::cin >> sequence.at(i);
    
    return sequence;
}

std::unordered_map<long long, int> initialize_memory() {
    std::unordered_map<long long, int> memory;
    return memory;
}

long long get_compressed_state(
    const int current_index,
    const int previous_index,
    const int current_xor_value
)

{
    const long long BASE = 1025;
    long long res = (long long)current_index;
    res = res*BASE + (long long)previous_index;
    res = res*BASE + (long long)current_xor_value;

    return res;
}


int find_length_of_longest_good_sequence(
    std::vector<int> &sequence,
    const int &size,
    const int &minimum_xor_value,
    std::unordered_map<long long, int> &memory,
    const int current_index=0,
    const int previous_index=-1,
    const int current_xor_value=0,
    const bool is_atleast_one_element_taken=false
)

{
    // BASE CASE WHERE WE COMPLETE TRAVERSING THE SEQUENCE
    // (1) ENSURE COMPUTED XOR IS GREATER THAN OR EQUAL TO MINIMUM XOR VALUE
    // (2) ENSURE THAT ATLEAST ONE ELEMENT IS THERE IN THE SEQUENCE
    if (current_index >= size) {
        if (is_atleast_one_element_taken and current_xor_value >= minimum_xor_value)
            return 0;
        else
            return MIN;
    }

    // COMPUTE COMPRESSED STATE
    long long compressed_state = get_compressed_state(current_index, previous_index+1, current_xor_value);

    // THIS STATE HAS ALREADY BEEN PRE-COMPUTED
    if (memory.find(compressed_state) != memory.end())
        return memory.at(compressed_state);
    
    // NOW THE REAL ACTION BEGINS
    int option1, option2;

    // CASE 1: NO ELEMENT WAS TAKEN PRIOR TO THAT
    if (previous_index == -1) {
        // CASE 1: WE SKIP THIS ELEMENT
        option1 = find_length_of_longest_good_sequence(sequence, size, minimum_xor_value, memory, current_index+1, previous_index, current_xor_value, is_atleast_one_element_taken);

        // CASE 2: WE TAKE THIS ELEMENT ALONG
        option2 = 1 + find_length_of_longest_good_sequence(sequence, size, minimum_xor_value, memory, current_index+1, current_index, sequence.at(current_index)^current_xor_value, true);
    }

    // CASE 2: ATLEAST ONE ELEMENT WAS TAKEN PRIOR TO THAT
    else {
        // CASE 1: THIS ELEMENT DOES NOT FIT HERE
        if (sequence.at(current_index) < sequence.at(previous_index))
            return memory[compressed_state] = find_length_of_longest_good_sequence(sequence, size, minimum_xor_value, memory, current_index+1, previous_index, current_xor_value, is_atleast_one_element_taken);

        // CASE 2: THIS ELEMENT FITS VERY WELL IN THE SUBSEQUENCE
        else {
            // CASE 1: WE SKIP THIS ELEMENT
            option1 = find_length_of_longest_good_sequence(sequence, size, minimum_xor_value, memory, current_index+1, previous_index, current_xor_value, is_atleast_one_element_taken);

            // CASE 2: WE TAKE THIS ELEMENT ALONG
            option2 = 1 + find_length_of_longest_good_sequence(sequence, size, minimum_xor_value, memory, current_index+1, current_index, sequence.at(current_index)^current_xor_value, true);
        }
    }

    return memory[compressed_state] = std::max(option1, option2);

}


int main() {
    int size;
    std::cout << "\nEnter the size of the sequence : ";
    std::cin >> size;

    std::vector<int> sequence = initialize_sequence(size);
    std::unordered_map<long long, int> memory = initialize_memory();

    int minimum_xor_value;
    std::cout << "\nEnter the mainimum XOR value : ";
    std::cin >> minimum_xor_value;

    const int result = find_length_of_longest_good_sequence(sequence, size, minimum_xor_value, memory);

    std::cout << "\nThe maximum possible length of subsequence with XOR value being minimum " << minimum_xor_value << " is : " << (result < 0 ? 0 : result) << std::endl << std::endl; 

    return 0;
}

