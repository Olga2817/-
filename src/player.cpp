#include "player.hpp"

Player::Player(std::string id, int64_t initial_balance) 
    : id_(std::move(id)), balance_(initial_balance) {
    if (balance_ < 0) {
        throw std::invalid_argument("Начальный баланс не может быть отрицательным!");
    }
}

bool Player::can_afford(int64_t amount) const noexcept {
    return amount > 0 && balance_ >= amount;
}

void Player::withdraw(int64_t amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Сумма вывода должна быть положительной!");
    }
    if (amount > balance_) {
        throw std::runtime_error("Недостаточно средств!");
    }
    balance_ -= amount;
}

void Player::deposit(int64_t amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Сумма депозита должна быть положительной!");
    }
    balance_ += amount;
}