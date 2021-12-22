
/* Class: Player
 * -------------
 * Represents a single player in pairs (memory) game.
 * Contains all the attributes for an individual player.
 *
 * COMP.CS.110 K2021
 * */

#ifndef PLAYER_HH
#define PLAYER_HH

#include "card.hh"


class Player
{
public:

    // Constructor: creates a player with the given name.
    Player(const std::string& name);


    // Returns the name of the player.
    std::string getName() const;


    // Returns the number of pairs collected by the player so far.
    unsigned int numberOfPairs() const;


    // Moves the given card from the game board for the player,
    // i.e. inserts it to the collected cards of the player and
    // removes it from the game board.
    void addCard(Card* card);




private:

    // Attributes
    std::string NAME_;
    double pairs_ = 0;



};

#endif // PLAYER_HH
