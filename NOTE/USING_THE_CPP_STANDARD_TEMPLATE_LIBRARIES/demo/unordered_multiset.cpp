#include <string>
#include <ostream>
#include <istream>
#include <unordered_set>
#include <algorithm>
#include <vector>
#include <iostream>
#include <iomanip>

using std::string;
using Names = std::unordered_multiset<Name, Hash_Name>;

class Name
{
private:
    string first {};
    string second {};

public:
    Name(const string& name1, const string& name2) : first(name1), second(name2){}
    Name() = default;

    const string& get_first() const { return first; }
    const string& get_second() const { return second; }

    size_t get_length() const { return first.length() + second.length() + 1; }
    bool operator<(const Name& name) const
    {
        return second < name.second || (second == name.second && first < name.first);
    }

    bool operator==(const Name& name) const
    {
        return (second == name.second) && (first == name.first);
    }

    size_t hash() const { return std::hash<std::string>()(first+second); }

    friend std::istream& operator>>(std::istream& in, Name& name);
    friend std::ostream& operator<<(std::ostream& out, const Name& name);
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

class Hash_Name
{
public:
    size_t operator()(const Name& name) { return name.hash(); }
};

void make_friends(Names& names) {
    std::vector<string> first_names {"John", "John", "John", "Joan", "Joan", "Jim", "Jim", "Jean"};
    std::vector<string> second_names {"Smith", "Jones", "Jones", "Hackenbush", "Szczygiel"};
    for(const auto& name1 : first_names)
        for(const auto& name2 : second_names)
            names.emplace(name1, name2);
}

void list_buckets(const Names& names)
{
    for(size_t n_bucket{}; n_bucket < names.bucket_count(); ++n_bucket)
    {
        std::cout << "Bucket " << n_bucket << ":\n";
        std::copy(names.begin(n_bucket), names.end(n_bucket), std::ostream_iterator<Name>(std::cout, " "));
        std::cout << std::endl;
    }
}

int main()
{
    Names pals {8};
    pals.max_load_factor(8.0);
    make_friends(pals);
    list_buckets(pals);

    Name js {"John", "Smith"};
    std::cout << "\nThere are " << pals.count(js) << " " << js << "'s.\n" << std::endl;

    pals.erase(Name{"John", "Jones"});

    while(true)
    {
        auto iter = std::find_if(std::begin(pals), std::end(pals),
            [](const Name& name){return name.get_second() == "Hackenbush"; });

        if(iter == std::end(pals))
            break;
        pals.erase(iter);
    }

    size_t max_length{};
    std::for_each(std::begin(pals), std::end(pals),
        [&max_length](const Name name){max_length = std::max(max_length, name.get_length()); });

    size_t count {};
    size_t perline {6};
    for(const auto& pal : pals)
    {
        std::cout << std::setw(max_length+2) << std::left << pal;
        if((++count % perline) == 0) std::count << "\n";
    }
    std::cout << std::endl;
}