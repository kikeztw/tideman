#include <iostream>

#include <Tideman.hpp>

using namespace std;

int main()
{
  size_t num_candidates{0};
  cin >> num_candidates;

  vector<string> candidates{num_candidates, ""};

  for (int i = 0; i < num_candidates; ++i)
  {
    cin >> candidates[i];
  }

  size_t num_voters{0};
  cin >> num_voters;

  Tideman tideman{candidates};

  for (int i = 0; i < num_voters; ++i)
  {
    vector<int> ranks(num_candidates, -1);

    for (int j = 0; j < num_candidates; ++j)
    {
      string name{};
      cin >> name;

      if (!tideman.vote(j, name, ranks))
      {
        cout << "Invalid vote\n";
        return EXIT_FAILURE;
      }
    }

    tideman.record_preferences(ranks);
  }

  string expected_winner{};
  cin >> expected_winner;

  auto pairs = tideman.create_pairs();
  auto locked = Tideman::lock_pairs(pairs, num_candidates);
  
  try
  {
    auto winner = tideman.get_winner(locked);
    cout << "Winner: " << winner << endl;    
  }
  catch (const exception& e)
  {
    cout << e.what() << endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
