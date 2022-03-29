#include "../includes/Registrar.hpp"

bool Registrar::registerStudentToCourse(std::shared_ptr<Student> student, std::shared_ptr<Course> course){
  std::vector<std::shared_ptr<Course>> studentCourses = student->getRegisteredCourses();
  int newCourseStartTime = course->getStartTime();
  int newCourseEndTime = course->getEndTime();

  // check for timing overlaps
  for(auto studentCourse: studentCourses){
    int currentCourseStartTime = studentCourse->getStartTime();
    int currentCourseEndTime = studentCourse->getEndTime();
    if(newCourseStartTime >= currentCourseStartTime && newCourseStartTime < currentCourseEndTime){
      return false;
    }
    if(newCourseEndTime <= currentCourseEndTime && newCourseEndTime > currentCourseStartTime){
      return false;
    }
  }
  
  // add course to student
  studentCourses.push_back(course);
  student->setRegisteredCourses(studentCourses);

  // add student to course
  auto courseStudents = std::vector<std::shared_ptr<Student>>(course->getRegisteredStudents().begin(), course->getRegisteredStudents().end());
  courseStudents.push_back(student);
  course->setRegisteredStudents(courseStudents);

  return true;
}