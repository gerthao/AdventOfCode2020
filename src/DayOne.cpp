#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <optional>
#include <vector>
#include <algorithm>

std::vector<int> read_expense_report(std::string file_path) {
    std::ifstream file(file_path);
    std::string line;
    std::vector<int> expenses;

    if (!file.is_open()) {
        std::cerr << "Failed to open file...";
        return expenses;
    }

    while (std::getline(file, line)) {
        expenses.push_back(std::stoi(line));
    }

    file.close();

    return expenses;
}

std::optional<std::tuple<int, int>> find_sum_pair(int target, std::vector<int> expenses) {
    std::unordered_map<int, int> pairs;

    for (const auto& expense: expenses) {
        int difference = target - expense;
        if (pairs.find(difference) != pairs.end()) {
            return std::tuple(expense, difference);
        }
        pairs[expense] = difference;
    }

    return std::nullopt;
}

std::optional<std::tuple<int, int, int>> find_sum_triplet(int target, std::vector<int> expenses) {
    std::sort(expenses.begin(), expenses.end());

    int number_of_expenses = expenses.size();

    for (int i = 0; i < number_of_expenses - 2; i++) {
        if (i > 0 && expenses[i] == expenses[i - 1]) continue;

        int left  = i + 1;
        int right = number_of_expenses - 1;

        while (left < right) {
            int sum = expenses[i] + expenses[left] + expenses[right];

            if (sum == target) return std::tuple(expenses[i], expenses[left], expenses[right]);
            else if (sum < target) left++;
            else right--;
        }
    }

    return std::nullopt;
}

int main() {
    int target             = 2020;
    auto expenses          = read_expense_report("resources/ExpenseReport.txt");
    auto maybe_sum_pair    = find_sum_pair(target, expenses);
    auto maybe_sum_triplet = find_sum_triplet(target, expenses);

    if (maybe_sum_pair.has_value()) {
        auto [first, second] = *maybe_sum_pair;
        std::cout << "Found pair with a sum equal to " << target << ": [" << first << ", " << second << "]" << std::endl;

        auto product = first * second;
        std::cout << "Product of the pair is " << product << std::endl;
    } else {
        std::cout << "Could not find a pair with a sum equal to " << target << std::endl;
    }


    if (maybe_sum_triplet.has_value()) {
        auto [first, second, third] = *maybe_sum_triplet;
        std::cout << "Found triplet with a sum equal to " << target << ": [" << first << ", " << second <<  ", " << third << "]" << std::endl;

        auto product = first * second * third;
        std::cout << "Product of the triplet is " << product << std::endl;
    } else {
        std::cout << "Could not find a triplet with a sum equal to " << target << std::endl;
    }

    return 0;
}
