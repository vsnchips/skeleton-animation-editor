
# Source Files
#
# If you add any new files, remember to add them here
SET(sources
  callbacks.cpp
  splineMath.cpp
  boneCurve.cpp
  a3_kfwin.cpp
  asf.hpp
  asf.cpp
  asf_files.cpp
  a3.hpp
  a3.cpp
  a3_dogui.cpp
  a3_inevents.cpp
  drawStyle.hpp
  #drawStyle.cpp
  app_renderer.hpp
  app_renderer.cpp
  ../include/skeleton/skeleton.cpp
  opengl.hpp
  main.cpp
)

add_executable(${CGRA_PROJECT} ${sources})

add_subdirectory(cgra)

target_source_group_tree(${CGRA_PROJECT})

target_link_libraries(${CGRA_PROJECT} PRIVATE ${OPENGL_LIBRARY})
target_link_libraries(${CGRA_PROJECT} PRIVATE glfw ${GLFW_LIBRARIES})
target_link_libraries(${CGRA_PROJECT} PRIVATE glew glm imgui)
target_link_libraries(${CGRA_PROJECT} PRIVATE nfd_lib)
target_link_libraries(${CGRA_PROJECT} PRIVATE ${GTK3_LIBRARIES})
target_link_libraries(${CGRA_PROJECT} PRIVATE stdc++fs)

target_include_directories(${CGRA_PROJECT} PRIVATE "${PROJECT_SOURCE_DIR}/src")
target_include_directories(${CGRA_PROJECT} PRIVATE "${PROJECT_SOURCE_DIR}/include/skeleton")

# Set the source directory as a preprocessor define, used to make sure that the relative paths
# work correctly, regardless of where the project is run fron (as long as it's run on the same
# machine it was built on).
target_compile_definitions(${CGRA_PROJECT} PRIVATE "-DCGRA_SRCDIR=\"${PROJECT_SOURCE_DIR}\"")
