#include "NimLearner.h"
#include <vector>
#include <iostream>
#include "edge.h"

int main() {
  NimLearner nim(10);

  // Play 10,000 games of Nim:
  const int gamesPlayed = 1000000;
  for (int i = 0; i < gamesPlayed; i++) {
    vector<Edge> path = nim.playRandomGame();
    nim.updateEdgeWeights(path);
    if (i%10000==0) 
    std::cout<<i<<"games played\n";
  }
  nim.labelEdgesFromThreshold(gamesPlayed / 50);

  // Print textual output of the graph:
  nim.getGraph().print();

  // Save an graph PNG:
  nim.getGraph().savePNG("Out");

  return 0;
}
