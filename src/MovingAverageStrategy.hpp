//
// Created by Ryan Elliott on 7/31/20.
//

#ifndef SUCCESSOR_MOVINGAVERAGESTRATEGY_HPP
#define SUCCESSOR_MOVINGAVERAGESTRATEGY_HPP


#include <ludere/Strategy.hpp>

class MovingAverageStrategy : public lud::Strategy
{
public:
    void notifyOfMarketEvent(lud::MarketEvent &event) override;
};


#endif //SUCCESSOR_MOVINGAVERAGESTRATEGY_HPP
