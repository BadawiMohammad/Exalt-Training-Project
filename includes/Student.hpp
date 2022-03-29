#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "Department.hpp"
#include "Course.hpp"

class Department;
class Course;

class Student{
public:
  Student();
  void setId(int id);
  int getId() const;
	void setFirstName(std::string firstName);
	std::string getFirstName() const;
	void setLastName(std::string lastName);
	std::string getLastName() const;
	void setDateOfBirth(std::string dateOfBirth);
	std::string getDateOfBirth() const;
  void setDepartment(std::shared_ptr<Department> department);
  std::shared_ptr<Department> getDepartment() const;
  void setRegisteredCourses(std::vector<std::shared_ptr<Course>> registeredCourses);
  std::vector<std::shared_ptr<Course>> getRegisteredCourses() const;
  friend std::ostream& operator<<(std::ostream& stream, Student student);
private:
	int id;
	std::string firstName;
	std::string lastName;
	std::string dateOfBirth;
  std::weak_ptr<Department> department;
  std::vector<std::weak_ptr<Course>> registeredCourses;
};

#endif