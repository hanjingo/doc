#include <string>
#include <ostream>
#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <iterator>
#include <map>
#include <vector>
#include <random>

using std::string;
using Distribution = std::uniform_int_distribution<size_t>;
using Subject = string;
using Subjects = std::vector<Subject>;
using Group = std::set<Student>;
using Students = std::vector<Student>;
using Course = std::pair<Subject, Group>;
using Courses = std::map<Subject, Group>;

static std::default_random_engine gen_value;

class Student
{
private:
    std::string first {};
    std::string second {};

public:
    Student(const std::string& name1, const std::string& name2) : first(name1), second(name2) {}
    Student(Student&& student) : first(std::move(student.first)),
                                 second(std::move(student.second)) {}
    Student(const Student& student) : 
            first(student.first), second(student.second) {}
    Student() {}

    bool operator<(const Student& student) const 
    {
        return second < student.second || (second == student.second && first < student.first);
    }

    friend std::ostream& operator<<(std::ostream& out, const Student& student);
};

Students create_students()
{
    Students students;
    string first_names[] {"Ann", "Jim", "Eve", "Dan", "Ted"};
    string second_names[] {"Smith", "Jones", "Howe", "Watt", "Beck"};

    for(const auto& first : first_names)
    {
        for(const auto& second : second_names)
        {
            students.emplace_back(first, second);
        }
    }
    return students;
}

inline std::ostream& operator<<(std::ostream& out, const Student& student)
{
    out << student.first + " " + student.second;
    return out;
}

class List_Course
{
public:
    void operator()(const Course& course)
    {
        std::cout << "\n\n" << course.first << " " << course.second.size()
                  << " student:\n";
        std::copy( std::begin(course.second), std::end(course.second),
                   std::ostream_iterator<Student>(std::cout, " ") );
    }
};

int main()
{
    Students students = create_students();
    Subjects subjects {"Biology", "Physics", "Chemistry", "Mathematics", 
                    "Astronomy", "Drama", "Politics", "Philosophy", "Economics"};
    Courses courses;
    size_t min_subjects {4};
    size_t min_group {min_subjects};

    size_t max_group {(students.size()*min_subjects)/subjects.size()};

    Distribution group_size {min_group, max_group};
    Distribution choose_student {0, students.size() - 1};
    for(const auto& student : students)
    {
        size_t course_count = std::count_if(std::begin(courses),
            std::end(courses), [&student](const Course& course){return course.second.count(student);});
        if(course_count >= min_subjects) 
            continue;
        size_t additional {min_subjects - course_count};
        if(!course_count)
            std::cout << student << " is work-shy, having signed up for NO Subjects!\n";
        else
            std::cout << student << " is only signed up for " << course_count << " Subjects!\n";

        std::cout << "Registering " << student << " for " << additional << " more course" << (additional > 1 ? "s" : "") << ".\n\n";

        while(course_count < min_subjects)
            if((courses.find(subjects[choose_course(gen_value)])->second.insert(student)).second)
                ++course_count;
    }
    std::for_each(std::begin(courses), std::end(course), List_Course());
    std::cout << std::endl;
}