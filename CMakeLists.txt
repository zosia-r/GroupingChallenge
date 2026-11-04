cmake_minimum_required(VERSION 3.16)
project(GroupingChallenge LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

add_executable(GroupingChallenge
  src/GaussianGroupingEvaluatorFactory.cpp
  src/GeneticAlgorithm.cpp
  src/GroupingChallenge.cpp
  src/GroupingEvaluator.cpp
  src/Individual.cpp
  src/Optimizer.cpp
  src/Point.cpp
)

target_include_directories(GroupingChallenge PRIVATE src)

if(MSVC)
  target_compile_options(GroupingChallenge PRIVATE /W3)
else()
  target_compile_options(GroupingChallenge PRIVATE -Wall -Wextra)
endif()
