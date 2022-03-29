#include "../includes/Faculty.hpp"

Faculty::Faculty(){
  name = "unset";
}

void Faculty::setName(std::string name){
  this->name = name;
}

std::string Faculty::getName() const{
  return name;
}

void Faculty::setDepartments(std::vector<std::shared_ptr<Department>> departments){
  this->departments = departments;
}

std::vector<std::shared_ptr<Department>> Faculty::getDepartments() const{
  return departments;
}

std::vector<std::shared_ptr<Student>> Faculty::getStudents() const{
  std::vector<std::shared_ptr<Student>> allStudents;
  size_t departmentsSize = departments.size();
  for(size_t i = 0 ; i < departmentsSize ; i++){
    std::vector<std::shared_ptr<Student>> studentsInDepartment = departments[i]->getStudents();
    allStudents.insert(
      allStudents.end(), 
      studentsInDepartment.begin(), 
      studentsInDepartment.end()
    );
  }
  return allStudents;
}