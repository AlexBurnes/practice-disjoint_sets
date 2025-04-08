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
#include <fmt/core.h>

#include <cxxopts.hpp>
#include <lazycsv.hpp>

#include <range/v3/all.hpp>
#include <vector>

#define VERSION "0.1.0"

#include "grouping.hpp"
#include "json.hpp"

#ifdef PROFILE_HEAP
#include <gperftools/heap-profiler.h>
#endif

#ifdef PROFILE_CPU
#include <gperftools/profiler.h>
#endif

int main(int argc, const char *argv[]) {

#ifdef PROFILE_HEAP
    HeapProfilerStart("var/profiles/heap/groups_profile");
#endif

#ifdef PROFILE_CPU
    ProfilerStart("var/profiles/cpu/groups_profile");
#endif

    cxxopts::Options options("groups", "Find nonintersected groups of source files by destination files");
    options.add_options()
        ("v,version", "Print version and exits")
        ("h,help", "Print help and exits")
        ("d,details", "Print list of files in found groups")
        ("mapping", "csv file contains source destination file relations format: src_id;dst_id",
            cxxopts::value<std::string>()
        )
        ("list", "json file contains list of destionation files for search, format: [dst_id, ...]",
            cxxopts::value<std::string>()
        );
    options.positional_help("mapping.csv [list.json]");
    options.parse_positional({"mapping", "list"});
    auto option = options.parse(argc, argv);

    if (option.count("help")) {
        fmt::print("{}\n", options.help());
        return 0;
    }

    if (option.count("version")) {
        fmt::print("{}\n", VERSION);
        return 0;
    }

    if (option.count("mapping") == 0) {
        fmt::print("usage: groups mapping.csv [list.json]");
        fmt::print("groups -h|--help for details");
        return 1;
    }

    Grouping                      grouping;
    Grouping::file_list_t         dst_list;
    std::unordered_map<int, bool> dst_map;
    bool                          has_list = false;

    /* read json if defined */
    if (option.count("list")) {
        has_list = true;
        if (not parse_json(option["list"].as<std::string>(), dst_list)) {
            return 1;
        }
    }

#ifdef PROFILE_HEAP
    HeapProfilerDump("var/profiles/heap/groups_profile");
#endif

    int rows = 0;
    try {
        lazycsv::parser<lazycsv::mmap_source, lazycsv::has_header<true>, lazycsv::delimiter<';'> > parser{
            option["mapping"].as<std::string>()};
        for (const auto row : parser) {
            const auto [src_id_str, dst_id_str] = row.cells(0, 1);
            int src_id, dst_id;
            grouping.push(
                src_id = std::stoi(std::string{src_id_str.raw()}),
                dst_id = std::stoi(std::string{dst_id_str.raw()})
            );
            rows++;
            if (has_list) continue;
            if (not dst_map.count(dst_id)) {
                dst_list.push_back(dst_id);
                dst_map[dst_id] = true;
            }
        }
    } catch (...) {
        fmt::print("Failed open or parse mapping file {}\n", option["mapping"].as<std::string>());
        return 1;
    }

#ifdef PROFILE_HEAP
    HeapProfilerDump("var/profiles/heap/groups_profile");
#endif

    fmt::print("Readed mapping source to destination files {}: {}\n", option["mapping"].as<std::string>(), rows);

    if (has_list) {
        fmt::print(
            "Search groups by destination file list {}: {}\n", option["list"].as<std::string>(), dst_list.size()
        );
    } else {
        fmt::print("Search groups by all destination files: {}\n", dst_list.size());
    }
    auto groups = grouping.find(dst_list);

#ifdef PROFILE_HEAP
    HeapProfilerDump("var/profiles/heap/groups_profile");
#endif

    fmt::print("Groups found: {}\n", groups.size());
    auto keys = groups
        | ranges::views::keys
        | ranges::views::transform([](auto &&v){return v;})
        | ranges::to<std::vector>()
        | ranges::actions::sort;
    for (auto &&group_id : keys) {
        auto files = groups[group_id];
        files |= ranges::actions::sort;
        fmt::print("\t[{}]: {}\n", group_id, files.size());
        if (option.count("details")) {
            for (auto &&src_id : files) {
                fmt::print("\t\t{}\n", src_id);
            }
        }
    }

#ifdef PROFILE_HEAP
    HeapProfilerDump("var/profiles/heap/groups_profile");
    HeapProfilerStop();
#endif

#ifdef PROFILE_CPU
    ProfilerStop();
#endif


    return 0;
}
