/*
    There are n+1 staircases.
    You are standing on 0th staircase.
    You can either go to next staircase or you can skip the next staircase to directly reach to the next of next staircase.
    Cost of reaching 0th and 1st staircase is 1.
    You need to find the total number of ways to reach nth staircase

    For example, staircase 2 has two ways to reach

                1> 0 -> 2
                2> 0 -> 1 -> 2
*/

#include <iostream>

// tabulation approach od DP
int find_ways_to_reach(const int to_reach) {

    // invalid case
    if (to_reach < 0)
        return -1;

    if (to_reach <= 1)
        return 1;

    int step1 = 1;
    int step2 = 1;
    int res = 0;

    for (int i=1; i<to_reach; i++) {
        res = step1+step2;
        step1 = step2;
        step2 = res;
    }

    return res;
}

int main() {
    std::cout << "\nEnter the staircase number you want to reach : ";
    int n;
    std::cin >> n;

    int res = find_ways_to_reach(n);

    if (res == -1)
        std::cout << "\n\t\t\t\t\t\tThe staircase number cannot be negative you idiot!\n\n";
    else
        std::cout << "\n\t\t\t\t\t\tIt would have " << res << " number of ways to reach stair number " << n << "\n\n";
    
    return 0;
}

