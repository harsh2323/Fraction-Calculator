// Harsh Shah
// Assignment 2

#ifndef _STACK_H
#define _STACK_H

#include "exceptions.h"

const int STACK_SIZE = 10;

template <class StackType> // "StackType" is the type of stack, whether it be int or char in this case

class Stack {
 public:
  Stack(void) { count = 0; }
  ~Stack(void) { }

  void clear(void) { count = 0; }
  int size(void) { return count; }
  bool isEmpty(void) { return count == 0; }

  void push(const StackType &d){

    if (count == STACK_SIZE)
      throw ContainerFullException("Stack");

    data[count] = d;

    count++;
  }

  StackType pop(void) {

    if (!count)
      throw ContainerEmptyException("Stack");

    count--;

    return data[count];

  }

  StackType peek(void){

    if (!count)
      throw ContainerEmptyException("Stack");

    return data[count-1];
  }

 private:
  StackType
   data[STACK_SIZE];
  int
   count;
};

#endif
