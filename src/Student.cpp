#include <algorithm>
#include "../includes/Student.hpp"

Student::Student(){
  firstName = "unset";
  lastName = "unset";
  dateOfBirth = "1/1/1970";
}

void Student::setId(int id){
  this->id = id;
}

int Student::getId() const {
  return id;
}

void Student::setFirstName(std::string firstName){
  this->firstName = firstName;   
}

std::string Student::getFirstName() const {
  return firstName;
}

void Student::setLastName(std::string lastName){
  this->lastName = lastName;
}

std::string Student::getLastName() const {
  return lastName;
}

void Student::setDateOfBirth(std::string dateOfBirth){
  this->dateOfBirth = dateOfBirth;
}

std::string Student::getDateOfBirth() const {
  return dateOfBirth;
}

void Student::setDepartment(std::shared_ptr<Department> department){
  this->department = department;
}

std::shared_ptr<Department> Student::getDepartment() const {
  return department.lock();
}

void Student::setRegisteredCourses(std::vector<std::shared_ptr<Course>> registeredCourses){
  this->registeredCourses = std::vector<std::weak_ptr<Course>>(registeredCourses.begin(), registeredCourses.end());
}

std::vector<std::shared_ptr<Course>> Student::getRegisteredCourses() const{
  std::vector<std::shared_ptr<Course>> returnedRegisteredCourses;
  returnedRegisteredCourses.resize(registeredCourses.size());
  std::transform(
    registeredCourses.begin(),
    registeredCourses.end(),
    returnedRegisteredCourses.begin(),
    [](std::weak_ptr<Course> course){
      return course.lock();
    }
  );
  return returnedRegisteredCourses;
}

std::ostream& operator<<(std::ostream& stream, Student student){
  stream 
    << "Student " << student.id << ' ' << student.firstName << ' ' << student.lastName << '\n'
    << "\tDate Of Birth: " << student.dateOfBirth << '\n'
    << "\tDepartment: " << student.getDepartment()->getName() << '\n';
  stream << "\tStudent Courses: \n";
  for(auto course: student.getRegisteredCourses()){
    stream << "\t\t" << course->getName() << '\n';
  }
  return stream;
}