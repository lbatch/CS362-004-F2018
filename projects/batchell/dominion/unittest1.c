/* unittest1: Testing shuffle function
**
** Include in makefile:
** unittest1: unittest1.c dominion.o rngs.o
** gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS) 
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
  printf("UNIT TEST 1: shuffle()\n");

  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

  int seed = 1000;
  int returnVal; 
  int game;
  int passNum = 0;
  int numTests = 0;
  int nump, p, c, i;
  int compareDeck[27];
  int sampledecks[4][10];
  int sampledeck1[10] = {adventurer, adventurer, embargo, village, minion, mine, village, embargo, tribute, smithy};
  int sampledeck2[10] = {adventurer, adventurer, adventurer, adventurer, adventurer, adventurer, adventurer, adventurer, adventurer, adventurer};
  int sampledeck3[10] = {adventurer, adventurer, gardens, gardens, embargo, embargo, village, village, minion, minion};
  memcpy(sampledecks[0], k, sizeof(int) * 10);
  memcpy(sampledecks[1], sampledeck1, sizeof(int) * 10);
  memcpy(sampledecks[2], sampledeck2, sizeof(int) * 10);
  memcpy(sampledecks[3], sampledeck3, sizeof(int) * 10);

  printf("Testing shuffle():\n");

  /* Shuffle a deck with 0 cards
  * Anticipated result, TEST 1: function returns -1 */
  #if(NOISY_TEST)
  printf("Testing deck with 0 cards: ");
  #endif

  memset(&G, 23, sizeof(struct gameState));
  game = initializeGame(2, k, seed, &G);
  G.deckCount[0] = 0;
  returnVal = shuffle(0, &G); 

  #if(NOISY_TEST)
  printf("Shuffle return = %d, expected -1", returnVal);
  #endif
  numTests++;
  passNum += assertTrue("Shuffling a deck with 0 cards returns error code", returnVal == -1);

  /*Shuffle 1-10 cards for player 1, 2, 3, and 4
  * Anticipated result, successful return, deck size is the same, all cards included in same quantities */
  for(nump = 2; nump <= 4; nump++)
  {
    for(p = 0; p < nump; p++)
    {
      for(c = 1; c <= 10; c++)
      {
        #if(NOISY_TEST)
        printf("Testing with %d players, Player %d, with %d cards in hand.\n", nump, p, c);
        #endif
       
        // Reset game and shuffle deck
        memset(&G, 23, sizeof(struct gameState));
        game = initializeGame(nump, k, seed, &G);
        G.deckCount[p] = c;
        memcpy(G.deck[p], sampledecks[p], sizeof(int) * c);
        returnVal = shuffle(p, &G);

        // Test whether deck size is the same
        numTests++;
        passNum += assertTrue("Shuffling results in identical deck size", G.deckCount[p] == c);

        // Test whether all cards are included in the same quantities
        memset(compareDeck, 0, 27 * sizeof(int));
        for(i = 0; i < c; i++)
        {        
           compareDeck[G.deck[p][i]] += 1;
           compareDeck[sampledecks[p][i]] -= 1;
        }
        for(i = 0; i < 10; i++)
        {
          numTests++;
          passNum += assertTrue("Number of cards is the same", compareDeck[k[i]] == 0);
        }
      }
    }
  }
        
  /*Shuffle 100 cards (offered online as possible maximum hand size at start of turn) for player 1, 2, 3, and 4
  * Anticipated result: successfsul return, deck size is the same, all the same cards are included in the same quantities */
  for(nump = 2; nump <= 4; nump++)
  {
    for(p = 0; p<nump; p++)
    {
      #if(NOISY_TEST)
      printf("Testing with %d players, Player %d, with 100 cards in hand.\n", nump, p);
      #endif

      // Reset game and shuffle deck
      memset(&G, 23, sizeof(struct gameState));
      game = initializeGame(nump, k, seed, &G);
      G.deckCount[p] = 100;
      for(i = 0; i < 10; i++)
      {
        memcpy(G.deck[p] + i*10, sampledecks[p], sizeof(int) * 10);
      }
      // Set compareDeck
      memset(compareDeck, 0, 27 * sizeof(int));
      for(i = 0; i < 100; i++)
      {
        compareDeck[G.deck[p][i]] -= 1;
      }
      returnVal = shuffle(p, &G);

      // Test whether deck size is the same
      numTests++;
      passNum += assertTrue("Shuffling 100 cards results in identical deck size", G.deckCount[p] == 100);

      // Test whether all cards are included in the same quantities
      for(i = 0; i < 100; i++)
      {
        compareDeck[G.deck[p][i]] += 1;
      }
      for(i = 0; i < 10; i++)
      {
        numTests++;
        passNum += assertTrue("Number of cards is the same", compareDeck[k[i]] == 0);
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
