/*
    We are given two machines A and B.
    We are also given a set of N tasks.
    The profit earned by preforming each task is given by A[], B[]

    If Machine-A performs task i then you earn A[i] profit
    If Machine-B performs task i then you earn B[i] profit.

    Machine-A can process atmost X tasks and Machine-B can process atmost Y tasks.
    It is ensured that X+Y >= N so no task will be left

    Find out the maximum possible profit earned by both of the machines.


                                1 ≤ N ≤ 100000
                                1 ≤ x, y ≤ 100000
                                1 ≤ a[i], b[i] ≤ 10000
*/

#include <iostream>
#include <vector>
#include <unordered_map>

std::vector<int> initialize_profits(const int &size, const std::string machine_name="ABC") {
    std::vector<int> profits(size);

    std::cout << "\nKeep entering the profits for machine : " << machine_name << " : ";
    for (int i=0; i<size; i++)
        std::cin >> profits.at(i);

    return profits;
}

void show_profits(const std::vector<int> &profits, const int &size, const std::string machine_name="XYZ") {
    std::cout << std::endl;
    std::cout << "\t\t\t\t\t\t\t\t\t\t\t\tFOR MACHINE : " << machine_name << std::endl;
    std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t";
    for (const int &ele : profits)
        std::cout << ele << " ";
    std::cout << std::endl;
    return;
}


unsigned long long get_compressed_state(
    const int &current_index,
    const int &remaining_performable_task_count_by_A,
    const int &remaining_performable_task_count_by_B
)

{
    const unsigned long long BASE = 100001;
    unsigned long long state = (unsigned long long)current_index;
    state = state*BASE + (unsigned long long)remaining_performable_task_count_by_A;
    state = state*BASE + (unsigned long long)remaining_performable_task_count_by_B;

    return state;
}

int find_maximum_profit(
    const std::vector<int> &machine_A_profits,
    const std::vector<int> &machine_B_profits,
    const int &size,
    std::unordered_map<unsigned long long, int> &memory,
    const int &remaining_task_count_by_A,
    const int &remaining_task_count_by_B,
    const int current_index=0
)

{
    if (current_index >= size)
        return 0;
    
    const unsigned long long state = get_compressed_state(current_index, remaining_task_count_by_A, remaining_task_count_by_B);

    if (memory.find(state) != memory.end())
        return memory.at(state);

    if (remaining_task_count_by_A > 0 and remaining_task_count_by_B > 0) {
        int option1 = machine_A_profits.at(current_index) + find_maximum_profit(machine_A_profits, machine_B_profits, size, memory, remaining_task_count_by_A-1, remaining_task_count_by_B, current_index+1);

        int option2 = machine_B_profits.at(current_index) + find_maximum_profit(machine_A_profits, machine_B_profits, size, memory, remaining_task_count_by_A, remaining_task_count_by_B-1, current_index+1);

        return memory[state] = std::max(option1, option2);
    }

    else if (remaining_task_count_by_A > 0 and remaining_task_count_by_B == 0) {
        return memory[state] = machine_A_profits.at(current_index) + find_maximum_profit(machine_A_profits, machine_B_profits, size, memory, remaining_task_count_by_A-1, remaining_task_count_by_B, current_index+1);
    }

    else if (remaining_task_count_by_A == 0 and remaining_task_count_by_B > 0) {
        return memory[state] = machine_B_profits.at(current_index) + find_maximum_profit(machine_A_profits, machine_B_profits, size, memory, remaining_task_count_by_A, remaining_task_count_by_B-1, current_index+1);
    }

    return 0;
}

int main() {
    int size;
    std::cout << "\nEnter the total number of tasks : ";
    std::cin >> size;

    std::vector<int> machine_A_profits = initialize_profits(size, "A");
    std::vector<int> machine_B_profits = initialize_profits(size, "B");

    show_profits(machine_A_profits, size, "A");
    show_profits(machine_B_profits, size, "B");

    int x;
    std::cout << "\nEnter how many tasks can machine-A perform? : ";
    std::cin >> x;

    int y;
    std::cout << "\nEnter how many tasks can machine-B perform? : ";
    std::cin >> y;

    std::unordered_map<unsigned long long, int> memory;

    const int maximum_profit = find_maximum_profit(machine_A_profits, machine_B_profits, size, memory, x, y);

    std::cout << "\nThe maximum earnable profit is : " << maximum_profit << std::endl;

    std::cout << maximum_profit << std::endl << std::endl;

    return 0;


}