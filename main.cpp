/*
Diese Datei beinhaltet die Funktion main(),
welche den Beginn und Ende des Programms symbolisiert.

Diese Funktion läuft solange in Dauerschleife, bis ein Abbruchkriterium erreicht wird.
Diese Dauerschleife wird genutzt, um das Programm dauerhaft auf neue Eingaben reagieren zu lassen,
die programmierte Logik auszuführen und Bilder auszugeben.

Da die gesamte Funktion als "int main()" ausgeführt ist, wird am Ende ein Wert des Types Integer erwartet. 
Daher wird eine "0" (NULL) als Ergebnis der Methode ausgegeben. Diese NULL signalisiert dem Betriebssystem ein erfolgreiches Ende des Programms.
*/

// Header-Dateien
#include "engine.h"

int main() {
    Engine engine;  // Erzeugt ein Objekt der Klasse "Engine"
    engine.run();   // Aufruf der Methode "run()"
    return 0;       // Übergebe dem Betriebssystem den Integer 0 (erfolgreiches Programmende)
}
