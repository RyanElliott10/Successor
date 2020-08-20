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

}

void MovingAverageStrategy::notifyOfMarketEvent(lud::MarketEvent &event)
{

}

void MovingAverageStrategy::handleMarketData(const std::unordered_map<std::string, lud::CandlestickData> &data)
{
    if (data.at("TSLA").close * 1.01 <= 225) {
        lud::OrderLifetime lifetime(lud::OrderLifetime::Duration::kDay, data.at("TSLA").timestamp);
        placeLimitOrder("TSLA", 1, lud::Order::PositionType::kLongPosition, lifetime, data.at("TSLA").close);
    }
}

void MovingAverageStrategy::handleConcludedOrder(std::shared_ptr<lud::FilledOrder> filledOrder)
{
    if (filledOrder->orderStatus == lud::FilledOrder::FilledOrderStatus::kSuccess) {
        LUD_DEBUG("Order concluded: %s at: $%.2f per share", filledOrder->security.c_str(), filledOrder->sharePrice)
    } else if (filledOrder->orderStatus == lud::FilledOrder::FilledOrderStatus::kInsufficientFunds) {
        LUD_DEBUG("Order unable to be completed due to insufficient funds: %s at %f", filledOrder->security.c_str(),
                  filledOrder->sharePrice);
    } else if (filledOrder->orderStatus == lud::FilledOrder::FilledOrderStatus::kExpired) {
        LUD_DEBUG("Order expired: %s at %d", filledOrder->security.c_str(), filledOrder->timestamp);
    }
}