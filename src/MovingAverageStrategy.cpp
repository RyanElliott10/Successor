//
// Created by Ryan Elliott on 7/31/20.
//

#include <ludere/Order.hpp>

#include "MovingAverageStrategy.hpp"

void MovingAverageStrategy::trade()
{
    AbstractStrategy::trade();
}

void MovingAverageStrategy::prepareToTrade()
{
    // Subscribe to an Exchange SSE feed, etc.
}

void MovingAverageStrategy::notifyOfMarketEvent(lud::MarketEvent &event)
{

}

void MovingAverageStrategy::handleMarketData(lud::CandlestickData &data)
{
    std::cout << data.ticker << " " << data << std::endl;
    placeLimitOrder(data.ticker, 1, lud::Order::PositionType::kLongPosition, data.low);
}

void MovingAverageStrategy::handleConcludedOrder(std::shared_ptr<lud::FilledOrder> filledOrder)
{
    std::cout << "handleConcludedOrder" << std::endl;
}