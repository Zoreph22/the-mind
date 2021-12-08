#pragma once

#include <stdio.h>
#include <stdlib.h>

/// Afficher les informations de débogage.
#define DEBUG_MODE 0

// Couleur d'écriture dans le terminal.
#define TERM_DEFAULT	"\033[0m"
#define TERM_BLACK		"\033[0;30m"
#define TERM_GREY		"\033[1;30m"
#define TERM_RED		"\033[0;31m"
#define TERM_GREEN		"\033[0;32m"
#define TERM_YELLOW		"\033[0;33m"
#define TERM_BLUE		"\033[1;34m"
#define TERM_PURPLE		"\033[0;35m"
#define TERM_CYAN		"\033[0;36m"
#define TERM_WHITE		"\033[0;37m"

#define pDebug(msg, ...) { if (DEBUG_MODE) printf(TERM_YELLOW msg TERM_DEFAULT, ##__VA_ARGS__); }
#define clear() { if (!DEBUG_MODE) system("clear"); }

#define printfc(color, msg, ...) { printf(color msg TERM_DEFAULT, ##__VA_ARGS__); }

#define TO_STR_INDIR(x) #x
/// Convertir un entier littéral en string.
#define TO_STR(x) TO_STR_INDIR(x)