#include "bet.hpp"

Bet::Bet(BetType type, int64_t amount, int target_number, Color target_color)
    : type_(type), amount_(amount), target_number_(target_number), target_color_(target_color) {}

Bet Bet::on_color(Color c, int64_t amt) {
    if (amt <= 0) {
        throw std::invalid_argument("Сумма ставки должна быть положительной!");
    }
    if (c == Color::GREEN) {
        throw std::invalid_argument("Нельзя делать ставку непосредственно на зелёный цвет!");
    }
    return Bet(BetType::COLOR, amt, -1, c);
}

Bet Bet::on_number(int num, int64_t amt) {
    if (amt <= 0) {
        throw std::invalid_argument("Сумма ставки должна быть положительной!");
    }
    if (num < 0 || num > 36) {
        throw std::invalid_argument("Номер рулетки должен быть от 0 до 36!");
    }
    
    Color col = Color::GREEN;
    if (num != 0) {
        col = (num % 2 == 0) ? Color::RED : Color::BLACK;
    }

    return Bet(BetType::NUMBER, amt, num, col);
}