#pragma once
#include <string>
#include <cstdint>
#include <stdexcept>

class Player {
    std::string id_;
    int64_t balance_;

public:
    Player(std::string id, int64_t initial_balance);

    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    Player(Player&&) noexcept = default;
    Player& operator=(Player&&) noexcept = default;

    const std::string& id() const noexcept { return id_; }
    int64_t balance() const noexcept { return balance_; }

    bool can_afford(int64_t amount) const noexcept;
    void withdraw(int64_t amount);
    void deposit(int64_t amount);
};