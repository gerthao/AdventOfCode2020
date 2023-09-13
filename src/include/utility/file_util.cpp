#include <fstream>
#include <optional>
#include <functional>

#include "file_util.h"

template <typename T>
std::optional<T> FileUtil::with_data(const std::string& file_path, const std::function<T(std::ifstream&)>& operation) {
    try {
        std::ifstream file(file_path);

        if (!file.is_open()) {
            return std::nullopt;
        }

        T data = operation(file);

        file.close();

        return data;
    } catch (...) {
        return std::nullopt;
    }
}


std::vector<std::string> FileUtil::get_lines(const std::string& file_path) {
    std::ifstream file(file_path);
    std::string line;
    std::vector<std::string> data;


    if (!file.is_open()) {
        return data;
    }

    while(std::getline(file, line)) {
        data.push_back(line);
    }

    file.close();

    return data;
}

template <typename T>
std::vector<T> collect(const std::string& file_path, const std::function<T(std::string&)>& operation) {
    std::ifstream file(file_path);
    std::string line;
    std::vector<T> data;


    if (!file.is_open()) {
        return data;
    }

    while(std::getline(file, line)) {
        T new_data = operation(line);
        data.push_back(new_data);
    }

    file.close();

    return data;
}

template std::optional<std::vector<std::string>> FileUtil::with_data(const std::string&, const std::function<std::vector<std::string>(std::ifstream&)>&);

