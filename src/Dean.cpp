#include "../includes/Dean.hpp"

Dean::Dean(){
  name = "unset";
}

void Dean::setName(std::string name){
  this->name = name;
}

std::string Dean::getName() const{
  return name;
}

void Dean::setDepartment(std::shared_ptr<Department> department){
  this->department = department;
}

std::shared_ptr<Department> Dean::getDepartment() const{
  return department.lock();
}