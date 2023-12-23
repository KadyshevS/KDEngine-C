cmake_minimum_required(VERSION 3.15)

set(WORKSPACE_PATH D:/VSCodeProjs/C/Game1)
set(CORE_PRJ_PATH ${WORKSPACE_PATH})

set(CORE_INC_PATH ${CORE_PRJ_PATH}/inc)
set(CORE_SRC_PATH ${CORE_PRJ_PATH}/src)

set(CORE_INC_PATH_THIRD ${CORE_PRJ_PATH}/ven/inc)
set(CORE_SRC_PATH_THIRD ${CORE_PRJ_PATH}/ven/src)
set(CORE_LIB_PATH_THIRD ${CORE_PRJ_PATH}/bin)

file(GLOB CORE_SRC_FILES
    "${CORE_INC_PATH}/*.h",
    "${CORE_INC_PATH}/**/*.h",
    "${CORE_INC_PATH}/**/**/*.h",
    "${CORE_SRC_PATH}/*.c",
    "${CORE_SRC_PATH}/**/*.c",
    "${CORE_SRC_PATH}/**/**/*.c"

    "${CORE_INC_PATH_THIRD}/*.h",
    "${CORE_INC_PATH_THIRD}/**/*.h",
    "${CORE_INC_PATH_THIRD}/**/**/*.h",
    "${CORE_SRC_PATH_THIRD}/*.c",
    "${CORE_SRC_PATH_THIRD}/**/*.c",
    "${CORE_SRC_PATH_THIRD}/**/**/*.c"
)

project(Game1)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CORE_PRJ_PATH}/bin")
include_directories(Game1 ${CORE_INC_PATH} ${CORE_INC_PATH_THIRD})
link_directories(Game1 ${CORE_LIB_PATH_THIRD})

add_executable(Game1 ${CORE_SRC_FILES})
target_link_libraries(Game1 SDL2)