#include <iostream>
#include <cctype>
#include <map>
#include <string>
#include "Quotations.h"
#include "Name.h"

using std::string;

inline Name get_name()
{
    Name name{};
    std::cout << "Enter first name and second name:";
    std::cin >> std::ws >> name;
    return name;
}

inline string get_quote(const Name& name)
{
    std::cout << "Enter the quotation for " << name << ". Enter * to end:\n";
    string quote;
    std::getline(std::cin >> std::ws, quote, '*');
    return quote;
}

int main()
{
    std::map<Name, Quotations> Quotations;
    std::cout << "Enter 'A' to add a quote."
                 "\nEnter 'L' to list all quotes."
                 "\nEnter 'G' to get quote."
                 "\nEnter 'Q' to end.\n";
    Name name{};
    string quote{};
    char command{};

    while (command != 'Q')
    {
        std::cout << "\nEnter command: ";
        std::cin >> command;
        command = static_cast<char>(std::toupper(command));
        switch(command)
        {
        case 'Q':
            break;

        case 'A':
            name = get_name();
            quote = get_quote(name);
            Quotations[name] << quote;
            break;

        case 'G':
            name = get_name();
            const auto& quotes = quotations[name];
            size_t count = quotes.size();
            if (!count)
            {
                std::cout << "There are no quotes recorded for "
                          << name << std::endl;
                continue;
            }
            size_t index{};
            if (count > 1)
            {
                std::cout << "There are " << count << " quotes for " << name << ".\n"
                          << "Enter an index from 0 to " << count - 1 << ": ";
                std::cin >> index;
            }
            std::cout << quotations[name][index] << std::endl;
            break;

        case 'L':
            if (quotations.empty())
            {
                std::cout << "\nNo quotations recorded for anyone." << std::endl;
            }
            for (const auto& pr : Quotations)
            {
                std::count << '\n' << pr.first << std::endl;
                for (const auto& quote : pr.second)
                    std::cout << " " << quote << std::endl;
            }
            break;

        default:
            std::cout << " Command must be 'A', 'G', 'L', or 'Q'. Try again.\n";
            continue;
            break;
        }
    }
}