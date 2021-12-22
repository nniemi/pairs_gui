#include "card.hh"
#include <iostream>
#include <QPixmap>
#include <mainwindow.hh>


Card::Card():
    letter_(EMPTY_CHAR), visibility_(EMPTY)
{

}

Card::Card(const char c,QPushButton* card):
    letter_(c), visibility_(HIDDEN), card_(card)
{

}

void Card::setLetter(const char c)
{
    letter_ = c;
}

void Card::setVisibility(const Visibility_type visibility)
{
    visibility_ = visibility;
}

char Card::getLetter() const
{
    return letter_;
}

Visibility_type Card::getVisibility() const
{
    return visibility_;
}

QPushButton *Card::getCard()
{
    return card_;
}

void Card::setCard(QPushButton *card)
{
    card_ = card;
}



void Card::turn()
{
    if(visibility_ == HIDDEN)
    {
        visibility_ = OPEN;
    }
    else if(visibility_ == OPEN)
    {
        visibility_ = HIDDEN;
    }
    else // if(visibility_ == EMPTY)
    {
        std::cout << "Cannot turn an empty place." << std::endl;
    }
}

void Card::print() const
{
    // Checks the visibility of a card.
    if (visibility_== HIDDEN) {

        // Sets the default background image for the card.
        card_->setText("");
        std::string filename = PREFIX + "smile" + SUFFIX;
        QPixmap pixmap(QString::fromStdString(filename));
        QIcon CardIcon(pixmap);
        card_->setIcon(CardIcon);
        card_->setIconSize(QSize(50,50));
    }
    else if (visibility_== EMPTY) {
        QChar empty = EMPTY_CHAR;
        card_->setText(empty);
    } else {

        // Sets the image according to the value of fruit_map to the card.
        std::string filename = PREFIX + fruit_map.at(letter_) + SUFFIX;
        QPixmap pixmap(QString::fromStdString(filename));
        QIcon CardIcon(pixmap);
        card_->setIcon(CardIcon);

        // Sets the icon size.
        card_->setIconSize(QSize(70,120));
        card_->show();

    }

}

void Card::removeFromGameBoard()
{
    // Hides the correctly guessed card.
    card_->hide();

}
