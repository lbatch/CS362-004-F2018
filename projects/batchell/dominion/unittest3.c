/* unittest2: Testing isgameover function
**
** Include in makefile:
** unittest3: unittest3.c dominion.o rngs.o
** gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS) 
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

  printf("UNIT TEST 3\n");

  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, province, smithy};

  int seed = 1000;
  int returnVal; 
  int game;
  int passNum = 0;
  int numTests = 0;
  
  printf("Testing fullDeckCount():\n");

  /* Test case 1: Card is not in deck, hand, or discard pile
  * Anticipated result: function returns 0 */
  #if(NOISY_TEST)
  printf("Testing deck count when card is not present anywhere in deck/hand/discard: \n");
  #endif

  memset(&G, 23, sizeof(struct gameState));
  game = initializeGame(2, k, seed, &G);
  returnVal = fullDeckCount(0, cutpurse, &G);

  #if(NOISY_TEST)
  printf("fullDeckCount return = %d, expected 0\n", returnVal);
  #endif
  numTests++;
  passNum += assertTrue("Deck count for non-present card is 0\n", returnVal == 0);
 
  /* Test case 2: Card is only in deck
  * Anticipated result: function returns 1 */
  #if(NOISY_TEST)
  printf("Testing deck count when card is only present in deck: \n");
  #endif

  memset(&G, 23, sizeof(struct gameState));
  game = initializeGame(2, k, seed, &G);
  G.deckCount[0] = 10;
  memcpy(G.deck[0], k, sizeof(int) * 10);
  
  // At beginning of deck
  returnVal = fullDeckCount(0, adventurer, &G); 
  #if(NOISY_TEST)
  printf("fullDeckCount return = %d, expected 1\n", returnVal);
  #endif
  numTests++;
  passNum += assertTrue("Single card found at beginning of deck\n", returnVal == 1);

  // At end of deck
  returnVal = fullDeckCount(0, smithy, &G); 
  #if(NOISY_TEST)
  printf("fullDeckCount return = %d, expected 1\n", returnVal);
  #endif
  numTests++;
  passNum += assertTrue("Single card found at end of deck\n", returnVal == 1);

  // In middle of deck
  returnVal = fullDeckCount(0, minion, &G); 
  #if(NOISY_TEST)
  printf("fullDeckCount return = %d, expected 1\n", returnVal);
  #endif
  numTests++;
  passNum += assertTrue("Single card found in middle of deck\n", returnVal == 1);

  /* Test case 3: Card is only in hand
  * Anticipated result: function returns 1 */
  #if(NOISY_TEST)
  printf("Testing deck count when card is only present in hand: \n");
  #endif

  memset(&G, 23, sizeof(struct gameState));
  game = initializeGame(2, k, seed, &G);
  G.handCount[0] = 10;
  memcpy(G.hand[0], k, sizeof(int) * 10);
  
  // At beginning of hand
  returnVal = fullDeckCount(0, adventurer, &G); 
  #if(NOISY_TEST)
  printf("fullDeckCount return = %d, expected 1\n", returnVal);
  #endif
  numTests++;
  passNum += assertTrue("Single card found at beginning of hand\n", returnVal == 1);

  // At end of hand
  returnVal = fullDeckCount(0, smithy, &G); 
  #if(NOISY_TEST)
  printf("fullDeckCount return = %d, expected 1\n", returnVal);
  #endif
  numTests++;
  passNum += assertTrue("Single card found at end of hand\n", returnVal == 1);

  // In middle of hand
  returnVal = fullDeckCount(0, minion, &G); 
  #if(NOISY_TEST)
  printf("fullDeckCount return = %d, expected 1\n", returnVal);
  #endif
  numTests++;
  passNum += assertTrue("Single card found in middle of hand\n", returnVal == 1);

  /* Test case 4: Card is only in discard
  * Anticipated result: function returns 1 */
  #if(NOISY_TEST)
  printf("Testing deck count when card is only present in discard pile: \n");
  #endif

  memset(&G, 23, sizeof(struct gameState));
  game = initializeGame(2, k, seed, &G);
  G.discardCount[0] = 10;
  memcpy(G.discard[0], k, sizeof(int) * 10);
  
  // At beginning of deck
  returnVal = fullDeckCount(0, adventurer, &G); 
  #if(NOISY_TEST)
  printf("fullDeckCount return = %d, expected 1\n", returnVal);
  #endif
  numTests++;
  passNum += assertTrue("Single card found at beginning of discard\n", returnVal == 1);

  // At end of deck
  returnVal = fullDeckCount(0, smithy, &G); 
  #if(NOISY_TEST)
  printf("fullDeckCount return = %d, expected 1\n", returnVal);
  #endif
  numTests++;
  passNum += assertTrue("Single card found at end of discard\n", returnVal == 1);

  // In middle of deck
  returnVal = fullDeckCount(0, minion, &G); 
  #if(NOISY_TEST)
  printf("fullDeckCount return = %d, expected 1\n", returnVal);
  #endif
  numTests++;
  passNum += assertTrue("Single card found in middle of discard\n", returnVal == 1);
 
  /* Test case 5: 1-10 cards each in deck, hand, and discard pile
  * Anticipated result: sum of deckCt, handCt, and disCt*/
  
  int deckCt, handCt, disCt;
  int i, j, m;

  for(deckCt = 1; deckCt <= 10; deckCt++)
  {
    for(handCt = 1; handCt <= 10; handCt++)
    {
      for(disCt = 1; disCt <= 10; disCt++)
      {
         #if(NOISY_TEST)
         printf("Testing deck count with %d in deck, %d in hand, and %d in discard pile: \n", deckCt, handCt, disCt);
         #endif

         memset(&G, 23, sizeof(struct gameState));
         game = initializeGame(2, k, seed, &G);
         G.deckCount[0] = 10;
         G.handCount[0] = 10;
         G.discardCount[0] = 10;
         memcpy(G.deck[0], k, sizeof(int) * 10);
         memcpy(G.hand[0], k, sizeof(int) * 10);
         memcpy(G.discard[0], k, sizeof(int) * 10);

         for(i = 0; i < deckCt; i++)
         {
           G.deck[0][i] = adventurer;
         }
         for(j = 0; j < handCt; j++)
         {
           G.hand[0][j] = adventurer;
         }
         for(m = 0; m < disCt; m++)
         {
           G.discard[0][m] = adventurer;
         }

         returnVal = fullDeckCount(0, adventurer, &G);

         #if(NOISY_TEST)
         printf("fullDeckCount return = %d, expected %d\n", returnVal, deckCt + handCt + disCt);
         #endif
         numTests++;
         passNum += assertTrue("Correct sum returned between deck, hand, and discard\n", returnVal == (deckCt + handCt + disCt));
      }
    }
  }

  if(passNum == numTests)
  {
    printf("\nSUCCESS: ALL TESTS PASSED\n");
  }
  else
  {
    printf("\n%d/%d TESTS PASSED\n", passNum, numTests);
  }
}
