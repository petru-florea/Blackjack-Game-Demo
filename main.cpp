#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <sstream>

#include "Card.h"
#include "Person.h"

int main() {
    uint8_t p = 0;
    std::string command;

    std::cin >> command;
    if (command == "check_cards")
        p = 1;
    else if (command == "shuffle_cards")
        p = 2;
    else if (command == "play_game")
        p = 3;
    else
        std::cout << "There is no such command!" << std::endl;

    switch (p) {
        case 1: {
            char comma;
            bool fakePack = false;
            uint32_t cardNumber;
            std::string cardSymbol;
            std::vector<Card> cardPack;

            while (std::cin >> cardNumber >> comma >> cardSymbol) {
                if ((cardNumber >= 2 && cardNumber <= 14) && (cardSymbol == "heart" || cardSymbol == "spade" || cardSymbol == "diamond" || cardSymbol == "clover")) {
                    cardPack.emplace_back(cardNumber, cardSymbol);
                }
                else {
                    std::cout << "Rigged card deck" << std::endl;
                    fakePack = true;
                    break;
                }
            }

            if ((cardPack.size() == 52) && (!fakePack))
                std::cout << "Deck of cards OK" << std::endl;
            else if (!fakePack)
                std::cout << "Ready for Blackjack" << std::endl;

            break;
        }

        case 2: {
            char comma;
            int32_t a1, a2, c1, c2, X1 = 0, X2 = 0, m;
            uint32_t cardNumber, count = 0;
            std::string cardSymbol;
            std::vector<Card> cardPack;

            std::cin >> a1 >> c1 >> X1;
            std::cin >> a2 >> c2 >> X2;
            while (std::cin >> cardNumber >> comma >> cardSymbol) {
                cardPack.emplace_back(cardNumber, cardSymbol);
            }

            m = cardPack.size();
            while(count != 50) {
                X1 = (a1 * X1 + c1) % m;
                X2 = (a2 * X2 + c2) % m;

                Card card = cardPack.at(X1);
                cardPack.at(X1) = cardPack.at(X2);
                cardPack.at(X2) = card;

                count++;
            }

            for (auto &card : cardPack) {
                std::cout << card.getCardNumber() << comma << card.getCardSymbol() << std::endl;
            }

            break;
        }

        case 3: {
            int32_t a1, a2, c1, c2, X1 = 0, X2 = 0, n;
            int32_t money, count = 0;
            std::string name;
            std::vector<Card> cardPack;
            std::vector<Person> persons;
            std::string cardNumber, cardSymbol;
            std::string defaultCardPack = "2,heart,3,heart,4,heart,5,heart,6,heart,7,heart,8,heart,9,heart,10,heart,10,heart,10,heart,10,heart,"
                                          "2,spade,3,spade,4,spade,5,spade,6,spade,7,spade,8,spade,9,spade,10,spade,10,spade,10,spade,10,spade,"
                                          "2,diamond,3,diamond,4,diamond,5,diamond,6,diamond,7,diamond,8,diamond,9,diamond,10,diamond,10,diamond,10,diamond,10,diamond,"
                                          "2,clover,3,clover,4,clover,5,clover,6,clover,7,clover,8,clover,9,clover,10,clover,10,clover,10,clover,10,clover,";

            std::stringstream scanf(defaultCardPack);
            while (std::getline(scanf, cardNumber, ',')) {
                std::getline(scanf, cardSymbol, ',');
                cardPack.emplace_back(std::stoi(cardNumber), cardSymbol);
            }

            std::cin >> n;
            for (uint32_t i = 0; i < n; i++) {
                std::cin >> name >> money;
                persons.emplace_back(name, money);
            }
            Person Dealer("Dealer", 1000);

            while (std::cin >> a1 >> c1 >> X1 >> a2 >> c2 >> X2) {

                while(count != 50) {
                    X1 = (a1 * X1 + c1) % 48;
                    X2 = (a2 * X2 + c2) % 48;

                    Card card = cardPack.at(X1);
                    cardPack.at(X1) = cardPack.at(X2);
                    cardPack.at(X2) = card;

                    count++;
                }
                count = 0;

                std::deque<Card> cardPack2(cardPack.begin(), cardPack.end());

                for (auto &person : persons) {
                    for (uint32_t i = 0; i < 2; i++) {
                        person.addCard(cardPack2.front());
                        cardPack2.pop_front();
                    }
                }
                for (uint32_t i = 0; i < 2; i++) {
                    Dealer.addCard(cardPack2.front());
                    cardPack2.pop_front();
                }

                for (auto &person : persons) {
                    while (person.cardsSum() <= 16) {
                        person.addCard(cardPack2.front());
                        cardPack2.pop_front();
                    }
                }
                while (Dealer.cardsSum() <= 16) {
                    Dealer.addCard(cardPack2.front());
                    cardPack2.pop_front();
                }

                if (Dealer.cardsSum() > 21) {
                    for (auto &person : persons) {
                        if (person.cardsSum() <= 21)
                            person.addMoney();
                        else
                            person.removeMoney();
                    }
                }
                else {
                    for (auto &person : persons) {
                        if (person.cardsSum() > 21) {
                            person.removeMoney();
                        }
                        else if (person.cardsSum() > Dealer.cardsSum()) {
                            person.addMoney();
                        }
                        else if (person.cardsSum() < Dealer.cardsSum()) {
                            person.removeMoney();
                        }
                        else if (person.cardsSum() == Dealer.cardsSum()) {
                            /// Keep money
                        }
                    }
                }

                for (uint32_t i = 0; i < persons.size(); i++) {
                    for (uint32_t j = 0; j < persons.size(); j++) {
                        if (persons.at(j).getMoney() < 10) {
                            persons.erase(persons.begin() + j);
                        }
                    }
                }

                for (auto &person : persons) {
                    person.returnCards();
                }
                Dealer.returnCards();
            }

            for (auto &person : persons) {
                std::cout << person.getName() << ": " << person.getMoney() << std::endl;
            }

            break;
        }

        default: {
            std::cout << "Default case!" << std::endl;
            break;
        }
    }

    return 0;
}
