/*
    Aryan and Ankit take turns picking all the balls from either the beginning or the end of the row of boxes.
    Aryan always plays first. Both players play optimally, meaning they make decisions to maximize their number of balls.

    The game ends when there are no more boxes left.
    Assume Aryan and Ankit play optimally.
    
    What  is the number of balls Aryan and Ankit collects after the gane ends?
*/

#include <iostream>
#include <vector>

// this DP implemented method return number of balls collected by Aryan since aryan starts the game

int find_number_of_balls_collected_by_ankit(std::vector<int>* &boxes, int left_index, int right_index, int turn, std::vector<std::vector<std::vector<int>>> &memory) {

    if (left_index == right_index)
        return turn? boxes->at(left_index) : 0;
    
    if (memory.at(left_index).at(right_index).at(turn) != -1)
        return memory.at(left_index).at(right_index).at(turn);
    
    int left_path_score = boxes->at(left_index)*turn + find_number_of_balls_collected_by_ankit(boxes, left_index+1, right_index, not turn, memory);

    int right_path_score = boxes->at(right_index)*turn + find_number_of_balls_collected_by_ankit(boxes, left_index, right_index-1, not turn, memory);

    return memory.at(left_index).at(right_index).at(turn) = turn? std::max(left_path_score, right_path_score) : std::min(left_path_score, right_path_score);
    
}

std::vector<int>* initialize_boxes() {
    int n;
    std::cout << "\nEnter the number of boxes  : ";
    std::cin >> n;

    std::vector<int>* boxes = new std::vector<int>(n);

    int size = boxes->size();

    for (int i=0; i<size; i++) {
        std::cout << "\nEnter the number of balls in box number - (" << (i+1) << ") : ";
        std::cin >> boxes->at(i);
    }

    std::cout << "\n\n";

    if (size > 0)
        std::cout << "\n\t\t\t\t\tHere's the number of balls in the sequence : ";

    for (auto ele : *boxes)
        std::cout << ele << " ";

    std::cout << std::endl;
    return boxes;

}

int main() {
    std::vector<int>* boxes = initialize_boxes();
    std::cout << std::endl;

    const int size = boxes->size();

    // initializing memory
    std::vector<std::vector<std::vector<int>>> memory(size, std::vector<std::vector<int>>(size, std::vector<int>(2, -1)));

    int res = find_number_of_balls_collected_by_ankit(boxes, 0, size-1, 1, memory);

    std::cout << "\n\t\t\t\t\t\tAryan is able to collect " << res;
    delete boxes;
    return 0;
}