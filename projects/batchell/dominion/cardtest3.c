/* cardtest2: Testing village function
**
** Include in makefile:
** cardtest3: cardtest3.c dominion.o rngs.o
** gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS) 
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

  printf("CARD TEST 3: VILLAGE\n");

  struct gameState G;
  int numPlayers = 2;
  int seed = 1000;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
  int choice1 = 0;
  int choice2 = 0;
  int choice3 = 0;
  int handPos = 0;
  int bonus = 0;
  int game, handSize, deckSize, discardSize, actions, returnVal; 
  int numTests = 0;
  int passNum = 0;

  /*Test Case 1: Deck is non-empty, 1 action left at start of play
  * Anticipated result: function returns 0, hand size increased by net 0, deck size decreased by 1, discard size unchanged, actions in state increased by 2, other players' hand/deck sizes affected */
  handPos = 3;
  handSize = 10;
  deckSize = 10; 
  discardSize = 2;
  actions = 1;
  memset(&G, 23, sizeof(struct gameState));
  game = initializeGame(2, k, seed, &G);

  G.handCount[0] = handSize;
  G.deckCount[0] = deckSize;
  G.discardCount[0] = discardSize;
  G.numActions = actions;
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
  returnVal = cardEffect(village, choice1, choice2, choice3, &G, handPos, &bonus);
  #if(NOISY_TEST)
  printf("Village return = %d, expected 0\n", returnVal);
  #endif
  numTests++;
  passNum += assertTrue("Village returns 0 when deck contains at least 1 card\n", returnVal == 0);

  // check hand size
  #if(NOISY_TEST)
  printf("Ending hand size = %d, expected %d\n", G.handCount[0], handSize);
  #endif
  numTests++;
  passNum += assertTrue("Village results in zero net cards added to the hand size\n", (G.handCount[0] == handSize)); 
  
  // check deck size
  #if(NOISY_TEST)
  printf("Ending deck size = %d, expected %d\n", G.deckCount[0], (deckSize - 1));
  #endif
  numTests++;
  passNum += assertTrue("Village results in one less card in the deck\n", (G.deckCount[0] == (deckSize-1)));

  // check discard size
  #if(NOISY_TEST)
  printf("Ending discard size = %d, expected %d\n", G.discardCount[0], (discardSize + 1));
  #endif
  numTests++;
  passNum += assertTrue("Village results in one more card in the discard pile\n", (G.discardCount[0] == (discardSize + 1)));

  // check actions
  #if(NOISY_TEST)
  printf("Ending action count = %d, expected %d\n", G.numActions, actions + 2);
  #endif
  numTests++;
  passNum += assertTrue("Village results in two additional actions\n", (G.numActions == (actions + 2)));
 
  // check other player hand size
  #if(NOISY_TEST)
  printf("Ending hand size = %d, expected %d\n", G.handCount[1], handSize);
  #endif
  numTests++;
  passNum += assertTrue("Village results in no change to other player's hand size\n", (G.handCount[1] == handSize)); 
  
  // check other player deck size
  #if(NOISY_TEST)
  printf("Ending deck size = %d, expected %d\n", G.deckCount[1], deckSize);
  #endif
  numTests++;
  passNum += assertTrue("Village results in no change to other player's deck size\n", G.deckCount[1] == deckSize);

  // check other player discard size
  #if(NOISY_TEST)
  printf("Ending discard size = %d, expected %d\n", G.discardCount[1], discardSize);
  #endif
  numTests ++;
  passNum += assertTrue("Village results in no change to other player's discard size\n", G.discardCount[1] == discardSize);

  /*Test Case 2: Deck is empty, 1 action left at start of play
  * Anticipated result: function returns 0, hand size increased by net 0, deck size increased by discard size -1, discard size is 1, actions in state increased by 2, other players' hand/deck sizes affected */
  handPos = 3;
  handSize = 10;
  deckSize = 0; 
  discardSize = 2;
  actions = 1;
  memset(&G, 23, sizeof(struct gameState));
  game = initializeGame(2, k, seed, &G);

  G.handCount[0] = handSize;
  G.deckCount[0] = deckSize;
  G.discardCount[0] = discardSize;
  G.numActions = actions;
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
  returnVal = cardEffect(village, choice1, choice2, choice3, &G, handPos, &bonus);
  #if(NOISY_TEST)
  printf("Village return = %d, expected 0\n", returnVal);
  #endif
  numTests++;
  passNum += assertTrue("Village returns 0 when deck is empty\n", returnVal == 0);

  // check hand size
  #if(NOISY_TEST)
  printf("Ending hand size = %d, expected %d\n", G.handCount[0], handSize);
  #endif
  numTests++;
  passNum += assertTrue("Village results in zero net cards added to the hand size\n", (G.handCount[0] == handSize)); 
  
  // check deck size
  #if(NOISY_TEST)
  printf("Ending deck size = %d, expected %d\n", G.deckCount[0], (deckSize - 1));
  #endif
  numTests++;
  passNum += assertTrue("Village results in deck size equal to discard - 1\n", (G.deckCount[0] == (discardSize - 1)));

  // check discard size
  #if(NOISY_TEST)
  printf("Ending discard size = %d, expected %d\n", G.discardCount[0], 1);
  #endif
  numTests++;
  passNum += assertTrue("Village results in one card in the discard pile\n", (G.discardCount[0] == 1));

  // check actions
  #if(NOISY_TEST)
  printf("Ending action count = %d, expected %d\n", G.numActions, actions + 2);
  #endif
  numTests++;
  passNum += assertTrue("Village results in two additional actions\n", (G.numActions == (actions + 2)));
 
  // check other player hand size
  #if(NOISY_TEST)
  printf("Ending hand size = %d, expected %d\n", G.handCount[1], handSize);
  #endif
  numTests++;
  passNum += assertTrue("Village results in no change to other player's hand size\n", (G.handCount[1] == handSize)); 
  
  // check other player deck size
  #if(NOISY_TEST)
  printf("Ending deck size = %d, expected %d\n", G.deckCount[1], deckSize);
  #endif
  numTests++;
  passNum += assertTrue("Village results in no change to other player's deck size\n", G.deckCount[1] == deckSize);

  // check other player discard size
  #if(NOISY_TEST)
  printf("Ending discard size = %d, expected %d\n", G.discardCount[1], discardSize);
  #endif
  numTests ++;
  passNum += assertTrue("Village results in no change to other player's discard size\n", G.discardCount[1] == discardSize);

  if(passNum == numTests)
  {
    printf("\nSUCCESS: ALL TESTS PASSED\n");
  }
  else
  {
    printf("\n%d/%d TESTS PASSED\n", passNum, numTests);
  }
}
