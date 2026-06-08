cmake_minimum_required(VERSION 3.12)
project(UIH)

message(STATUS ${VCPKG_TARGET_TRIPLET})
find_package(Boost REQUIRED CONFIG COMPONENTS serialization)
add_executable(dump1 dump1.cxx)
target_link_libraries(dump1 PRIVATE Boost::serialization)
