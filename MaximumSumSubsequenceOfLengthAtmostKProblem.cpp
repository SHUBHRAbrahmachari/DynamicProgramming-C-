/*
    Given a list of N integers.
    Our task is to find out the maximum sum of those non-decreasing subsequences with length atmost K.

    1 ≤ N ≤ 1000
    1 <= K <= N
    -1000 ≤ arr[i] ≤ 1000
*/

#include <iostream>
#include <vector>


std::vector<int> initialize_sequence(const int &size) {
    
    std::vector<int> sequence(size);

    std::cout << "\nKeep entering the values : ";
    for (int i=0; i<size; i++)
        std::cin >> sequence.at(i);
    
    return sequence;
}

void show_sequence(const std::vector<int> &sequence) {

    std::cout << std::endl;

    for (int ele: sequence)
        std::cout << ele << " ";

    std::cout << std::endl;
}

std::vector<std::vector<std::vector<int>>> initialize_memory(
    const int &size,
    const int &k
) 

{
    std::vector<std::vector<std::vector<int>>> memory(size, std::vector<std::vector<int>>(size+1, std::vector<int>(k+1, -1)));
    return memory;
}

int find_maximum_non_decreasing_subsequence_sum_of_length_atmost(
    const std::vector<int> &sequence,
    const int &size,
    const int k,
    std::vector<std::vector<std::vector<int>>> &memory,
    const int current_index=0,
    const int previous_index=-1
)

{
    // you have either already taken K elements into account or the list is exhausted
    if (k == 0 or current_index >= size)
        return 0;
    
    // this state has been computed earlier
    if (memory.at(current_index).at(previous_index+1).at(k) != -1)
        return memory.at(current_index).at(previous_index+1).at(k);
    
    // GAME STARTS NOW
    int option1, option2;

    // CASE 1: NO ELEMENT WAS TAKEN EARLIER
    if (previous_index == -1) {
        // CASE 1: YOU TAKE THIS ELEMENT INTO ACCOUNT
        option1 = sequence.at(current_index) + find_maximum_non_decreasing_subsequence_sum_of_length_atmost(sequence, size, k-1, memory, current_index+1, current_index);

        // CASE 2: YOU SKIP THIS ELEMENT
        option2 = find_maximum_non_decreasing_subsequence_sum_of_length_atmost(sequence, size, k, memory, current_index+1, previous_index);
    }

    // CASE 2: ATLEAST ONE ELEMENT WAS TAKEN EARLIER
    else {
        // CASE 1: THIS ELEMENT DOES NOT FIT INTO CURRENT SUBSEQUENCE
        if (sequence.at(current_index) < sequence.at(previous_index)) {
            return memory.at(current_index).at(previous_index+1).at(k) = find_maximum_non_decreasing_subsequence_sum_of_length_atmost(sequence, size, k, memory, current_index+1, previous_index);
        }

        // CASE 2: THIS ELEMENT FITS INTO THE CURRENT SUBSEQUENCE
        else {
            // CASE 1: YOU TAKE THIS ELEMENT INTO ACCOUNT
            option1 = sequence.at(current_index) + find_maximum_non_decreasing_subsequence_sum_of_length_atmost(sequence, size, k-1, memory, current_index+1, current_index);

            // CASE 2: YOU SKIP THIS ELEMENT
            option2 = find_maximum_non_decreasing_subsequence_sum_of_length_atmost(sequence, size, k, memory, current_index+1, previous_index);
        }
    }

    return memory.at(current_index).at(previous_index+1).at(k) = std::max(option1, option2);
}



int main() {
    int size;
    std::cout << "\nEnter the size of the sequence : ";
    std::cin >> size;

    std::vector<int> sequence = initialize_sequence(size);

    int k;
    std::cout << "\nEnter the maximum length of the subsequence : ";
    std::cin >> k;

    std::vector<std::vector<std::vector<int>>> memory = initialize_memory(size, k);

    const int result = find_maximum_non_decreasing_subsequence_sum_of_length_atmost(sequence, size, k, memory);

    std::cout << "\nThe maximum possible sum of subsequence of length atmost " << k <<" is : " << result << std::endl;

    return 0;
}

