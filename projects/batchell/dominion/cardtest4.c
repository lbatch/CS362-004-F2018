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

  printf("CARD TEST 4: EMBARGO\n");

  struct gameState G;
  int numPlayers = 2;
  int seed = 1000;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
  int choice1 = 5;
  int choice2 = 0;
  int choice3 = 0;
  int handPos = 0;
  int bonus = 0;
  int game, handSize, deckSize, discardSize, returnVal, embargoCt, coins, supplyCount; 
  int numTests = 0;
  int passNum = 0;

  /*Test Case 1: No embargo currently on supply
  * Anticipated result: function returns 0, hand size decreased by 1, deck size unchanged, discard size increased by 1, embargo set on supply card, treasure increased by 2, other players' hand/deck sizes unaffected */
  supplyCount = 10;
  handPos = 2;
  handSize = 10;
  deckSize = 10; 
  discardSize = 2;
  embargoCt = 0;
  coins = 0;
  memset(&G, 23, sizeof(struct gameState));
  game = initializeGame(2, k, seed, &G);

  G.handCount[0] = handSize;
  G.deckCount[0] = deckSize;
  G.discardCount[0] = discardSize;
  G.embargoTokens[choice1] = embargoCt;
  G.coins = coins;
  G.supplyCount[choice1] = supplyCount;
  memcpy(G.hand[0], k, sizeof(int) * handSize);
  memcpy(G.deck[0], k, sizeof(int) * deckSize);
  memcpy(G.discard[0], k, sizeof(int) * discardSize);

  G.handCount[1] = handSize;
  G.deckCount[1] = deckSize;
  G.discardCount[1] = discardSize;
  memcpy(G.hand[1], k, sizeof(int) * handSize);
  memcpy(G.deck[1], k, sizeof(int) * deckSize);
  memcpy(G.discard[1], k, sizeof(int) * discardSize);

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
  numTests ++;
  passNum += assertTrue("Embargo results in no change to other player's discard size\n", G.discardCount[1] == discardSize);

  /*Test Case 2: One embargo currently on supply
  * Anticipated result: function returns 0, hand size decreased by 1, deck size unchanged, discard size increased by 1, embargo set on supply card, treasure increased by 2, other players' hand/deck sizes unaffected */
  supplyCount = 10;
  handPos = 2;
  handSize = 10;
  deckSize = 10; 
  discardSize = 2;
  embargoCt = 1;
  coins = 0;
  memset(&G, 23, sizeof(struct gameState));
  game = initializeGame(2, k, seed, &G);

  G.handCount[0] = handSize;
  G.deckCount[0] = deckSize;
  G.discardCount[0] = discardSize;
  G.embargoTokens[choice1] = embargoCt;
  G.coins = coins;
  G.supplyCount[choice1] = supplyCount;
  memcpy(G.hand[0], k, sizeof(int) * handSize);
  memcpy(G.deck[0], k, sizeof(int) * deckSize);
  memcpy(G.discard[0], k, sizeof(int) * discardSize);

  G.handCount[1] = handSize;
  G.deckCount[1] = deckSize;
  G.discardCount[1] = discardSize;
  memcpy(G.hand[1], k, sizeof(int) * handSize);
  memcpy(G.deck[1], k, sizeof(int) * deckSize);
  memcpy(G.discard[1], k, sizeof(int) * discardSize);

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
  numTests ++;
  passNum += assertTrue("Embargo results in no change to other player's discard size\n", G.discardCount[1] == discardSize);

  /*Test Case 3: Ten embargos currently on supply
  * Anticipated result: function returns 0, hand size decreased by 1, deck size unchanged, discard size increased by 1, embargo set on supply card, treasure increased by 2, other players' hand/deck sizes unaffected */
  supplyCount = 10;
  handPos = 2;
  handSize = 10;
  deckSize = 10; 
  discardSize = 2;
  embargoCt = 10;
  coins = 0;
  memset(&G, 23, sizeof(struct gameState));
  game = initializeGame(2, k, seed, &G);

  G.handCount[0] = handSize;
  G.deckCount[0] = deckSize;
  G.discardCount[0] = discardSize;
  G.embargoTokens[choice1] = embargoCt;
  G.coins = coins;
  G.supplyCount[choice1] = supplyCount;
  memcpy(G.hand[0], k, sizeof(int) * handSize);
  memcpy(G.deck[0], k, sizeof(int) * deckSize);
  memcpy(G.discard[0], k, sizeof(int) * discardSize);

  G.handCount[1] = handSize;
  G.deckCount[1] = deckSize;
  G.discardCount[1] = discardSize;
  memcpy(G.hand[1], k, sizeof(int) * handSize);
  memcpy(G.deck[1], k, sizeof(int) * deckSize);
  memcpy(G.discard[1], k, sizeof(int) * discardSize);

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
  numTests ++;
  passNum += assertTrue("Embargo results in no change to other player's discard size\n", G.discardCount[1] == discardSize);

  /*Test Case 4: Supply selected is empty
  * Anticipated result: function returns -1, hand size -1, deck size unchanged, discard size -1, embargo not set, treasure increased by 2, other players' hand/deck sizes unaffected */
  supplyCount = -1;
  handPos = 2;
  handSize = 10;
  deckSize = 10; 
  discardSize = 2;
  embargoCt = 0;
  coins = 0;
  memset(&G, 23, sizeof(struct gameState));
  game = initializeGame(2, k, seed, &G);

  G.handCount[0] = handSize;
  G.deckCount[0] = deckSize;
  G.discardCount[0] = discardSize;
  G.embargoTokens[choice1] = embargoCt;
  G.coins = coins;
  G.supplyCount[choice1] = supplyCount;
  memcpy(G.hand[0], k, sizeof(int) * handSize);
  memcpy(G.deck[0], k, sizeof(int) * deckSize);
  memcpy(G.discard[0], k, sizeof(int) * discardSize);

  G.handCount[1] = handSize;
  G.deckCount[1] = deckSize;
  G.discardCount[1] = discardSize;
  memcpy(G.hand[1], k, sizeof(int) * handSize);
  memcpy(G.deck[1], k, sizeof(int) * deckSize);
  memcpy(G.discard[1], k, sizeof(int) * discardSize);

  // check return value
  returnVal = cardEffect(embargo, choice1, choice2, choice3, &G, handPos, &bonus);
  #if(NOISY_TEST)
  printf("Embargo return = %d, expected -1\n", returnVal);
  #endif
  numTests++;
  passNum += assertTrue("Embargo returns -1 when supply is empty\n", returnVal == -1);

  // check hand size
  #if(NOISY_TEST)
  printf("Ending hand size = %d, expected %d\n", G.handCount[0], handSize);
  #endif
  numTests++;
  passNum += assertTrue("Embargo results in unchanged hand size when supply is empty\n", (G.handCount[0] == (handSize))); 
  
  // check deck size
  #if(NOISY_TEST)
  printf("Ending deck size = %d, expected %d\n", G.deckCount[0], (deckSize));
  #endif
  numTests++;
  passNum += assertTrue("Embargo results in an unchanged deck size when supply is empty\n", (G.deckCount[0] == (deckSize)));

  // check discard size
  #if(NOISY_TEST)
  printf("Ending discard size = %d, expected %d\n", G.discardCount[0], (discardSize));
  #endif
  numTests++;
  passNum += assertTrue("Embargo results in an unchanged played card pile when supply is empty\n", (G.discardCount[0] == (discardSize)));

  // check embargo count
  #if(NOISY_TEST)
  printf("Ending embargo count = %d, expected %d\n", G.embargoTokens[choice1], embargoCt);
  #endif
  numTests++;
  passNum += assertTrue("Embargo does not result in an incremented embargo status\n", (G.embargoTokens[choice1] == (embargoCt)));

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
  numTests ++;
  passNum += assertTrue("Embargo results in no change to other player's discard size\n", G.discardCount[1] == discardSize);



  if(passNum == numTests)
  {
    printf("\nSUCCESS: ALL TESTS PASSED\n\n");
  }
  else
  {
    printf("\n%d/%d TESTS PASSED\n\n", passNum, numTests);
  }
}
