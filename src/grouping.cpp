// Student practice C++ searching disjoint sets
// Copyright 2025 AlexBurnes@gmail.com
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include "grouping.hpp"

/*!@ctor Grouping from vector of source destination pairs */
Grouping::Grouping(const files_link_t &&file_map) {
    //FIXME implement
}

/*!@func Grouping::push */
void Grouping::push(const int src_id, const int dst_id) {
    //FIXME implement
}

/*!@func Grouping::merge */
void Grouping::merge(
    const int group_id, file_list_t &a, file_list_t &b, group_map_t &src_group, group_map_t &dst_group
) {
    //FIXME implement
    return;
}

/*!@func Grouping::find */
Grouping::group_files_t Grouping::find(const file_list_t &list) {
    /*!@variable found
     * map of found groups, group contain list of source files, group => [src_id, ...]
     */
    group_files_t found;

    //FIXME implement

    return found;
}
