#ifndef PASSWORD_VALIDATOR_H
#define PASSWORD_VALIDATOR_H

#include <string>
#include <algorithm>

#include "password_entry.h"

class PasswordValidator {
public:
    bool has_valid_letter_count(PasswordEntry entry);
    bool has_valid_letter_position(PasswordEntry entry);
};

#endif
