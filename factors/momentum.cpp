#include "momentum.h"

double daily_return(double close_price_today, double close_price_yesterday) {
    return (close_price_today - close_price_yesterday) / close_price_yesterday;
}

double momentum_factor(const std::vector<double>& close_prices, int look_back_period) {
    if (close_prices.size() < look_back_period + 1) {
        std::cerr << "Not enough data for the look-back period.\n";
        return 0.0;
    }

    double total_return = 0.0;
    for (int i = close_prices.size() - 1; i >= close_prices.size() - look_back_period; --i) {
        total_return += daily_return(close_prices[i], close_prices[i - 1]);
    }

    return total_return / look_back_period;
}