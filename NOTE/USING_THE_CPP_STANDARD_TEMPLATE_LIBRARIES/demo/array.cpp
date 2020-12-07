#include <iostream>
#include <iomanip>
#include <array>

int main()
{
    const unsigned int min_wt {100U};
    const unsigned int max_wt {250U};
    const unsigned int wt_step {10U};
    const size_t wt_count {1 + (max_wt - min_wt) / wt_step};

    const unsigned int min_ht {48U};
    const unsigned int max_ht {84U};
    const unsigned int ht_step {2U};
    const size_t ht_count {1 + (max_ht - min_ht) / ht_step};

    const double lbs_per_kg {2.20462};
    const double ins_per_m {39.3701};

    std::array<unsigned int, wt_count> weight_lbs;
    std::array<unsigned int, ht_count> height_ins;

    for (size_t i{}, w{min_wt}; i < wt_count; w += wt_step, ++i)
    {
        weight_lbs.at(i) = w;
    }

    unsigned int h{ min_ht };
    for(auto& height : height_ins)
    {
        height = h;
        h += ht_step;
    }

    std::cout << std::setw(7) << " |";
    for (const auto& w : weight_lbs)
        std::cout << std::setw(5) << w << " |";
    std::cout << std::endl;

    double bmi {};
    unsigned int feet {};
    unsigned int inches {};
    const unsigned int inches_per_foot {12U};
    for (const auto& h : height_ins)
    {
        feet = h / inches_per_foot;
        inches = h % inches_per_foot;
        std::cout << std::setw(2) << feet << "'" << std::setw(2) << inches << "\"" << "|";
        std::cout << std::fixed << std::setprecision(1);
        for (const auto& w : weight_lbs)
        {
            bmi = h / ins_per_m;
            bmi = (w / lbs_per_kg) / (bmi*bmi);
            std::cout << std::setw(2) << " " << bmi << " |";
        }
        std::cout << std::endl;
    }
    for (size_t i {1}; i < wt_count; ++i)
        std::cout << "----------";
    std::cout << "\nBMI from 18.5 to 24.9 is normal" << std::endl;
}