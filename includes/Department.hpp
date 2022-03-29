#ifndef DEPARTMENT_H
#define DEPARTMENT_H
#include <string>
#include <memory>
#include "Dean.hpp"
#include "Student.hpp"

class Dean;
class Student;

class Department{
  public:
    Department();
    void setName(std::string name);
    std::string getName() const;
    void setDean(std::shared_ptr<Dean> dean);
    std::shared_ptr<Dean> getDean() const;
    void setStudents(std::vector<std::shared_ptr<Student>> students);
    std::vector<std::shared_ptr<Student>> getStudents() const;
    bool hasStudent(int studentId);
  private:
    std::string name;
    std::weak_ptr<Dean> dean;
    std::vector<std::weak_ptr<Student>> students;
};

#endif