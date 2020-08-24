//
// Created by Ryan Elliott on 7/31/20.
//

#include <ludere/order.hpp>

#include "MovingAverageStrategy.hpp"

void MovingAverageStrategy::trade()
{
    abstract_strategy::trade();
}

void MovingAverageStrategy::prepare_to_trade()
{

}

void MovingAverageStrategy::notify_of_market_event(lud::market_event &event)
{

}

void MovingAverageStrategy::handle_market_data(const std::unordered_map<std::string, lud::candlestick_data> &data)
{
    m_historicalData.push_back(data.at("AAPL"));
    float sum = 0;
    for (size_t i = m_historicalData.size()-1; i > (m_historicalData.size() - 50) && i > 0; i--) {
        sum += m_historicalData[i].m_close;
    }
    float movingAverage = sum / 50;
    std::cout << "Moving Average: " << movingAverage << std::endl;

    if (data.at("AAPL").m_close <= movingAverage * 0.75 && movingAverage > 0) {
        lud::order_lifetime lifetime(lud::order_lifetime::order_lifetime_durations::DAY, data.at("AAPL").m_timestamp);
        place_limit_order("AAPL", 1, lud::order::order_signals::BUY, lud::order::position_types::LONG, lifetime,
                          data.at("AAPL").m_close);
    } else if (data.at("AAPL").m_close >= movingAverage * 1.5 && movingAverage > 0) {
//        lud::order_lifetime lifetime(lud::order_lifetime::order_lifetime_durations::DAY, data.at("AAPL").timestamp);
//        placeLimitOrder("AAPL", 1, lud::order::order_signal::BUY, lud::order::position_types::LONG, lifetime, data.at("AAPL").close);
    }
}

void MovingAverageStrategy::handle_concluded_order(std::shared_ptr<lud::filled_order> filledOrder)
{
    if (filledOrder->m_order_status == lud::filled_order::filled_order_statuses::SUCCESS) {
        LUD_DEBUG("order concluded: %s at: $%.2f per share", filledOrder->m_security.c_str(), filledOrder->m_share_price)
    } else if (filledOrder->m_order_status == lud::filled_order::filled_order_statuses::INSUFFICIENT_FUNDS) {
        LUD_DEBUG("order unable to be completed due to insufficient funds: %s at %f", filledOrder->m_security.c_str(),
                  filledOrder->m_share_price);
    } else if (filledOrder->m_order_status == lud::filled_order::filled_order_statuses::EXPIRED) {
        LUD_DEBUG("order expired: %s at %d", filledOrder->m_security.c_str(), filledOrder->m_timestamp);
    }
}