cmake_minimum_required(VERSION 3.11)
project (vkvoxel VERSION 1.0.0)
set (CMAKE_CXX_STANDARD 17)

find_package(glfw3 CONFIG REQUIRED)
find_package(Vulkan REQUIRED)
find_package(glm REQUIRED)

set (GLSL_VALIDATOR "$ENV{VULKAN_SDK}/Bin/glslangValidator.exe")
file(GLOB_RECURSE GLSL_SOURCE_FILES
  "shaders/*.frag",
  "shaders/*.vert"
)

foreach(GLSL ${GLSL_SOURCE_FILES})
  get_filename_component(FILE_NAME ${GLSL} NAME)
  set(SPIRV "${PROJECT_BINARY_DIR}/shaders/${FILE_NAME}.spv")
  add_custom_command(
    OUTPUT ${SPIRV}
    COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_BINARY_DIR}/shaders/"
    COMMAND ${GLSL_VALIDATOR} -V ${GLSL} -o ${SPIRV}
    DEPENDS ${GLSL}
  )
  list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

add_custom_target(
  Shaders
  DEPENDS ${SPIRV_BINARY_FILES}
)

add_executable(vkvoxel
  Main.cpp
  Block.h
  BlockType.h
  BlockType.cpp
  Camera.cpp
  Camera.h
  Chunk.h
  Chunk.cpp
  Plane.cpp
  Plane.h
  Frustum.cpp
  Frustum.h
  Renderer.cpp
  Renderer.h
  TextureAtlas.cpp
  TextureAtlas.h
  Vertex.h
  Vertex.cpp
  VkChunk.h
  VkChunk.cpp
  VkManager.h
  VkManager.cpp
  VkRenderer.h
  VkRenderer.cpp
  VkVoxelApplication.h
  VkVoxelApplication.cpp
  VkUtil.h
)

add_dependencies(vkvoxel Shaders)

target_include_directories(vkvoxel PRIVATE
  ${Vulkan_INCLUDE_DIRS}
)

target_link_libraries(vkvoxel PRIVATE
  Vulkan::Vulkan
  glfw
  glm
)

add_custom_command(TARGET vkvoxel POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:vkvoxel>/shaders/"
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${PROJECT_BINARY_DIR}/shaders"
    "$<TARGET_FILE_DIR:vkvoxel>/shaders"
  COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_BINARY_DIR}/textures/"
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/textures" "${PROJECT_BINARY_DIR}/textures"
)