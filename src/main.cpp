#include <iostream>
#include <string>
#include "player.hpp"
#include "table.hpp"
#include "bet.hpp"
#include "game_service.hpp"
#include "logger.hpp"
#include <fstream>
#include <vector>

void saveResultsToFile(const std::string& filename, const std::vector<double>& balances) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка открытия файла для записи!" << std::endl;
        return;
    }
    
    for (size_t i = 0; i < balances.size(); ++i) {
        outFile << i << " " << balances[i] << "\n";
    }
    outFile.close();
    std::cout << "Результаты успешно сохранены в " << filename << std::endl;
}

int main() {
    std::setlocale(LC_ALL, "Russian");

    LOG_INF("Запуск симулятора казино...");

    std::string player_name;
    std::cout << "Введите имя игрока: ";
    std::cin >> player_name;

    int64_t initial_balance = 0;
    std::cout << "Введите начальный баланс (руб.): ";
    std::cin >> initial_balance;

    Player player(player_name, initial_balance);

    CasinoTable table(1000000, 10, 50000); 
    GameService game_service(table);

    std::vector<double> balance_history;
    balance_history.push_back(static_cast<double>(player.balance()));

    int choice = 0;
    do {
        std::cout << " Игрок: " << player.id() 
                  << " | Баланс: " << player.balance() << " руб.\n";
        std::cout << "1. Сделать ставку на число (0-36)\n";
        std::cout << "2. Сделать ставку на цвет (Красный/Черный/Зеленый)\n";
        std::cout << "3. Выйти из казино\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        if (choice == 1) {
            int64_t amount = 0;
            int target_number = -1;

            std::cout << "Введите сумму ставки: ";
            std::cin >> amount;

            std::cout << "На какое число ставите (от 0 до 36): ";
            std::cin >> target_number;

            try {
                Bet bet = Bet::on_number(target_number, amount);

                std::cout << "\nКрутим колесо рулетки...\n";
                int rolled_number = game_service.play_round(player, bet);
                
                std::cout << ">>> Выпало число: " << rolled_number << " <<<\n";
                std::cout << "Текущий баланс: " << player.balance() << " руб.\n";

                balance_history.push_back(static_cast<double>(player.balance()));

            } catch (const std::exception& e) {
                std::cout << "[ОШИБКА СТАВКИ]: " << e.what() << "\n";
            }

        } else if (choice == 2) {
            int64_t amount = 0;
            int color_choice = 0;

            std::cout << "Введите сумму ставки: ";
            std::cin >> amount;

            std::cout << "Выберите цвет:\n";
            std::cout << "1. Красный (RED)\n";
            std::cout << "2. Черный (BLACK)\n";
            std::cout << "3. Зеленый (GREEN)\n";
            std::cout << "Ваш выбор цвета: ";
            std::cin >> color_choice;

            Color chosen_color = Color::RED;
            if (color_choice == 1) {
                chosen_color = Color::RED;
            } else if (color_choice == 2) {
                chosen_color = Color::BLACK;
            } else if (color_choice == 3) {
                chosen_color = Color::GREEN;
            } else {
                std::cout << "Неверный выбор цвета! Попробуйте снова.\n";
                continue;
            }

            try {
                Bet bet = Bet::on_color(chosen_color, amount);

                std::cout << "\nКрутим колесо рулетки (ставка на цвет)...\n";
                int rolled_number = game_service.play_round(player, bet);
                
                std::cout << ">>> Выпало число: " << rolled_number << " <<<\n";
                std::cout << "Текущий баланс: " << player.balance() << " руб.\n";

                balance_history.push_back(static_cast<double>(player.balance()));

            } catch (const std::exception& e) {
                std::cout << "[ОШИБКА СТАВКИ]: " << e.what() << "\n";
            }

        } else if (choice != 3) {
            std::cout << "Неверный выбор. Попробуйте снова.\n";
        }

        if (player.balance() <= 0) {
            std::cout << "\nУ вас совсем не осталось денег! Игра окончена.\n";
            break;
        }

    } while (choice != 3);

    saveResultsToFile("simulation_results.txt", balance_history);

    std::cout << "\nСпасибо за игру! Ваш конечный баланс: " << player.balance() << " руб.\n";
    return 0;
}