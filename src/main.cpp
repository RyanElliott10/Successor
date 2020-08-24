#include <unordered_set>

#include <ludere/data_event_subscribable.hpp>
#include <ludere/engine.hpp>
#include <ludere/exchange.hpp>

#include "data_streamer.hpp"
#include "MovingAverageStrategy.hpp"

constexpr std::string_view AAPL_CSV = "../data/aapl_daily.csv";
constexpr std::string_view TSLA_CSV = "../data/tsla_minute.csv";

int main()
{
    std::shared_ptr<lud::data_streamable> data_stream_ = std::make_shared<data_streamer>(AAPL_CSV);
    lud::exchange exchange_(data_stream_, false);
    std::shared_ptr<lud::portfolio> portfolio_ = std::make_shared<lud::portfolio>(exchange_, 1000);

    std::unordered_set<std::shared_ptr<lud::abstract_strategy>> strategies_;
    std::shared_ptr<lud::abstract_strategy> ma_strategy_ = std::make_shared<MovingAverageStrategy>(portfolio_, true);

    lud::engine engine_(exchange_, strategies_);
    std::unordered_set<std::string> securities_ = {"AAPL" };

    strategies_.insert(ma_strategy_);
    exchange_.subscribe_to_data_stream(std::make_shared<lud::data_event_subscription>(ma_strategy_, securities_));
    exchange_.subscribe_to_data_stream(std::make_shared<lud::data_event_subscription>(portfolio_, securities_));

    engine_.trade();
    portfolio_->summary();

    return 0;
}
