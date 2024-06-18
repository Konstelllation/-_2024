#include <algorithm> 
#include <array>
#include <ctime>     
#include <iostream>
#include <random>    

enum class CardSuit
{
    suit_club,
    suit_diamond,
    suit_heart,
    suit_spade,

    max_suits
};

enum class CardRank
{
    rank_2,
    rank_3,
    rank_4,
    rank_5,
    rank_6,
    rank_7,
    rank_8,
    rank_9,
    rank_10,
    rank_jack,
    rank_queen,
    rank_king,
    rank_ace,

    max_ranks
};

struct Card
{
    CardRank rank{};
    CardSuit suit{};
};

struct Player
{
    int score{};
};

using deck_type = std::array<Card, 52>;
using index_type = deck_type::size_type;


constexpr int maximumScore{ 21 };


constexpr int minimumDealerScore{ 17 };

void printCard(const Card& card)
{
    switch (card.rank)
    {
    case CardRank::rank_2:      std::cout << '2';   break;
    case CardRank::rank_3:      std::cout << '3';   break;
    case CardRank::rank_4:      std::cout << '4';   break;
    case CardRank::rank_5:      std::cout << '5';   break;
    case CardRank::rank_6:      std::cout << '6';   break;
    case CardRank::rank_7:      std::cout << '7';   break;
    case CardRank::rank_8:      std::cout << '8';   break;
    case CardRank::rank_9:      std::cout << '9';   break;
    case CardRank::rank_10:     std::cout << 'T';   break;
    case CardRank::rank_jack:   std::cout << 'J';   break;
    case CardRank::rank_queen:  std::cout << 'Q';   break;
    case CardRank::rank_king:   std::cout << 'K';   break;
    case CardRank::rank_ace:    std::cout << 'A';   break;
    default:
        std::cout << '?';
        break;
    }

    switch (card.suit)
    {
    case CardSuit::suit_club:       std::cout << '♣';   break;
    case CardSuit::suit_diamond:    std::cout << '♦';   break;
    case CardSuit::suit_heart:      std::cout << '♥';   break;
    case CardSuit::suit_spade:      std::cout << '♠';   break;
    default:
        std::cout << '?';
        break;
    }
}

int getCardValue(const Card& card)
{
    
    if (card.rank <= CardRank::rank_10)
    {
        
        return (static_cast<int>(card.rank) + 2);
    }

    switch (card.rank)
    {
    case CardRank::rank_jack:
    case CardRank::rank_queen:
    case CardRank::rank_king:
        return 10;
    case CardRank::rank_ace:
        return 11;
    default:
        
        return 0;
    }
}

void printDeck(const deck_type& deck)
{
    for (const auto& card : deck)
    {
        printCard(card);
        std::cout << ' ';
    }

    std::cout << '\n';
}

deck_type createDeck()
{
    deck_type deck{};


    index_type card{ 0 };

    auto suits{ static_cast<int>(CardSuit::max_suits) };
    auto ranks{ static_cast<int>(CardRank::max_ranks) };

    for (int suit{ 0 }; suit < suits; ++suit)
    {
        for (int rank{ 0 }; rank < ranks; ++rank)
        {
            deck[card].suit = static_cast<CardSuit>(suit);
            deck[card].rank = static_cast<CardRank>(rank);
            ++card;
        }
    }

    return deck;
}


void shuffleDeck(deck_type& deck)
{
    static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

    std::shuffle(deck.begin(), deck.end(), mt);
}


bool playerWantsHit()
{
    while (true)
    {
        std::cout << "(h) to hit, or (s) to stand: ";

        char ch{};
        std::cin >> ch;

        switch (ch)
        {
        case 'h':
            return true;
        case 's':
            return false;
        }
    }
}


bool playerTurn(const deck_type& deck, index_type& nextCardIndex, Player& player)
{
    while (true)
    {
        if (player.score > maximumScore)
        {
            std::cout << "You busted!\n";
            return true;
        }
        else
        {
            if (playerWantsHit())
            {
                int cardValue{ getCardValue(deck[nextCardIndex++]) };
                player.score += cardValue;
                std::cout << "You were dealt a " << cardValue
                    << " and now have " << player.score << '\n';
            }
            else
            {
                
                return false;
            }
        }
    }
}


bool dealerTurn(const deck_type& deck, index_type& nextCardIndex, Player& dealer)
{
    while (dealer.score < minimumDealerScore)
    {
        int cardValue{ getCardValue(deck[nextCardIndex++]) };
        dealer.score += cardValue;
        std::cout << "The dealer turned up a " << cardValue
            << " and now has " << dealer.score << '\n';

    }

    
    if (dealer.score > maximumScore)
    {
        std::cout << "The dealer busted!\n";
        return true;
    }

    return false;
}

bool playBlackjack(const deck_type& deck)
{
    
    index_type nextCardIndex{ 0 };

    
    Player dealer{ getCardValue(deck[nextCardIndex++]) };

   
    std::cout << "The dealer is showing: " << dealer.score << '\n';

    
    Player player{ getCardValue(deck[nextCardIndex]) + getCardValue(deck[nextCardIndex + 1]) };
    nextCardIndex += 2;

    std::cout << "You have: " << player.score << '\n';

    if (playerTurn(deck, nextCardIndex, player))
    {
        
        return false;
    }

    if (dealerTurn(deck, nextCardIndex, dealer))
    {
        
        return true;
    }

    return (player.score > dealer.score);
}

int main()
{
    auto deck{ createDeck() };

    shuffleDeck(deck);

    if (playBlackjack(deck))
    {
        std::cout << "You win!\n";
    }
    else
    {
        std::cout << "You lose!\n";
    }

    return 0;
}