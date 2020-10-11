#include <queue>
#include <memory>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <random>

using std::string;
using distribution = std::uniform_int_distribution<>;
using PCheckout = std::unique_ptr<Checkout>;

class Customer
{
private:
    size_t service_t {};
public:
    explicit Customer(size_t st = 10) : service_t {st}{}

    Customer& time_decrement()
    {
        if(service_t > 0)
            --service_t;
        return *this;
    }
    bool done() const { return service_t == 0; }
};

using PCustomer = std::unique_ptr<Customer>;

class Checkout
{
private:
    std::queue<PCustomer> customers;

public:
    void add(PCustomer&& customer) { customers.push(std::move(customer)); }
    size_t qlength() const { return customers.size(); }

    void time_increment()
    {
        if(customers.front()->time_decrement().done())
            customers.pop();
    };

    bool operator<(const Checkout& other) const { return qlength() < other.qlength(); }
    bool operator>(const Checkout& other) const { return qlength() < other.qlength(); }
};

void histogram(const std::vector<int>& v, int min)
{
    string bar (60, '*');
    for(size_t i {}; i < v.size(); ++i)
    {
        std::cout << std::setw(3) << i+min << " " << std::setw(4) << v[i] << " "
                  << bar.substr(0, v[i]) << (v[i] > static_cast<int>(bar.size()) ? "..." : "")
                  << std::endl;
    }
}

int main()
{
    std::random_device random_n;

    int service_t_min {2}, service_t_max {15};
    std::uniform_int_distribution<> service_t_d {service_t_min, service_t_max};

    int min_customers {15}, max_customers {20};
    distribution n_1st_customers_d {min_customers, max_customers};

    int min_arr_interval {1}, max_arr_interval {5};
    distribution arrival_interval_d {min_arr_interval, max_arr_interval};
    size_t n_checkouts {};
    std::cout << "Enter the number of checkouts in the supermarket: ";
    std::cin >> n_checkouts;
    if(!n_checkouts)
    {
        std::cout << "Number of checkouts must be greater than 0. Setting to 1. " << std::endl;
        n_checkouts = 1;
    }

    std::vector<PCheckout> checkouts;
    checkouts.reserve(n_checkouts);

    for(size_t i {}; i < n_checkouts; ++i)
        checkouts.push_back(std::make_unique<Checkout>());
    std::vector<int> service_times(service_t_max-service_t_min+1);

    int count {n_1st_customers_d(random_n)};
    std::cout << "Customers waiting at store opening: " << count << std::endl;
    int added {};
    int service_t {};

    auto comp = [](const PCheckout& pc1, const PCheckout& pc2){ return *pc1 < *pc2; };
    while(added++ < count)
    {
        service_t = service_t_d(random_n);
        auto iter = std::min_element(std::begin(checkouts), std::end(checkouts), comp);
        (*iter)->add(std::make_unique<Customer>(service_t));
        ++service_times[service_t - service_t_min];
    }

    size_t time {};
    const size_t total_time {600};
    size_t longest_q {};

    int new_cust_interval { arrival_interval_d(random_n) };

    while(time < total_time)
    {
        ++time;

        if(--new_cust_interval == 0)
        {
            service_t = service_t_d(random_n);
            (*std::min_element(std::begin(checkouts),
                std::end(checkouts), comp))->add(std::make_unique<Customer>(service_t));
            ++service_times[service_t - service_t_min];
            for(auto& pcheckout : checkouts)
                longest_q = std::max(longest_q, pcheckout->qlength());
            new_cust_interval = arrival_interval_d(random_n);
        }
        for(auto& pcheckout : checkouts)
            pcheckout->time_increment();
    }

    std::cout << "Maximum queue length = " << longest_q << std::endl;
    std::cout << "\nHistogram of service times:\n";
    histogram(service_times, service_t_min);

    std::cout << "\nTotal number of customers today: "
              << std::accumulate(std::begin(service_times), std::end(service_times), 0) << std::endl;
}