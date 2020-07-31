#include <iostream>
#include <ludere/Exchange.hpp>

int main()
{
    std::unique_ptr<lud::Exchange> exchange = std::unique_ptr<lud::Exchange>(new lud::Exchange());
    return 0;
}
