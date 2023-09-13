#include <string>
#include <algorithm>
#include <iostream>

#include "password_entry.h"
#include "password_validator.h"

bool PasswordValidator::has_valid_letter_count(PasswordEntry entry) {
    int character_count = std::count_if(
        entry.password.begin(),
        entry.password.end(),
        [entry](char c) { return c == entry.target_character ;}
    );

    return entry.lower_limit <= character_count && character_count <= entry.upper_limit;
}

bool PasswordValidator::has_valid_letter_position(PasswordEntry entry) {
    auto validate = [entry](int limit) { return entry.password[limit - 1] == entry.target_character; };

    bool is_first  = validate(entry.lower_limit);
    bool is_second = validate(entry.upper_limit);

    return (is_first || is_second) && !(is_first && is_second);
}
