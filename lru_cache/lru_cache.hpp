#pragma once

#include <string>
#include <list>
#include <map>

using std::string;
using std::list;
using std::map;

namespace jander {

class LRUCache {
  using Id = string;
  using Value = string;
  using Size = unsigned int;

  Size currentSize = 0;
  Size maxSize;

  struct Entry {
    Value value;
    list<Id>::iterator priority;
  };

  map<Id, Entry> values;
  list<Id> priorityList;

public:
  LRUCache(Size maxSize): maxSize(maxSize) {}
  bool put(Id id, Value value);
  Value get(Id id);
  list<Value> getAll();
};

}; // namespace jander
