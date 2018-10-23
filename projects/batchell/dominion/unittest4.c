/* unittest4: Testing handcard function
**
** Include in makefile:
** unittest4: unittest4.c dominion.o rngs.o
** gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS) 
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

  printf("UNIT TEST 4\n");

  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, province, smithy};

  int seed = 1000;
  int returnVal; 
  int game;
  int passNum = 0;
  int numTests = 0;
  int currentPlayer;
  
  printf("Testing handCard():\n");

  /* Test case 1: Hand position is not valid (hand is empty)
  * Anticipated result: function returns -1 or other error response */
  #if(NOISY_TEST)
  printf("Testing response when hand is empty: \n");
  #endif

  memset(&G, 23, sizeof(struct gameState));
  game = initializeGame(2, k, seed, &G);
  currentPlayer = whoseTurn(&G);
  G.handCount[currentPlayer] = 0;
  returnVal = handCard(0, &G);

  #if(NOISY_TEST)
  printf("handCard() return = %d, expected -1 or error\n", returnVal);
  #endif
  numTests++;
  passNum += assertTrue("handCard() indicates error when hand is empty\n", returnVal == -1);
 
  /* Test case 2: Hand position is not empty (exceeds hand size)
  * Anticipated result: function returns -1 or other error response */
  #if(NOISY_TEST)
  printf("Testing response when hand position is invalid: \n");
  #endif

  memset(&G, 23, sizeof(struct gameState));
  game = initializeGame(2, k, seed, &G);
  currentPlayer = whoseTurn(&G);
  G.handCount[currentPlayer] = 10;
  memcpy(G.deck[0], k, sizeof(int) * 10);
  returnVal = handCard(0, &G);  

  #if(NOISY_TEST)
  printf("handCart() return = %d, expected -1 or error\n", returnVal);
  #endif
  numTests++;
  passNum += assertTrue("handCard() indicates error when hand position is invalid\n", returnVal == -1);

  /* Test case 4: Valid card present
  * Anticipated result: function returns card */
  #if(NOISY_TEST)
  printf("Testing response when card is present in hand position: \n");
  #endif

  memset(&G, 23, sizeof(struct gameState));
  game = initializeGame(2, k, seed, &G);
  currentPlayer = whoseTurn(&G);
  G.handCount[0] = 10;
  memcpy(G.hand[0], k, sizeof(int) * 10);
  
  // At beginning of hand
  returnVal = handCard(0, &G); 
  #if(NOISY_TEST)
  printf("handCard return = %d, expected adventurer\n", returnVal);
  #endif
  numTests++;
  passNum += assertTrue("Correct card returned from beginning of hand\n", returnVal == adventurer);

  // At end of deck
  returnVal = handCard(9, &G); 
  #if(NOISY_TEST)
  printf("handCard return = %d, expected smithy\n", returnVal);
  #endif
  numTests++;
  passNum += assertTrue("Correct card returned from end of hand\n", returnVal == smithy);

  // In middle of deck
  returnVal = handCard(4, &G); 
  #if(NOISY_TEST)
  printf("handCard return = %d, expected minion\n", returnVal);
  #endif
  numTests++;
  passNum += assertTrue("Correct card returned from middle of hand\n", returnVal == minion);
 
  if(passNum == numTests)
  {
    printf("\nSUCCESS: ALL TESTS PASSED\n\n");
  }
  else
  {
    printf("\n%d/%d TESTS PASSED\n\n", passNum, numTests);
  }
}
