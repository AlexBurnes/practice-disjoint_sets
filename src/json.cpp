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
#include "json.hpp"

#include <fmt/core.h>

#include <memory>

/*!@func read_file
 * Read file into buffer char[], private function
 * @param file_name, File name to read
 * @return unique_ptr<char *>, Reference to buffer of file size, or nullptr if failed open file
 */
std::unique_ptr<char[]> read_file(const std::string &file_name) {
    std::ifstream file;
    file.exceptions(std::ifstream::failbit);
    size_t size;
    try {
        file.open(file_name);
    } catch (...) {
        return nullptr;
    }
    file.seekg(0, std::ios::end);
    size = file.tellg();
    file.seekg(0, std::ios::beg);
    auto buffer = std::make_unique<char[]>(size + 1);
    file.read(buffer.get(), size);
    buffer.get()[size] = 0;
    file.close();
    return buffer;
}

/*!@func parse_json
 * Parse json file as array of integer
 * @param list_file, File name of json file, std::string
 * @param dst_list, Reference to vector of integers Grouping::file_list_t
 * @return 0 on failure, 1 on success
 */
int parse_json(const std::string &list_file, Grouping::file_list_t &dst_list) {
    /*read file*/
    auto json = read_file(list_file);
    if (json == nullptr) {
        fmt::print("failed open file {}\n", list_file);
        return 0;
    }
    /*parse file content as json*/
    rapidjson::Document document;
    if (document.Parse(json.get()).HasParseError()) {
        fmt::print(
            "Error: {} is not valid json, failed parse at {}, error {}\n", list_file,
            (unsigned)document.GetErrorOffset(), rapidjson::GetParseError_En(document.GetParseError())
        );
        return 0;
    }

    /*check json is Array*/
    if (not document.IsArray()) {
        fmt::print("Error: {} is not a json array of integer\n", list_file);
    }
    int  i = 0;
    auto json_array = document.GetArray();
    dst_list.reserve(json_array.Size());

    /*require unique list*/
    std::unordered_map<int, bool> dst_map;

    /*featch array element is integers*/
    for (auto &element : json_array) {
        if (not element.IsNumber()) {
            fmt::print("Error: {} element [{}] is not an integer\n", list_file, i);
        }
        i++;
        int dst_id = element.GetInt();
        if (not dst_map.count(dst_id)) {
            dst_list.push_back(dst_id);
            dst_map[dst_id] = true;
        }
    }
    return 1;
}
