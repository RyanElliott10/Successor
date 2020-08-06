#include <unordered_set>

#include <ludere/Engine.hpp>
#include <ludere/Exchange.hpp>

#include "MovingAverageStrategy.hpp"

#define AAPL_CSV "../data/aapl-daily.csv"

int main()
{
    lud::Exchange exchange(AAPL_CSV, false);
    lud::Portfolio portfolio(exchange, 100, 100);

    std::unordered_set<std::unique_ptr<lud::AbstractStrategy>> strategies;
    std::unique_ptr<lud::AbstractStrategy> maStrat = std::make_unique<MovingAverageStrategy>(portfolio, true);
    strategies.insert(std::move(maStrat));

    lud::Engine engine(exchange, strategies);
    engine.trade();

    return 0;
}
