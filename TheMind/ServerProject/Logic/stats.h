#pragma once

#include <stdbool.h>

typedef struct {
	unsigned int gameCount;
	unsigned int minReactionTime;
	unsigned int maxReactionTime;
	float avgReactionTime;
	float avgRoundWon;
	unsigned int worsePlayerId;
	unsigned int roundWonPerGame[50];
} GlobalStats;

extern GlobalStats globalStats;

typedef struct {
	unsigned int minReactionTime;
	unsigned int maxReactionTime;
	float avgReactionTime;
	unsigned int failCount;
} PlayerStats;

void stats_generatePDF();

// Statistiques globales.

unsigned int stats_elapsedSecs(bool resetTimer);
void stats_updateReactionTimes(unsigned int reactionTime);
void stats_updateGameStats();

// Statistiques des joueurs.

void stats_updatePlayerReactionTimes(unsigned int id, unsigned int reactionTime);
void stats_updatePlayerFailCount(unsigned int id);