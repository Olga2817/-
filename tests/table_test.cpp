#include <gtest/gtest.h>
#include "player.hpp"
#include "bet.hpp"
#include "table.hpp"

TEST(CasinoTableTest, InitializationValidation) {
    EXPECT_NO_THROW(CasinoTable table(50000, 50, 2000));

    EXPECT_THROW(CasinoTable table(-100, 50, 2000), std::invalid_argument);
    EXPECT_THROW(CasinoTable table(50000, 0, 2000), std::invalid_argument);
    EXPECT_THROW(CasinoTable table(50000, 3000, 2000), std::invalid_argument);
}

TEST(CasinoTableTest, BetValidation) {
    CasinoTable table(50000, 100, 1000);
    Player rich_player("Rich", 5000);
    Player poor_player("Poor", 50);

    Bet valid_bet = Bet::on_number(10, 500);
    Bet too_small = Bet::on_number(10, 50);
    Bet too_large = Bet::on_number(10, 1500);
    Bet unaffordable = Bet::on_number(10, 500);

    EXPECT_TRUE(table.validate_bet(valid_bet, rich_player));
    EXPECT_FALSE(table.validate_bet(too_small, rich_player));
    EXPECT_FALSE(table.validate_bet(too_large, rich_player));
    EXPECT_FALSE(table.validate_bet(unaffordable, poor_player));
}

TEST(CasinoTableTest, ResolveNumberBetWin) {
    CasinoTable table(100000, 10, 5000);
    Player player("TestPlayer", 1000);
    
    Bet bet = Bet::on_number(17, 100);
    int64_t initial_balance = player.balance();
    int64_t initial_cash = table.casino_cash();

    bool won = table.resolve_bet(player, bet, 17);

    EXPECT_TRUE(won);
    EXPECT_EQ(player.balance(), initial_balance + 3600);
    EXPECT_EQ(table.casino_cash(), initial_cash - 3500);
}

TEST(CasinoTableTest, ResolveBetLoss) {
    CasinoTable table(100000, 10, 5000);
    Player player("TestPlayer", 1000);
    
    Bet bet = Bet::on_number(5, 200);
    int64_t initial_balance = player.balance();
    int64_t initial_cash = table.casino_cash();

    bool won = table.resolve_bet(player, bet, 10);

    EXPECT_FALSE(won);
    EXPECT_EQ(player.balance(), initial_balance - 200);
    EXPECT_EQ(table.casino_cash(), initial_cash + 200);
}