#pragma once

#include <vector>

double daily_return(double close_price_today, double close_price_yesterday);
double momentum_factor(const std::vector<double>& close_prices, int look_back_period);