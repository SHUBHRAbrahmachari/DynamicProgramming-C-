/*
    There's a thief named Bob.
    There are a series of houses he can rob (given an array with values as wealth of that house).
    He wants to rob as amuch as wealth possible.
    Just the condition is that he cannot rob two consecutive houses becase doing that he would get caught.
    What is the maximum wealth he can rob?
*/

#include <iostream>
#include <vector>
#include <stdexcept>
#include <utility>

void show_wealths(double* houses, const int n) {
    std::cout << "\n\n";
    for (int i=0; i<n; i++) {
        std::cout << "\n\t\t\t\t\t\t\t\t\t\tWealth at house number - (" << (i+1) << ") is : " << houses[i]; 
    }
    std::cout << "\n\n";
    return;
}

std::pair<double*, int> initialize_wealth() {
    int n;
    std::cout << "\nEnter the number of houses in the series : ";
    std::cin >> n;

    double* houses = new double[n];

    for (int i=1; i<=n; i++) {
        std::cout << "\nEnter the wealth at house number - (" << i << ") : ";
        std::cin >> houses[i-1];
    }

    show_wealths(houses, n);
    return std::pair<double*, int>({houses, n});
}

double find_maximum_wealth(double* wealths, const int n, double* &memory, int index=0) {
    if (index >= n)
        return 0;
    
    // if already computed
    if (memory[index] != -1)
        return memory[index];
    
    // option 1 : rob the house and skip the next house
    double result1 = wealths[index] + find_maximum_wealth(wealths, n, memory, index+2);

    // options 2 : do not rob this house and go to next
    double result2 = find_maximum_wealth(wealths, n, memory, index+1);

    return memory[index] = std::max(result1, result2);
}

int main() {
    std::pair<double*, int> wealths = initialize_wealth();
    
    double* memory = new double[wealths.second];

    for (int i=0; i<wealths.second; i++)
        memory[i] = -1;
    
    double res = find_maximum_wealth(wealths.first, wealths.second, memory);

    std::cout << "\n\t\t\t\t\t\t\tMaximum wealth Bob can rob is : " << res << "\n\n";

    delete[] wealths.first;
    delete[] memory;

    return 0;
}