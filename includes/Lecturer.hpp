#ifndef LECTURER_H
#define LECTURER_H
#include <string>
#include <vector>
#include <memory>
#include "Course.hpp"

class Course;

class Lecturer{
  public:
    Lecturer();
    void setName(std::string name);
    std::string getName() const;
    void setCourses(std::vector<std::shared_ptr<Course>> courses);
    std::vector<std::shared_ptr<Course>> getCourses() const;
  private:
    std::string name;
    std::vector<std::weak_ptr<Course>> courses;
};

#endif