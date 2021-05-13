#include <algorithm>
#include <iostream>
#include <forward_list>
#include <iterator>
#include <utility>

using namespace std::rel_ops;

class Box
{
private:
    size_t length {};
    size_t width {};
    size_t height {};
public:
    explicit Box(size_t l = 1, size_t w = 1, size_t h = 1) : length {1}, width {w}, height {h} {}
    double volume() const { return length * width * height; }
    bool operator<(const Box& box) { return volume() < box.volume(); }
    bool operator==(const Box& box) { return length == box.length && width == box.width && height == box.height; }

    friend std::istream& operator>>(std::istream& in, Box& box);
    friend std::ostream& operator<<(std::ostream& out, const Box& box);
};

inline std::istream& operator>>(std::istream& in, Box& box)
{
    std::cout << "Enter box length, width, & height separated by spaces - Ctrl+Z to end: ";
    size_t value;
    in >> value;
    if (in.eof()) return in;

    box.length = value;
    in >> value;
    box.width = value;
    in >> value;
    box.height = value;
    return in;
}

inline std::ostream& operator<<(std::ostream& out, const Box& box)
{
    out << "Box(" << box.length << "," << box.width << "," << box.height << ") ";
    return out;
}

template<typename Iter>
void list_elements(Iter begin, Iter end)
{
    size_t perline {6};
    size_t count {};
    while(begin != end)
    {
        std::cout << *begin++;
        if(++count % perline == 0)
        {
            std::cout << "\n";
        }
    }
    std::cout << std::endl;
}

int main()
{
    std::forward_list<Box> boxes;
    std::copy(std::istream_iterator<Box>(std::cin), std::istream_iterator<Box>(), std::front_inserter(boxes));

    boxes.sort();
    std::cout << "\nAfter sorting the sequence is:\n";
    std::copy(std::begin(boxes), std::end(boxes), std::ostream_iterator<Box>(std::cout, " "));
    std::cout << std::endl;

    std::forward_list<Box> more_boxes {Box {3, 3, 3}, Box {5, 5, 5}, Box {4, 4, 4}, Box {2, 2, 2}};
    boxes.insert_after(boxes.before_begin(), std::begin(more_boxes), std::end(more_boxes));
    std::cout << "After inserting more boxes the sequence is:\n";
    list_elements(std::begin(boxes), std::end(boxes));
    boxes.sort();
    std::cout << std::endl;
    std::cout << "The sorted sequence is now:\n";
    list_elements(std::begin(boxes), std::end(boxes));

    more_boxes.sort();
    boxes.merge(more_boxes);
    std::cout << "After merging more_boxes the sequence is:\n";
    list_elements(std::begin(boxes), std::end(boxes));

    boxes.unique();
    std::cout << "After removing successive duplicates the sequence is:\n";
    list_elements(std::begin(boxes), std::end(boxes));

    const double max_v {30.0};
    boxes.remove_if([max_v](const Box& box){return box.volume() < max_v;});
    std::cout << "After removing those with volume less than 30 the sorted sequence is:\n";
    list_elements(std::begin(boxes), std::end(boxes));
}