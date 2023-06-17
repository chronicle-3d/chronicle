add_subdirectory(GLFW)

target_sources(chronicle-core
PRIVATE
    "Platform.cpp"
    "Platform.h"
    "Window.h"
)