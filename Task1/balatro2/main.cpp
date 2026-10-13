#include <iostream>
#include "Game.h"

// Demo: uji ke-13 checker dengan hand yang sudah ditentukan.
static void runCheckerDemo() {
    struct Case { const char* cards; HandType expected; };
    const Case cases[] = {
        {"2H 5D 9C JS KH",  HandType::HighCard},
        {"5H 5D 9C JS KH",  HandType::Pair},
        {"5H 5D 9C 9S KH",  HandType::TwoPair},
        {"5H 5D 5C JS KH",  HandType::ThreeOfAKind},
        {"5H 6D 7C 8S 9H",  HandType::Straight},
        {"2H 5H 9H JH KH",  HandType::Flush},
        {"5H 5D 5C 9S 9H",  HandType::FullHouse},
        {"5H 5D 5C 5S KH",  HandType::FourOfAKind},
        {"5H 6H 7H 8H 9H",  HandType::StraightFlush},
        {"10S JS QS KS AS", HandType::RoyalFlush},
        {"5H 5D 5C 5S 5H",  HandType::FiveOfAKind},
        {"5H 5H 5H 9H 9H",  HandType::FlushHouse},
        {"5H 5H 5H 5H 5H",  HandType::FlushFive},
    };

    HandEvaluator evaluator;
    DefaultScoringRule scoring;
    std::cout << "=== CHECKER TEST ===\n";
    for (const auto& c : cases) {
        HandResult r = evaluator.evaluate(parseHand(c.cards));
        std::cout << (r.type == c.expected ? "[PASS] " : "[FAIL] ")
                  << c.cards << " -> " << handInfo(r.type).name
                  << " (score " << scoring.computeScore(r) << ")\n";
    }
    std::cout << '\n';
}

int main() {
    runCheckerDemo();

    RandomHandGenerator generator;
    HandPlayer player;
    DefaultScoringRule scoring;
    DefaultBlindRule blind;
    DefaultRewardRule reward;
    ShopSystem shop;

    GameManager game(generator, player, scoring, blind, reward, shop);
    game.run();
    return 0;
}
