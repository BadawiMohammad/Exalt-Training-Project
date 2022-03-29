#include "../includes/Course.hpp"
#include <algorithm>

Course::Course(){
  id = -1;
  startTime = 0;
  endTime = 0;
}

void Course::setId(int id){
  this->id = id;    
}   

int Course::getId() const{
  return id;
}

void Course::setStartTime(int startTime){
  this->startTime = startTime;
}

int Course::getStartTime() const{
  return startTime;
}

void Course::setEndTime(int endTime){
  this->endTime = endTime;
}

int Course::getEndTime() const{
  return endTime;
}

void Course::setName(std::string name){
  this->name = name;
}

std::string Course::getName() const{
  return name;
}

void Course::setDaysOfWeek(std::vector<Day> daysOfWeek){
  this->daysOfWeek = daysOfWeek;
}

std::vector<Day> Course::getDaysOfWeek() const{
  return daysOfWeek;
}

void Course::setRegisteredStudents(std::vector<std::shared_ptr<Student>> registeredStudents){
  this->registeredStudents = std::vector<std::weak_ptr<Student>>(registeredStudents.begin(), registeredStudents.end());
}

std::vector<std::shared_ptr<Student>> Course::getRegisteredStudents() const{
  std::vector<std::shared_ptr<Student>> returnedRegisteredStudents;
  returnedRegisteredStudents.resize(registeredStudents.size());
  std::transform(
    registeredStudents.begin(),
    registeredStudents.end(),
    returnedRegisteredStudents.begin(),
    [](std::weak_ptr<Student> student){
      return student.lock();
    }
  );
  return returnedRegisteredStudents;
}

void Course::setLecturer(std::shared_ptr<Lecturer> lecturer){
  this->lecturer = lecturer;
}

std::shared_ptr<Lecturer> Course::getLecturer() const{
  return lecturer.lock();
}
