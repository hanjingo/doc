#include <algorithm>
#include <numeric>
#include <iostream>
#include <vector>

#include <exception>
#include <iterator>
#include <type_traits>
#include <utility>
using namespace std::rel_ops;

template <typename T> 
class Numeric_Iterator; // 自定义迭代器

template<typename T>
class Numeric_Range
{
    static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value,
                  "Numeric_Range type argument must be numeric.");
    friend class Numeric_Iterator <T>;

private:
    T start;
    T step;
    size_t count;

public:
    explicit Numeric_Range(T first = 0, T incr = 1, size_t n = 2) : start{first}, step{incr}, count{n} {}
    Numeric_Iterator<T> begin() { return Numeric_Iterator<T>(*this); }
    Numeric_Iterator<T> end()
    {
        Numeric_Iterator<T> end_iter(*this);
        end_iter.value = start + count * step;
        return end_iter;
    }
};

template<typename T>
class Numeric_Iterator : public std::iterator<std::forward_iterator_tag, T>
{
    friend class Numeric_Range <T>;
private:
    Numeric_Range<T>& range;
    T value;

public:
    explicit Numeric_Iterator(Numeric_Range<T>& a_range) : range{a_range}, value{a_range.start} {}

    Numeric_Iterator& operator=(const Numeric_Iterator& src)
    {
        range = src.range;
        value = src.value;
    }

    T& operator* ()
    {
        if (value == static_cast<T>(range.start + range.count * range.step))
            throw std::logic_error("Cannot dereference an end iterator.");
        return value;
    }

    Numeric_Iterator& operator++()
    {
        if (value == static_cast<T>(range.start + range.count * range.step))
        {
            throw std::logic_error("Cannot increment an end iterator.");
        }
        value += range.step;
        return *this;
    }

    Numeric_Iterator operator++(int)
    {
        if (value == static_cast<T>(range.start + range.count * range.step))
        {
            throw std::logic_error("Cannot increment an end iterator.");
        }
        auto temp = *this;
        value += range.step;
        return temp;
    }

    bool operator<(const Numeric_Iterator& iter) const { return value < iter.value; }
    bool operator==(const Numeric_Iterator& iter) const { return value == iter.value; }
    bool operator!=(const Numeric_Iterator& iter) const { return value != iter.value; }
    bool operator>(const Numeric_Iterator& iter) const { return value > iter.value; }
    bool operator<=(const Numeric_Iterator& iter) const { *this < iter || *this == iter; }
    bool operator>=(const Numeric_Iterator& iter) const { *this > iter || *this == iter; }
};

int main()
{
    Numeric_Range<double> range{1.5, 0.5, 5};
    auto first = range.begin();
    auto last = range.end();
    std::copy(first, last, std::ostream_iterator<double>(std::cout, " "));
    std::cout << "\nSum = " << std::accumulate(std::begin(range), std::end(range), 0.0) << std::endl;

    // 初始化
    Numeric_Range<long> numbers{15L, 4L, 10};
    std::vector<long> data{std::begin(numbers), std::end(numbers)};
    std::cout << "\nValues in vector are:\n";
    std::copy(std::begin(data), std::end(data), std::ostream_iterator<long>(std::cout, " "));
    std::cout << std::endl;

    // 列出range中的元素
    std::cout << "\nThe values in the numbers range are:\n";
    for (auto n : numbers)
        std::cout << n << " ";
    std::cout << std::endl;
}