#include <iostream>

#include <ludere/Engine.hpp>
#include <ludere/Exchange.hpp>

int main()
{
    std::cout << "This is a demonstration of how to use Ludere" << std::endl;
    std::unique_ptr<lud::Exchange> exchange = std::make_unique<lud::Exchange>();
    std::unordered_set<std::unique_ptr<lud::Strategy>> strategies;
    lud::Engine engine {
        &exchange,
        &strategies
    };
    return 0;
}
