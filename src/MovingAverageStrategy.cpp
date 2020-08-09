//
// Created by Ryan Elliott on 7/31/20.
//

#include <ludere/Order.hpp>

#include "MovingAverageStrategy.hpp"

void MovingAverageStrategy::notifyOfMarketEvent(lud::MarketEvent &event)
{

}

void MovingAverageStrategy::handleMarketData(lud::CandlestickData &data)
{
    std::cout << data.ticker << " " << data << std::endl;
    placeLimitOrder(data.ticker, 2, lud::Order::PositionType::kLongPosition, data.low);
}

void MovingAverageStrategy::trade()
{
    AbstractStrategy::trade();
}

void MovingAverageStrategy::prepareToTrade()
{
    // Subscribe to an Exchange SSE feed, etc.
}