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
add_executable(
    test_grouping
        test.cpp
)

target_compile_definitions(
    test_grouping
    PRIVATE
        $<TARGET_PROPERTY:grouping,COMPILE_DEFINITIONS>
)


target_link_libraries(
    test_grouping
        PRIVATE
            grouping
            GTest::gtest_main
)

add_test(
    NAME grouping
    COMMAND $<TARGET_FILE:test_grouping>
)

add_executable(
    test_bench
        bench.cpp
)

target_link_libraries(
    test_bench
        PRIVATE
            grouping
            benchmark::benchmark_main
            gperftools::gperftools
)


install(
    TARGETS
        test_grouping
        test_bench
    RUNTIME DESTINATION bin
)
