cmake_minimum_required(VERSION 3.12)
project(UIH)

# UIH1

message(STATUS ${VCPKG_TARGET_TRIPLET})
find_package(Boost REQUIRED CONFIG COMPONENTS serialization)
add_executable(dump1 dump1.cxx)
target_link_libraries(dump1 PRIVATE Boost::serialization)
add_executable(dump2 dump2.cxx)
target_link_libraries(dump2 PRIVATE Boost::serialization)
add_executable(dump3 dump3.cxx)
target_link_libraries(dump3 PRIVATE Boost::serialization)
add_executable(dump4 dump4.cxx)
target_link_libraries(dump4 PRIVATE Boost::serialization)
#add_executable(dump5 dump5.cxx)
#target_link_libraries(dump5 PRIVATE Boost::serialization)
#set_target_properties(dump5 PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
add_executable(inspect inspect.cxx)
target_link_libraries(inspect PRIVATE Boost::serialization)

# UIH2
add_executable(parse1 parse1.cxx)
