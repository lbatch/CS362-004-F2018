/* cardtest2: Testing adventurer function
**
** Include in makefile:
** cardtest2: cardtest2.c dominion.o rngs.o
** gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS) 
**
*/

#include <sys/types.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rngs.h"
#include <pthread.h>
#include <errno.h>

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

struct args{
  int *totalTests;
  int *totalPass;
  int *totalFail;
  int handSize;
  int deckSize;
  int discardSize;
  int type;
  int c1;
  int c2;
  int c3;
  struct gameState* game;
  int handPos;
  int *b;

};

void * timedCall(void *input) {
    
    int passNum = 0;
    int numTests = 0;
    int handSize = ((struct args*)input)->handSize;
    int deckSize = ((struct args*)input)->deckSize;
    int discardSize = ((struct args*)input)->discardSize;
    struct gameState* game = ((struct args*)input)->game;

    // check return value
    int returnVal = cardEffect(((struct args*)input)->type, ((struct args*)input)->c1, ((struct args*)input)->c2, ((struct args*)input)->c3, ((struct args*)input)->game, ((struct args*)input)->handPos, ((struct args*)input)->b);

    #if(NOISY_TEST)
    printf("Adventurer return = %d, expected 0\n", returnVal);
    #endif
    numTests++;
    passNum += assertTrue("Adventurer returns 0 when deck contains at least 2 treasure cards\n", returnVal == 0);

    // check hand size
    #if(NOISY_TEST)
    printf("Ending hand size = %d, expected %d\n", game->handCount[0], (handSize + 2 - 1));
    #endif
    numTests++;
    passNum += assertTrue("Adventurer results in one net card added to the hand size\n", (game->handCount[0] == handSize + 2 - 1)); 
   
    // check deck size
    #if(NOISY_TEST)
    printf("Ending deck size = %d, expected %d\n", game->deckCount[0], (deckSize - 6));
    #endif
    numTests++;
    passNum += assertTrue("Adventurer results in less cards in the deck equal to 2 treasures and cards on top\n", (game->deckCount[0] == (deckSize - 6)));

    // check discard size
    #if(NOISY_TEST)
    printf("Ending discard size = %d, expected %d\n", game->discardCount[0], (discardSize + 5));
    #endif
    numTests++;
    passNum += assertTrue("Adventurer results in increase to discard pile equal to 1 Adventurer and cards on top of treasures\n", (game->discardCount[0] == discardSize + 5));

    // check other player hand size
    #if(NOISY_TEST)
    printf("Ending hand size = %d, expected %d\n", game->handCount[1], handSize);
    #endif
    numTests++;
    passNum += assertTrue("Adventurer results in no change to other player's hand size\n", (game->handCount[1] == handSize)); 
  
    // check other player deck size
    #if(NOISY_TEST)
    printf("Ending deck size = %d, expected %d\n", game->deckCount[1], deckSize);
    #endif
    numTests++;
    passNum += assertTrue("Adventurer results in no change to other player's deck size\n", game->deckCount[1] == deckSize);

    // check other player discard size
    #if(NOISY_TEST)
    printf("Ending discard size = %d, expected %d\n", game->discardCount[1], discardSize);
    #endif
    numTests++;
    passNum += assertTrue("Adventurer results in no change to other player's discard size\n", game->discardCount[1] == discardSize);

    (((struct args*)input)->totalTests)++;
 
    if(passNum == numTests)
    {
      (((struct args*)input)->totalPass)++;
    }
    else
    {
      (((struct args*)input)->totalFail)++;
    }
}

int main() {

  srand(time(NULL));
  printf("CARD TEST 2: ADVENTURER\n");

  pthread_cond_t done = PTHREAD_COND_INITIALIZER;
  pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
  struct timespec abstime;
  struct timespec max_wait;
  int ret;
  pthread_t tid;

  struct args *fArgs = (struct args *)malloc(sizeof(struct args));

  memset(&max_wait, 0, sizeof(max_wait));
  max_wait.tv_sec = 5;

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
  int numTestsTotal = 0;
  int passNum = 0;
  int totalPass = 0;
  int totalFail = 0;

  for(int i = 0; i < 50; i++)
  {
    handPos = 0;
    handSize = rand() % 11 + 10;
    deckSize = rand() % 11 + 10; 
    discardSize = rand() % 11 + 10;
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

    printf("Test #%d conditions: hand size is %d, deck size is %d, discard size is %d, cards randomly assigned to hand, deck, and discard, including treasure randomly assigned with 1/3 chance per hand to deck and discard\n", i+1, handSize, deckSize, discardSize);
  
    fArgs->totalTests = &numTestsTotal;
    fArgs->totalPass = &totalPass;
    fArgs->totalFail = &totalFail;
    fArgs->handSize = handSize;
    fArgs->deckSize = deckSize;
    fArgs->discardSize = discardSize;
    fArgs->type = adventurer;
    fArgs->c1 = choice1;
    fArgs->c2 = choice2;
    fArgs->c3 = choice3;
    fArgs->game = &G;
    fArgs->handPos = handPos;
    fArgs->b = &bonus;  

    pthread_mutex_lock(&m);
    clock_gettime(CLOCK_REALTIME, &abstime);
    abstime.tv_sec += max_wait.tv_sec;
    abstime.tv_nsec += max_wait.tv_nsec;


    pthread_create(&tid, NULL, timedCall, (void*)fArgs);
    ret = pthread_cond_timedwait(&done, &m, &abstime);
    if(ret)
    {
       printf("Test execution exited due to timeout.\n");
       exit(0);
    }
    if(!ret)
      pthread_mutex_unlock(&m);

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
