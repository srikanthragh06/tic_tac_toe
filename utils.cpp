#include <random>
#include <iostream>
#include <vector>
#include "custom_exception.h"

int get_random_int(std::vector<int> vector) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distribution(0, vector.size() - 1);

	return vector[distribution(gen)];
}

int get_random_turn() {
	std::vector<int> turns = { -1,1 };
	return get_random_int(turns);
}