#include "Card.h"

namespace {
std::string rankToString(Rank rank) {
    switch (rank) {
    case Rank::Two:
        return "Two";
    case Rank::Three:
        return "Three";
    case Rank::Four:
        return "Four";
    case Rank::Five:
        return "Five";
    case Rank::Six:
        return "Six";
    case Rank::Seven:
        return "Seven";
    case Rank::Eight:
        return "Eight";
    case Rank::Nine:
        return "Nine";
    case Rank::Ten:
        return "Ten";
    case Rank::Jack:
        return "Jack";
    case Rank::Queen:
        return "Queen";
    case Rank::King:
        return "King";
    case Rank::Ace:
        return "Ace";
    }

    return "";
}

std::string suitToString(Suit suit) {
    switch (suit) {
    case Suit::Hearts:
        return "Hearts";
    case Suit::Diamonds:
        return "Diamonds";
    case Suit::Clubs:
        return "Clubs";
    case Suit::Spades:
        return "Spades";
    }

    return "";
}
}

int Card::getRankValue() const {
    return static_cast<int>(rank);
}

bool Card::operator==(const Card& other) const {
    return rank == other.rank && suit == other.suit;
}

bool Card::operator<(const Card& other) const {
    return rank < other.rank;
}

std::string Card::toString() const {
    return rankToString(rank) + " of " + suitToString(suit);
}
