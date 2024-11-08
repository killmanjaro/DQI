#ifndef ELEMENTESA_H_INCLUDED
#define ELEMENTESA_H_INCLUDED

#pragma once
#include "Student.h"
#include <iostream>
#include <string>
#define GROW_POLICY 2
#define SHRINK_POLICY 2
#define INITIAL_ARRAY_SIZE 10

//#define __DEBUG__

/// HM1
// This is the interface to an "Enhanced" element array that you will write.
// The methods that need to be supported are shown below. Note: Array
// auto-resizing may need to be done.

//...Handles incorrect input, exits the program
void ErrorMessage(string functionName, string message) {
    cout<<"ERROR: "<<functionName<<" : "<<message<<endl;
    exit(1);
}

void WarningMessage(string functionName, string message) {
    cout<<"WARNING: "<<functionName<<" : "<<message<<endl;
}

template <typename Element>
class ElementEsa {
private:         // Define what you need
  Element **sap; // Underlying pointer to array of Element pointers, which you
                 // will allocate
  Element **tp;  // Optionally used in realloc
  size_t cnum;      // Number of elements currently in array
  size_t cmz;       // Current Max size of the array (may need to be expanded)
public:          // Publically supported methods you need to implement
  ElementEsa() : sap(nullptr), tp(nullptr), cnum(0), cmz(0) {
  }  // Default Constructor
  ElementEsa(ElementEsa &elementEsa){
    *this = elementEsa;
  } // Copy Constructor
  // Initialization Constructor. Allocate array ofthis size.
  // May need to be expanded
  ElementEsa(size_t size) : sap(new Element*[size]), tp(nullptr), cnum(0), cmz(size)  {
  }

  ~ElementEsa(); // Default destructor
  // Return the number of Elements in the Collection
  size_t getNum(){
    return cnum;
  }
  // GET: Get and return the ptr to the Element at the specified Index
  // Error if the supplied index >= array size. Return a NULL ptr
  Element* get(size_t idx) {
    if (idx >= cnum) {
       WarningMessage("get", "Invalid Index");
       return 0;
    }
    return sap[idx]; // Otherwise return Element ptr at that index in the  array
  }

  // SET: Replace
  // Destruct the Element whose ptr is at the supplied index
  // Insert the ptr of the new Element at that index. Return index # on success
  // Error if the supplied index >= array size. Return -1
  size_t set(Element* element, size_t idx){
    if(idx >= cnum) {
        WarningMessage("set", "Invalid Index");
        return 0;
    }

    delete sap[idx];
    sap[idx] = element;
    return idx;
  }
  // INSERT
  // Insert the Element ptr at the supplied index, by first "pushing back" every
  // subsequent element, bump Esa Size Note: This may force a reallocation of
  // the array. Return index # on success Error if the supplied index >= array
  // size. Return -1
  size_t insert(Element* element, size_t idx){
    if(idx >= cmz) {
        WarningMessage("insert", "Invalid Index");
        return 0;
    }

    if(cnum == cmz){
        // reallaoc
#ifdef __DEBUG__
        cout << "DEBUG Increasing the Extended Array Size from " <<cmz << " to "<<cmz * GROW_POLICY<<" size " <<" for element "<<element->getName()<<"\t"<<element->getId()<<endl;
#endif
        tp = new Element*[cmz * GROW_POLICY]; // allocate multiples of previous size
        // copy till idx
        size_t i = 0;
        for(i = 0; i < idx; i++){
            tp[i] = sap[i];
        }
        tp[i] = element;
        for(i = idx; i < cnum ; i++){
            tp[i + 1] = sap[i];
        }
        sap = tp;
        tp = NULL;
        cnum++;
        cmz = cmz * GROW_POLICY;
        return idx;
    }
    // pushing back subsequent element
    Element* prev = element;
    for(size_t i = idx ; i < cnum; i++){
        Element* np = sap[i];
        sap[i] = prev;
        prev = np;
    }
    sap[cnum] = prev;
    // increase count
    cnum++;
    return idx;
  }
  // REMOVE: Delete
  // Destruct the Element whose ptr is at the supplied index
  // "Pull forward" every subsequent element, decrement Esa Size
  // Error if the supplied index >= array size.
  // We could shrink the array, based on the policy, but this optimization is not implemented yet
  size_t remove(size_t idx){
    if(idx >= cnum) {
        WarningMessage("remove", "Invalid Index");
        return 0;
    }
    Element* element = sap[idx];
    // pull forward
    for(size_t i = idx; i < cnum - 1; i++){
        sap[i] = sap[i + 1];
    }
    cnum--;
    delete element;
    return idx;
  }
  // APPEND:
  // Append the pointer of the supplied Element to back of the Esa, bump Esa
  // size Note: This may force a reallocation of the array. Return index # of
  // new entry on success
  size_t append(Element* element){
    // insert at last index
    return insert(element,cnum);
  }
  // PREPEND:
  // Prepend the pointer of the supplied Element to the front of the Esa,
  // decrement Esa size Note: This may force a reallocation of the array. Return
  // index # of new entry on success
  size_t prepend(Element* element){
    // insert at zero index
    return insert(element,0);
  }
};


#endif // ELEMENTESA_H_INCLUDED
