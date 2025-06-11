#include <aligncount/aligncount.h>
#include <aligncount/version.h>

#include <cxxopts.hpp>
#include <iostream>
#include <string>
#include <filesystem>

auto main(int argc, char** argv) -> int {

  cxxopts::Options options(*argv, "A program to count alignment records");

  std::string alignments;

  // clang-format off
  options.add_options()
    ("h,help", "Show help")
    ("v,version", "Print the current version number")
    ("a,alignments", "Path to SAM/BAM/CRAM file.", cxxopts::value(alignments)->default_value(""))
  ;
  // clang-format on

  auto result = options.parse(argc, argv);

  if (result["help"].as<bool>()) {
    std::cout << options.help() << "\n";
    return 0;
  }

  if (result["version"].as<bool>()) {
    std::cout << "Aligncount, version " << ALIGNCOUNT_VERSION << "\n";
    return 0;
  }

  if (alignments.empty()) {
    std::cout << "alignments file not specified!" << "\n";
    return 1;
  }

  std::filesystem::path p = alignments;
  if (!exists(p) || !is_regular_file(p)) {
    std::cout << "File " << p << " does not exist!" << "\n";
    return 1;
  }

  aligncount::Aligncount aligncount(alignments);
  std::cout << aligncount.count_records()  << "\n";

  return 0;
}