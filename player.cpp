


#include "player.hh"
#include <string>
#include <iostream>



Player::Player(const std::string &name):

    NAME_(name)
{

}

std::string Player::getName() const

// Returns the name of the player.
{
    return NAME_;
}

unsigned int Player::numberOfPairs() const

// Returns the amount of pairs each player has
{
    return pairs_;
}



void Player::addCard(Card* card)

// Adds a half of a pair to pairs, as the program runs through every card in the game board
// Removes the guessed card from the game board.
{
    pairs_ += 0.5;
    card->removeFromGameBoard();
}




