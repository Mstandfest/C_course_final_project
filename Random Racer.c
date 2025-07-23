#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Erstellen der Structures
// Eine für das Rennen, mit Rundenanzahl, aktueller Runde, Name des Fahrers auf dem ersten Platz und der Farbe seines Fahrzeuges
struct Race {
  int numberOfLaps;
  int currentLap;
  char firstPlaceDriverName[50];
  char firstPlaceRaceCarColor[20];
};
// Eine für die Fahrzeuge mit dem Fahrernamen, der Farbe und den Variablen die wir später für die logischen Funktionen benötigen:
// Gesamtzeit, Geschwindigkeit (1-3), Beschleunigung (1-3) und Nerven (1-3)
struct RaceCar {
  char driverName[50];
  char raceCarColor[20];
  int totalLapTime;
  int speed;
  int acceleration;
  int nerves;
};
// Funktionen für die Ausgabe
// Einleitung zum Rennen
void printIntro() {
  printf("Herzlich Willkommen zu unserem heutigen digitalen Rennen, liebe Freunde des Rennsports!\n");
  printf("Holt euch euer Popcorn und macht euch bereit!\n");
};
// Countdown vor dem Rennen von 5-0
void printCountDown() {
  printf("Fahrer bereit machen!\n");
  printf("5\n");
  printf("4\n");
  printf("3\n");
  printf("2\n");
  printf("1\n");
  printf("LOS!!!\n");
};
// Ausgabe des aktuell führenden nach jeder Runde
void printFirstPlaceAfterLap(struct Race race) {
  printf("Nach runde %d führt:\n", race.currentLap);
  printf("%s im %s Fahrzeug!\n", race.firstPlaceDriverName, race.firstPlaceRaceCarColor);
};
// Ausgabe des Siegers
void printCongratulation(struct Race race) {
  printf("Herzlichen Glückwunsch an %s im %s Fahrzeug für diese großartige Leistung!\n", race.firstPlaceDriverName, race.firstPlaceRaceCarColor);
  printf("Es war ein beeindruckendes Rennen! Wir wünschen allen Zuschauern eine gute Nacht!\n");
};
// Logische Funktionen
// Berechnung der Zeit für eine Runde
/* Hier werden 3 int Varialen randomisiert (zwischen 1 und 3) vergeben:
   speed, acceleration, nerves
   Die Summe der Werte ergeben die gesamtpunktzahl und somit die Geschwindigkeit */
int calculateTimeToCompleteLap(int speed, int acceleration, int nerves) {
  speed = rand() % (3 - 1 ) + 1;
  acceleration = rand() % (3 - 1) + 1;
  nerves = rand() % (3 - 1) + 1;
  int sum = speed + acceleration + nerves;
  return sum;
};
// Berechnung der Gesamtzeit der Fahrzeuge
void updateRaceCar(struct RaceCar* raceCar){
  int lapTime = calculateTimeToCompleteLap(raceCar->speed, raceCar->acceleration, raceCar->nerves);
  raceCar->totalLapTime += lapTime;
};
// Funktion um den ersten Platz zu aktualisieren
void updateFirstPlace(struct Race* race, struct RaceCar* raceCar1, struct RaceCar* raceCar2) {
  // if-Funktion zur Überprüfung welches Fahrzeug die schnellere Gesamtzeit besitzt
  // wenn raceCar2 langsamer ist, wird der Name und die Farbe von raceCar1 angezeigt.
  if(raceCar2->totalLapTime > raceCar1->totalLapTime) {
   strcpy(race->firstPlaceDriverName, raceCar1->driverName);
   strcpy(race->firstPlaceRaceCarColor, raceCar1->raceCarColor);
  // wenn das nicht der Fall ist, befindet sich raceCar2 auf dem ersten Platz
  } else {
    strcpy(race->firstPlaceDriverName, raceCar2->driverName);
    strcpy(race->firstPlaceRaceCarColor, raceCar2->raceCarColor);
  }
};
// In dieser Funktion wird das Rennen gestartet und die Rundenzahlen eingestellt.
void startRace(struct RaceCar* raceCar1, struct RaceCar* raceCar2) {
  struct Race race = {5, 1, "", ""};
  // Schleife läuft i < race.numberOfLaps ( = 5 ) mal durch und updatet die Parameter
  // Ausserdem wird die Funktion für den ersten Platz aufgerufen
  for(int i = 0; i < race.numberOfLaps; i++) {
    updateRaceCar(raceCar1);
    updateRaceCar(raceCar2);
    updateFirstPlace(&race, raceCar1, raceCar2);
    printFirstPlaceAfterLap(race);
    // Hochzählen der Rundenzahlen, vor allem für die FirstPlaceAfterLap-Funktion
    race.currentLap++;
  };
  // Ausgabe des Gewinners, nachdem die for-Schleife 5 mal durchgelaufen und das Rennen
  // somit beendet ist
  printCongratulation(race);
};
// Hauptfunktion:
int main() {
	// Definieren der beiden Teilnehmer mit Name und Fahrzeugfarbe
  srand(time(0));
  struct RaceCar raceCar1 = {"Michael Schumacher", "roten"};
  struct RaceCar raceCar2 = {"Mika Häkkinen", "silbernen"};
  // Ausgabe des Willkommenstextes
  printIntro();
  // Countdown für den Start
  printCountDown();
  // Ausführen des Rennens
  startRace(&raceCar1, &raceCar2);
};