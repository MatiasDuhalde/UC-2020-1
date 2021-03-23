#include <ctype.h>      // isdigit()
#include <limits.h>     // 
#include <stdbool.h>    // bool as type (+ true and false)

// Adapted from https://eternallyconfuzzled.com/atoi-is-evil-c-learn-why-atoi-is-awful
bool is_valid_int(const char *s) {
    long long temp = 0;
    bool negative = false;

    // Checks if negative
    if (*s != '\0' && (*s == '-' || *s == '+')) {
        negative = *s++ == '-';
    }
    // Checks digit by digit
    while (*s != '\0') {
        if (!isdigit((unsigned char)*s)) {
            return false;
        }
        temp = 10 * temp + (*s - '0');
        // Checks number size
        if ((!negative && temp > INT_MAX) || (negative && -temp < INT_MIN)) {
            return false;
        }
        ++s;
    }
    return true;
}

int parse_int(const char *s) {
    if (is_valid_int(s)) {
        return atoi(s);
    }
    printf("ERROR: %s is not a number.\n", s);
    exit(1);
}
