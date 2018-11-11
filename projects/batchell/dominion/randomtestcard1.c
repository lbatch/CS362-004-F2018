/* cardtest1: Testing smithy function
**
** Include in makefile:
** cardtest1: cardtest1.c dominion.o rngs.o
** gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS) 
**
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

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

  printf("RANDOM TEST 1: SMITHY\n");

  struct gameState G;
  int numPlayers;
  int seed = 1000;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
  int choice1 = 0;
  int choice2 = 0;
  int choice3 = 0;
  int handPos = 0;
  int bonus = 0;
  int game, handSize, deckSize, discardSize, returnVal; 
  int numTests = 0;
  int passNum = 0;
  int numTestsTotal = 0;
  int passTotal = 0;
  int failTotal = 0;

  printf("Testing Smithy:\n");

  for(int i = 0; i < 100; i++)
  {
    numTests = 0;
    numTestsTotal++;
    passNum = 0;
    handPos = 0;
    numPlayers = rand() % 3 + 2;
    handSize = rand() % 11 + 3;
    deckSize = rand() % 26 + 5;
    discardSize = rand() % 26 + 5;
    memset(&G, 23, sizeof(struct gameState));
    game = initializeGame(2, k, seed, &G);

    printf("Test #%d Conditions; number of players is %d, hand size is %d, deck size is %d, discard size is %d; hand, deck and discard contents randomly assigned\n", i+1, numPlayers, handSize, deckSize, discardSize);
   
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
  
   G.hand[0][0] = smithy;
   G.whoseTurn = 0;

    // check return value
    returnVal = cardEffect(smithy, choice1, choice2, choice3, &G, handPos, &bonus);
    #if(NOISY_TEST)
    printf("Smithy return = %d, expected 0\n", returnVal);
    #endif
    numTests++;
    passNum += assertTrue("Smithy returns 0\n", returnVal == 0);

    // check hand size
    #if(NOISY_TEST)
    printf("Ending hand size = %d, expected %d\n", G.handCount[0], (handSize + 3 - 1));
    #endif
    numTests++;
    passNum += assertTrue("Smithy results in two net cards added to the hand size\n", (G.handCount[0] == handSize + 3 - 1)); 
  
    // check deck size
    #if(NOISY_TEST)
    printf("Ending deck size = %d, expected %d\n", G.deckCount[0], (deckSize - 3));
    #endif
    numTests++;
    passNum += assertTrue("Smithy results in three less cards in the deck\n", (G.deckCount[0] == deckSize - 3));

    // check discard size
    #if(NOISY_TEST)
    printf("Ending discard size = %d, expected %d\n", G.discardCount[0], (discardSize + 1));
    #endif
    numTests++;
    passNum += assertTrue("Smithy results in one card added to the discard\n", (G.discardCount[0] == discardSize + 1));

    // check other player hand size
    #if(NOISY_TEST)
    printf("Ending hand size = %d, expected %d\n", G.handCount[1], handSize);
    #endif
    numTests++;
    passNum += assertTrue("Smithy results in no change to other player's hand size\n", (G.handCount[1] == handSize)); 
  
    // check other player deck size
    #if(NOISY_TEST)
    printf("Ending deck size = %d, expected %d\n", G.deckCount[1], deckSize);
    #endif
    numTests++;
    passNum += assertTrue("Smithy results in no change to other player's deck size\n", G.deckCount[1] == deckSize);

    // check other player discard size
    #if(NOISY_TEST)
    printf("Ending discard size = %d, expected %d\n", G.discardCount[1], discardSize);
    #endif
    numTests++;
    passNum += assertTrue("Smithy results in no change to other player's discard size\n", G.discardCount[1] == discardSize);

    printf("\nIteration #%d passed %d out of %d tests\n\n", i + 1, passNum, numTests);

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
    printf("\n%d/%d TESTS CASES PASSED ALL TESTS; %d/%d TEST CASES FAILED AT LEAST ONE TEST\n\n", passTotal, numTestsTotal, failTotal, numTestsTotal);
  }
}
