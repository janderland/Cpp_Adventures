#pragma once

#include <string>
#include <list>
#include <map>

namespace jander {

class LRUCache {
  using Id = std::string;
  using Value = std::string;
  using Size = unsigned int;

  Size currentSize = 0;
  Size maxSize;

  struct Entry {
    Value value;
    std::list<Id>::iterator it;
  };

  std::map<Id, Entry> values;
  std::list<Id> priorityList;

public:
  LRUCache(Size maxSize);

  bool put(Id id, Value value);

  Value get(Id id);

  std::list<Value> getAll();
};

}; // namespace jander
