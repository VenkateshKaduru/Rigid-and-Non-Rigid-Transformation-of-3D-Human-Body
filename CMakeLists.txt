
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(Reader)

find_package(VTK COMPONENTS 
  vtkFiltersCore
  vtkFiltersSources
  vtkIOLegacy
  vtkCommonColor
  vtkCommonCore
  vtkCommonDataModel
  vtkFiltersGeneral
  vtkInteractionStyle
  vtkRenderingCore
  vtkRenderingFreeType
  vtkCommonMath
  vtkCommonTransforms
  vtkRenderingOpenGL2 QUIET)
if (NOT VTK_FOUND)
  message("Skipping Reader: ${VTK_NOT_FOUND_MESSAGE}")
  return ()
endif()
message (STATUS "VTK_VERSION: ${VTK_VERSION}")
if (VTK_VERSION VERSION_LESS "8.90.0")
  # old system
  include(${VTK_USE_FILE})
  add_executable(Reader MACOSX_BUNDLE main.cxx )
  target_link_libraries(Reader PRIVATE ${VTK_LIBRARIES})
else ()
  # include all components
  add_executable(Reader MACOSX_BUNDLE main.cxx )
  target_link_libraries(Reader PRIVATE ${VTK_LIBRARIES})
  # vtk_module_autoinit is needed
  vtk_module_autoinit(
    TARGETS Reader
    MODULES ${VTK_LIBRARIES}
    )
endif () 
target_compile_features(Reader PRIVATE cxx_range_for)
