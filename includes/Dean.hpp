#ifndef DEAN_H
#define DEAN_H
#include <string>
#include <memory>
#include "Department.hpp"

class Department;

class Dean{
  public:
    Dean();
    void setName(std::string name);
    std::string getName() const;
    void setDepartment(std::shared_ptr<Department> department);
    std::shared_ptr<Department> getDepartment() const;
  private:
    std::string name;
    std::weak_ptr<Department> department;
};

#endif