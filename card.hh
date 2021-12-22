/* Class: Card
 * -----------
 * Represents a single card in pairs (memory) game.
 * Contains attributes for each card.
 *
 * COMP.CS.110 K2021
 * */


#ifndef CARD_HH
#define CARD_HH

#include <QMainWindow>
#include <QPushButton>



enum Visibility_type {OPEN, HIDDEN, EMPTY};
const char HIDDEN_CHAR = '#';
const char EMPTY_CHAR = '.';


class Card
{
public:

    // Constructor: Creates an empty card.
    Card();

    // Creates a hidden card with the given character-
    Card(const char c,QPushButton* card);

    // Sets the letter for a card.
    void setLetter(const char c);

    // Sets the visibility for a card.
    void setVisibility(const Visibility_type visibility);

    // Gets the letter of a card.
    char getLetter() const;

    // Gets the visibility for a card.
    Visibility_type getVisibility() const;

    // Sets a push button to a card object.
    void setCard(QPushButton* card);
    QPushButton* getCard();


    // Turns a card.
    void turn();

    // Prints a card based on its current state
    void print() const;

    // Removes a card from the game board
    void removeFromGameBoard();

private:

    // Attributes for card objects.
    char letter_;
    Visibility_type visibility_;
    QPushButton* card_;

    // Creates a prefix and suffix for the file names.
    const std::string PREFIX = ":/images/";
    const std::string SUFFIX = ".png";


    // Contains information about every letter and their corresponding filename.
    std::map<char, std::string> fruit_map = {{'A',"apple"},{'B',"banana"},
                                             {'C',"cantaloupe"},{'D',"durian"},
                                             {'E',"elderberry"},{'F',"fig"},
                                             {'G',"grapefruit"},
                                             {'H',"horned_melon"},
                                             {'I',"indianprune"},
                                             {'J',"jackfruit"}};






};

#endif // CARD_HH
