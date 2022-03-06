#ifndef QUOTATIONS_H
#define QUOTATIONS_H
#include <vector>
#include <string>
#include <exception>

class Quotations
{
private:
    std::vector<std::string> quotes;

public:
    Quotations& operator<<(const char* quote)
    {
        quotes.emplace_back(quote);
        return *this;
    }

    Quotations& operator<<(const std::string& quote)
    {
        quotes.push_back(quote);
        return *this;
    }

    Quotations& operator<<(std::string&& quote)
    {
        quotes.push_back(std::move(quote));
        return *this;
    }

    std::string& operator[](size_t index)
    {
        if (index < quotes.size())
            return quotes[index];
        else
            throw std::out_of_range{"Invalid index to quotations."};
    }

    size_t size() const { return quotes.size(); }

    std::vector<std::string>::iterator begin()
    {
        return std::begin(quotes);
    }

    std::vector<std::string>::const_iterator begin() const
    {
        return std::begin(quotes);
    }

    std::vector<std::string>::iterator end()
    {
        return std::end(quotes);
    }

    std::vector<std::string>::const_iterator end() const
    {
        return std::end(quotes);
    }
};

#endif