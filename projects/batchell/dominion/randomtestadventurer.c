/* cardtest2: Testing adventurer function
**
** Include in makefile:
** cardtest2: cardtest2.c dominion.o rngs.o
** gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS) 
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
  printf("CARD TEST 2: ADVENTURER\n");

  struct gameState G;
  int numPlayers = 2;
  int seed = 1000;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
  int treasure[3] = {copper, silver, gold};
  int choice1 = 0;
  int choice2 = 0;
  int choice3 = 0;
  int handPos = 0;
  int bonus = 0;
  int game, handSize, deckSize, discardSize, returnVal; 
  int numTests = 0;
  int passNum = 0;

  for(int i = 0; i < 50; i++)
  {
    handPos = 0;
    handSize = rand() % 8 + 3;
    deckSize = rand() % 8 + 3; 
    discardSize = rand() % 8 + 3;
    memset(&G, 23, sizeof(struct gameState));
    game = initializeGame(2, k, seed, &G);

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
        if(rand() % 3 == 0)
          G.deck[j][n] = treasure[rand() % 3];
        else
          G.deck[j][n] = k[rand() % 10];
      }
      for(int p = 0; p < discardSize; p++)
      {
        if(rand() % 3 == 0)
          G.discard[j][p] = treasure[rand() % 3];
        else
          G.discard[j][p] = k[rand() % 10];
      }
    }

    G.hand[0][handPos] = adventurer;
    G.whoseTurn = 0;

    // check return value
    returnVal = cardEffect(adventurer, choice1, choice2, choice3, &G, handPos, &bonus);
    #if(NOISY_TEST)
    printf("Adventurer return = %d, expected 0\n", returnVal);
    #endif
    numTests++;
    passNum += assertTrue("Adventurer returns 0 when deck contains at least 2 treasure cards\n", returnVal == 0);

    // check hand size
    #if(NOISY_TEST)
    printf("Ending hand size = %d, expected %d\n", G.handCount[0], (handSize + 2 - 1));
    #endif
    numTests++;
    passNum += assertTrue("Adventurer results in one net card added to the hand size\n", (G.handCount[0] == handSize + 2 - 1)); 
   
    // check deck size
    #if(NOISY_TEST)
    printf("Ending deck size = %d, expected %d\n", G.deckCount[0], (deckSize - 6));
    #endif
    numTests++;
    passNum += assertTrue("Adventurer results in less cards in the deck equal to 2 treasures and cards on top\n", (G.deckCount[0] == (deckSize - 6)));

    // check discard size
    #if(NOISY_TEST)
    printf("Ending discard size = %d, expected %d\n", G.discardCount[0], (discardSize + 5));
    #endif
    numTests++;
    passNum += assertTrue("Adventurer results in increase to discard pile equal to 1 Adventurer and cards on top of treasures\n", (G.discardCount[0] == discardSize + 5));

    // check other player hand size
    #if(NOISY_TEST)
    printf("Ending hand size = %d, expected %d\n", G.handCount[1], handSize);
    #endif
    numTests++;
    passNum += assertTrue("Adventurer results in no change to other player's hand size\n", (G.handCount[1] == handSize)); 
  
    // check other player deck size
    #if(NOISY_TEST)
    printf("Ending deck size = %d, expected %d\n", G.deckCount[1], deckSize);
    #endif
    numTests++;
    passNum += assertTrue("Adventurer results in no change to other player's deck size\n", G.deckCount[1] == deckSize);

    // check other player discard size
    #if(NOISY_TEST)
    printf("Ending discard size = %d, expected %d\n", G.discardCount[1], discardSize);
    #endif
    numTests++;
    passNum += assertTrue("Adventurer results in no change to other player's discard size\n", G.discardCount[1] == discardSize);

  }
  
  if(passNum == numTests)
  {
    printf("\nSUCCESS: ALL TESTS PASSED\n\n");
  }
  else
  {
    printf("\n%d/%d TESTS PASSED\n\n", passNum, numTests);
  }
}
