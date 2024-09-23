cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

add_executable(task_02-01 task_1/01.cc)
add_executable(task_02-02 task_2/02.cc)
add_executable(task_02-03 task_3/03.cc)
add_executable(task_02-04 task_4/04.cc)
add_executable(task_02-05 task_5/05.cc)
add_executable(task_02-06 task_6/06.cc)

set_target_properties(
        ${TASK_NAME}
        PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)