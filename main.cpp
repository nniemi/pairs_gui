/*Memory game
 *
 * Description:
 * This program is a basic memory game, which asks the user
 * to input card amount, seed value and amount of players. After this the
 * player can press "Confirm" which allows the player to input player names.
 * After submitting player names, the program will form a game board which
 * consists the card amount which the player submitted.
 *
 * After the game board has been formed, the player can choose which card to
 * turn by clicking on the card. Once the player chooses a card, program
 * checks if it is the first or secon card chosen. If it is the second one
 * of a pair, program checks if they form a correct pair. If so, the player
 * gains a pair and gets to choose a new card. Once the player guesses wrong,
 * next player gets a turn.
 *
 * Once all cards has been turned, program prints a message to show who won and
 * how many pairs the winner had. If there happens to be a tie, the game will
 * inform how many players had a tie and how many pairs they had.
 *
 * Player can close the program using close button at any time.
 *
 *
 * */



#include "mainwindow.hh"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}



