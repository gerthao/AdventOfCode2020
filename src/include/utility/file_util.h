#ifndef FILE_UTIL_H
#define FILE_UTIL_H

#include <fstream>
#include <optional>
#include <functional>

class FileUtil {
public:
    // only works with explicit instantiation //
    template <typename T>
    static std::optional<T> with_data(const std::string& file_path, const std::function<T(std::ifstream&)>& operation);

    // only one that works, not sure how to use template types with function arguments //
    static std::vector<std::string> get_lines(const std::string& file_path);

    // doesn't work right, might need explicit instantiation //
    template <typename T>
    static std::vector<T> collect(const std::string& file_path, const std::function<T(std::string&)>& operation);
};

#endif
