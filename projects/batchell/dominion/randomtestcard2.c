/* cardtest4: Testing embargo function
**
** Include in makefile:
** cardtest4: cardtest4.c dominion.o rngs.o
** gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS) 
**
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int assertTrue(char* test, int a)
{
  if(a)
  {
    printf("TEST SUCCESSFUL: %s\n", test);
    return 1;
  }
  else
  {
    printf("TEST FAILED: %s\n", test);
    return 0;
  } 
}

int main() {

  srand(time(NULL));
  printf("RANDOM CARD TEST 2: EMBARGO\n");

  struct gameState G;
  int numPlayers;
  int seed = 1000;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
  int choice1;
  int choice2 = 0;
  int choice3 = 0;
  int handPos = 0;
  int bonus = 0;
  int game, handSize, deckSize, discardSize, returnVal, embargoCt, coins, supplyCount; 
  int numTests = 0;
  int passNum = 0;
  int numTestsTotal = 0;
  int passTotal = 0;
  int failTotal = 0;


  for(int i = 0; i < 500; i++)
  {
    numTests = 0;
    numTestsTotal++;
    passNum = 0;
    handPos = 0;

    choice1 = rand() % 10;
    supplyCount = rand() % 31 + 1;
    numPlayers = rand() % 3 + 2;
    handSize = rand() % 11 + 3;
    deckSize = rand() % 31 + 10; 
    discardSize = rand() % 31 + 10;
    embargoCt = rand() % 10;
    coins = rand() % 11 + 2;
    memset(&G, 23, sizeof(struct gameState));
    game = initializeGame(numPlayers, k, seed, &G);

    G.handCount[0] = handSize;
    G.deckCount[0] = deckSize;
    G.discardCount[0] = discardSize;
    G.embargoTokens[choice1] = embargoCt;
    G.supplyCount[choice1] = supplyCount;
    G.coins = coins;

    for(int j = 0; j < numPlayers; j++)
    {
      G.handCount[j] = handSize;
      G.deckCount[j] = deckSize;
      G.discardCount[j] = discardSize;
 
      for(int m = 0; m < handSize; m++)
      {
        G.hand[j][m] = k[rand() % 10];
      }
      for(int n = 0; n < deckSize; n++)
      {
        G.deck[j][n] = k[rand() % 10];
      }
      for(int p = 0; p < discardSize; p++)
      {
        G.discard[j][p] = k[rand() % 10];
      }
    }
    G.hand[0][0] = embargo;
    G.whoseTurn = 0;

    printf("Test #%d conditions: supply choice is %d, supply count is %d, number of players is %d, hand size is %d, deck size is %d, discard size is %d, current embargo count is %d, coin count is %d, cards are randomly assigned to hand, deck, and discard\n", i + 1, choice1, supplyCount, numPlayers, handSize, deckSize, discardSize, embargoCt, coins);

    // check return value
    returnVal = cardEffect(embargo, choice1, choice2, choice3, &G, handPos, &bonus);
    #if(NOISY_TEST)
    printf("Embargo return = %d, expected 0\n", returnVal);
    #endif
    numTests++;
    passNum += assertTrue("Embargo returns 0 when deck contains at least 1 card\n", returnVal == 0);

    // check hand size
    #if(NOISY_TEST)
    printf("Ending hand size = %d, expected %d\n", G.handCount[0], handSize - 1);
    #endif
    numTests++;
    passNum += assertTrue("Embargo results in one less card in hand\n", (G.handCount[0] == (handSize - 1))); 
  
    // check deck size
    #if(NOISY_TEST)
    printf("Ending deck size = %d, expected %d\n", G.deckCount[0], (deckSize));
    #endif
    numTests++;
    passNum += assertTrue("Embargo results in an unchanged deck size\n", (G.deckCount[0] == (deckSize)));

    // check discard size
    #if(NOISY_TEST)
    printf("Ending discard size = %d, expected %d\n", G.discardCount[0], (discardSize + 1));
    #endif
    numTests++;
    passNum += assertTrue("Embargo results in one more card in the discard pile\n", (G.discardCount[0] == (discardSize + 1)));

    // check embargo count
    #if(NOISY_TEST)
    printf("Ending embargo count = %d, expected %d\n", G.embargoTokens[choice1], embargoCt + 1);
    #endif
    numTests++;
    passNum += assertTrue("Embargo results in an incremented embargo status\n", (G.embargoTokens[choice1] == (embargoCt + 1)));

    // check coins
    #if(NOISY_TEST)
    printf("Ending coin count = %d, expected %d\n", G.coins, coins + 2);
    #endif
    numTests++;
    passNum += assertTrue("Embargo results in an increase by 2 coins\n", (G.coins == (coins + 2)));

    // check other player hand size
    #if(NOISY_TEST)
    printf("Ending hand size = %d, expected %d\n", G.handCount[1], handSize);
    #endif
    numTests++;
    passNum += assertTrue("Embargo results in no change to other player's hand size\n", (G.handCount[1] == handSize)); 
  
    // check other player deck size
    #if(NOISY_TEST)
    printf("Ending deck size = %d, expected %d\n", G.deckCount[1], deckSize);
    #endif
    numTests++;
    passNum += assertTrue("Embargo results in no change to other player's deck size\n", G.deckCount[1] == deckSize);

    // check other player discard size
    #if(NOISY_TEST)
    printf("Ending discard size = %d, expected %d\n", G.discardCount[1], discardSize);
    #endif
    numTests++;
    passNum += assertTrue("Embargo results in no change to other player's discard size\n", G.discardCount[1] == discardSize);

    printf("\nIteration #%d passed %d out of %d tests\n\n", i+1, passNum, numTests);

    if(passNum == numTests)
      passTotal++;
    else
      failTotal++;
  }


  if(passTotal == numTestsTotal)
  {
    printf("\nSUCCESS: ALL TESTS PASSED\n\n");
  }
  else
  {
    printf("\n%d/%d TEST CASES PASSED ALL TESTS; %d/%d TEST CASES FAILED AT LEAST ONE TEST\n\n", passTotal, numTestsTotal, failTotal, numTestsTotal);
  }
}
