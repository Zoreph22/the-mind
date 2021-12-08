/**
 * @file utils.h
 * @brief Bibliothèque de fonctions, macros, et constantes utilitaires.
 * Contient surtout des utilitaires pour l'affichage dans le terminal.
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>

/// Afficher les informations de débogage ?
#define DEBUG_MODE 0

// Couleur d'écriture dans le terminal.
#define TERM_DEFAULT  "\033[0m"
#define TERM_BLACK    "\033[0;30m"
#define TERM_GREY     "\033[1;30m"
#define TERM_RED      "\033[0;31m"
#define TERM_GREEN    "\033[0;32m"
#define TERM_YELLOW   "\033[0;33m"
#define TERM_BLUE     "\033[1;34m"
#define TERM_PURPLE   "\033[0;35m"
#define TERM_CYAN     "\033[0;36m"
#define TERM_WHITE    "\033[0;37m"

/**
 * @def printfc(color, msg, ...)
 * @brief Imprimer un message formaté dans une couleur spécifique dans la sortie standard.
 * @param color Séquence d'échappement ANSI. Voir les constantes @a TERM_<COULEUR> pour les couleurs prédéfinies.
 */
#define printfc(color, format, ...) { printf(color format TERM_DEFAULT, ##__VA_ARGS__); }

/**
 * @def pDebug(msg, ...)
 * @brief Imprimer un message formaté jaune dans la sortie standard uniquement en mode débogage.
 * La constante @link DEBUG_MODE @endlink doit être à @a 1.
 */
#define pDebug(format, ...) { if (DEBUG_MODE) printf(TERM_YELLOW format TERM_DEFAULT, ##__VA_ARGS__); }

/**
 * @def clear()
 * @brief Effacer le terminal uniquement en mode non-débogage.
 * La constante @link DEBUG_MODE @endlink doit être à @a 0.
 */
#define clear() { if (!DEBUG_MODE) system("clear"); }

/**
 * @def TO_STR(x)
 * @brief Convertir un entier littéral en string.
 */
#define TO_STR_INDIR(x) #x
#define TO_STR(x) TO_STR_INDIR(x)