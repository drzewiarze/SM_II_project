/*-------------------------------------------------------------------------------------
Technika Mikroprocesorowa II - projekt
Cel programu:   - Obsługa akcelerometru za pomocą przerwań, wykorzystując INT2 dołączone do PTA10. 
                - Wyświetlanie danych z osi X, Y, Z oraz punku na wyswietlaczu lcd 16x2. 
                - Zmiana wyświetlanych danych przy uzyciu pola dotykowego jako przycisku.
Autor: Jakub Płoskonka
data: styczen 2025
-------------------------------------------------------------------------------------*/

#include "accelerometer.h"
#include "lcd1602.h"
#include "frdm_bsp.h"
#include "MKL05Z4.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(void) {

    char display[]={0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20};

    // Struktura do przechowywania danych z akcelerometru
    accelerometer_data_t accelData;

    // Inicjalizacja wyświetlacza LCD
    LCD1602_Init();
    // Inicjalizacja akcelerometru
    Accelerometer_Init();
    LCD1602_Print("Accelerometer OK");

    // Główna pętla programu
    while (1) {
        // Odczyt danych z akcelerometru
        Accelerometer_ReadData(&accelData);

        // Wyświetlanie danych na LCD
        LCD1602_SetCursor(0, 0);
        LCD1602_Print("X:");
        sprintf(display, "%d", accelData)
        LCD1602_Print(display);

        LCD1602_SetCursor(0, 1);
        LCD1602_Print("Y:");
        LCD1602_Print(accelData.y);

        LCD1602_SetCursor(8, 1);
        LCD1602_Print("Z:");
        LCD1602_Print(accelData.z);

        // Odświeżanie co 500 ms
        DELAY(500)
    }
}


