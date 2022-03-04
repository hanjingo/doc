#ifndef CHECKOUT_H
#define CHECKOUT_H
#include <queue>
#include "Customer.h"

class Checkout
{
private:
    std::queue<Customer> customers;

public:
    void add(const Customer& customer) { customers.push(customer); }
    size_t qlength() const { return customers.size(); }

    void time_increment()
    {
        if (!customers.empty())
        {
            if (customers.front().time_decrement().done())
                customers.pop();
        }
    };

    bool operator<(const Checkout& other) const { return qlength() < other.qlength(); }
    bool operator>(const Checkout& other) const { return qlength() > other.qlength(); }
};

#endif