#include <cassert>
#include <windows.h>
#include "mesConstantes.h"
#include "mesFonctions.h"

using namespace std;

/***********************************************/
/* NE MODIFIEZ PAS LES FONCTIONS QUI SUIVENT ! */
/* ELLES SONT DÉJÀ PLEINEMENT FONCTIONNELLES ! */
/***********************************************/

// Attend un clic de souris et retourne la position du clic sous forme de Point
Point getMouseClick() {
	bool clicked = false;

	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD irInBuf[128];
	DWORD cNumRead;
	MOUSE_EVENT_RECORD mer;

	DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT;
	SetConsoleMode(hStdin, fdwMode);

	while (!clicked) {
		ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead);

		for (DWORD i = 0; i < cNumRead; ++i) {
			if (irInBuf[i].EventType == MOUSE_EVENT) {
				mer = irInBuf[i].Event.MouseEvent;
				if (mer.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
					clicked = true;
					break;
				}
			}
		}
	}

	return Point(mer.dwMousePosition.X, mer.dwMousePosition.Y);
}

// Vide la file d'attente des clics de souris. À utiliser après un Sleep pour
// ignorer les clics survenus pendant celui-ci.
void ignoreMouseClicks() {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT;
	SetConsoleMode(hStdin, fdwMode);

    INPUT_RECORD irInBuf[128];
    DWORD cNumRead;

    // Clear any existing input events
    while (true) {
		PeekConsoleInput(hStdin, irInBuf, 128, &cNumRead);

        if (!cNumRead)
            break;

		ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead);
    }
}

// Efface l'écran. À utiliser à la place de system("cls") ou de system("clear")
// pour éviter des problèmes avec la fonction getMouseClick.
void clearScreen(std::ostream& output) {
	output << "\033[2J\033[1;1H";
}