#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <optional>
#include <vector>
#include <algorithm>
#include <numeric>

#include "password_entry.h"
#include "password_validator.h"

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) {
        return "";
    }

    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}

std::vector<PasswordEntry> read_input(std::string file_path) {
    std::ifstream file(file_path);
    std::string line;
    std::vector<PasswordEntry> entries;

    if (!file.is_open()) {
        std::cerr << "Failed to open file...";
        return entries;
    }

    while (std::getline(file, line)) {
        if (!trim(line).empty()) {
            size_t delimiter     = line.find(':');
            std::string policy   = trim(line.substr(0, delimiter));
            std::string password = trim(line.substr(delimiter + 1));

            delimiter                = policy.find(' ');
            std::string letter_range = policy.substr(0, delimiter);
            std::string letter       = policy.substr(delimiter + 1);

            delimiter       = letter_range.find('-');
            int lower_limit = std::stoi(letter_range.substr(0, delimiter));
            int upper_limit = std::stoi(letter_range.substr(delimiter + 1));

            entries.push_back({
                .lower_limit      = lower_limit,
                .upper_limit      = upper_limit,
                .target_character = letter[0],
                .password         = password
            });
        }
    }

    file.close();

    return entries;
}

int main() {
    auto password_entries = read_input("../resources/day_two/input.txt");
    auto validator        = PasswordValidator();
    int valid_count       = 0;

    for (const auto& entry: password_entries) {
        // if (validator.has_valid_letter_count(entry)) valid_count++;
        if (validator.has_valid_letter_position(entry)) valid_count++;
    }

    std::cout << "Number of valid passwords [" << valid_count << "] out of [" << password_entries.size() << "].";

    return 0;
}
