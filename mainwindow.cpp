
#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QLineEdit>
#include <QGraphicsScene>
#include <QLabel>
#include <QTextBrowser>
#include <player.hh>
#include <card.hh>
#include <random>
#include <string>
#include <QPixmap>
#include <algorithm>
#include <QTimer>


QString INVALID_CARD_AMOUNT = "Card amount must be positive and even (2-20)";
QString INVALID_SEED_VALUE = "Seed value must be positive.";
QString INVALID_PLAYER_AMOUNT = "Player amount must be positive";
QString CARD_AMOUNT = "Enter a card amount:";
QString SEED_VALUE = "Enter a seed value:";
QString PLAYER_AMOUNT = "Input a player amount:";
QString PLAYER_LABEL = "Add player names:";





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init_board();
    init_player_input();
    init_confirm_button();
    // Constructs the start button.
    init_start_button();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleStartButtonClick()
/* Handles the start button click, creates the player objects for Player class
 * also inits the cards, close button and displays current player.
 */
{


    // Takes the names out of the QLineEdit boxes.
    std::vector<std::string> player_names = {};
    for(QLineEdit* player : players) {
        player_names.push_back(player->text().toStdString());
    }

    // Creates a vector of new player objects.
    for (std::string name : player_names) {
        Player new_player = Player(name);
        player_vector.push_back(new_player);
    }

    // Inits cards for the gameboard.
    init_cards();

    // Inits the close button for the user.
    init_close_button();

    // Displays the current player
    show_current_player();

}

void MainWindow::handleCardClick()
/* Handles the action when the user presses a card. This function iniates the
 * hide button in case the player guesses wrong, takes signal from the pressed
 * card and compares it to the values in the all_cards_ vector. When the
 * function finds the correct card from all_cards_ it will turn the card and
 * print whatever is on the other side of the card. Also disables the card so
 * it can't be pressed again. Adds the card to a temporary vector card_pair.
 *
 * After the card has been added, funtion will check if the card_pair vector
 * contains two cards, so they can be compared. If the card_pair vector contains
 * two identical cards, the current player gains a pair and gets to continue.
 * Then again if the two cards have different values e.g pictures, the
 * player has to press hide cards button which turns the cards back to their
 * default state and gives a next player a turn.
 *
 * After every pair chosen, program checks if the whole game board is empty. If
 * so the program will announce a winner.
 *
 */

{


    // Iniates the hide button to turn cards again if the player guessed wrong.
    init_hide_button();


    // Takes the signal from the sender card and compares it to the
    // all_cards vector.
    QPushButton* pressed_card = static_cast<QPushButton*>(sender());
    for(Card* card : all_cards_)
    {
        // Checks if the value of the card is equal to the pressed card.
        if (card->getCard() == pressed_card)
        {
            // Turns the card and shows the player the value of the card.
            card->turn();
            card->print();
            card->getCard()->setEnabled(false);

            // Adds the card to a temp vector.
            card_pair.push_back(card);

            // Checks if the two back-to-back cards have equal values.
            if (card_pair.size() == 2)
            {
                // Compares the card values.
                if(card_pair.front()->getLetter() == card_pair.back()->
                        getLetter())
                {
                    // Adds a card to players point score.
                    player_vector.at(current_player).addCard(card_pair.front());

                    // Sets the visibility of the card to empty since it has
                    // been picked.
                    card_pair.front()->setVisibility(EMPTY);

                    // Adds the other card to players point score.
                    player_vector.at(current_player).addCard(card_pair.back());

                    // Sets the visibility of the card to empty.
                    card_pair.back()->setVisibility(EMPTY);

                    // Clears the temporary card_pair vector.
                    card_pair.clear();

                }
                else
                {
                    // Disables the cards if the user guessed wrong.
                    for(Card* card : all_cards_) {
                        card->getCard()->setEnabled(false);

                    }
                    // Shows the hide button for the user.
                    hide_card->show();

                }

            }

        }

    }

    // Checks if all the cards visibilities are empty.
    if (has_won())
    {
        // Checks who won or if there was a tie.
        who_won();
    }

}


void MainWindow::handleHideClick()

/* Handles the action when hide cards button is clicked.
 * Resets the turned cards back to their default state, enables all te cards,
 * sets the current player to the next one in turn, hides the button after
 * click and displays the next player in turn.
 */
{
    // Reset the cards to their default state.
    card_pair.front()->turn();
    card_pair.back()->turn();
    card_pair.front()->print();
    card_pair.back()->print();

    // Enables all the cards again.
    for(Card* card : all_cards_) {
        card->getCard()->setEnabled(true);
    }

    // Gives a another player a turn.
    current_player += 1;
    if (current_player > player_amount_->text().toInt()-1)
    {
        current_player = 0;
    }

    // Clears the temp vector
    card_pair.clear();

    // Hides the button after use.
    hide_card->hide();

    // Displays which player is in turn.
    curr_player->setText("");
    show_current_player();

}

void MainWindow::handleCloseClick()
// Calls for the close button function.
{
    handle_close_click();
}



void MainWindow::handleConfirmButtonClick()
/* Calculates the factors for the dimensions of the cards. Checks the amount
 * of players and forms QLineEdits accordingly to the amount, so the user can
 * add names to the players. Also checks the player input for validity, if
 * the input isn't valid, an error message will be displayed on the error text
 * box. After two seconds this error message will be deleted and the program
 * asks for a new player input. Enables the start button, if all inputs were
 * valid.
 *
 */
{
    // Calculates the factors for rows
    calculate_factors(factor1,factor2);


    // Takes the player amount from the input box
    int player_amount = player_amount_->text().toInt();
    if (player_amount > 0)
    {

        // Adds a player name label
        QString player_name_label = PLAYER_LABEL;
        QLabel* player_names = new QLabel(player_name_label,base_);
        player_names->setGeometry(10, 90,LABEL_WIDTH,LABEL_HEIGHT);
        player_names->show();

        // Creates LineEdit input boxes for player names.
        for (int i = 0; i < player_amount; ++i)
        {
            QLineEdit* player = new QLineEdit(base_);
            player->setGeometry(10,120+i*(PLAYER_BUFFER),BUTTON_WIDHT, INPUT_HEIGHT);
            players.push_back(player);
            player->show();

        }
        // Checks the valid_player flag to true;
        valid_player = true;

    } else {

        // Displays an error message on the error box.
        text_box->setText(INVALID_PLAYER_AMOUNT);

        // Clears the text box after two seconds.
        QTimer::singleShot(2000, this, SLOT(clearTextBox()));

        // Checks the valid_player flag to false.
        valid_player = false;
    }

    // Checks if all the inputs are valid, if so the start button will be
    // enabled.
    if (valid_card) {
        if(valid_seed) {
            if (valid_player) {
                start_button->setEnabled(true);
                confirm_button->setEnabled(false);

            }
        }

    }

}

void MainWindow::init_board()
/* Iniates the background for the whole progam. Iniates the QGraphicsView for
 * the program, where all the other widgets will be placed.
 * Also creates the text_box for error messages.
 */
{
    // Creates the base window for the program.
    base_ = new QGraphicsView(this);
    base_->setGeometry(0,0,BOARD_WIDHT, BOARD_HEIGHT);


    // Creates a text box for error messages.
    text_box = new QTextBrowser(base_);
    text_box->setGeometry(400,10, LABEL_WIDTH, BUTTON_HEIGHT);
}

void MainWindow::init_player_input()
/* Creates all the player input boxes, where the player can input card amount,
 * seed value and player amount.
 * Also creates the informative label for each of these input boxes.
 *
 */
{
    // Creates a label for card amount.
    QString card_string = CARD_AMOUNT;
    QLabel* card_amount_label = new QLabel(card_string, base_);
    card_amount_label->setGeometry(10,12,LABEL_WIDTH,LABEL_HEIGHT);

    // Creates the player input box for card amount.
    card_amount_ = new QLineEdit(base_);
    card_amount_->setGeometry(160,12,INPUT_WIDTH,INPUT_HEIGHT);

    // Creates a label for player amount.
    QString seed_string = SEED_VALUE;
    QLabel* seed_string_label = new QLabel(seed_string, base_);
    seed_string_label->setGeometry(10,40,LABEL_WIDTH,LABEL_HEIGHT);

    //Creates the player input box for card amount.
    seed_value_ = new QLineEdit(base_);
    seed_value_->setGeometry(160,40,INPUT_WIDTH,INPUT_HEIGHT);

    // Creates a label for player amount.
    QString player_string = PLAYER_AMOUNT;
    QLabel* player_string_label = new QLabel(player_string, base_);
    player_string_label->setGeometry(10,65,LABEL_WIDTH,LABEL_HEIGHT);

    //Creates the player input box for player amount.
    player_amount_ = new QLineEdit(base_);
    player_amount_->setGeometry(160,65,INPUT_WIDTH,INPUT_HEIGHT);



}

void MainWindow::init_cards()
/* Creates the cards and gives them a value, which translates to a picture
 * accordingly to card.hh fruit_map. The cards get randomized values out of
 * randomize() function. Adds the cards to all_cards_ vector which contains
 * every card created.
 */
{  
    // Assigns values for rows and columns out of factors.
    unsigned int rows = factor1;
    unsigned int columns = factor2;
    std::string random_string = randomize();


    // Creates the cards for the database.

    for(unsigned int i = 0; i < rows; ++i) {


        for(unsigned int j = 0; j < columns; ++j)
        {
            // Creates a new card object to Card class

            QPushButton* new_card = new QPushButton(base_);
            Card* card = new Card(random_string.back(), new_card);



            // Points it to a place on the game_board.
            card->getCard()->setGeometry(250+j*(CARD_BUFFER_X),
                                         150+i*(CARD_BUFFER_Y),
                                         CARD_WIDTH,CARD_HEIGHT);

            // Sets the fixed size for cards.
            card->getCard()->setFixedSize(CARD_WIDTH,CARD_HEIGHT);


            // Sets the backside image for the card
            std::string filename = PREFIX + "smile" + SUFFIX;
            QPixmap pixmap(QString::fromStdString(filename));
            QIcon CardIcon(pixmap);
            card->getCard()->setIcon(CardIcon);
            card->getCard()->setIconSize(QSize(50,50));
            card->getCard()->show();


            // Sets the value for the card
            card->setLetter(random_string.back());
            random_string.pop_back();
            card->setVisibility(HIDDEN);

            // Connects the card to a slot.
            connect(card->getCard(), &QPushButton::clicked,this,
                    &MainWindow::handleCardClick);


            // Adds  the card to the database.
            all_cards_.push_back(card);
        }
    }

}


std::string MainWindow::randomize()
/* Creates a randomized string used to give cards random values to make the
 * game more interesting. Also checks the seed value for validity.
 *
 */
{
    // Constants used in the function.
    int seed_value = seed_value_->text().toInt();
    int pairs = card_amount_->text().toInt()/2;
    std::string string = "";

    // Checks the validity of the seed value.
    if(seed_value > 0) {

        // Creates a string of alphabets which is as long as the amount of pairs
        char x = 'A';
        for(int i = 0;i < pairs;++i)
        {
            string += x;
            string += x;
            ++x;
        }


        // Shuffles the string to a random order.
        std::shuffle(string.begin(),string.end(),
                     std::default_random_engine(seed_value));

        // Checks the valid_seed flag to true;
        valid_seed = true;



    } else {

        // Displays an error message on the text box.
        text_box->setText(INVALID_SEED_VALUE);

        // The error message will be shown for two seconds.
        QTimer::singleShot(2000, this, SLOT(clearTextBox()));

        // Checks the valid_seed flag to false.
        valid_seed = false;
    }
    // Returns the randomized string.
    return string;
}

void MainWindow::show_current_player()
// Displays the current player in turn on a label.

{
    // Takes the current player on turn.
    std::string player = player_vector.at(current_player).getName();

    // Reforms the std::string to a Qstring.
    QString player_qstring = QString::fromStdString(player+"'s turn.");

    // Creates a new label.
    curr_player = new QLabel(player_qstring,base_);

    // Positions the label.
    curr_player->setGeometry(400,60,LABEL_WIDTH,LABEL_HEIGHT);

    // Displays the label.
    curr_player->show();
}

bool MainWindow::has_won()
/* Loops through all cards and checks the visibility for each one. If a card
 * is found which isn't empty, will return false.
 */

{
    // Loops through cards.
    for (Card* card : all_cards_)
    {
        // Checks for visibility.
        if (card->getVisibility() != EMPTY) {
            return false;
        }
    }

    // If all cards were empty, will return true;
    return true;

}

void MainWindow::who_won()
/* Checks through the point scores and determines a winner. Also recognizes if
 * there happens to be a tie and informs about it.
 */

{
    // Constants for the function
    int highest_pairs = 0;
    int winner = 0;
    int tied = -1;
    bool is_tie = false;


    // Loops through the player pair total and determines who has the highest.
    for(int player = 0; player < int(player_vector.size()); ++player) {
        if (int(player_vector.at(player).numberOfPairs()) > highest_pairs) {
            highest_pairs = int(player_vector.at(player).numberOfPairs());
            winner = player;
        } else {

            // If there happens to be a tie, it will add a person to tied
            // players.
            if (int(player_vector.at(player).numberOfPairs()) == highest_pairs)
            {
                tied += 1;
                is_tie = true;
            } else {
                continue;

            }

        }
    }

    // Iniates the leaderboard label.
    init_leaderboard();

    // Reforms the values from the for-loop to std::string.
    std::string tied_string = std::to_string(tied);
    std::string highest_pairs_string = std::to_string(highest_pairs);
    std::string winner_name = player_vector.at(winner).getName();
    std::string winner_string = std::to_string(player_vector.at(winner).
                                               numberOfPairs());

    // Iniates a string.
    QString string = "";

    // If there happens to be a tie, string will be different.
    if (is_tie)
    {
        string = QString::fromStdString("Tie of " +
                                        tied_string + " players with " +
                                        winner_string + " pairs.");
    }
    else
    // The more commmon string. Informs the name of the winner and the amount
    // of pairs.
    {
        string = QString::fromStdString(winner_name +
                                        " has won with " +
                                        highest_pairs_string + " pairs.");
    }

    // Iniates result label for the string formed earlier.
    QTextBrowser* result_label = new QTextBrowser(base_);
    result_label->setGeometry(200,150,LABEL_WIDTH+200,LABEL_HEIGHT);

    // Sets the text to the label.
    result_label->setText(string);
    result_label->show();

}

void MainWindow::delete_cards()
// Destructor for cards.
{
    Card* card_to_be_deleted = nullptr;
    for(Card* card : all_cards_) {
        card_to_be_deleted = card;
        delete card_to_be_deleted;
    }
    all_cards_.clear();
}

void MainWindow::delete_players()
// Destructor for player pointers.
{
    // Destructor for players.
    QLineEdit* player_to_be_deleted = nullptr;
    for (QLineEdit* player : players) {
        player_to_be_deleted = player;
        delete player_to_be_deleted;
    }
}

void MainWindow::delete_card_pair()
// Destructor for card_pair, if there happens to be any.
{
    Card* card_to_be_deleted = nullptr;
    for(Card* card : card_pair) {
        card_to_be_deleted = card;
        delete card_to_be_deleted;
    }
}

void MainWindow::clearTextBox()
// Clears the text box.
{

    text_box->setText((""));
}


void MainWindow::init_confirm_button()
// Iniates the confirm button.
{
    // Iniates confirm button for the program.
    QString confirm_label = "Confirm";
    confirm_button = new QPushButton(confirm_label, base_);
    confirm_button->setGeometry(250,10, BUTTON_WIDHT, BUTTON_HEIGHT);

    connect(confirm_button, &QPushButton::clicked, this,
            &MainWindow::handleConfirmButtonClick);


}

void MainWindow::init_start_button()
// Iniates the start button.
{

    // Initiates the start button.
    QString start_label = "Start";
    start_button = new QPushButton(start_label,base_);

    start_button->setGeometry(250, 70, BUTTON_WIDHT, BUTTON_HEIGHT);
    start_button->show();

    connect(start_button, &QPushButton::clicked, this,
            &MainWindow::handleStartButtonClick);

    // Will be disabled upon creation.
    start_button->setEnabled(false);

}

void MainWindow::init_hide_button()
// Iniates hide button.
{
    // Initates a hide button for cards.
    QString hide_label = "Hide cards";
    hide_card = new QPushButton(hide_label,base_);
    hide_card->setGeometry(60,400,BUTTON_WIDHT,BUTTON_HEIGHT);
    connect(hide_card,&QPushButton::clicked, this,
            &MainWindow::handleHideClick);
}

void MainWindow::init_leaderboard()
// Iniates the leaderboard label.
{
    // Creates the label for the leaderboard.
    QString leaderboard_string = "Leaderboard:";
    QLabel* leaderboard_label = new QLabel(leaderboard_string,base_);
    leaderboard_label->setGeometry(200,120,LABEL_WIDTH,LABEL_HEIGHT);

    leaderboard_label->show();


}

void MainWindow::init_close_button()
// Iniates close button, which shuts down the program.
{

    QString close_label = "Close";
    QPushButton* close_button = new QPushButton(close_label,base_);
    close_button->setGeometry(625,10,BUTTON_WIDHT,BUTTON_HEIGHT);
    close_button->show();

    connect(close_button,&QPushButton::clicked, this,
            &MainWindow::handle_close_click);

}

void MainWindow::calculate_factors(unsigned int& smaller_factor,
                                   unsigned int& bigger_factor)
// Calculates factors for the program. Also checks if the card amount is valid.
// Program handles maximum of 20 cards.
{
    // Takes the card_amount from the QLineEdit input.
    unsigned int card_amount = card_amount_->text().toInt();


    // Calculates the closest factor to each other from the card amount.
    if (card_amount > 0 && card_amount % 2 == 0 && card_amount <= 20)
    {

        // Finds the smaller factor
        for(unsigned int i = 1; i * i <= card_amount; ++i)
        {
            if(card_amount % i == 0)
            {
                smaller_factor = i;
            }
        }

        // Finds out the bigger factor.
        bigger_factor = card_amount / smaller_factor;

        // Checks the valid_card flag to true;
        valid_card = true;

    } else
    {

        // Displays an error message on the text box.
        text_box->setText(INVALID_CARD_AMOUNT);

        // The error message will displayed for two seconds.
        QTimer::singleShot(2000, this, SLOT(clearTextBox()));

        // Checks the valid_card flag to false.
        valid_card = false;

    }


}

void MainWindow::handle_close_click()
// Basically a destructor for the whole program.
{

    delete_cards();
    delete_players();
    delete_card_pair();
    close();
}








