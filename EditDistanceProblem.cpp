/*
    Given two strings s1 and s2. Return the minimum number of operations required to convert s1 to s2.
    The possible operations are permitted:

        Insert a character at any position of the string.
        Remove any character from the string.
        Replace any character from the string with any other character.
    
    Example :-

        Input: s1 = "abcd", s2 = "bcfe"
        Output: 3
        Explanation: We can convert s1 into s2 by removing ‘a’, replacing ‘d’ with ‘f’ and inserting ‘e’ at the end. 

        Input: s1 = "geek", s2 = "gesek"
        Output: 1
        Explanation: One operation is required, inserting 's' between two 'e' in s1.

*/

#include <iostream>
#include <vector>

int find_edit_distance(const std::string &str1, const std::string &str2, std::vector<std::vector<int>>* &memory, const int str1_size, const int str2_size) {
    if (str1_size == 0)
        return str2_size;
    
    if (str2_size == 0)
        return str1_size;
    
    if (memory->at(str1_size).at(str2_size) != -1)
        return memory->at(str1_size).at(str2_size);
    
    if (str1[str1_size-1] == str2[str2_size-1])
        return memory->at(str1_size).at(str2_size) = find_edit_distance(str1, str2, memory, str1_size-1, str2_size-1);
    
    const int choice_1 = find_edit_distance(str1, str2, memory, str1_size-1, str2_size);
    const int choice_2 = find_edit_distance(str1, str2, memory, str1_size, str2_size-1);
    const int choice_3 = find_edit_distance(str1, str2, memory, str1_size-1, str2_size-1);

    return memory->at(str1_size).at(str2_size) = 1 + std::min(choice_1, std::min(choice_2, choice_3));
}

int main() {
    std::cout << "\nEnter the strings consecutively : ";
    std::string str1, str2;
    std::cin >> str1 >> str2;

    int size1 = str1.size();
    int size2 = str2.size();

    std::vector<std::vector<int>>* memory = new std::vector<std::vector<int>>(size1+1, std::vector<int>(size2+1, -1));

    int res = find_edit_distance(str1, str2, memory, str1.size(), str2.size());

    std::cout << "\n\t\t\tMinimum " << res << " operation(s) are required!\n\n";

    delete memory;
    return 0;
}