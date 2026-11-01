#include "table.hpp"
#include <stdexcept>

CasinoTable::CasinoTable(int64_t initial_cash, int64_t min_bet, int64_t max_bet)
    : casino_cash_(initial_cash), min_bet_(min_bet), max_bet_(max_bet) {
    if (initial_cash < 0 || min_bet <= 0 || max_bet < min_bet) {
        throw std::invalid_argument("Некорректные параметры инициализации стола казино!");
    }
}

bool CasinoTable::try_adjust_cash(int64_t delta) noexcept {
    if (casino_cash_ + delta < 0) {
        return false;
    }
    casino_cash_ += delta;
    return true;
}

bool CasinoTable::validate_bet(const Bet& bet, const Player& player) const noexcept {
    if (bet.amount() < min_bet_ || bet.amount() > max_bet_) {
        return false;
    }
    return player.can_afford(bet.amount());
}

bool CasinoTable::resolve_bet(Player& player, const Bet& bet, int rolled_number) {
    bool has_won = false;
    int64_t payout = 0;

    if (bet.type() == BetType::NUMBER) {
        if (bet.target_number() == rolled_number) {
            has_won = true;
            payout = bet.amount() * 35;
        }
    } else if (bet.type() == BetType::COLOR) {
        if (rolled_number != 0 && bet.target_color() == bet.target_color()) { 

            Color rolled_color = (rolled_number % 2 == 0) ? Color::RED : Color::BLACK;
            if (bet.target_color() == rolled_color) {
                has_won = true;
                payout = bet.amount() * 1;
            }
        }
    }

    if (has_won) {
        if (!try_adjust_cash(-payout)) {
            throw std::runtime_error("Казино обанкротилось! Недостаточно средств в кассе для выплаты.");
        }
        player.deposit(bet.amount() + payout);
        return true;
    } else {
        player.withdraw(bet.amount());
        casino_cash_ += bet.amount();
        return false;
    }
}