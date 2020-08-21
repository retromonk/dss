add_executable(dss_test main.cpp 
    data/data_provider.cpp 
    data/image_provider.cpp
    ui/background.cpp 
    ui/button.cpp 
    ui/controller.cpp 
    ui/display.cpp 
    ui/selector.cpp 
    ui/text.cpp)

target_link_libraries(dss_test ${CONAN_LIBS} -lSOIL -lftgl)

add_custom_command(TARGET dss_test PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/resources/ $<TARGET_FILE_DIR:dss_test>)
