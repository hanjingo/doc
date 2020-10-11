#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <deque>
using std::string;

void show(const std::deque<string>& words, size_t count = 5)
{
    if(words.empty()) return;
    auto max_len = std::max_element(std::begin(words), std::end(words), 
        [](const string& s1, const string& s2){return s1.size() < s2.size();})->size();
}