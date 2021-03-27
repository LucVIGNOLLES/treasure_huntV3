cmake_minimum_required(VERSION 2.8.3)
project(treasure_hunt_server CXX)

SET(DUELS_ROOT "/opt/duels" CACHE STRING "Path to duels installation folder")
set(CMAKE_INSTALL_PREFIX ${DUELS_ROOT})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-pthread)
find_package (Threads)

# find ZeroMQ
find_path ( ZMQ_INCLUDE_DIR zmq.h )
find_library ( ZMQ_LIBRARY NAMES zmq )

include_directories(include ${DUELS_ROOT}/include ${ZMQ_INCLUDE_DIR})
add_definitions(-DDUELS_BIN_PATH="${DUELS_ROOT}/bin")
add_definitions(-DGAME_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(treasure_hunt_server server.cpp Boat_game.cpp Boat_game.h AI.h AI.cpp)
target_link_libraries(treasure_hunt_server ${CMAKE_THREAD_LIBS_INIT} ${ZMQ_LIBRARY})

# add whatever is needed to build display executable


# install server
install(TARGETS treasure_hunt_server DESTINATION bin)

# install gui and its deps
install(FILES treasure_hunt_gui.py DESTINATION bin
        PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
        
# client headers and templates
install(FILES include/duels/treasure_hunt/game.h include/duels/treasure_hunt/msg.h DESTINATION include/duels/treasure_hunt)
install(FILES client_template/CMakeLists.txt DESTINATION games/treasure_hunt)
install(FILES client_template/treasure_hunt.cpp DESTINATION games/treasure_hunt )
