#ifndef UNIVERSITY_H
#define UNIVERSITY_H
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "Faculty.hpp"

class Faculty;
class Student;

class University{
  public:
    University(const University& university) = delete;
    ~University();
    University& operator=(const University& university) = delete;
    static University* getUniversity();
    void setName(std::string name);
    std::string getName();
    void setFaculties(std::vector<std::shared_ptr<Faculty>> faculties);
    std::vector<std::shared_ptr<Faculty>> getFaculties();
    std::vector<std::shared_ptr<Student>> getStudents();
    std::shared_ptr<Student> getStudentWithId(int id);
    std::unordered_map<std::string, std::vector<std::shared_ptr<Student>>> getDublicateStudents();
    bool isStudentInMultipleDepartments(int studentId);
  private:
    University();
    static University* university;
    std::string name;
    std::vector<std::shared_ptr<Faculty>> faculties;
};

#endif