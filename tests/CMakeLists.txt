# ============================================================================
#
# This file hosts all tests.
#
# If INCLUDE_PILE_SOURCES_DIRECTLY is ON then DXF_SOURCES and
# DXF_HEADERS are defined we add them to the executable. DXF_LIBRARY
# is empty.
#
# On the other hand if INCLUDE_PILE_SOURCES_DIRECTLY is
# OFF then DXF_SOURCES and DXF_HEADERS are empty and we link
# against DXF_LIBRARY that is now the name of the target that
# builds the library.
#
# ============================================================================

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

if (NOT INCLUDE_PILE_SOURCES_DIRECTLY)
    set (DXF_LIBRARY dxf)
endif()

add_executable(test_basic
    ${DXF_SOURCES}
    ${DXF_HEADERS}
    ${USERMSG_SOURCES}
    ${USERMSG_HEADERS}
    basic.cc)

target_link_libraries(test_basic
    ${GTEST_BOTH_LIBRARIES}
    ${DXF_LIBRARY}
    ${USERMSG_LIBRARY})

qt5_use_modules (test_basic Core)

add_test(
    NAME test_basic
    COMMAND $<TARGET_FILE:test_basic>)
