#include <unordered_set>

#include <ludere/IDataEventSubscriber.hpp>
#include <ludere/Engine.hpp>
#include <ludere/Exchange.hpp>

#include "MovingAverageStrategy.hpp"

#define AAPL_CSV "../data/aapl-daily.csv"

int main()
{
    lud::Exchange exchange(AAPL_CSV, false);
    lud::Portfolio portfolio(exchange, 1000);

    std::unordered_set<std::shared_ptr<lud::AbstractStrategy>> strategies;
    std::shared_ptr<lud::AbstractStrategy> maStrat = std::make_shared<MovingAverageStrategy>(portfolio, true);

    lud::Engine engine(exchange, strategies);

    strategies.insert(maStrat);
    std::unordered_set<std::string> securities = {"AAPL"};
    exchange.subscribeToDataStream(std::make_shared<lud::DataEventSubscription>(maStrat, securities));

    engine.trade();

    return 0;
}
