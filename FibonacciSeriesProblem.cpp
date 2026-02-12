/*

                fibonacci series is defined as 0, 1, 1, 2, 3, 5, 8, 13,.....

            basically, fib(n) = fib(n-1) + fib(n-2), when n > 1
                       fib(1) = 1
                       fib(0) = 0
                we need to find nth term of this fibonacci series using Dynamic Programming (memoization approach)
                Tabulation approach (loop) becomes too easy
*/

#include <iostream>
#include <utility>
#include <stdexcept>
#include <vector>

int fibonacci_tabulation(const int n) {
    if (n < 0) {
        throw std::logic_error("negative numbers cannot be passed!");
    }

    if (n == 0 or n == 1) {
        return n;
    }

    int term1 = 0;
    int term2 = 1;
    int res = 0;

    for (int i=1; i < n; i++) {
        res = term1 + term2;
        term1 = term2;
        term2 = res;
    }

    return res;

}

int fibonacci_memoization(const int n, std::vector<int>* &memory) {

    if (n < 0) {
        throw std::logic_error("negative numbers cannot be passed!");
    }

    if (n == 0 or n == 1) {
        return memory->at(n) = n;
    }

    if (memory->at(n) != -1) {
        return memory->at(n);
    }

    return memory->at(n) = fibonacci_memoization(n-1, memory) + fibonacci_memoization(n-2, memory);

}

int main() {
    int n;
    std::cout << "\nEnter the term number : ";
    std::cin >> n;

    try {

        int res = fibonacci_tabulation(n);
        std::cout << "\nThe " << n << "-th fibonacci number using tabulation is : " << res << std::endl;

        std::vector<int>* memory = new std::vector<int>(n+1, -1);
        res = fibonacci_memoization(n, memory);

        std::cout << "\nThe " << n << "-th fibonacci number using memoization is : " << res << std::endl;
        delete memory;

    }catch (const std::logic_error& error) {

        std::cout << error.what() << std::endl;

    }

    return 0;
}