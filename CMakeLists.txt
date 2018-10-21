cmake_minimum_required(VERSION 3.11)
project (vkvoxel VERSION 1.0.0)
set (CMAKE_CXX_STANDARD 17)

find_package(glfw3 CONFIG REQUIRED)
find_package(Vulkan REQUIRED)
find_package(glm REQUIRED)

add_executable(vkvoxel
  Main.cpp
)

target_include_directories(vkvoxel PRIVATE
  ${Vulkan_INCLUDE_DIRS}
)

target_link_libraries(vkvoxel PRIVATE
  Vulkan::Vulkan
  glfw
  glm
)