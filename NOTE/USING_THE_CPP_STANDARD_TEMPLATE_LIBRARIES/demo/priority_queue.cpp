#include <iostream>
#include <queue>
#include <string>
using std::string;

template<typename T>
void list_pq(std::priority_queue<T> pq, size_t count = 5)
{
    size_t n {count};
    while(!pq.empty())
    {
        std::cout << pq.top() << " ";
        pq.pop();
        if(--n) continue;
        std::cout << std::endl;
        n = count;
    }
    std::cout << std::endl;
}

int main()
{
    std::priority_queue<std::string> words;
    std::string word;
    std::cout << "Enter words separated by spaces, enter Ctrl+Z on a separate line to end:\n";
    while(true)
    {
        if((std::cin >> word).eof())
            break;
        words.push(word);
    }
    std::cout << "You entered " << words.size() << " words. " << std::endl;
    list_pq(words);
}