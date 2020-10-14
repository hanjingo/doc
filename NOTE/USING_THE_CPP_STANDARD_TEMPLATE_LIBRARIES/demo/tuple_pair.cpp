#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <map>
#include <vector>
#include <tuple>
#include <algorithm>

using std::string;
using Name = std::pair<string, string>;
using DOB = std::tuple<size_t, size_t, size_t>;
using Details = std::tuple<DOB, size_t, string>;

using Element_type = std::map<Name, Details>::value_type;
using People = std::map<Name, Details>;

void list_DOB_Job(const People& people)
{
    DOB dob;
    string occupation {};
    std::cout << '\n';
    for(auto iter = std::begin(people); iter != std::end(people); ++iter)
    {
        std::tie(dob, std::ignore, occupation) = iter->second;
        std::cout << std::setw(20) << std::left << (iter->first.first + " " + iter->first.second)
                  << "DOB: " << std::right << std::setw(2) << std::setfill('0') << std::get<1>(dob)
                  << "-" << std::setw(4) << std::get<2>(dob) << std::setfill(' ')
                  << " Occupation: " << occupation << std::endl;
    }
}

template<typename Compare>
void list_sorted_people(const People& people, Compare comp)
{
    std::vector<Element_type*> folks;
    for(const auto& pr : people)
        folks.push_back(&pr)
    
    auto ptr_comp = 
    [&comp](const Element_type* pr1, const Element_type* pr2)->bool{return comp(*pr1, *pr2);};

    std::sort(std::begin(folks), std::end(folks), ptr_comp);
    DOB dob {};
    size_t height {};
    string occupation {};
    std::cout << '\n';

    for(const auto& p : folks)
    {
        std::tie(dob, height, occupation) = p->second;
        std::cout << std::setw(20) << std::left << (p->first.first + " " + p->first.second)
                  << "DOB: " << std::right << std::setw(2) << std::get<0>(dob) << "-"
                  << std::setw(2) << std::setfill('0') << std::get<1>(dob) << "-"
                  << " Height: " << height << " Occupation: " << occupation << std::endl;
    }
}

void get_people(People& people)
{
    string first {}, second {};
    size_t month {}, day {}, year {};
    size_t height {};
    string occupation {};
    char answer ('Y');

    while(std::toupper(answer) == 'Y')
    {
        std::cout << "Enter a first name and a second name: ";
        std::cin >> std::ws >> first >> second;

        std::cout << "Enter date of birth as month day year (integers): ";
        std::cin >> month >> day >> year;
        DOB dob {month, day, year};

        std::cout << "Enter height in inches: ";
        std::cin >> height;

        std::cout << "Enter occupation: ";
        std::getline(std::cin >> std::ws, occupation, '\n');
        people.emplace(
            std::make_pair(Name {first, second}, std::make_tuple(dob, height, occupation))
        );

        std::cout << "Do you want to enter another(Y or N): ";
        std::cin >> answer;
    }
}

int main()
{
    std::map<Name, Details> people;
    get_people(people);

    std::cout << "\nThe DOB & jobs are: \n";
    list_DOB_Job(people);

    auto comp = [](const Element_type& pr1, const Element_type& pr2)
    {
        return std::get<1>(pr1.second) < std::get<1>(pr2.second);
    };

    std::cout << "\nThe people in height order are: \n";
    list_sorted_people(people, comp);
}