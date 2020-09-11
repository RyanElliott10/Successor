//
// Created by Ryan Elliott on 7/31/20.
//

#ifndef SUCCESSOR_MOVING_AVERAGE_STRATEGY_HPP
#define SUCCESSOR_MOVING_AVERAGE_STRATEGY_HPP


#include <utility>

#include <ludere/abstract_strategy.hpp>

#include "simple_moving_average.hpp"

class moving_average_strategy : public lud::abstract_strategy
{
public:
    moving_average_strategy(std::shared_ptr<lud::portfolio> portfolio, bool currentData)
            : lud::abstract_strategy(std::move(portfolio), currentData)
    {}

    ~moving_average_strategy() override = default;

    void trade() override;
    void prepare_to_trade() override;
    void notify_of_market_event(lud::market_event &event) override;
    void handle_market_data(const lud::candlestick_data_aggregate<std::string> &data) override;
    void handle_concluded_order(std::shared_ptr<lud::filled_order>) override;

    void update_smas(const lud::candlestick_data_aggregate<std::string> &data);

private:
    std::vector<lud::candlestick_data> m_historicalData;
    simple_moving_average<float, 50> m_50sma;
};


#endif //SUCCESSOR_MOVING_AVERAGE_STRATEGY_HPP
