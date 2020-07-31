#include <iostream>

#include <ludere/Exchange.hpp>
#include <memory>

int main()
{
    std::cout << "This is a demonstration of how to use Ludere" << std::endl;
    std::unique_ptr<lud::Exchange> exchange = std::make_unique<lud::Exchange>();
    return 0;
}
