#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QGraphicsView>
#include <QLineEdit>
#include <card.hh>
#include <QPushButton>
#include <player.hh>
#include <QTextBrowser>
#include <QLabel>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QGraphicsView* get_base();

private slots:

    // All the slots used when clicking a button.
    void handleConfirmButtonClick();
    void handleStartButtonClick();
    void handleCardClick();
    void handleHideClick();
    void handleCloseClick();
    void clearTextBox();

private:
    Ui::MainWindow *ui;

    // Constants for widget dimensions
    const int CARD_WIDTH = 80;
    const int CARD_HEIGHT = 100;
    const int INPUT_WIDTH = 25;
    const int INPUT_HEIGHT = 20;
    const int BOARD_WIDHT = 900;
    const int BOARD_HEIGHT = 600;
    const int BUTTON_WIDHT = 100;
    const int BUTTON_HEIGHT = 50;
    const int LABEL_WIDTH = 200;
    const int LABEL_HEIGHT = 20;
    const int CARD_BUFFER_X = 90;
    const int CARD_BUFFER_Y = 110;
    const int PLAYER_BUFFER = 30;
    const int MAX_PLAYER_AMOUNT = 10;
    const int MIN_PLAYER_AMOUNT = 10;

    // Prefix and suffix for filenames.
    const std::string PREFIX = ":/images/";
    const std::string SUFFIX = ".png";


    // All the functions used in mainwindow.cpp
    void init_board();
    void init_player_input();
    void init_cards();
    void init_confirm_button();
    void init_start_button();
    void init_hide_button();
    void init_leaderboard();
    void init_close_button();
    void calculate_factors(unsigned int& factor1,unsigned int& factor2);
    void handle_confirm_click();
    void handle_close_click();
    std::string randomize();
    void show_current_player();
    bool has_won();
    void who_won();
    void delete_cards();
    void delete_players();
    void delete_card_pair();



    // Database where all the cards are stored.
    std::vector<Card*> all_cards_;

    // The base for every widget used in this program.
    QGraphicsView* base_;

    // Iniating factors used to calculate dimensions of the card positions.
    unsigned int factor1 = 1;
    unsigned int factor2 = 1;

    // Input box for the user to submit card amount.
    QLineEdit* card_amount_;

     // Input box for the user to submit seed value.
    QLineEdit* seed_value_;

     // Input box for the user to submit player amount.
    QLineEdit* player_amount_;

    // Vector containing input boxes, used to give players names.
    std::vector<QLineEdit*> players;

    // Player object vector which contains all players.
    std::vector<Player> player_vector;

    // Index which displays the current player.
    int current_player = 0;

    // Temporary vector used to handle turned cards.
    std::vector<Card*> card_pair;

    // Hide button for cards.
    QPushButton* hide_card;

    // An error message box used to display if the user input is invalid.
    QTextBrowser* text_box;

    // The button to start the actual game.
    QPushButton* start_button;

    // The button to confirm inputs
    QPushButton* confirm_button;

    // Label displaying the current player.
    QLabel* curr_player;

    // Flags for valid input.
    bool valid_seed = true;
    bool valid_card = true;
    bool valid_player = true;





};
#endif // MAINWINDOW_HH
