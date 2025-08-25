link_directories( ${GTKMM_LIBRARY_DIRS} )

include_directories( ${GTKMM_INCLUDE_DIRS} )

# Add other flags to the compiler like -std+c++11 and etc.
add_definitions(${GTKMM_CFLAGS_OTHER})

add_executable(
    Practice       # name of the executable on Windows will be gtkmm-hello.exe
    main.cpp
    prWindow.cpp
    MyDraw.cpp
    prWindow.hpp
    MyDraw.hpp
    Data.hpp
)

target_link_libraries(Practice ${GTKMM_LIBRARIES} )
