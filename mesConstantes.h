#pragma once

/********************************/
/* NE MODIFIEZ PAS CE FICHIER ! */
/* IL EST DÉJÀ COMPLET !        */
/********************************/

// Constantes pour les bateaux (objet "Ship")
#define SHIP_MAX_NB				5
#define SHIP_MAX_LENGTH			15
#define SHIP_HIDDEN_COLOR		0
#define SHIP_HIT_COLOR			13
#define SHIP_SUNK_COLOR			12

// Constantes pour la grille de jeu (objet "Grid")
#define GRID_INNER_MIN_X		1
#define	GRID_INNER_MIN_Y		5
#define GRID_INNER_MAX_X		10
#define GRID_INNER_MAX_Y		14
#define GRID_WIDTH				(GRID_INNER_MAX_X - GRID_INNER_MIN_X + 3)
#define GRID_HEIGHT				(GRID_INNER_MAX_Y - GRID_INNER_MIN_Y + 3)
#define GRID_SHIPS_FILENAME     "ships.txt"
#define GRID_SHIPS_STATUS_X		(GRID_INNER_MAX_X + 5)
#define GRID_SHIPS_STATUS_Y		(GRID_INNER_MIN_Y - 1)
#define GRID_MISSED_HITS_COLOR	11

// Constantes pour le déroulement de la partie (objet "Game")
#define GAME_NB_PLAYERS			2