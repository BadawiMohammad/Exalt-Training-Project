#include <algorithm>
#include "../includes/Department.hpp"

Department::Department(){
  name = "unset";
}

void Department::setName(std::string name){
  this->name = name;
}

std::string Department::getName() const{
  return name;
}

void Department::setDean(std::shared_ptr<Dean> dean){
  this->dean = dean;
}

std::shared_ptr<Dean> Department::getDean() const{
  return dean.lock();
}

void Department::setStudents(std::vector<std::shared_ptr<Student>> students){
  this->students = std::vector<std::weak_ptr<Student>>(students.begin(), students.end());
}

std::vector<std::shared_ptr<Student>> Department::getStudents() const{
  std::vector<std::shared_ptr<Student>> returnedStudents;
  returnedStudents.resize(students.size());
  std::transform(
    students.begin(),
    students.end(),
    returnedStudents.begin(),
    [](std::weak_ptr<Student> student){
      return student.lock();
    }
  );
  return returnedStudents;
}

bool Department::hasStudent(int studentId){
  for(auto student: students){
    if(student.lock()->getId() == studentId){
      return true;
    }
  }
  return false;
}