//
// Created by Ryan Elliott on 7/31/20.
//

#include <ludere/order.hpp>

#include "moving_average_strategy.hpp"
#include "simple_moving_average.hpp"

const static std::vector<std::string> s_instrument_tickers{"AAPL", "SQ", "NVDA", "CRON", "ZM"};

void moving_average_strategy::trade()
{
    abstract_strategy::trade();
}

void moving_average_strategy::prepare_to_trade()
{

}

void moving_average_strategy::notify_of_market_event(lud::market_event &event)
{

}

void moving_average_strategy::handle_market_data(const lud::candlestick_data_aggregate<std::string> &data)
{
    update_smas(data);
    std::string interested_security_ = s_instrument_tickers[std::rand() % 4];
    lud::order_lifetime lifetime(lud::enums::order::lifetime_durations::DAY, data.at(interested_security_).m_timestamp);
    if (m_portfolio->soft_verify_capital(data.at(interested_security_).m_close)) {
        place_limit_order(interested_security_, 1, lud::enums::order::signals::BUY,
                          lud::enums::order::position_types::LONG,
                          lifetime, data.at(interested_security_).m_close);
    }
    if (std::rand() % 10 > 8 && m_portfolio->soft_verify_shares(interested_security_, 1)) {
        place_limit_order(interested_security_, 1, lud::enums::order::signals::SELL,
                          lud::enums::order::position_types::LONG,
                          lifetime, data.at(interested_security_).m_close);
    }
}

void moving_average_strategy::handle_concluded_order(std::shared_ptr<lud::filled_order> filledOrder)
{
    if (filledOrder->m_order_status == lud::enums::order::fill_statuses::INSUFFICIENT_FUNDS) {
        LUD_DEBUG("Order unable to be completed due to insufficient funds: %s at %f", filledOrder->m_security.c_str(),
                  filledOrder->m_share_price);
    } else if (filledOrder->m_order_status == lud::enums::order::fill_statuses::EXPIRED) {
        LUD_DEBUG("Order expired: %s at %d", filledOrder->m_security.c_str(), filledOrder->m_timestamp);
    }
}

void moving_average_strategy::update_smas(const lud::candlestick_data_aggregate<std::string> &data)
{
//    std::cout << data << std::endl;
}
