#include <iostream>
#include <array>
#include <map>
#include <numeric>

constexpr int num_players = 2;
constexpr int num_fields = 10;

int main(int argc, char* argv[]) {
  std::array<int,num_players> initial_players;
  for (int i = 0; i < num_players; i++) {
    initial_players[i] = std::stoi(argv[i+1]) - 1;
  }

  /////// Part 1 //////
  const int score_to_win1 = 1000;
  std::array<int,num_players> players = initial_players;
  std::array<int,num_players> scores = {0,0};

  int dice = 1;
  int player = 0;
  while(true) {
    players[player] += dice++;
    players[player] += dice++;
    players[player] += dice++;
    players[player] %= num_fields;
    scores[player] += players[player]+1;

    if (scores[player] >= score_to_win1) break;
    player = (++player%num_players);
  }
  player = (++player%num_players);

  std::cout << "Losing player is player " << player+1 << " with score "
            << scores[player] << " and " << dice-1 << " dice rolls.\n";
  std::cout << "Solution for part 1: " << scores[player] * (dice-1) << '\n';

  scores = {0,0};

  ////// Part 2 //////

  // Throws are one of 3^3 possible outcomes.
  std::map<int,int> throws;
  for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= 3; j++) {
      for (int k = 1; k <= 3; k++) {
        throws[i+j+k]++;
      }
    }
  }

  const int score_to_win2 = 21;

  typedef unsigned long long Count;
  struct PlayerState {
    int position;
    int score;
    bool operator<(const PlayerState &o) const {
      if (position == o.position) return score < o.score;
      return position < o.position;
    }
  };

  std::array<std::map<PlayerState,Count>,num_players> player_states = {{
    {{{initial_players[0], 0}, 1}},
    {{{initial_players[1], 0}, 1}}
  }};
  std::array<Count,num_players> wins;
  for (int player = 0;; player = (++player)%num_players) {
    std::map<PlayerState,Count> new_player_states;
    for (auto [state, count] : player_states[player]) {
      for (auto [k, n] : throws) {
        PlayerState new_state;
        new_state.position = (state.position+k)%num_fields;
        new_state.score = state.score + new_state.position+1;
        if (new_state.score >= score_to_win2) {
          auto losing_player_states = player_states[(player+1)%num_players];
          Count num_losing_players = std::accumulate(losing_player_states.begin(),
                                                     losing_player_states.end(), 0,
                                                     [](auto a, auto c){return a + c.second;});
          wins[player] += count * n * num_losing_players;
        } else {
          new_player_states[new_state] += count*n;
        }
      }
    }
    if (new_player_states.empty()) break;
    player_states[player] = new_player_states;
  }
  std::cout << "Player 1 wins: " << wins[0] << "; player 2 wins: " << wins[1] << '\n';
  std::cout << "Part 2 solution: " << std::max(wins[0],wins[1]) << '\n';
}
