#pragma once

#include "Card.h"

#include <unordered_map>
#include <vector>

std::unordered_map<Rank, int> countRanks(const std::vector<Card>& cards);
std::unordered_map<Suit, int> countSuits(const std::vector<Card>& cards);
bool hasNOfAKind(const std::unordered_map<Rank, int>& rankCount, int n);
bool hasAtLeastNOfAKind(const std::unordered_map<Rank, int>& rankCount, int n);
int countPairs(const std::unordered_map<Rank, int>& rankCount);
