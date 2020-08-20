add_executable(dss_test main.cpp ui/background.cpp ui/button.cpp ui/controller.cpp ui/display.cpp ui/selector.cpp ui/text.cpp)
target_link_libraries(dss_test ${CONAN_LIBS} -lSOIL -lftgl)