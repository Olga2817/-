#pragma once
#include "player.hpp"
#include "bet.hpp"
#include <cstdint>

class CasinoTable {
public:
    CasinoTable(int64_t initial_cash, int64_t min_bet, int64_t max_bet);

    int64_t casino_cash() const noexcept { return casino_cash_; }
    int64_t min_bet() const noexcept { return min_bet_; }
    int64_t max_bet() const noexcept { return max_bet_; }

    bool try_adjust_cash(int64_t delta) noexcept;

    bool validate_bet(const Bet& bet, const Player& player) const noexcept;

    bool resolve_bet(Player& player, const Bet& bet, int rolled_number);

private:
    int64_t casino_cash_;
    int64_t min_bet_;
    int64_t max_bet_;
};