#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>
using std::string;
using std::vector;

int main() {
    vector<string> words;
    words.reserve(10);
    std::cout << "Enter words separated by space. Enter Ctrl+Z on a separate line to end:"
                << std::endl;
    std::copy(std::istream_iterator<string> {std::cin}, std::istream_iterator<string> {},
            std::back_inserter{words});
    std::cout << "Starting sort." << std::endl;
    bool out_of_order {false};
    auto last = std::end(words);
    while(true)
    {
        for (auto first = std::begin(words) + 1; first != last; ++first)
        {
            if(*(first - 1) > *first)
            {
                std::swap(*first, *(first - 1));
                out_of_order = true;
            }
        }
        if(!out_of_order)
            break;
        out_of_order = false;
    }

    std::cout << "your words in ascending sequence:" << std::endl;
    std::copy(std::begin(words), std::end(words), std::ostream_iterator<string> {std::cout, " "});
    std::cout << std::endl;

    vector<string> words_copy {std::make_move_iterator(std::begin(words)),
                                std::make_move_iterator(std::end(words))};
    std::cout << "\nAfter moving elements from words, words_copy contains:" << std::endl;
    std::copy(std::begin(words_copy), std::end(words_copy),
                std::ostream_iterator<string> {std::cout, " "});
    std::cout << std::endl;

    std::cout << "\nwords vector has " << words.size() << " elements\n";
    if(words.front().empty())
        std::cout << "First element is empty string object." << std::endl;
    std::cout << "First element is \"" << words.front() << "\"" << std::endl;
}