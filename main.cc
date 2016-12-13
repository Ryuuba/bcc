#include "BCCSimulator.h"

int main(int argc, char* argv[]) {
  BCCSimulator simulator(argv[1]);
  simulator.start();
  simulator.compute_statistics(argv[2]);
  return 0;
}