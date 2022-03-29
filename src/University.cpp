#include "../includes/University.hpp"
#include <thread>
#include <mutex>

University::University(){ }

University* University::getUniversity(){
  if(University::university == nullptr){
    university = new University();
  }
  return university;
}

void University::setName(std::string name){
  this->name = name;
}

std::string University::getName(){
  return name;
}

University* University::university = nullptr;

void University::setFaculties(std::vector<std::shared_ptr<Faculty>> faculties){
  this->faculties = faculties;
}

std::vector<std::shared_ptr<Faculty>> University::getFaculties(){
  return faculties;
}

std::vector<std::shared_ptr<Student>> University::getStudents(){
  std::vector<std::shared_ptr<Student>> allStudents;
  size_t facultiesSize = faculties.size();
  std::thread threads[facultiesSize];

  // To make the allStudents vector thread safe
  std::mutex allStudents_mutex;
  
  // Initialize threads to get all students from each faculty
  for(size_t i = 0 ; i < facultiesSize ; i++){
    threads[i] = std::thread([](std::shared_ptr<Faculty> &faculty, std::vector<std::shared_ptr<Student>> &allStudents, std::mutex &allStudents_mutex){
      std::vector<std::shared_ptr<Student>> studentsInFaculty = faculty->getStudents();
      std::lock_guard<std::mutex> lock(allStudents_mutex);
      allStudents.insert(
        allStudents.end(),
        studentsInFaculty.begin(),
        studentsInFaculty.end()
      );
    }, std::ref(faculties[i]), std::ref(allStudents), std::ref(allStudents_mutex));
  }

  // Wait for threads to finish then return all students;
  for(size_t i = 0 ; i < facultiesSize ; i++){
    threads[i].join();
  }
  return allStudents;
}

std::shared_ptr<Student> University::getStudentWithId(int Id){
  auto students = getStudents();
  for(auto student: students){
    if(student->getId() == Id){
      return student;
    }
  }
  return nullptr;
}

std::unordered_map<std::string, std::vector<std::shared_ptr<Student>>> University::getDublicateStudents(){
  auto students = getStudents();
  std::unordered_map<std::string, std::vector<std::shared_ptr<Student>>> dublicateStudents;

  // The map will be used to check for all dublicate students in O(nlogn) time
  std::unordered_map<std::string, std::shared_ptr<Student>> studentsMap;
  for(auto student : students){
    std::string studentKey = student->getFirstName() + student->getLastName() + student->getDateOfBirth();
    if(studentsMap.count(studentKey) == 0){
      studentsMap[studentKey] = student;
      continue;
    }
    if(dublicateStudents.count(studentKey) == 0){
      dublicateStudents[studentKey].push_back(studentsMap[studentKey]);
    }
    dublicateStudents[studentKey].push_back(student);
  }
  return dublicateStudents;
}

bool University::isStudentInMultipleDepartments(int studentId){
  int numberOfDepartmentsHaveStudent = 0;
  for(std::shared_ptr<Faculty> faculty: faculties){
    for(std::shared_ptr<Department> department: faculty->getDepartments()){
      if(department->hasStudent(studentId)){
        numberOfDepartmentsHaveStudent++;
      }
    }
  }
  if(numberOfDepartmentsHaveStudent > 1){
    return true;
  }
  return false;
}