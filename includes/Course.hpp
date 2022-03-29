#ifndef COURSE_H
#define COURSE_H
#include <string>
#include <memory>
#include <vector>
#include "Day.hpp"
#include "Student.hpp"
#include "Lecturer.hpp"

enum Day;
class Student;
class Lecturer;

class Course{
  public:
    Course();
    void setId(int id);
    int getId() const;
    void setStartTime(int startTime);
    int getStartTime() const;
    void setEndTime(int endTime);
    int getEndTime() const;
    void setName(std::string name);
    std::string getName() const;
    void setDaysOfWeek(std::vector<Day> daysOfWeek);
    std::vector<Day> getDaysOfWeek() const;
    void setRegisteredStudents(std::vector<std::shared_ptr<Student>> registeredStudents);
    std::vector<std::shared_ptr<Student>> getRegisteredStudents() const;
    void setLecturer(std::shared_ptr<Lecturer> lecturere);
    std::shared_ptr<Lecturer> getLecturer() const;
  private:
    int id;
    int startTime;
    int endTime;
    std::string name;
    std::vector<Day> daysOfWeek;
    std::vector<std::weak_ptr<Student>> registeredStudents;
    std::weak_ptr<Lecturer> lecturer;
};

#endif