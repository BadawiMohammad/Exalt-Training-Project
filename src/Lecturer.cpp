#include <algorithm>
#include "../includes/Lecturer.hpp"

Lecturer::Lecturer(){
  name = "unset";
}

void Lecturer::setName(std::string name){
  this->name = name;
}

std::string Lecturer::getName() const{
  return name;
}

void Lecturer::setCourses(std::vector<std::shared_ptr<Course>> courses){
  this->courses = std::vector<std::weak_ptr<Course>>(courses.begin(), courses.end());
}

std::vector<std::shared_ptr<Course>> Lecturer::getCourses() const{
  std::vector<std::shared_ptr<Course>> returnedCourses;
  returnedCourses.resize(courses.size());
  std::transform(
    courses.begin(),
    courses.end(),
    returnedCourses.begin(),
    [](std::weak_ptr<Course> course){
      return course.lock();
    }
  );
  return returnedCourses;
}

