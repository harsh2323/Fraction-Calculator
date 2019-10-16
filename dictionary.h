#ifndef _DICTIONARY_H
#define _DICTIONARY_H

#include <exceptions.h>

const unsigned int DICTIONARY_SIZE = 307,MAX_ELEMENTS = 215;

enum DictionaryStatus {
  UNUSED,
  INUSE,
  DELETED
};

template <class KeyType,class ValueType>
class Dictionary {
 public:
  Dictionary();
  ~Dictionary();

  void clear();
  bool isEmpty();
  int size();

  void insert(KeyType k,ValueType v);
  void remove(KeyType k);
  void update(KeyType k,ValueType v);

  ValueType search(KeyType k);

 private:
  KeyType
    keys[DICTIONARY_SIZE];
  ValueType
    values[DICTIONARY_SIZE];
  DictionaryStatus
    status[DICTIONARY_SIZE];
  int
    count;
};

unsigned int hash(std::string k);

#include <dictionary-implementation.h>

#endif
