
#ifndef BLACKJACK_PERSON_H
#define BLACKJACK_PERSON_H

#include <string>
#include <vector>
#include "Card.h"

class Person {
private:
    std::string mName;
    int32_t mMoney;
    std::vector<Card> personCards;

public:
    Person(std::string name, int32_t money) {
        mName = std::move(name);
        mMoney = money;
    }

    std::string getName() const {
        return mName;
    }

    int32_t getMoney() const {
        return mMoney;
    }

    void addCard(const Card &card) {
        personCards.push_back(card);
    }

    int32_t cardsSum() {
        int32_t sum = 0;
        for (auto &card : personCards) {
            sum += card.getCardNumber();
        }

        return sum;
    }

    void addMoney() {
        mMoney += 10;
    }

    void removeMoney() {
        mMoney -= 10;
    }

    void returnCards() {
        personCards.clear();
    }
};

#endif //BLACKJACK_PERSON_H
