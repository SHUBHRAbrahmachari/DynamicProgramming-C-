/*
    You are given an array coins[], where each element represents a coin of a different denomination.
    A target value sum. You have an unlimited supply of each coin type {coins1, coins2, ..., coinsm}.

    Your task is to determine the minimum number of coins needed to obtain the target sum.
    If it is not possible to form the sum using the given coins, return -1.

            For example [3, 6, 8] and sum is 9
            answer is 2 (3 + 6)
*/

#include <iostream>
#include <vector>
#include <limits>

#define MAX std::numeric_limits<int>::max()/2       // imagining infinity with MAX


int find_minimum_number_of_coins(std::vector<int>* &coins, std::vector<int>* &memory, int target_sum) {

    // target sum has been successfully reached!
    if (target_sum == 0)
        return 0;
    
    // with this configuration you can never reach the target sum, so you return INFINITY path
    if (target_sum < 0)
        return MAX;
    
    if (memory->at(target_sum) != -1)
        return memory->at(target_sum);
    
    int current_best_result = std::numeric_limits<int>::max();

    for (int value: *coins) {

        int new_target_sum = target_sum - value;
        int result = 1 + find_minimum_number_of_coins(coins, memory, new_target_sum);

        if (result < current_best_result)
            current_best_result = result;
    }

    return memory->at(target_sum) = current_best_result;
}


int main() {
    std::cout << MAX << "\n\n";
    std::cout << "\nEnter the number of unique coins you want to have : ";
    int number_of_coins;
    std::cin >> number_of_coins;

    // coin values are stored here
    std::vector<int>* coins = new std::vector<int>(number_of_coins);

    std::vector<int>::iterator itr = coins->begin();

    std::cout << "\nKeep entering the unique coins values (non-negative integers only) : ";
    while (itr != coins->end()) {
        std::cin >> *itr;
        std::advance(itr, 1);
    }

    std::cout << "\n\t\t\tThe coin values are : ";
    for (auto ele : *coins)
        std::cout << ele << " ";
    
    std::cout << "\n\n";

    std::cout << "\nEnter the target sum please (non-negative integer only) : ";
    int target_sum;
    std::cin >> target_sum;

    // initialized memory
    std::vector<int>* memory = new std::vector<int>(target_sum+1, -1);

    int res = find_minimum_number_of_coins(coins, memory, target_sum);

    if (res >= MAX) 
        std::cout << "\nTarget sum cannot be reached!";
    else
        std::cout << "\nwe need atleast " << res << " coins to make up that!"; 
    
    std::cout << "\n\n";
    
    delete coins;
    delete memory;

    return 0;

}