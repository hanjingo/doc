#include <string>
#include <ostream>
#include <istream>
#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <cctype>

using std::string;
using std::make_pair;
using std::map;

class Name
{
private:
    std::string first {};
    std::string second {};
public:
    Name(const std::string& name1, const std::string& name2) : first (name1),second (name2) {}
    Name() = default;

    bool operator<(const Name& name) const
    {
        return second < name.second || (second == name.second && first < name.first);
    }
    friend std::istream& operator>>(std::istream& in, Name& name);
    friend std::ostream& operator<<(std::ostream& out, const Name& box);
};

inline std::istream& operator>>(std::istream& in, Name& name)
{
    in >> name.first >> name.second;
    return in;
}

inline std::ostream& operator<<(std::ostream& out, const Name& name)
{
    out << name.first + " " + name.second;
    return out;
}

using Entry = std::pair<const Name, size_t>;

Entry get_entry()
{
    std::cout << "Enter first and second names followed by the age: ";
    Name name {};
    size_t age {};
    std::cin >> name >> age;
    return make_pair(name, age);
}

void list_entries(const map<Name, size_t>& people)
{
    for(auto& entry : people)
    {
        std::cout << std::left << entry.first << std::right << entry.second << std::endl;
    }
}

int main()
{
    map<Name, size_t> people { {{"Ann", "Dante"}, 25}, {{"Bill", "Hook"}, 46},
                               {{"Jim", "Jams"}, 32}, {{"Mark", "Time"}, 32} };
    std::cout << "\nThe initial contents of the map is:\n";
    list_entries(people);

    char answer {'Y'};
    std::cout << "\nEnter a Name and age entry.\n";
    while(std::toupper(answer) == 'Y')
    {
        Entry entry {get_entry()};
        auto pr = people.insert(entry);
        if(!pr.second)
        {
            std::cout << "Key \"" << pr.first->first << "\" already present. Do you want to update the age (Y or N)?";
            std::cin >> answer;
            if(std::toupper(answer) == 'Y')
                pr.first->second = entry.second;
        }
        std::cout << "Do you want to enter another entry(Y or N)? ";
        std::cin >> answer;
    }

    std::cout << "\nThe map now contains the following entries:\n";
    list_entries(people);
}