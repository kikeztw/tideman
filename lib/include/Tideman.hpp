#pragma once

#include <string>
#include <vector>

#include <IOUtils.hpp>

class Tideman
{
public:
  /** Constructor that receives que list of canditates.
   * 
   * It initializes the list of candidates from the list passed as an argument, then,
   * lets n be the number of candidates, it initializes the matrix of preferences to
   * be an n x n matrix filled with zeros.
   */
  Tideman(const std::vector<std::string>& _candidates) noexcept;

  const std::vector<std::string>& get_candidates() const noexcept;

  const std::vector<std::vector<int>>& get_preferences() const noexcept;

  bool vote(int rank, const std::string& name, OUT_PARAM std::vector<int>& ranks) const noexcept;

  void record_preferences(const std::vector<int>& ranks) noexcept;

  std::vector<std::pair<int, int>> create_pairs() const noexcept;

  static std::vector<std::vector<bool>> lock_pairs(const std::vector<std::pair<int, int>>& pairs, size_t num_candidates) noexcept;

  std::string get_winner(const std::vector<std::vector<bool>>& locked) const;

private:
  const std::vector<std::string>& candidates;
  std::vector<std::vector<int>> preferences;
};
