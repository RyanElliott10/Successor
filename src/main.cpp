#include <unordered_set>

#include <ludere/Engine.hpp>
#include <ludere/Exchange.hpp>

#include "MovingAverageStrategy.hpp"

#define AAPL_CSV "../data/aapl-daily.csv"

int main()
{
    lud::Exchange exchange(AAPL_CSV, false);
    lud::Portfolio portfolio(exchange, 10000);

    std::unordered_set<std::shared_ptr<lud::AbstractStrategy>> strategies;
    std::shared_ptr<lud::AbstractStrategy> maStrat = std::make_shared<MovingAverageStrategy>(portfolio, true);

    lud::Engine engine(exchange, strategies);

    strategies.insert(maStrat);
    exchange.subscribeToDataStream(maStrat);

    engine.trade();

    return 0;
}
