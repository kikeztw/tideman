// Carlos Enrique Hurtado Puente 22929504
// #include <NoImplementedException.hpp>
// #include <NoWinnerException.hpp>
#include <Tideman.hpp>
#include <iostream>
#include <algorithm>

bool makes_circle(size_t first, size_t second, std::vector<std::vector<bool>>& locked, std::vector<bool>& visited, size_t num_candidates) noexcept
{
  if (first == second)
  {
    return true;
  }

  visited[second] = true;

  for (size_t i = 0; i < num_candidates; i++)
  {
    if(locked[second][i]){
      if (!visited[i] &&  makes_circle(first, i, locked, visited, num_candidates))
      {
        return true;
      }
    }
  }

  return false;
}

Tideman::Tideman(const std::vector<std::string>& _candidates) noexcept
  : candidates{_candidates}, preferences{candidates.size(), std::vector<int>(candidates.size(), 0)}
{
  // empty
}

const std::vector<std::string>& Tideman::get_candidates() const noexcept
{
  return candidates;
}

const std::vector<std::vector<int>>& Tideman::get_preferences() const noexcept
{
  return preferences;
}

bool Tideman::vote(int rank, const std::string& name, OUT_PARAM std::vector<int>& ranks) const noexcept
{
    int index = -1;
    size_t candidate_count_ =  candidates.size();
    for (int i = 0; i < candidate_count_; i++) {
      if (candidates[i] == name) {
        index = i;
        break;
      }
    }

    if (index == -1) {
      return false;
    }

    if (rank < 0 || rank >= candidate_count_) {
      return false;
    }

    ranks[rank] = index;
    return true;
}

void Tideman::record_preferences(const std::vector<int>& ranks) noexcept
{
  size_t candidate_count_ =  candidates.size();
  for (int i = 0; i < candidate_count_; i++) {
    for (int j = i + 1; j < candidate_count_; j++) {
      int candidate_i = ranks[i];
      int candidate_j = ranks[j];
      preferences[candidate_i][candidate_j]++;
    }
  }
}

std::vector<std::pair<int, int>> Tideman::create_pairs() const noexcept
{

    size_t candidate_count_ =  candidates.size();
    std::vector<std::pair<int, int>> pairs;

    for (int i = 0; i < candidate_count_; i++) {
      for (int j = i; j < candidate_count_; j++) {
        if (i != j) {
          int pref_i_j = preferences[i][j];
          int pref_j_i = preferences[j][i];

          if (pref_i_j > pref_j_i) {
            pairs.push_back({i, j});
          }else if (pref_i_j < pref_j_i) {
            pairs.push_back({j, i});
          }
        }
      }
    }

    std::sort(pairs.begin(), pairs.end(), [&](std::pair<int, int> a, std::pair<int, int> b) {
      int pref_a = preferences[a.first][a.second];
      int pref_b = preferences[b.first][b.second];
      return pref_a > pref_b;
    });

    return pairs;
}


std::vector<std::vector<bool>> Tideman::lock_pairs(const std::vector<std::pair<int, int>>& pairs, size_t num_candidates) noexcept
{
  std::vector<std::vector<bool>> locked(num_candidates, std::vector<bool>(num_candidates, false));

  for(auto& _pair: pairs){
    std::vector<bool> visited(num_candidates, false);
    if(!makes_circle(_pair.first, _pair.second, locked, visited, num_candidates)){
      locked[_pair.first][_pair.second] = true;
    }
  }

  return locked;
}

std::string Tideman::get_winner(const std::vector<std::vector<bool>>& locked) const
{
  std::vector<int> sources;
  size_t candidate_count_ =  candidates.size();
  for (int i = 0; i < candidate_count_; i++) {
    bool has_edge = false;
    for (int j = 0; j < candidate_count_; j++) {
      if (locked[j][i]) {
        has_edge = true;
        break;
      }
    }
    if (!has_edge) {
      sources.push_back(i);
    }
  }

  if (sources.empty()) {
    // throw NoWinnerException();
  }

  if (sources.size() == 1) {
    return candidates[sources[0]];
  }


  for (int source : sources) {
    bool is_source_winner = true;
    for (int j = 0; j < candidate_count_; j++) {
      if (locked[source][j] && std::find(sources.begin(), sources.end(), j) != sources.end()) {
        is_source_winner = false;
        break;
      }
    }
    if (is_source_winner) {
      return candidates[source];
    }
  }

  // throw NoWinnerException();
}
