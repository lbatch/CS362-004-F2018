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

  printf("CARD TEST 2: ADVENTURER\n");

  struct gameState G;
  int numPlayers = 2;
  int seed = 1000;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
  int deck1[10] = {adventurer, gold, gardens, embargo, copper, village, silver, minion, mine, cutpurse};
  int deck2[3] = {copper, embargo, gardens};
  int discard2[3] = {adventurer, embargo, gold};
  int deck3[3] = {gardens, copper, adventurer};
  int discard3[3] = {embargo, embargo, embargo};
  int choice1 = 0;
  int choice2 = 0;
  int choice3 = 0;
  int handPos = 0;
  int bonus = 0;
  int game, handSize, deckSize, discardSize, returnVal; 
  int numTests = 0;
  int passNum = 0;

  /*Test Case 1: at least 2 treasures in deck
  * Anticipated result: function returns 0, hand size increased by 1, deck size decreased by 2 treasures + cards on top, discard size increased by 1 Adventurer + cards on top, no other players' hand/deck sizes affected */
  handPos = 0;
  handSize = 10;
  deckSize = 10; 
  discardSize = 3;
  memset(&G, 23, sizeof(struct gameState));
  game = initializeGame(2, k, seed, &G);

  G.handCount[0] = handSize;
  G.deckCount[0] = deckSize;
  G.discardCount[0] = discardSize;
  memcpy(G.hand[0], k, sizeof(int) * handSize);
  memcpy(G.deck[0], deck1, sizeof(int) * deckSize);
  memcpy(G.discard[0], k, sizeof(int) * discardSize);

  G.handCount[1] = handSize;
  G.deckCount[1] = deckSize;
  G.discardCount[1] = discardSize;
  memcpy(G.hand[1], k, sizeof(int) * handSize);
  memcpy(G.deck[1], deck1, sizeof(int) * deckSize);
  memcpy(G.discard[1], k, sizeof(int) * discardSize);

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
  numTests ++;
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
  numTests ++;
  passNum += assertTrue("Adventurer results in no change to other player's discard size\n", G.discardCount[1] == discardSize);

  /* Test case 2: Treasure is split between deck and discard pile
  * Anticipated result: function returns 0, hand size increased by 1, no other players' hand/deck sizes affected */
  #if(NOISY_TEST)
  printf("Testing Adventurer when treasure is split between deck and discard pile: \n");
  #endif

  handPos = 0;
  handSize = 10;
  deckSize = 3; 
  discardSize = 3;
  memset(&G, 23, sizeof(struct gameState));
  game = initializeGame(2, k, seed, &G);

  G.handCount[0] = handSize;
  G.deckCount[0] = deckSize;
  G.discardCount[0] = discardSize;
  memcpy(G.hand[0], k, sizeof(int) * handSize);
  memcpy(G.deck[0], deck2, sizeof(int) * deckSize);
  memcpy(G.discard[0], discard2, sizeof(int) * discardSize);

  G.handCount[1] = handSize;
  G.deckCount[1] = deckSize;
  G.discardCount[1] = discardSize;
  memcpy(G.hand[1], k, sizeof(int) * handSize);
  memcpy(G.deck[1], k, sizeof(int) * deckSize);
  memcpy(G.discard[1], k, sizeof(int) * discardSize);

  // check return value
  returnVal = cardEffect(adventurer, choice1, choice2, choice3, &G, handPos, &bonus);
  #if(NOISY_TEST)
  printf("Adventurer return = %d, expected 0\n", returnVal);
  #endif
  numTests++;
  passNum += assertTrue("Adventurer returns 0 when treasure cards are split between deck and discard\n", returnVal == 0);

  // check hand size
  #if(NOISY_TEST)
  printf("Ending hand size = %d, expected %d\n", G.handCount[0], (handSize + 2 - 1));
  #endif
  numTests++;
  passNum += assertTrue("Adventurer results in one net card added to the hand size\n", (G.handCount[0] == handSize + 2 - 1)); 
  
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
  numTests ++;
  passNum += assertTrue("Adventurer results in no change to other player's discard size\n", G.discardCount[1] == discardSize);

  /* Test case 3: Less than 2 treasures between deck and discard
  * Anticipated result: function returns 0, hand size increased by 0, deck size at 0, discard size at previous discard + previous deck + 1, no other players' hand/deck sizes affected */
  #if(NOISY_TEST)
  printf("Testing Adventurer when deck and discard contain only one treasure card: \n");
  #endif

  handPos = 0;
  handSize = 10;
  deckSize = 3; 
  discardSize = 3;
  memset(&G, 23, sizeof(struct gameState));
  game = initializeGame(2, k, seed, &G);

  G.handCount[0] = handSize;
  G.deckCount[0] = deckSize;
  G.discardCount[0] = discardSize;
  memcpy(G.hand[0], k, sizeof(int) * handSize);
  memcpy(G.deck[0], deck3, sizeof(int) * deckSize);
  memcpy(G.discard[0], discard3, sizeof(int) * discardSize);

  G.handCount[1] = handSize;
  G.deckCount[1] = deckSize;
  G.discardCount[1] = discardSize;
  memcpy(G.hand[1], k, sizeof(int) * handSize);
  memcpy(G.deck[1], k, sizeof(int) * deckSize);
  memcpy(G.discard[1], k, sizeof(int) * discardSize);

  // check return value
  returnVal = cardEffect(adventurer, choice1, choice2, choice3, &G, handPos, &bonus);
  #if(NOISY_TEST)
  printf("Adventurer return = %d, expected 0\n", returnVal);
  #endif
  numTests++;
  passNum += assertTrue("Adventurer returns 0 when deck+discard contains only 1 treasure card\n", returnVal == 0);

  // check hand size
  #if(NOISY_TEST)
  printf("Ending hand size = %d, expected %d\n", G.handCount[0], handSize);
  #endif
  numTests++;
  passNum += assertTrue("Adventurer results in 0 net cards added to the hand size\n", G.handCount[0]); 
  
  // check deck size
  #if(NOISY_TEST)
  printf("Ending deck size = %d, expected %d\n", G.deckCount[0], 0);
  #endif
  numTests++;
  passNum += assertTrue("Adventurer results in 0 cards in the deck\n", (G.deckCount[0] == 0));

  // check discard size
  #if(NOISY_TEST)
  printf("Ending discard size = %d, expected %d\n", G.discardCount[0], (discardSize + deckSize + 1));
  #endif
  numTests ++;
  passNum += assertTrue("Adventurer results in increase to discard pile equal to 1 Adventurer and the previous deck\n", (G.discardCount[0] == discardSize + deckSize + 1));

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
  numTests ++;
  passNum += assertTrue("Adventurer results in no change to other player's discard size\n", G.discardCount[1] == discardSize);
 
  
  if(passNum == numTests)
  {
    printf("\nSUCCESS: ALL TESTS PASSED\n");
  }
  else
  {
    printf("\n%d/%d TESTS PASSED\n", passNum, numTests);
  }
}
