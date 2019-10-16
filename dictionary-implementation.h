//
// warning: this should not be directly included in anything except
//          dictionary.h
//

template <class KeyType,class ValueType>
Dictionary<KeyType,ValueType>::Dictionary() {

  count = 0;

  for (int i=0;i<DICTIONARY_SIZE;i++)
    status[i] = UNUSED;
}

template <class KeyType,class ValueType>
Dictionary<KeyType,ValueType>::~Dictionary() { }

template <class KeyType,class ValueType>
void Dictionary<KeyType,ValueType>::clear() {

  count = 0;

  for (int i=0;i<DICTIONARY_SIZE;i++)
    status[i] = UNUSED;
}

template <class KeyType,class ValueType>
bool Dictionary<KeyType,ValueType>::isEmpty() { return !count; }

template <class KeyType,class ValueType>
int Dictionary<KeyType,ValueType>::size() { return count; }

template <class KeyType,class ValueType>
void Dictionary<KeyType,ValueType>::insert(KeyType k,ValueType v) {
  unsigned int pos;

  if (count == MAX_ELEMENTS)
    throw ContainerFullException();

  pos = hash(k) % DICTIONARY_SIZE;

  while (status[pos] == INUSE) {
    if (k == keys[pos])
      throw DuplicateKeyException();
    pos = (pos + 1) % DICTIONARY_SIZE;
  }

  keys[pos] = k;
  values[pos] = v;
  status[pos] = INUSE;
}

template <class KeyType,class ValueType>
void Dictionary<KeyType,ValueType>::remove(KeyType k) {
  unsigned int pos;

  pos = hash(k) % DICTIONARY_SIZE;

  while (status[pos] != UNUSED) {
    if (k == keys[pos]) {
      status[pos] = DELETED;
      return;
    }
    pos = (pos + 1) % DICTIONARY_SIZE;
  }

  throw KeyNotFoundException(k);
}

template <class KeyType,class ValueType>
void Dictionary<KeyType,ValueType>::update(KeyType k,ValueType v) {
  unsigned int pos;

  pos = hash(k) % DICTIONARY_SIZE;

  while (status[pos] != UNUSED) {
    if (k == keys[pos]) {
      values[pos] = v;
      return;
    }
    pos = (pos + 1) % DICTIONARY_SIZE;
  }

  throw KeyNotFoundException(k);
}

template <class KeyType,class ValueType>
ValueType Dictionary<KeyType,ValueType>::search(KeyType k) {
  unsigned int pos;

  pos = hash(k) % DICTIONARY_SIZE;

  while (status[pos] != UNUSED) {
    if (k == keys[pos])
      return values[pos];
    pos = (pos + 1) % DICTIONARY_SIZE;
  }

  throw KeyNotFoundException(k);
}


