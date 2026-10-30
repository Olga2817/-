#pragma once
#include "table.hpp"
#include "player.hpp"
#include "bet.hpp"
#include <random>
#include <stdexcept>

class GameService {
public:
    explicit GameService(CasinoTable& table, unsigned int seed = std::random_device{}());

    GameService(const GameService&) = delete;
    GameService& operator=(const GameService&) = delete;
    GameService(GameService&&) = delete;
    GameService& operator=(GameService&&) = delete;

    int play_round(Player& player, const Bet& bet);

    int spin_wheel() const;

private:
    CasinoTable& table_;
    mutable std::mt19937 rng_;
    std::uniform_int_distribution<int> dist_;
};