#include "backtest.h"
#include "momentum.h"
#include <iostream>

void backtest(const std::vector<double>& close_prices, const std::vector<double>& momentum_values) {
    double portfolio_value = 10000.0; // 初始投资组合价值
    bool is_in_position = false; // 是否持有股票

    for (size_t i = 0; i < momentum_values.size(); ++i) {
        double momentum = momentum_values[i];
        if (momentum > 0 && !is_in_position) {
            is_in_position = true;
            std::cout << "Buying at " << close_prices[i] << "\n";
        } else if (momentum < 0 && is_in_position) {
            is_in_position = false;
            std::cout << "Selling at " << close_prices[i] << "\n";
        }

        if (is_in_position) {
            portfolio_value *= (1.0 + daily_return(close_prices[i], close_prices[i - 1]));
        }
    }

    std::cout << "Final portfolio value: " << portfolio_value << "\n";
}