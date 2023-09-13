#include <vector>
#include <string>
#include <fstream>
#include <optional>
#include <functional>
#include <iostream>
#include <numeric>

#include "../include/utility/file_util.h"

int navigate(std::tuple<int, int> slope, std::vector<std::string>& map) {
    auto [slope_x, slope_y] = slope;
    std::cout << "\n======================================================================================================" << std::endl;
    std::cout << "------------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "Starting navigation with slope (" << slope_x << ", " << slope_y << ")..." << std::endl;
    std::cout << "------------------------------------------------------------------------------------------------------" << std::endl;
    auto y = map.size();
    auto x = map[0].size();
    std::tuple<int, int> cursor = std::tuple(0, 0);
    auto tree_count = 0;

    for (int i = 0; i < y; i++) {
        auto entry = map[i];
        auto [current_x, current_y] = cursor;
        auto character = map[current_y][current_x];

        if (i % slope_y != 0) {
            std::cout << " | Position: '" << "N/A" << "' @ (" << "_" << ", " << "_" << ") | " << "\t" << " | " << "N/A" << " | \t | " << "Trees Hit: " << tree_count << " | \t | " << entry << " | " << std::endl;
            continue;
        }

        auto hit_a_tree = character == '#';
        auto hit_or_safe = hit_a_tree ? "HIT!" : "SAFE";
        char update_character;

        if (character == '#') {
            tree_count++;
            update_character = 'X';
        } else {
            update_character = 'O';
        }

        cursor = std::tuple((current_x + slope_x) % x, (current_y + slope_y));

        auto updated_entry = entry;
        updated_entry[current_x] = update_character;

        std::cout << " | Position: '" << character << "' @ (" << current_x << ", " << current_y << ") | " << "\t" << " | " << hit_or_safe << " | \t | " << "Trees Hit: " << tree_count << " | \t | " << updated_entry << " | " << std::endl;
    }

    std::cout << "------------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "Number of trees encountered for given slope (" << slope_x << ", " << slope_y << "): " << tree_count << std::endl;
    std::cout << "------------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "======================================================================================================\n" << std::endl;
    return tree_count;
}

int main() {
    auto data = FileUtil::get_lines("../resources/day_three/input.txt");
    auto tree_hit_count = std::vector<int>();

    long t1 = navigate(std::tuple(1, 1), data);
    long t2 = navigate(std::tuple(3, 1), data);
    long t3 = navigate(std::tuple(5, 1), data);
    long t4 = navigate(std::tuple(7, 1), data);
    long t5 = navigate(std::tuple(1, 2), data);

    std::cout << (t1 * t2 * t3 * t4 * t5) << std::endl;

    return 0;
}
