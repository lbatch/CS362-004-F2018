/* unittest2: Testing isgameover function
**
** Include in makefile:
** unittest2: unittest1.c dominion.o rngs.o
** gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS) 
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

  printf("UNIT TEST 2\n");

  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, province, smithy};

  int seed = 1000;
  int returnVal; 
  int game;
  int passNum = 0;
  int numTests = 0;
  
  printf("Testing isGameOver():\n");

  /* Test case 1: No supply piles are empty
  * Anticipated result: function returns 0 */
  #if(NOISY_TEST)
  printf("Testing deck with no empty stacks: \n");
  #endif

  memset(&G, 23, sizeof(struct gameState));
  game = initializeGame(2, k, seed, &G);
  returnVal = isGameOver(&G);

  #if(NOISY_TEST)
  printf("isGameOver return = %d, expected 0\n", returnVal);
  #endif
  numTests++;
  passNum += assertTrue("Game does not end with no empty stacks\n", returnVal == 0);
 
  /* Test case 2: 1 supply pile is empty
  * Anticipated result: function returns 0 */
  #if(NOISY_TEST)
  printf("Testing deck with one (non-Province) empty stack: \n");
  #endif

  memset(&G, 23, sizeof(struct gameState));
  game = initializeGame(2, k, seed, &G);
  G.supplyCount[adventurer] = 0;
  returnVal = isGameOver(&G); 

  #if(NOISY_TEST)
  printf("isGameOver return = %d, expected 1\n", returnVal);
  #endif
  numTests++;
  passNum += assertTrue("Game does not end with one empty stack\n", returnVal == 0);

  /* Test case 3: 2 supply piles are empty
  * Anticipated result: function returns 0 */
  #if(NOISY_TEST)
  printf("Testing deck with two (non-Province) empty stacks: \n");
  #endif

  memset(&G, 23, sizeof(struct gameState));
  game = initializeGame(2, k, seed, &G);
  G.supplyCount[gardens] = 0;
  G.supplyCount[embargo] = 0;
  returnVal = isGameOver(&G); 

  #if(NOISY_TEST)
  printf("isGameOver return = %d, expected 0\n", returnVal);
  #endif
  numTests++;
  passNum += assertTrue("Game does not end with two empty stacks\n", returnVal == 0);

  /* Test case 4: 3 supply piles are empty
  * Anticipated result: function returns 1 */
  #if(NOISY_TEST)
  printf("Testing deck with three (non-Province) empty stacks: \n");
  #endif

  memset(&G, 23, sizeof(struct gameState));
  game = initializeGame(2, k, seed, &G);
  G.supplyCount[minion] = 0;
  G.supplyCount[cutpurse] = 0;
  G.supplyCount[mine] = 0;
  returnVal = isGameOver(&G); 

  #if(NOISY_TEST)
  printf("isGameOver return = %d, expected 1\n", returnVal);
  #endif
  numTests++;
  passNum += assertTrue("Game ends with three empty stacks\n", returnVal == 1);

  /* Test case 5: 3 supply piles are empty
  * Anticipated result: function returns 1 */
  #if(NOISY_TEST)
  printf("Testing deck with nine (non-Province) empty stacks: \n");
  #endif

  memset(&G, 23, sizeof(struct gameState));
  game = initializeGame(2, k, seed, &G);
  G.supplyCount[adventurer] = 0;
  G.supplyCount[gardens] = 0;
  G.supplyCount[embargo] = 0;
  G.supplyCount[village] = 0;
  G.supplyCount[sea_hag] = 0;
  G.supplyCount[smithy] = 0;
  G.supplyCount[minion] = 0;
  G.supplyCount[cutpurse] = 0;
  G.supplyCount[mine] = 0;
  returnVal = isGameOver(&G); 

  #if(NOISY_TEST)
  printf("isGameOver return = %d, expected 1\n", returnVal);
  #endif
  numTests++;
  passNum += assertTrue("Game ends with nine empty stacks\n", returnVal == 1);



  /* Test case 6: Stack of Province cards is empty
  * Anticipated result: function returns 1 */
  #if(NOISY_TEST)
  printf("Testing deck with empty Province stack: \n");
  #endif

  memset(&G, 23, sizeof(struct gameState));
  game = initializeGame(2, k, seed, &G);
  G.supplyCount[province] = 0;
  returnVal = isGameOver(&G); 

  #if(NOISY_TEST)
  printf("isGameOver return = %d, expected 1\n", returnVal);
  #endif
  numTests++;
  passNum += assertTrue("Game ends with 0 Province cards\n", returnVal == 1);

  if(passNum == numTests)
  {
    printf("\nSUCCESS: ALL TESTS PASSED\n\n");
  }
  else
  {
    printf("\n%d/%d TESTS PASSED\n\n", passNum, numTests);
  }
}
