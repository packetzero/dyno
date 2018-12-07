set (PROJECT_NAME dyno)
PROJECT(${PROJECT_NAME})

CMAKE_MINIMUM_REQUIRED(VERSION 2.7)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF) # want c++11 not gnu++11

set(CMAKE_SUPPRESS_REGENERATION "1") # avoid ALL_BUILD targets

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG=1")

if($ENV{MAKE_TESTS})
  file(GLOB TESTSRCS "test/*.c*")

  ADD_EXECUTABLE(dynotests ${TESTSRCS})
  TARGET_LINK_LIBRARIES(dynotests gtest)
else()
  message("===================================")
  message("NOTE: This is a header-only library")
  message("===================================")
endif()

#install(TARGETS ${PROJECT_NAME} ARCHIVE DESTINATION lib)
install(DIRECTORY include/ DESTINATION include FILES_MATCHING PATTERN "*.hpp")
