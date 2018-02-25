#include <stdio.h>
#include <stdlib.h>
#include "shuffle.h"

void shuffle(AGENT **agentsShuffle, int NAGENTS) {
    AGENT *temp;
    for (int i = NAGENTS - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        temp = agentsShuffle[i];
        agentsShuffle[i] = agentsShuffle[j];
        agentsShuffle[j] = temp;
    }
}
