//
// Created by Ryan Elliott on 7/31/20.
//

#ifndef SUCCESSOR_MOVINGAVERAGESTRATEGY_HPP
#define SUCCESSOR_MOVINGAVERAGESTRATEGY_HPP


#include <ludere/abstract_strategy.hpp>
#include <utility>

class MovingAverageStrategy : public lud::abstract_strategy
{
public:
    MovingAverageStrategy(std::shared_ptr<lud::portfolio> portfolio, bool currentData)
            : lud::abstract_strategy(std::move(portfolio), currentData)
    {}

    ~MovingAverageStrategy() override = default;

    void trade() override;
    void prepare_to_trade() override;
    void notify_of_market_event(lud::market_event &event) override;
    void handle_market_data(const std::unordered_map<std::string, lud::candlestick_data> &data) override;
    void handle_concluded_order(std::shared_ptr<lud::filled_order>) override;

private:
    std::vector<lud::candlestick_data> m_historicalData;
    // TODO: Implement a custom class, pop_vector<m_type, max_size> that stores up to max_size elements and pops
    //      max_size+1 off when a new member is pushed
    std::array<float, 50> m_50movingAverageCloses;
};


#endif //SUCCESSOR_MOVINGAVERAGESTRATEGY_HPP
