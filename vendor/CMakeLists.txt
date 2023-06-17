# Add SPDLOG
set(SPDLOG_NO_EXCEPTIONS OFF CACHE BOOL "" FORCE)
add_subdirectory(spdlog EXCLUDE_FROM_ALL)

# Add Google DAWN
set(DAWN_BUILD_SAMPLES OFF CACHE INTERNAL "" FORCE)
set(DAWN_EMIT_COVERAGE OFF CACHE INTERNAL "" FORCE)
set(TINT_BUILD_TESTS OFF CACHE INTERNAL "" FORCE)
set(TINT_BUILD_SAMPLES OFF CACHE INTERNAL "" FORCE)
add_subdirectory(dawn EXCLUDE_FROM_ALL)

# Add Magic Enum
add_subdirectory(magic_enum EXCLUDE_FROM_ALL)

# Add HarfBuzz
#add_subdirectory(harfbuzz EXCLUDE_FROM_ALL)

# Add FreeType
#add_subdirectory(freetype EXCLUDE_FROM_ALL)

# Add RmlUi
#set(NO_FONT_INTERFACE_DEFAULT ON CACHE INTERNAL "" FORCE)
add_subdirectory(rmlui EXCLUDE_FROM_ALL)