#ifndef PASSWORD_ENTRY_H
#define PASSWORD_ENTRY_H

#include <string>

struct PasswordEntry {
    const int lower_limit;
    const int upper_limit;
    const char target_character;
    const std::string password;
};

#endif
