#include <iostream>
#include <vector>
int main()
{
    std::vector <size_t> sizes;
    std::vector <size_t> capacities;
    size_t el_incr {10};
    size_t incr_count {4 * el_incr};

    for (size_t n_elements {}; n_elements < incr_count; n_elements += el_incr)
    {
        std::vector<int> values(n_elements);
        std::cout << "\nAppending to a vector with " << n_elements << " initial elements:\n";
        sizes.push_back(values.size());
        size_t space {values.capacity()};
        capacities.push_back(space);

        size_t count {};
        size_t n_increases {10};
        while(count < n_increases)
        {
            values.push_back(22);
            if(space < values.capacity())
            {
                space = values.capacity();
                capacities.push_back(space);
                sizes.push_back(values.size());
                ++count;
            }
        }
        std::cout << "Size/Capacity: ";
        for (size_t i {}; i < sizes.size(); ++i)
            std::cout << sizes.at(i) << "/" << capacities.at(i) << " ";
        std::cout << std::endl;
        sizes.clear();
        capacities.clear();
    }
}