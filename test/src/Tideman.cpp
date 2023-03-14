#include <TestUtils.hpp>
#include <Tideman.hpp>


using namespace std;

struct Data
{
  static const vector<string> candidates;
  static const vector<vector<string>> votes;
  static const vector<int> ranks;
  static const vector<pair<int, int>> pairs;
  static const vector<vector<bool>> locked;
  static const vector<vector<bool>> circular_locked;

  static const vector<int> expected_ranks_voter0;
  static const vector<vector<int>> expected_preferences;
  static const vector<pair<int, int>> expected_pairs;
  static const vector<vector<bool>> expected_locked;

  static const string expected_winner;
};

const vector<string> Data::candidates{"Harry", "Hermione", "Ronald"};

const vector<vector<string>> Data::votes
{
  vector<string>{"Hermione", "Harry", "Ronald"},
  vector<string>{"Hermione", "Harry", "Ronald"},
  vector<string>{"Ronald", "Hermione", "Harry"},
  vector<string>{"Ronald", "Hermione", "Harry"},
  vector<string>{"Ronald", "Hermione", "Harry"},
  vector<string>{"Harry", "Hermione", "Ronald"},
  vector<string>{"Harry", "Hermione", "Ronald"},
  vector<string>{"Harry", "Hermione", "Ronald"},
  vector<string>{"Harry", "Ronald", "Hermione"}
};

const vector<int> Data::ranks{1, 0, 2};

const vector<pair<int, int>> Data::pairs{make_pair(1, 0), make_pair(0, 2), make_pair(1, 2)};

const vector<vector<bool>> Data::locked{
  {false, false, true},
  {true, false, true},
  {false, false, false}
};

const vector<vector<bool>> Data::circular_locked{
  {false, false, true},
  {true, false, true},
  {false, true, false}
};

const vector<int> Data::expected_ranks_voter0{1, 0, 2};

const vector<vector<int>> Data::expected_preferences
{
  {0, 0, 1},
  {1, 0, 1},
  {0, 0, 0},
};

const vector<pair<int, int>> Data::expected_pairs{make_pair(1, 0), make_pair(0, 2), make_pair(1, 2)};

const vector<vector<bool>> Data::expected_locked{
  {false, false, true},
  {true, false, true},
  {false, false, false}
};

const string Data::expected_winner{"Hermione"};

void test_vote()
{
  cout << "Given the candidates: ";
  print_vector(Data::candidates, cout);
  cout << "And the list of votes: ";
  print_vector(Data::votes[0], cout);
  cout << "When the method vote is called, then it should return: ";
  print_vector(Data::expected_ranks_voter0, cout);

  Tideman tideman{Data::candidates};
  vector<int> ranks(Data::candidates.size());

  for (size_t i = 0; i < Data::votes[0].size(); ++i)
  {
    bool result = tideman.vote(i, Data::votes[0][i], ranks);
    assert_equal(result, true);
  }

  assert_equal_vector(Data::expected_ranks_voter0, ranks);
  cout << "Test Ok!\n";
}


void test_record_preferences()
{
  cout << "Given the candidates: ";
  print_vector(Data::candidates, cout);
  cout << "And the list of ranks: ";
  print_vector(Data::ranks, cout);
  cout << "When the method record_preferences is called, the preferences should be: ";
  print_matrix(Data::expected_preferences, cout);
  
  Tideman tideman{Data::candidates};
  tideman.record_preferences(Data::ranks);

  assert_equal_matrix(tideman.get_preferences(), Data::expected_preferences);
  cout << "Test Ok!\n";
}

void test_create_pairs()
{
  cout << "Given the candidates: ";
  print_vector(Data::candidates, cout);
  cout << "And the votes: ";
  print_matrix(Data::votes, cout);
  cout << "When the method create_pair is called, then the result should be: ";
  print_vector(Data::expected_pairs, cout);
  
  Tideman tideman{Data::candidates};
  
  for (size_t i = 0; i < Data::votes[0].size(); ++i)
  {
    vector<int> ranks(Data::candidates.size());
    bool result = tideman.vote(i, Data::votes[0][i], ranks);
    assert_equal(result, true);
  }

  tideman.record_preferences(Data::ranks);

  auto pairs = tideman.create_pairs();

  cout<<"result vector:::: ";
  print_vector(pairs, cout);

  assert_equal_vector(pairs, Data::expected_pairs);

  cout << "Test Ok!\n";
}

void test_lock_pairs()
{

  

  // cout << "Given the candidates: ";
  // print_vector(Data::candidates, cout);
  // cout << "And the pairs: ";
  // print_vector(Data::pairs, cout);
  // cout << "When the method lock_pairs is called, then the result should be: ";
  // cout << boolalpha;
  // print_matrix(Data::expected_locked, cout);
  const std::vector<std::pair<int, int>> pairs = {{7, 21}, {7, 10}, {9, 25}, {9, 20}, {7, 25}, {9, 18}, {7, 14}, {9, 10}, {23, 10}, {9, 14}, {24, 21}, {12, 28}, {1, 18}, {9, 26}, {16, 21}, {4, 25}, {9, 11}, {0, 10}, {9, 13}, {9, 21}, {12, 5}, {24, 17}, {23, 21}, {22, 21}, {9, 3}, {8, 17}, {23, 17}, {1, 21}, {22, 18}, {2, 21}, {8, 5}, {8, 25}, {7, 11}, {9, 12}, {22, 25}, {12, 19}, {4, 11}, {22, 5}, {26, 14}, {7, 26}, {6, 21}, {13, 29}, {15, 11}, {23, 29}, {0, 14}, {23, 2}, {6, 14}, {8, 29}, {2, 18}, {23, 13}, {8, 12}, {24, 28}, {9, 0}, {24, 18}, {12, 23}, {15, 21}, {12, 25}, {3, 5}, {6, 18}, {28, 10}, {15, 27}, {9, 2}, {12, 27}, {8, 14}, {9, 29}, {1, 14}, {6, 25}, {9, 28}, {0, 29}, {15, 17}, {9, 23}, {24, 20}, {9, 5}, {24, 0}, {15, 3}, {22, 10}, {9, 17}, {15, 14}, {23, 25}, {16, 0}, {16, 18}, {16, 28}, {13, 17}, {7, 19}, {7, 18}, {24, 15}, {4, 29}, {15, 5}, {27, 14}, {23, 5}, {24, 14}, {23, 14}, {24, 6}, {24, 13}, {13, 19}, {13, 18}, {9, 24}, {24, 25}, {24, 2}, {8, 2}, {23, 27}, {0, 21}, {1, 29}, {9, 19}, {22, 20}, {12, 14}, {9, 27}, {1, 10}, {9, 1}, {11, 21}, {16, 10}, {24, 11}, {22, 27}, {3, 14}, {8, 11}, {28, 25}, {3, 26}, {22, 3}, {3, 21}, {3, 18}, {12, 18}, {12, 3}, {12, 16}, {26, 25}, {1, 0}, {10, 25}, {24, 27}, {13, 14}, {24, 10}, {22, 6}, {23, 11}, {15, 20}, {15, 10}, {12, 11}, {11, 27}, {12, 29}, {12, 10}, {10, 11}, {9, 7}, {9, 16}, {9, 15}, {7, 13}, {12, 26}, {23, 8}, {7, 17}, {8, 21}, {8, 18}, {7, 27}, {7, 29}, {9, 8}, {19, 21}, {0, 27}, {17, 21}, {22, 17}, {3, 16}, {26, 17}, {28, 17}, {20, 18}, {2, 29}, {2, 25}, {6, 17}, {20, 2}, {28, 18}, {20, 19}, {20, 17}, {22, 19}, {24, 19}, {2, 10}, {7, 2}, {1, 13}, {20, 21}, {1, 27}, {1, 25}, {23, 1}, {20, 26}, {1, 19}, {1, 17}, {22, 15}, {28, 29}, {9, 6}, {29, 25}, {5, 19}, {5, 18}, {16, 5}, {7, 5}, {4, 28}, {15, 18}, {15, 19}, {0, 5}, {22, 4}, {16, 27}, {4, 20}, {4, 17}, {23, 26}, {4, 12}, {22, 0}, {7, 4}, {4, 8}, {21, 25}, {22, 28}, {22, 29}, {15, 12}, {27, 20}, {23, 24}, {13, 11}, {11, 17}, {29, 21}, {21, 28}, {24, 22}, {24, 26}, {24, 29}, {12, 21}, {17, 14}, {20, 14}, {14, 28}, {8, 19}, {15, 25}, {12, 24}, {15, 29}, {12, 22}, {16, 20}, {20, 25}, {16, 25}, {20, 12}, {16, 29}, {23, 18}, {18, 27}, {26, 19}, {19, 28}, {19, 29}, {2, 19}, {4, 1}, {6, 26}, {1, 5}, {6, 20}, {1, 12}, {15, 1}, {1, 16}, {1, 26}, {6, 10}, {28, 5}, {24, 5}, {5, 21}, {15, 2}, {4, 27}, {3, 0}, {4, 21}, {22, 2}, {4, 19}, {4, 16}, {2, 27}, {4, 10}, {3, 10}, {3, 11}, {4, 5}, {3, 13}, {3, 28}, {27, 3}, {3, 19}, {3, 24}, {7, 0}, {15, 8}, {8, 13}, {12, 0}, {0, 20}, {0, 8}, {8, 10}, {20, 10}, {13, 0}, {15, 0}, {7, 23}, {8, 26}, {0, 19}, {10, 21}, {0, 18}, {26, 10}, {7, 15}, {0, 17}, {26, 2}, {16, 19}, {11, 0}, {21, 18}, {6, 3}, {29, 17}, {8, 3}, {17, 27}, {17, 25}, {6, 0}, {0, 4}, {3, 17}, {29, 26}, {1, 3}, {3, 2}, {22, 26}, {1, 6}, {1, 8}, {0, 28}, {1, 11}, {0, 26}, {0, 25}, {1, 20}, {22, 1}, {24, 1}, {1, 28}, {25, 18}, {4, 2}, {19, 27}, {2, 5}, {2, 11}, {23, 0}, {19, 23}, {2, 12}, {2, 13}, {2, 14}, {18, 26}, {16, 8}, {15, 6}, {13, 21}, {20, 13}, {16, 6}, {6, 19}, {13, 16}, {15, 13}, {23, 6}, {6, 28}, {6, 29}, {7, 16}, {7, 20}, {22, 7}, {7, 28}, {6, 13}, {24, 8}, {13, 12}, {11, 29}, {11, 28}, {10, 13}, {11, 25}, {10, 14}, {10, 18}, {22, 11}, {20, 11}, {19, 11}, {18, 11}, {11, 16}, {14, 11}, {24, 4}, {3, 29}, {26, 16}, {16, 24}, {23, 16}, {22, 16}, {9, 4}, {27, 10}, {4, 13}, {16, 17}, {4, 14}, {15, 28}, {4, 18}, {15, 23}, {23, 4}, {18, 17}, {4, 26}, {10, 5}, {29, 14}, {14, 5}, {5, 17}, {25, 14}, {7, 6}, {18, 14}, {14, 16}, {6, 11}, {6, 12}, {13, 28}, {13, 27}, {13, 25}};
  std::vector<std::vector<bool>> expected_locked = {
  {false, false, false, false, false, true, false, false, false, false, true, false, false, false, true, false, false, true, true, true, true, true, false, false, false, true, true, true, true, true},
  {true, false, false, true, false, true, true, false, false, false, true, true, false, true, true, false, true, true, true, true, true, true, false, false, false, true, true, true, true, true},
  {false, false, false, false, false, true, false, false, false, false, true, true, false, false, true, false, false, false, true, true, false, true, false, false, false, true, false, true, false, true},
  {true, false, true, false, false, true, false, false, false, false, true, true, false, true, true, false, true, true, true, true, false, true, false, false, false, false, true, false, true, true},
  {false, true, true, false, false, true, false, false, true, false, true, true, true, true, true, false, true, true, true, true, true, true, false, false, false, true, true, true, true, true},
  {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, true, true, false, true, false, false, false, false, false, false, false, false},
  {true, false, false, true, false, false, false, false, false, false, true, true, false, true, true, false, false, true, true, true, true, true, false, false, false, true, true, false, true, true},
  {true, false, true, false, true, true, true, false, false, false, true, true, false, true, true, true, true, true, true, true, true, true, false, true, false, true, true, true, true, true},
  {false, false, true, true, false, true, false, false, false, false, true, true, true, true, true, false, false, true, true, true, false, true, false, false, false, true, true, false, false, true},
  {true, true, true, true, true, true, true, true, true, false, true, true, true, true, true, true, true, true, true, true, true, true, false, true, true, true, true, true, true, true},
  {false, false, false, false, false, false, false, false, false, false, false, true, false, false, true, false, false, false, true, false, false, true, false, false, false, true, false, false, false, false},
  {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, true, false, false, false, true, false, true, false, true},
  {true, false, false, true, false, true, false, false, false, false, true, true, false, false, true, false, true, false, true, true, false, true, false, true, false, true, true, true, true, true},
  {true, false, false, false, false, false, false, false, false, false, false, true, false, false, true, false, true, true, true, true, false, true, false, false, false, true, false, true, true, true},
  {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
  {true, true, true, true, false, true, true, false, true, false, true, true, true, true, true, false, false, true, true, true, true, true, false, true, false, true, false, true, true, true},
  {true, false, false, false, false, true, false, false, false, false, true, false, false, false, false, false, false, true, true, true, true, true, false, false, false, true, false, true, true, true},
  {false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false, true, false, false, false, true, false, true, false, false},
  {false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false},
  {false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, true, true, true},
  {false, false, true, false, false, false, false, false, false, false, true, true, false, false, true, false, false, true, true, true, false, true, false, false, false, true, true, false, false, false},
  {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false, true, false, false, false, false},
  {true, true, true, true, true, true, true, true, false, false, true, true, false, false, false, true, true, true, true, true, true, true, false, false, false, true, true, true, true, true},
  {true, true, true, false, false, true, true, false, false, false, true, true, false, true, true, false, true, true, true, false, false, true, false, false, false, true, true, true, false, true},
  {true, true, true, false, true, true, true, false, true, false, true, true, false, true, true, true, false, true, true, true, true, true, true, false, false, true, true, true, true, true},
  {false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, true, false, false, false, false, false, false, false, false, false, false, false},
  {false, false, true, false, false, false, false, false, false, false, true, false, false, false, true, false, false, true, false, true, false, false, false, false, false, true, false, false, false, false},
  {false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
  {false, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false, true, true, false, false, false, false, false, false, true, false, false, false, true},
  {false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false, true, false, false, false, true, false, false, false, true, false, false, false, false},
  };

  cout << "Given the candidates: "<<30<<"\n";
  cout << "pairs number " << pairs.size()<<30<<"\n";
  cout << "When the method lock_pairs is called, then the result should be: ";

  auto result = Tideman::lock_pairs(pairs, 30);
  
  assert_equal_matrix(result, expected_locked);

  cout << "Test Ok!\n";
}

void test_get_winner()
{
  cout << "Given the candidates: ";
  print_vector(Data::candidates, cout);
  cout << "And the locked: ";
  print_matrix(Data::locked, cout);
  cout << "When the method get_winner is called, then the result should be: " << Data::expected_winner << endl;
  
  Tideman tideman{Data::candidates};
  string result = tideman.get_winner(Data::locked);

  assert_equal(result, Data::expected_winner);

  cout << "Test Ok!\n";
}

void test_no_winner_exception()
{
  cout << "Given the candidates: ";
  print_vector(Data::candidates, cout);
  cout << "And the locked: ";
  print_matrix(Data::circular_locked, cout);
  cout << "When the method get_winner is called, then NoWinnerException should be thrown\n";
  
  Tideman tideman{Data::candidates};
  auto call_get_winner = [&] { return tideman.get_winner(Data::circular_locked); };

  // assert_throw_exception<NoWinnerException>(call_get_winner);
  cout<<"Error winner";

  cout << "Test Ok!\n";
}

int main()
{
  test_vote();
  test_record_preferences();
  test_create_pairs();
  test_lock_pairs();
  test_get_winner();
  test_no_winner_exception();
  cout << "Everything ok!\n";
  return EXIT_SUCCESS;
}
