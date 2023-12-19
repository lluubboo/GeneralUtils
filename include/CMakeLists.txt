add_library(incl_lib INTERFACE)
target_sources(incl_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/LRUCache.hpp ${CMAKE_CURRENT_SOURCE_DIR}/ThreadSafeContainer.hpp)
target_include_directories(incl_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})