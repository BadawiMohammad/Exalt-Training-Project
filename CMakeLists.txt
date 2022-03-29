cmake_minimum_required (VERSION 3.16)

project (Training)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_THREAD_PREFER_PTHREAD true)
set(THREADS_PERFER_PTHREAD_FLAG true)
find_package(Threads REQUIRED)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
file(GLOB SOURCES
     "src/*.cpp"
)
file(GLOB HEADERS
	"includes/*.hpp"
)
add_executable(Training ${SOURCES} ${HEADERS})
target_include_directories(Training PUBLIC src includes)
target_link_libraries(Training PUBLIC gtest_main PRIVATE Threads::Threads)

include(GoogleTest)
gtest_discover_tests(Training)