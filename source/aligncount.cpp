#include <aligncount/aligncount.h>
#include <fmt/format.h>
#include <iostream>
#include <string>
#include <cstdlib>

// HTSlib headers
extern "C" {
#include <htslib/sam.h>
}

using namespace aligncount;

Aligncount::Aligncount(std::string file_path) : m_alignment_file(std::move(file_path)) {}

uint64_t Aligncount::count_records() const {

  const char* fname = m_alignment_file.c_str();

  // Open the SAM/BAM/CRAM file
  htsFile* fp = sam_open(fname, "r");
  if (!fp) {
    std::cerr << fmt::format("cannot open \"{}\"", m_alignment_file) << "\n";
    std::exit(EXIT_FAILURE);
  }

  // Read the header
  bam_hdr_t* hdr = sam_hdr_read(fp);
  if (!hdr) {
    std::cerr << fmt::format("Failed to read header from: \"{}\"", m_alignment_file) << "\n";
    sam_close(fp);
    std::exit(EXIT_FAILURE);
  }

  // Prepare alignment record
  bam1_t* rec = bam_init1();

  // Iterate through all records and count
  uint64_t count = 0;
  while (sam_read1(fp, hdr, rec) >= 0) {
    ++count;
  }

  // Clean up
  bam_destroy1(rec);
  bam_hdr_destroy(hdr);
  sam_close(fp);

  return count;
}