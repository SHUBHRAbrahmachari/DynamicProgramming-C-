/*
        We have a maze of M X N shape.
        A rat sits at cell (0, 0) and wants to reach at cell (M-1, N-1) with minimum possible cell movements
        A cell movement means moving from one cell to another. The rat can move either down or right or right-diagonal by one cell at a time.
        Few cells are dead cell i.e. the rat cannot go to that cell since its poisoned
*/

#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <limits>

void show_maze(const std::vector<std::vector<int>>* maze) {
    int m = maze->size();
    int n = maze->at(0).size();

    std::cout << "\nHere's the maze : \n\n";

    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            if (i == 0 and j == 0) {
                std::cout << "S ";
            }else if (i == m-1 and j == n-1) {
                std::cout << "D ";
            }else {
                std::cout << (maze->at(i).at(j) == 0? "- " : "X ");
            }
        }
        std::cout << std::endl;
    }

    std::cout << "\n\n";
    return;
}

std::vector<std::vector<int>>* initialize_maze() {
    
    int m, n;
    std::cout << "\nEnter the number of rows and columns in the maze respectively : ";
    std::cin >> m >> n;

    if (m <= 0 or n <= 0) {
        throw std::logic_error("number of rows or columns cannot be zero or negative!");
    }

    int dead_cell_count = 0;
    std::cout << "\nEnter the number of dead cells in the maze : ";
    std::cin >> dead_cell_count;

    std::vector<std::vector<int>>* maze = new std::vector<std::vector<int>>(m, std::vector<int>(n, 0));

    int r, c;

    for (int i=1; i<=dead_cell_count; i++) {
        std::cout << "\nEnter the row & column index for dead cell number : (" << i << ") : ";
        std::cin >> r >> c;
        if ((r == 0 and c == 0) or (r == m-1 and c == n-1) or c >= m or c < 0 or c >= n or c < 0) {
            std::cout << "cell index out of bound! try again\n";
            i -= 1;
            continue;
        }
        
        maze->at(r).at(c) = -1;

    }

    return maze;

}

int find_minimum_movements(const int r, const int c, std::vector<std::vector<int>>* &maze, std::vector<std::vector<int>>* &memory, const int m, const int n) {

    // if rat reaches the end cell then get the prize with 0 penalty
    if (r == m-1 and c == n-1) {
        return 0;
    }

    // we accidentally sent the rat out of maze or mistakenly entered dead-cell. Then we apply some penalty (large movement cost)
    if (r >= m or c >= n or maze->at(r).at(c) == -1) {
        return std::numeric_limits<int>::max() / 2;
    }

    if (memory->at(r).at(c) != -1) {
        return memory->at(r).at(c);
    }

    // going down
    int down_path = 1 + find_minimum_movements(r+1, c, maze, memory, m, n);

    // going right
    int right_path = 1 + find_minimum_movements(r, c+1, maze, memory, m, n);

    // diagonal path
    int diagonal_path = 1 + find_minimum_movements(r+1, c+1, maze, memory, m, n);


    if (down_path < right_path) {
        if (down_path < diagonal_path) {
            memory->at(r).at(c) = down_path;
        }else {
            memory->at(r).at(c) = diagonal_path;
        }
    }else {
        if (right_path < diagonal_path) {
            memory->at(r).at(c) = right_path;
        }else {
            memory->at(r).at(c) = diagonal_path;
        }
    }

    return memory->at(r).at(c);

}

int main() {
    try {
        std::vector<std::vector<int>>* maze = initialize_maze();
        show_maze(maze);

        int m = maze->size();
        int n = maze->at(0).size();

        std::vector<std::vector<int>>* memory = new std::vector<std::vector<int>>(m+1, std::vector<int>(n+1, -1));

        int ans = find_minimum_movements(0, 0, maze, memory, m, n);

        if (ans >= 9999)
            std::cout << "\n\t\t\t\t\t\t\t\t\t\tTarget cannot be reached!\n\n";
        else
            std::cout << "\n\t\t\t\t\t\t\t\t\t\tIt needs to take atleast " << ans << " movements!\n\n";

        delete maze;
        delete memory;

    }catch (std::logic_error error) {
        std::cout << error.what() << std::endl << std::endl;
    }
    return 0;
}