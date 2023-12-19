#include "gtest/gtest.h"
#include "LRUCache.hpp"

TEST(LRUCacheTest, PutAndGet) {
    LRUCache<int, std::string> cache(2);
    cache.put(1, "one");
    cache.put(2, "two");
    EXPECT_EQ(cache.get(1).value_or(""), "one");
    EXPECT_EQ(cache.get(2).value_or(""), "two");
}

TEST(LRUCacheTest, Size) {
    LRUCache<int, std::string> cache(2);
    cache.put(1, "one");
    cache.put(2, "two");
    EXPECT_EQ(cache.size(), 2);
}

TEST(LRUCacheTest, Empty) {
    LRUCache<int, std::string> cache(2);
    EXPECT_TRUE(cache.empty());
    cache.put(1, "one");
    EXPECT_FALSE(cache.empty());
}

TEST(LRUCacheTest, Clear) {
    LRUCache<int, std::string> cache(2);
    cache.put(1, "one");
    cache.put(2, "two");
    cache.clear();
    EXPECT_TRUE(cache.empty());
    EXPECT_EQ(cache.size(), 0);
}

TEST(LRUCacheTest, PutMoreThanCapacity) {
    LRUCache<int, std::string> cache(2);
    cache.put(1, "one");
    cache.put(2, "two");
    cache.put(3, "three");
    EXPECT_EQ(cache.size(), 2);
    EXPECT_EQ(cache.get(1).value_or(""), "");
    EXPECT_EQ(cache.get(2).value_or(""), "two");
    EXPECT_EQ(cache.get(3).value_or(""), "three");
}

TEST(LRUCacheTest, EvictionTest) {
    LRUCache<std::string, double> cache(3);
    cache.put("one", 1.0);
    cache.put("two", 2.0);
    cache.put("three", 3.0);
    // Cache is full at this point. Adding another element will cause eviction.
    cache.put("four", 4.0);
    // "one" should have been evicted as it was the least recently used.
    EXPECT_FALSE(cache.get("one").has_value());
    // "two", "three", and "four" should still be in the cache.
    EXPECT_EQ(cache.get("two").value_or(0.0), 2.0);
    EXPECT_EQ(cache.get("three").value_or(0.0), 3.0);
    EXPECT_EQ(cache.get("four").value_or(0.0), 4.0);
}

TEST(LRUCacheTest, LeastRecentlyAccessedToFront) {
    LRUCache<std::string, double> cache(3);
    cache.put("one", 1.0);
    cache.put("two", 2.0);
    cache.put("three", 3.0);
    // Access "two", making it the most recently accessed.
    cache.get("two");
    // Add a new item, which should evict "one", as it is now the least recently accessed.
    cache.put("four", 4.0);
    // Check that "two", "three", and "four" are still in the cache.
    EXPECT_EQ(cache.get("two").value_or(0.0), 2.0);
    EXPECT_EQ(cache.get("three").value_or(0.0), 3.0);
    EXPECT_EQ(cache.get("four").value_or(0.0), 4.0);
}