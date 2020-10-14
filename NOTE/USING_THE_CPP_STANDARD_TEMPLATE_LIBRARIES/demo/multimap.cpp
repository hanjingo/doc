#include <iostream>
#include <string>
#include <map>
#include <cctype>

using std::string;
using Pet_type = string;
using Pet_name = string;

int main()
{
    std::multimap<Pet_type, Pet_name> pets;
    Pet_type type {};
    Pet_name name {};
    char more {'Y'};
    while(std::toupper(more) == 'Y')
    {
        std::cout << "Enter the type of your pet and its name: ";
        std::cin >> std::ws >> type >> name;
        auto iter = pets.lower_bound(type);
        if(iter != std::end(pets))
            pets.emplace_hint(iter, type, name);
        else
            pets.emplace(type, name);

        std::cout << "Do you want to enter another(Y or N)? ";
        std::cin >> more;
    }
    
    std::cout << "\nPet list by type:\n";
    auto iter = std::begin(pets);
    while(iter != std::end(pets))
    {
        auto pr = pets.equal_range(iter->first);
        std::cout << "\nPets of type " << iter->first << " are:\n";
        for(auto p = pr.first; p != pr.second; ++p)
        std::cout << " " << p->second;
        std::cout << std::endl;
        iter = pr.second;
    }
}