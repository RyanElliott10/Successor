#include <unordered_set>

#include <ludere/IDataEventSubscriber.hpp>
#include <ludere/Engine.hpp>
#include <ludere/Exchange.hpp>

#include "DataStreamer.hpp"
#include "MovingAverageStrategy.hpp"

constexpr std::string_view AAPL_CSV = "../data/aapl_daily.csv";
constexpr std::string_view TSLA_CSV = "../data/tsla_minute.csv";

int main()
{
    std::shared_ptr<DataStreamer> dataStream = std::make_shared<DataStreamer>(TSLA_CSV);
    lud::Exchange exchange(dataStream, false);
    std::shared_ptr<lud::Portfolio> portfolio = std::make_shared<lud::Portfolio>(exchange, 1000);

    std::unordered_set<std::shared_ptr<lud::AbstractStrategy>> strategies;
    std::shared_ptr<lud::AbstractStrategy> maStrategy = std::make_shared<MovingAverageStrategy>(portfolio, true);

    lud::Engine engine(exchange, strategies);
    std::unordered_set<std::string> securities = { "TSLA" };

    strategies.insert(maStrategy);
    exchange.subscribeToDataStream(std::make_shared<lud::DataEventSubscription>(maStrategy, securities));
    exchange.subscribeToDataStream(std::make_shared<lud::DataEventSubscription>(portfolio, securities));

    engine.trade();
    std::cout << portfolio->netValue() << std::endl;

    return 0;
}
