#pragma once

#include <string>

namespace aligncount {

  /**
   * @brief A class for counting alignment records
   */
  class Aligncount {

    std::string m_alignment_file;

  public:
    /**
     * @brief Creates a new aligncount
     * @param alignment file to read from
     */
    Aligncount(std::string file_path);

    /**
     * @brief Returns the number of alignment records parsed by htslib
     * @return an int representing the number of SAM records
     */
    [[nodiscard]] uint64_t count_records() const;
  };

}  // namespace aligncount