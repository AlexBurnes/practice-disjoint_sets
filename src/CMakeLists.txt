# Student practice C++ searching disjoint sets
# Copyright 2025 AlexBurnes@gmail.com
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
include_directories(include)

add_library(
    grouping
        grouping.cpp
)


set(
    GROUPS_SOURCE_FILES
        main.cpp
        json.cpp
)

add_executable(
    ${CMAKE_PROJECT_NAME}
        ${GROUPS_SOURCE_FILES}
)

target_compile_definitions(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
        $<TARGET_PROPERTY:grouping,COMPILE_DEFINITIONS>
)

target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
        grouping
        fmt::fmt
        lazycsv::lazycsv
        cxxopts::cxxopts
        rapidjson
        range-v3::range-v3
)

add_subdirectory(tests)

add_executable(
    ${CMAKE_PROJECT_NAME}_profile-heap
        ${GROUPS_SOURCE_FILES}
)

target_compile_definitions(
    ${CMAKE_PROJECT_NAME}_profile-heap
    PRIVATE
        PROFILE_HEAP
        $<TARGET_PROPERTY:grouping,COMPILE_DEFINITIONS>
)

target_link_libraries(
    ${CMAKE_PROJECT_NAME}_profile-heap
    PRIVATE
        grouping
        fmt::fmt
        lazycsv::lazycsv
        cxxopts::cxxopts
        rapidjson
        range-v3::range-v3
        gperftools::gperftools
        tcmalloc
)


add_executable(
    ${CMAKE_PROJECT_NAME}_profile-cpu
        ${GROUPS_SOURCE_FILES}
)

target_compile_definitions(
    ${CMAKE_PROJECT_NAME}_profile-cpu
    PRIVATE
        PROFILE_CPU
        $<TARGET_PROPERTY:grouping,COMPILE_DEFINITIONS>
)

target_link_libraries(
    ${CMAKE_PROJECT_NAME}_profile-cpu
    PRIVATE
        grouping
        fmt::fmt
        lazycsv::lazycsv
        cxxopts::cxxopts
        rapidjson
        range-v3::range-v3
        gperftools::gperftools
        profiler
)

install(
    TARGETS
        ${CMAKE_PROJECT_NAME}
        ${CMAKE_PROJECT_NAME}_profile-heap
        ${CMAKE_PROJECT_NAME}_profile-cpu
    RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
)
