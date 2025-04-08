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
#pragma once
#include <iterator>
#include <string>
#include <unordered_map>
#include <vector>
#include "types.hpp"

/*!@class Grouping
 * container for file mapping and function to search non intersected groups of souce files for dest files
 */
struct Grouping {
        /*!@type file_list_t
         * list of files: [file_id, ...]
         */
        typedef vector<int> file_list_t;

        /*!@type files_link_t
         * list of file pairs, link between source and destination file: [{src_id, dst_id}, ...]
         */
        typedef vector<pair<int, int>> files_link_t;

        /*!@type file_map_t
         * map of files and link files for it, file_id => [file_id, ...]
         */
        typedef map<int, file_list_t> file_map_t;

        /*!@type group_files_t
         * map of group and list of files for it, group => [file_id, ...]
         */
        typedef map<int, file_list_t> group_files_t;

        /*!@type group_map_t
         * map of groups and files in group, group_id => [file_id, ...]
         */
        typedef map<int, int> group_map_t;

        /*!@ctor default */
        Grouping(){};

        /*!@ctor Init internal structures from list of source and destination file pairs
         *@param file_map, vector of file pairs, source file and destination file
         */
        explicit Grouping(const files_link_t &&file_map);

        /*!@dtor default */
        ~Grouping() {};

        /*!@func push
         * add link for source file to destination file into search structures, src_id, dst_id
         * @param src_id file identifier for source file
         * @param dst_id file identifier for destination file
         */
        void push(const int src_id, const int dst_id);

        /*!@func find
         * Find nonintersection groups of source files by list of destination files
         * @param list list of destination files
         * @returns map of groups to list of destination file for each group: group_id => [src_id, ...]
         */
        group_files_t find(const file_list_t &list);

    private:
        /*!@member src_map
         * Map of source files and link destination files for it, src_id => [dst_id, ...]
         */
        file_map_t src_map;

        /*!@member dst_map
         * map of destination files and link source files for it, dst_id => [src_id, ...]
         */
        file_map_t dst_map;

        /*!@func merge
         * merge groups of type file_list_t, merge group b into a
         * @param group_id, id of group a
         * @param a, file list of source files for group a
         * @param b, file list of source files for group b
         * @param src_group, mapping source file to group, src_id => group_id
         * @param dst_group, mapping destination file to group, dst_id => group_iod
         * @return nothing
         */
        void merge(const int group_id, file_list_t& a, file_list_t& b, group_map_t& src_group, group_map_t& dst_group);
};
