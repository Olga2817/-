#pragma once
#include <cstdint>
#include <stdexcept>

enum class BetType { COLOR, NUMBER };
enum class Color { RED, BLACK, GREEN };

class Bet {
    BetType type_;
    int64_t amount_;
    int target_number_;
    Color target_color_;

    Bet(BetType type, int64_t amount, int target_number, Color target_color);

public:
    static Bet on_color(Color c, int64_t amt);
    static Bet on_number(int num, int64_t amt);

    BetType type() const noexcept { return type_; }
    int64_t amount() const noexcept { return amount_; }
    int target_number() const noexcept { return target_number_; }
    Color target_color() const noexcept { return target_color_; }
};