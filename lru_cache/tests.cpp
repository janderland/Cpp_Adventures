#include "lru_cache/lru_cache.hpp"
#include "catch/catch.hpp"

TEST_CASE("things can be put in the cache") {
  jander::LRUCache cache(10);

  cache.put("1", "hello");
  auto list = cache.getAll();
  REQUIRE(list.size() == 1);
  REQUIRE(list.front() == "hello");

  cache.put("2", "world");
  list = cache.getAll();
  REQUIRE(list.size() == 2);
  REQUIRE(list.front() == "world");
}

TEST_CASE("get updates the thing's priority") {
  jander::LRUCache cache(10);

  cache.put("1", "hello");
  cache.put("2", "world");

  auto list = cache.getAll();
  REQUIRE(list.front() == "world");

  cache.get("1");
  list = cache.getAll();
  REQUIRE(list.front() == "hello");
}

TEST_CASE("items are removed when the cache is too full") {
  using List = std::list<std::string>;
  jander::LRUCache cache(15);

  cache.put("1", "hello");
  cache.put("2", "world");
  cache.put("3", "wohoo");
  REQUIRE(cache.getAll() == List{"wohoo", "world", "hello"});

  cache.put("4", "helloworld");
  REQUIRE(cache.getAll() == List{"helloworld", "wohoo"});
}
