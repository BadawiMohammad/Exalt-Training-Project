#ifndef FACULTY_H
#define FACULTY_H
#include <string>
#include <memory>
#include "Department.hpp"

class Department;

class Faculty{
  public:
    Faculty();
    void setName(std::string name);
    std::string getName() const;
    void setDepartments(std::vector<std::shared_ptr<Department>> departments);
    std::vector<std::shared_ptr<Department>> getDepartments() const;
    std::vector<std::shared_ptr<Student>> getStudents() const;
  private:
    std::string name;
    std::vector<std::shared_ptr<Department>> departments;
};

#endif
