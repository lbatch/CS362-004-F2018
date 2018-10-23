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

  printf("CARD TEST 1: SMITHY\n");

  struct gameState G;
  int numPlayers = 2;
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

  printf("Testing Smithy:\n");

  /* Test case 1: Deck contains at least 3 cards to draw
  * Anticipated result: function returns 0, net hand size increased by 2, deck size decreased by 3, discard increased by 1, no other players' hand/deck sizes affected */
  #if(NOISY_TEST)
  printf("Testing Smithy when deck contains at least 3 cards to draw:: \n");
  #endif

  handPos = 9;
  handSize = 4;
  deckSize = 10; 
  discardSize = 10;
  memset(&G, 23, sizeof(struct gameState));
  game = initializeGame(2, k, seed, &G);

  G.handCount[0] = handSize;
  G.deckCount[0] = deckSize;
  G.discardCount[0] = discardSize;
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
  returnVal = cardEffect(smithy, choice1, choice2, choice3, &G, handPos, &bonus);
  #if(NOISY_TEST)
  printf("Smithy return = %d, expected 0\n", returnVal);
  #endif
  numTests++;
  passNum += assertTrue("Smithy returns 0 when deck contains at least 3 cards to draw\n", returnVal == 0);

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
  numTests ++;
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
  numTests ++;
  passNum += assertTrue("Smithy results in no change to other player's discard size\n", G.discardCount[1] == discardSize);

  /* Test case 2: Deck contains less than 3 cards to draw
  * Anticipated result: function returns 0, net hand size increased by 2, deck size increased by discard size - 3, discard equal to 1, no other players' hand/deck sizes affected */
  #if(NOISY_TEST)
  printf("Testing Smithy when deck contains less than 3 cards to draw, requiring a shuffle of the discard pile: \n");
  #endif

  handPos = 9;
  handSize = 4;
  deckSize = 2; 
  discardSize = 10;
  memset(&G, 23, sizeof(struct gameState));
  game = initializeGame(2, k, seed, &G);

  G.handCount[0] = handSize;
  G.deckCount[0] = deckSize;
  G.discardCount[0] = discardSize;
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
  returnVal = cardEffect(smithy, choice1, choice2, choice3, &G, handPos, &bonus);
  #if(NOISY_TEST)
  printf("Smithy return = %d, expected 0\n", returnVal);
  #endif
  numTests++;
  passNum += assertTrue("Smithy returns 0 when deck contains at least 3 cards to draw\n", returnVal == 0);

  // check hand size
  #if(NOISY_TEST)
  printf("Ending hand size = %d, expected %d\n", G.handCount[0], handSize + 3 - 1);
  #endif
  numTests++;
  passNum += assertTrue("Smithy results in two net cards added to the hand size\n", (G.handCount[0] == handSize + 3 - 1)); 
  
  // check deck size
  #if(NOISY_TEST)
  printf("Ending deck size = %d, expected %d\n", G.deckCount[0], deckSize + discardSize - 3);
  #endif
  numTests++;
  passNum += assertTrue("Smithy results in (deck size + discard pile size - 3) cards in the deck\n", (G.deckCount[0] == deckSize + discardSize - 3));

  // check discard size
  #if(NOISY_TEST)
  printf("Ending discard size = %d, expected %d\n", G.discardCount[0], 1);
  #endif
  numTests ++;
  passNum += assertTrue("Smithy results in one card added to the discard\n", (G.discardCount[0] == 1));

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
  numTests ++;
  passNum += assertTrue("Smithy results in no change to other player's discard size\n", G.discardCount[1] == discardSize);
 
 
  if(passNum == numTests)
  {
    printf("\nSUCCESS: ALL TESTS PASSED\n");
  }
  else
  {
    printf("\n%d/%d TESTS PASSED\n", passNum, numTests);
  }
}
