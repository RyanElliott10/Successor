//
// Created by Ryan Elliott on 7/31/20.
//

#include "MovingAverageStrategy.hpp"

void MovingAverageStrategy::notifyOfMarketEvent(lud::MarketEvent &event)
{

}

void MovingAverageStrategy::handleMarketData(lud::CandlestickData &data)
{
    AbstractStrategy::handleMarketData(data);
    std::cout << data << std::endl;
}

void MovingAverageStrategy::trade()
{
    AbstractStrategy::trade();
}
