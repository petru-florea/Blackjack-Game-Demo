
#ifndef BLACKJACK_CARD_H
#define BLACKJACK_CARD_H

#include <string>

class Card {
private:
    uint32_t mCardNumber;
    std::string mCardSymbol;

public:
    Card(uint32_t cardNumber, std::string cardSymbol) {
        mCardNumber = cardNumber;
        mCardSymbol = std::move(cardSymbol);
    }

    uint32_t getCardNumber() const {
        return mCardNumber;
    }

    std::string getCardSymbol() const {
        return mCardSymbol;
    }
};

#endif //BLACKJACK_CARD_H
