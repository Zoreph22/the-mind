#include <time.h>
#include <stdbool.h>
#include "../socket.h"
#include "utils.h"
#include "partie.h"
#include "stats.h"

GlobalStats globalStats = { 0 };
PlayerStats playerStats[MAX_CONNECTIONS] = { 0 };

// Statistiques globales.

unsigned int stats_elapsedSecs(bool resetTimer)
{
	static bool isFirst = true;
	static time_t start;

	isFirst = resetTimer;

	if (isFirst)
	{
		isFirst = false;
		time(&start);
		return 0;
	}

	isFirst = true;

	time_t end;
	time(&end);

	return (end - start);
}

void stats_updateReactionTimes(unsigned int reactionTime)
{
	if (globalStats.minReactionTime == 0) globalStats.minReactionTime = reactionTime;
	if (reactionTime < globalStats.minReactionTime) globalStats.minReactionTime = reactionTime;
	if (reactionTime > globalStats.maxReactionTime) globalStats.maxReactionTime = reactionTime;

	// Calcul du temps de réaction moyen.
	static unsigned int currentN = 0;
	static float currentSum = 0;

	currentN++;
	currentSum += reactionTime;

	globalStats.avgReactionTime = currentSum / currentN;

	printfc(TERM_RED, "[STATS REACTTIME] min : %i, max : %i, avg : %f\n", globalStats.minReactionTime, globalStats.maxReactionTime, globalStats.avgReactionTime);
}

void stats_updateAvgRoundWon()
{
	static unsigned int currentSum = 0;
	currentSum += p.manche - 1;

	globalStats.avgRoundWon = (float)currentSum / globalStats.gameCount;
}

void stats_updateWorsePlayer()
{
	unsigned int worsePlayerId = 0;
	unsigned int highestFailCount = 0;

	for (int i = 0; i < p.nbJoueurs; i++)
	{
		unsigned int lostCount = playerStats[i].failCount;

		if (lostCount > highestFailCount)
		{
			worsePlayerId = i;
			highestFailCount = lostCount;
		}
	}

	globalStats.worsePlayerId = worsePlayerId;
}

void stats_updateGameStats()
{
	globalStats.roundWonPerGame[globalStats.gameCount++] = p.manche - 1;
	stats_updateAvgRoundWon();
	stats_updateWorsePlayer();

	printfc(TERM_RED, "[STATS] avgRoundWon : %f, worsePlayer : %s\n", globalStats.avgRoundWon, p.joueurs[globalStats.worsePlayerId].nom);

	for (unsigned int i = 0; i < globalStats.gameCount; i++)
	{
		printfc(TERM_RED, "[STATS] game num %i round won : %i\n", i, globalStats.roundWonPerGame[i]);
	}
}

// Statistiques des joueurs.

void stats_updatePlayerReactionTimes(unsigned int id, unsigned int reactionTime)
{
	PlayerStats* stats = &playerStats[id];

	if (stats->minReactionTime == 0) stats->minReactionTime = reactionTime;
	if (reactionTime < stats->minReactionTime) stats->minReactionTime = reactionTime;
	if (reactionTime > stats->maxReactionTime) stats->maxReactionTime = reactionTime;

	// Calcul du temps de réaction moyen.
	static unsigned int currentN[MAX_CONNECTIONS];
	static float currentSum[MAX_CONNECTIONS];

	currentN[id]++;
	currentSum[id] += reactionTime;

	stats->avgReactionTime = currentSum[id] / currentN[id];

	printfc(TERM_RED, "[STATS REACTTIME PLAYER %i] min : %i, max : %i, avg : %f\n", id, stats->minReactionTime, stats->maxReactionTime, stats->avgReactionTime);
}

void stats_updatePlayerFailCount(unsigned int id)
{
	playerStats[id].failCount++;

	printfc(TERM_RED, "[STATS PLAYER %i] fail count : %i\n", id, playerStats[id].failCount);
}