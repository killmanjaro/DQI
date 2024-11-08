#ifndef STUDENTDQI_H_INCLUDED
#define STUDENTDQI_H_INCLUDED

#pragma once
using namespace std;
#include <iostream>
#include "Student.h"
#include "StudentESA.h"  // Student Orderable Array (normally enabled)


class StudentDQI {
private:
    StudentEsa* soa;  // Allocated Student Orderable Array (normally enabled)
    Student** sa; // Pointer to actual array of Student Ptrs

    // These might be useful;
    unsigned int top; // Index value 1 above highest OA element used
    unsigned int btm; // Index value 1 below lowest OA element used
public:
    StudentDQI(unsigned int); // Create a DQ with this initial size
    StudentDQI(StudentDQI&); // Equate this to an existing DQ (can use private parts directly)
    ~StudentDQI(); // Destruct the DQI (free OA space)

    int getSize();  // Gets # elements (Student *) in the DQ
    bool isEmpty(); // True if no elements held (“pop” will fail)

    int pushFront(Student*); // Prepend a new element to the front

    Student* popFront();      // Remove the first element and return it
    Student* lookFront();      // Return the first element but do not remove it

    int pushBack(Student*); // Append a new element to the back
    Student* popBack();     // Remove the last element and return it
    Student* lookBack();     // Return the last element but do not remove it
};

#endif // STUDENTDQI_H_INCLUDED
