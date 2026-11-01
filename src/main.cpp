#include <iostream>
#include <exception>
#include "player.hpp"
#include "bet.hpp"
#include "table.hpp"
#include "game_service.hpp"
#include "logger.hpp"

int main() {
    std::setlocale(LC_ALL, "Russian");

    LOG_INF("Запуск симулятора казино...");

    try {

        Player player("Player_777", 10000);
        LOG_INF("Игрок создан: Имя = %s, Баланс = %lld", player.id().c_str(), player.balance());

        CasinoTable table(100000, 100, 5000);
        LOG_INF("Стол казино открыт. Касса стола = %lld, Лимиты: [%lld - %lld]", 
                table.casino_cash(), table.min_bet(), table.max_bet());

        GameService game_service(table);

        LOG_INF("Раунд 1: Ставка на число 17: ");
        Bet bet1 = Bet::on_number(17, 500);

        if (table.validate_bet(bet1, player)) {
            int rolled1 = game_service.play_round(player, bet1);
            LOG_INF("Колесо рулетки остановилось. Выпало число: %d", rolled1);
            LOG_INF("Текущий баланс игрока: %lld | Касса казино: %lld", player.balance(), table.casino_cash());
        } else {
            LOG_ERR("Ставка отклонена правилами стола или балансом игрока!");
        }

        std::cout << "\n----------------------------------------\n\n";

        LOG_INF("Раунд 2: Ставка на КРАСНЫЙ цвет: ");
        Bet bet2 = Bet::on_color(Color::RED, 1000);

        if (table.validate_bet(bet2, player)) {
            int rolled2 = game_service.play_round(player, bet2);
            LOG_INF("Колесо рулетки остановилось. Выпало число: %d", rolled2);
            LOG_INF("Текущий баланс игрока: %lld | Касса казино: %lld", player.balance(), table.casino_cash());
        } else {
            LOG_ERR("Ставка отклонена правилами стола или балансом игрока!");
        }

        LOG_INF("Игра завершена.");

    } catch (const std::exception& e) {
        LOG_ERR("Произошла критическая ошибка: %s", e.what());
        return 1;
    }

    return 0;
}