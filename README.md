# Blackjack Game Demo
### Revision 1.0

---

<img src="./blackjack.png" width='250' align="right">

### Game rules
Blackjack is one of the easiest card games to play:
+ Cards 2 through 10 have a value written on them, while figures **(J, Q, K)** have a value of 10, the ace **(A)** can have a value of 1 or 11.
+ Players play against a person called **the Dealer** and in order to win they must have a higher number of cards than the dealer. If the sum of the cards exceeds the value **21** the player loses. If the dealer exceeds the value **21**, then everyone present at the table wins, except those who have exceeded **21** before the dealer.
+ Each player receives 2 cards at the beginning, and the dealer also receives 2 cards, but one is reversed (**ATTENTION!** In the real game of Blackjack each player receives one card at a time, to **simplify** the problem, we will consider that the players receive the 2 cards from the get go, and the dealer is the last person to receive the 2 cards).
+ After the cards have been dealt, each player has the right to draw a card **(HIT)** or to stop at the amount he already has **(STAND)**. Players can draw as many cards as they want, but if they exceed 21 they lose (**ATTENTION!** For simplicity we will consider the following scenario: If the sum of the dealer's or player's cards is less than 16, they are required to draw a card. If the sum of the cards is between 17 and 21, they must stop drawing cards. If the amount is more than 21 they lost).

### Requirements
1) If the **command** is *check_cards*, check if the deck of cards is rigged, if it is a normal deck, or if it is a blackjack-ready deck. A deck of cards is considered rigged if there are cards whose numbers or coats of arms do not actually exist (the allowed numbers are 2 to 14, where 11 is the ace and the allowed coats of arms are **spade**, **heart**, **clover** or **diamond**) and *Rigged card deck* will be displayed. A deck of cards is considered OK if it is not rigged, if all the cards in it are different, and if there are a total of 52 cards, in which case *Deck of cards OK* will be displayed. A deck of cards is considered good for Blackjack if it is not rigged, in which case *Ready for Blackjack* will be displayed.

2) If the command is *shuffle_cards*, shuffle the cards using the **Linear Congruential Generator (LCG)** algorithm. The generator is defined by the recurrence relation **Xn + 1 = (a * Xn + c) modulo m**. If 2 pairs of numbers **a**, **c** and **X0** are given from the keyboard, then a pair of indexes will be generated and the cards in those positions will be exchanged, and the current index will become the previous index for the generator. The constant **m** will represent the number of cards in the pack. This algorithm will be applied to the package **50** times. The books in the package will be mixed in the format **<card_number>,<card_coat_of_arms>**.

3) If the **command** is *play_game*, play Blackjack until EOF with **n** players at a table. The game will be played according to the rules stated at the beginning. It is considered that there are **NO** aces in the deck! (That is, the deck will consist of 48 cards, not 52!). The deck of cards will be shuffled every round of Blackjack using the LCG algorithm described above (also applied 50 times). There will be 48 cards in a pack (because we don't have aces). Initially the pack of cards is arranged in the following order: 2 heart, 3 heart, ..., 14 heart, 2 spade, ..., 14 spade, 2 diamond, ..., 14 diamond, 2 clover, ..., 14 clover (Attention there are no cards with a value of 11!). Each round the deck of cards will be shuffled using the LCG algorithm with the current values read from the keyboard. The stake is 10 euros per player so winning the round brings the player 10 euros, and if he loses he will have 10 euros less. If the player runs out of money (under 10 euros) he will leave the table. At the end, the remaining people at the table will be displayed in the format **person_name: sum_money**.

### Input
On the first line is a **command** word, representing the subpoint you want to make. For sub-item **1)**, lines such as **<card_number>,<card_coat_of_arms>** are read from the keyboard to the **EOF**, where the **card_number** is an 8-bit, unsigned integer, and the **card_coat_of_arms** is a character string up to 30 characters. For sub-item **2)**, read 6 integers from the keyboard, 3 on one line and 3 on the other, representing the constants a, c and X0. Then read cards to the EOF in the format specified at sub-item 1). For sub-item **3)**, read an integer **n** representing the number of players present at the Blackjack table. On the next **n** lines are the **n** players in the format **<name> <sum_money>**, where **name** is a string representing the name of the player, consisting of a single word, and the **sum_money** represents the amount of money he owns, 32-bit unsigned integer. The following lines up to the EOF read 6 values per line, representing the inputs of the LCG generator for shuffling the cards in the current game.
  
### Examples
Input:
```
check_cards
4,diamond
3,heart
12,clover
17,spade
7,heart
9,clover
7,heart
```
Output:
```
Rigged card deck
```
  
----------------------------------

Input:
```
check_cards
4,diamond
3,heart
12,clover
10,spade
7,heart
9,diamond
7,spade
3,heart
```
Output:
```
Ready for Blackjack
```

----------------------------------

Input:
```
shuffle_cards
1 5 4
2 2 3
4,diamond
3,heart
12,clover
10,spade
7,heart
9,diamond
7,spade
3,heart
```
Output:
```
7,spade
10,spade
7,heart
9,diamond
12,clover
3,heart
3,heart
4,diamond
```

----------------------------------

Input:
```
play_game
4
Mihai 100
Maria 50
Matei 176
Andrei 100
10 26 33 34 37 45
2 4 30 32 38 48
3 24 27 34 45 48
```
Output:
```
Mihai: 70
Maria: 20
Matei: 146
Andrei: 80
```
