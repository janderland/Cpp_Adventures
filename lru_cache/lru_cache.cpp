#include "lru_cache.hpp"
#include <exception>

namespace jander {

bool LRUCache::put(Id id, Value value) {
  if (value.length() > maxSize) {
    return false;
  }
  else {
    if (!values.empty()) {
      while (currentSize + value.length() > maxSize) {
        const auto& idToRemove = priorityList.back();
        const auto& [valueToRemove, priority] = values.at(idToRemove);

        currentSize -= valueToRemove.length();

        values.erase(idToRemove);
        priorityList.pop_back();
      }
    }

    priorityList.push_front(id);
    values.insert({id, Entry{value, priorityList.begin()}});
    currentSize += value.length();
    return true;
  }
}

LRUCache::Value LRUCache::get(Id id) {
  auto& entry = values.at(id);
  priorityList.erase(entry.priority);
  priorityList.push_front(id);
  entry.priority = priorityList.begin();
  return entry.value;
}

list<LRUCache::Value> LRUCache::getAll() {
  std::list<Value> allValues;
  for (const Id& id : priorityList) {
    const auto& [value, priority] = values.at(id);
    allValues.push_back(value);
  }
  return allValues;
}

}; // namespace jander
