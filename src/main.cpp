#include <unordered_set>

#include <ludere/data_event_subscribable.hpp>
#include <ludere/engine.hpp>
#include <ludere/exchange.hpp>

#include "datastreamer.hpp"
#include "moving_average_strategy.hpp"

constexpr std::string_view AAPL_CSV = "../data/aapl_daily.csv";
constexpr std::string_view SQ_CSV = "../data/sq_daily.csv";
constexpr std::string_view TSLA_CSV = "../data/tsla_minute.csv";

int main()
{
  const std::unordered_map<std::string, std::string_view> csvs = {
          std::make_pair("AAPL", AAPL_CSV), std::make_pair("SQ", SQ_CSV)
  };
  std::shared_ptr<lud::datastreamable> datastream_ = std::make_shared<datastreamer>(csvs);
  lud::exchange exchange_(datastream_, false);
  std::shared_ptr<lud::portfolio> portfolio_ = std::make_shared<lud::portfolio>(exchange_, 500);

  lud::brokerage_fees brokerage_fees_(3.0f);
  portfolio_->set_brokerage_fees(brokerage_fees_);

  std::unordered_set<std::shared_ptr<lud::abstract_strategy>> strategies_;
  std::shared_ptr<lud::abstract_strategy> ma_strategy_ = std::make_shared<moving_average_strategy>(portfolio_, true);

  lud::engine engine_(exchange_, strategies_);
  std::unordered_set<std::string> securities_ = {"SQ"};

  strategies_.insert(ma_strategy_);
  exchange_.subscribe_to_datastream(std::make_shared<lud::data_event_subscription>(ma_strategy_, securities_));
  exchange_.subscribe_to_datastream(std::make_shared<lud::data_event_subscription>(portfolio_, securities_));

  engine_.trade();
  portfolio_->summary();

  return 0;
}
