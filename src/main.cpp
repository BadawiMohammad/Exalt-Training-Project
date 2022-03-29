#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <gtest/gtest.h>
#include "../includes/University.hpp"
#include "../includes/Registrar.hpp"

class StudentTest : public ::testing::Test{
  protected:
    void SetUp() override{
      university = University::getUniversity();
      computerEngineeringDepartment = std::make_shared<Department>();
      computerEngineeringDepartment->setName("Computer Engineering");
      engineeringFaculty = std::make_shared<Faculty>();
      engineeringFaculty->setName("Engineering");
      engineeringFaculty->setDepartments({computerEngineeringDepartment});
      university->setFaculties({engineeringFaculty});
    }
    University* university;
    std::shared_ptr<Department> computerEngineeringDepartment;
    std::shared_ptr<Faculty> engineeringFaculty;
};

TEST(UniversityTest, SingletonTest){
  University* university1 = University::getUniversity();
  University* university2 = University::getUniversity();
  ASSERT_EQ(university1, university2);
}

TEST_F(StudentTest, GetAllStudents){
  auto firstStudent = std::make_shared<Student>();
  auto secondStudent = std::make_shared<Student>();
  firstStudent->setId(1);
  firstStudent->setDepartment(computerEngineeringDepartment);
  secondStudent->setId(2);
  secondStudent->setDepartment(computerEngineeringDepartment);
  computerEngineeringDepartment->setStudents({firstStudent, secondStudent});
  auto allStudents = university->getStudents();
  EXPECT_EQ(allStudents.size(), 2) << "Unexpected item size";
  auto it = std::find(allStudents.begin(), allStudents.end(), firstStudent);
  EXPECT_EQ(*it, firstStudent) << "Students are not equal";
  it = std::find(allStudents.begin(), allStudents.end(), secondStudent);
  EXPECT_EQ(*it, secondStudent) << "Students are not equal";
}

TEST_F(StudentTest, SearchById){
  auto firstStudent = std::make_shared<Student>();
  auto secondStudent = std::make_shared<Student>();
  firstStudent->setId(1);
  firstStudent->setDepartment(computerEngineeringDepartment);
  secondStudent->setId(2);
  secondStudent->setDepartment(computerEngineeringDepartment);
  computerEngineeringDepartment->setStudents({firstStudent, secondStudent});
  std::shared_ptr<Student> firstSearchedStudent = university->getStudentWithId(1);
  EXPECT_EQ(firstSearchedStudent, firstStudent);
  std::shared_ptr<Student> secondSearchedStudent = university->getStudentWithId(2);
  EXPECT_EQ(secondSearchedStudent, secondStudent);
  std::shared_ptr<Student> thirdSearchedStudent = university->getStudentWithId(3);
  EXPECT_EQ(thirdSearchedStudent, nullptr);
}

TEST_F(StudentTest, DublicateStudent){
  auto firstStudent = std::make_shared<Student>();
  auto secondStudent = std::make_shared<Student>();
  auto thirdStudent = std::make_shared<Student>();
  firstStudent->setId(1);
  firstStudent->setFirstName("Ahmad");
  firstStudent->setLastName("Arafat");
  firstStudent->setDepartment(computerEngineeringDepartment);
  firstStudent->setDateOfBirth("1/3/2000");
  secondStudent->setId(2);
  secondStudent->setFirstName("Ahmad");
  secondStudent->setLastName("Arafat");
  secondStudent->setDateOfBirth("1/3/2000");
  secondStudent->setDepartment(computerEngineeringDepartment);
  thirdStudent->setId(3);
  thirdStudent->setFirstName("Taher");
  thirdStudent->setLastName("Anaya");
  thirdStudent->setDepartment(computerEngineeringDepartment);
  thirdStudent->setDateOfBirth("4/7/2000");
  auto expectedDublicateStudents = std::vector<std::shared_ptr<Student>>{firstStudent, secondStudent};
  std::string expectedDublicateStudentsKey = "AhmadArafat1/3/2000";
  std::string expectedNoDublicateStudentsKey = "TaherAnaya4/7/2000";
  computerEngineeringDepartment->setStudents({firstStudent, secondStudent, thirdStudent});
  auto realDublicateStudents = university->getDublicateStudents();
  EXPECT_EQ(realDublicateStudents[expectedDublicateStudentsKey], expectedDublicateStudents);
  EXPECT_EQ(realDublicateStudents.count(expectedNoDublicateStudentsKey), 0);
}

TEST_F(StudentTest, StudentIsInMultipleDepartments){
  auto civilEngineeringDepartment = std::make_shared<Department>();
  auto firstStudent = std::make_shared<Student>();
  auto secondStudent = std::make_shared<Student>();
  firstStudent->setId(1);
  secondStudent->setId(2);
  firstStudent->setDepartment(computerEngineeringDepartment);
  secondStudent->setDepartment(civilEngineeringDepartment);
  computerEngineeringDepartment->setStudents({firstStudent});
  civilEngineeringDepartment->setStudents({firstStudent, secondStudent});
  engineeringFaculty->setDepartments({computerEngineeringDepartment, civilEngineeringDepartment});
  EXPECT_TRUE(university->isStudentInMultipleDepartments(1)) << "Student is not in multiple different departments";
  EXPECT_FALSE(university->isStudentInMultipleDepartments(2)) << "Student is in multiple different departments";
}

TEST_F(StudentTest, CoursesRegistrar){
  auto student = std::make_shared<Student>();
  auto firstCourse = std::make_shared<Course>();
  auto secondCourse = std::make_shared<Course>();
  auto thirdCourse = std::make_shared<Course>();
  firstCourse->setStartTime(7);
  firstCourse->setEndTime(11);
  secondCourse->setStartTime(11);
  secondCourse->setEndTime(13);
  thirdCourse->setStartTime(9);
  thirdCourse->setEndTime(10);
  EXPECT_TRUE(Registrar::registerStudentToCourse(student, firstCourse));
  EXPECT_TRUE(Registrar::registerStudentToCourse(student, secondCourse));
  EXPECT_FALSE(Registrar::registerStudentToCourse(student, thirdCourse));
}