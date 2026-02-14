/*
    Given two strings `a` and `b`.
    We need to find the length of the longest common subsequence in them.
    Subsequence means that the characters need not to be adjackent, just the relative order must be maintained
    What is the length of the longest common subsequence?
*/

#include <iostream>
#include <vector>
#include <string>

int get_longest_common_subsequence_length(const std::string &str1, const std::string &str2, const int n1, const int n2, std::vector<std::vector<int>>* &memory, int index1=0, int index2=0) {

    // characters exhausted
    if (index1 >= n1 or index2 >= n2)
        return 0;
    
    // if subproblem is already computed then simply return it
    if (memory->at(index1).at(index2) != -1) 
        return memory->at(index1).at(index2);
    
    // common character found. So collect it and move forward
    if (str1[index1] == str2[index2]) {
        return memory->at(index1).at(index2) = 1 + get_longest_common_subsequence_length(str1, str2, n1, n2, memory, index1+1, index2+1);
    }

    // common character not found... now we have 3 options to move forward
    else {

        // option 1 > move first index ahead and keep second fix

        int length1 = get_longest_common_subsequence_length(str1, str2, n1, n2, memory, index1+1, index2);

        // option 2 > move second index ahead and keep the second index fix

        int length2 = get_longest_common_subsequence_length(str1, str2, n1, n2, memory, index1, index2+1);

        // option 3 > move both indexes forward together
        
        int length3 = get_longest_common_subsequence_length(str1, str2, n1, n2, memory, index1+1, index2+1);

        return memory->at(index1).at(index2) = std::max(std::max(length1, length2), length3);

    }

}

int main() {
    std::string str1, str2;

    std::cout << "\nEnter the first string : ";
    std::cin >> str1;

    std::cout << "\nEnter the second string : ";
    std::cin >> str2;

    std::cout << "\nThe strings are : '" << str1 << "' & '" << str2 << "'" << std::endl << std::endl;

    const int n1 = str1.size();
    const int n2 = str2.size();

    std::vector<std::vector<int>>* memory = new std::vector<std::vector<int>>(n1+1, std::vector<int>(n2+1, -1));

    int res = get_longest_common_subsequence_length(str1, str2, n1, n2, memory);

    std::cout << "\n\t\t\t\t\t\t\t\t\tThe maximum length of common subsequence is : " << res << "\n\n";
    return 0;
}