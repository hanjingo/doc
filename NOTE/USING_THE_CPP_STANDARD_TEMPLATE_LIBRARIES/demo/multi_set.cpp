#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>
#include <iterator>
#include <cctype>

using std::string;

int main()
{
    std::cout << "Enter some text and enter * to end:\n";
    string text_in {};
    std::getline(std::cin, text_in, '*');

    std::replace_if(std::begin(text_in), std::end(text_in), [](const char& ch){return !isalpha(ch);}, ' ');
    std::istringstream text(text_in);
    std::istream_iterator<string> begin(text);
    std::istream_iterator<string> end;

    std::multiset<string> words;
    size_t max_len {};

    std::for_each(begin, end, [&max_len, &words](const string& word){
        words.emplace(word);
        max_len = std::max(max_len, word.length());
    });
    size_t per_line {4}, count {};

    for(auto iter = std::begin(words); iter != std::end(words); iter = words.upper_bound(*iter))
    {
        std::cout << std::left << std::setw(max_len + 1) << *iter << std::setw(3) << std::right << words.count(*iter) << " ";
        if(++count % per_line == 0) std::cout << std::endl;
    }
    std::cout << std::endl;
}