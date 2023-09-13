#include <vector>
#include <string>
#include <fstream>
#include <optional>
#include <functional>
#include <iostream>

#include "../include/utility/file_util.h"

int main() {
    auto data = FileUtil::get_lines("../resources/day_three/input.txt");

    for (const auto& entry: data) {
        std::cout << entry << std::endl;
    }

    return 0;
}
