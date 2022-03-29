#ifndef REGISTRAR_H
#define REGISTRAR_H
#include "Student.hpp"
#include "Course.hpp"
#include <memory>

class Student;
class Course;

class Registrar{
  public:
    static bool registerStudentToCourse(std::shared_ptr<Student> student, std::shared_ptr<Course> course);
};

#endif