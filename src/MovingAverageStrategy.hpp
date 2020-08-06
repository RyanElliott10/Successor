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

    void trade() override;

    void notifyOfMarketEvent(lud::MarketEvent &event) override;

    void handleMarketData(lud::CandlestickData &data) override;
};


#endif //SUCCESSOR_MOVINGAVERAGESTRATEGY_HPP
