set(target_name "meteos")

# include(${QT_USE_FILE})
include_directories(${QT_INCLUDES})

set(SRCS
main.cpp
mainwindow.cpp
gamescene.cpp
block.cpp
hud/timer.cpp
)

set(HDRS
mainwindow.h
gamescene.h
block.h
hud/timer.h
)

qt5_wrap_cpp(MOCS ${HDRS})

add_executable(${target_name} ${SRCS} ${MOCS})
# target_link_libraries(${target_name} ${QT_LIBRARIES})
qt5_use_modules(${target_name} Widgets)
