#include "tsi.h"
#include "view.h"
#include "lcd1602.h"
#include "frdm_bsp.h"
#include "MKL05Z4.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Zmienne globalne
volatile uint8_t touchDetectedFlag;      // Flaga wykrycia dotyku
enum ViewType currentView = VIEW_X;          // Początkowy widok


int main(void) {
    // Inicjalizacje
    LCD1602_Init();      // Inicjalizacja LCD
    TSI_Init();          // Inicjalizacja panelu dotykowego
    View_Init();         // Inicjalizacja widoków osi (X, Y, Z)

    // Wyświetl początkowy widok
    View_Update(currentView);
	
    while (1) {
				touchDetectedFlag = TSI_ReadSlider() > 0 ? 1:0;
        if (touchDetectedFlag) {            // Sprawdź flagę dotyku

          currentView = NextView(currentView); // Przełącz widok
          View_Update(currentView);          	// Zaktualizuj widok na LCD
					touchDetectedFlag = 0;          // Zresetuj flagę
        }
    }
}
