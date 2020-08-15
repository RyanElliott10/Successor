//
// Created by Ryan Elliott on 7/31/20.
//

#ifndef SUCCESSOR_MOVINGAVERAGESTRATEGY_HPP
#define SUCCESSOR_MOVINGAVERAGESTRATEGY_HPP


#include <ludere/AbstractStrategy.hpp>

class MovingAverageStrategy : public lud::AbstractStrategy
{
public:
    MovingAverageStrategy(lud::Portfolio &portfolio, bool currentData)
            : lud::AbstractStrategy(portfolio, currentData)
    {}

    ~MovingAverageStrategy() override = default;

    void trade() override;
    void prepareToTrade() override;
    void notifyOfMarketEvent(lud::MarketEvent &event) override;
    void handleMarketData(lud::CandlestickData &data) override;
    void handleConcludedOrder(std::shared_ptr<lud::FilledOrder> ) override;
};


#endif //SUCCESSOR_MOVINGAVERAGESTRATEGY_HPP
