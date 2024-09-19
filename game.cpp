// Header-Dateien
#include "game.h"
#include "global.h"

// PUBLIC
Game::Game() {
    initTextStrings();  // Initialisiert die Textobjekte, z.B. für den Punktestand und den Endbildschirm
}

void Game::setScoreboard(Scoreboard& inScoreboard) {
    scoreboard = &inScoreboard;  // Setzt die Verknüpfung zum Scoreboard
}

// IPO (Eingabe, Verarbeitung, Ausgabe)
int Game::input(sf::Event& event) {
    if (!gameOver) {
        return processState(event);  // Verarbeitung des Spiels, wenn es nicht vorbei ist
    }
    else {
        return processState_gameOver(event);  // Verarbeitung bei Spielende
    }
}

void Game::update() {
    if (!gameOver) {
        updateFruit();      // Aktualisiert die Frucht, falls nötig
        updateSnake();      // Aktualisiert die Bewegung der Schlange
        updateCollision();  // Überprüft Kollisionen
    }
}

void Game::render(sf::RenderWindow& window) {
    window.clear(gb::colBackground);  // Fenster mit Hintergrundfarbe füllen
    if (!gameOver) {
        window.draw(activeScoreText);  // Zeichnet den aktuellen Punktestand
        renderArena(window);           // Zeichnet das Spielfeld (Arena)
        renderSnake(window);           // Zeichnet die Schlange
        renderFruit(window);           // Zeichnet die Frucht
    }
    else {
        window.draw(finalText);        // Zeichnet "SPIEL BEENDET!"-Text
        window.draw(finalScoreText);   // Zeichnet den Endpunktestand
        window.draw(nameText);         // Zeichnet den Spielernamen
        window.draw(helpText);
    }
}

// --------------------------------------
// PRIVAT
int Game::processState(sf::Event& event) {
    if (gb::pressedAnyKey(event)) {
        if (gb::pressedEscape(event)) {
            resetGame();  // Setzt das Spiel zurück
            return 3;  // Rückkehr ins Hauptmenü
        }
        // Bewegungssteuerung (W, A, S, D)
        if (gb::pressedW(event) && direction.y == 0) direction = sf::Vector2i(0, -1);  // Nach oben
        else if (gb::pressedA(event) && direction.x == 0) direction = sf::Vector2i(-1, 0);  // Nach links
        else if (gb::pressedS(event) && direction.y == 0) direction = sf::Vector2i(0, 1);   // Nach unten
        else if (gb::pressedD(event) && direction.x == 0) direction = sf::Vector2i(1, 0);   // Nach rechts
    }
    return -1;
}

int Game::processState_gameOver(sf::Event& event) {
    getName(event);
    if (gb::pressedAnyKey(event)) {
        if (gb::pressedEnter(event)) {
            scoreboardEntry();  // Fügt den aktuellen Score ins Scoreboard ein
            resetGame();  // Spiel zurücksetzen
            return 3;  // Rückkehr ins Hauptmenü   
        }
        else if (gb::pressedEscape(event)) {
            return 3;
        }
    }
    return -1;
}

// SPAWN
void Game::spawnFruit() {
    // Zufällige Position für die Frucht generieren, die nicht auf der Schlange liegt
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    sf::Vector2i fruitPosition;
    bool positionValid = false;

    while (!positionValid) {
        fruitPosition.x = std::rand() % gb::arenaWidth;
        fruitPosition.y = std::rand() % gb::arenaHeight;

        positionValid = true;
        for (const auto& segment : snake) {
            if (segment == fruitPosition) {
                positionValid = false;  // Position liegt auf der Schlange -> neue Position wählen
                break;
            }
        }
    }

    // Setzt die Position und Darstellung der Frucht
    fruit.setRadius(gb::blockSize / 2);
    fruit.setFillColor(gb::colFruit);
    fruit.setPosition(getScreenPosition(fruitPosition.x, fruitPosition.y));
}

void Game::spawnSnake() {
    // Schlange mit einer Länge von 5 Segmenten in der Mitte des Spielfelds spawnen
    int initialLength = 5;
    int startX = gb::arenaWidth / 2;
    int startY = gb::arenaHeight / 2;

    for (int i = 0; i < initialLength; i++) {
        snake.push_back(sf::Vector2i(startX - i, startY));  // Neue Segmente hinzufügen
    }

    direction = sf::Vector2i(1, 0);  // Schlange startet nach rechts
    snakeActive = true;
}

void Game::scoreboardEntry() {
    if (!playerName.empty()) {
        scoreboard->addScore(playerName, playerScore);  // Spielername und Punktestand ins Scoreboard eintragen
    }
}

void Game::resetGame() {
    initTextStrings();  // Texte zurücksetzen
    gameOver = false;
    snakeActive = false;
    fruitActive = false;
    playerName.clear();  // Spielername zurücksetzen
    playerScore = 0;     // Punktestand zurücksetzen
    snake.clear();       // Schlange leeren
    growSnake = false;   // Kein Wachstum der Schlange
}

void Game::updateCollision() {
    // Kollision mit der Frucht überprüfen
    sf::Vector2f fruitPosition = fruit.getPosition();
    sf::Vector2f newHeadPositionFloat(getScreenPosition(snake.front().x,snake.front().y));

    if (fruitPosition == newHeadPositionFloat) {
        playerScore++;  // Punktestand erhöhen
        activeScoreText.setString("PUNKTE: " + std::to_string(playerScore));  // Punkteanzeige aktualisieren
        spawnFruit();  // Neue Frucht spawnen
        growSnake = true;  // Schlange soll wachsen
    }

    // Kollision mit der Wand überprüfen
    sf::Vector2i headPosition = snake.front();
    if (headPosition.x < 0 || headPosition.x >= gb::arenaWidth ||
        headPosition.y < 0 || headPosition.y >= gb::arenaHeight) {
        finalScoreText.setString("PUNKTE: " + std::to_string(playerScore));  // Endpunktestand anzeigen
        gameOver = true;  // Spiel beenden
        return;
    }

    // Kollision mit dem eigenen Körper überprüfen
    for (size_t i = 1; i < snake.size(); ++i) {
        if (headPosition == snake[i]) {
            finalScoreText.setString("PUNKTE: " + std::to_string(playerScore));  // Endpunktestand anzeigen
            gameOver = true;  // Spiel beenden
            return;
        }
    }
}

// UPDATE
void Game::updateFruit() {
    if (!fruitActive) {
        spawnFruit();  // Neue Frucht spawnen
        fruitActive = true;
    }
}

void Game::updateSnake() {
    if (!snakeActive) spawnSnake();  // Schlange spawnen, wenn sie nicht aktiv ist

    moveInterval = sf::seconds(0.2f);  // Zeitintervall für die Bewegung
    if (moveClock.getElapsedTime() >= moveInterval) {
        if (!snake.empty()) {
            // Neue Kopfposition berechnen
            sf::Vector2i newHeadPosition = snake.front() + direction;
            snake.insert(snake.begin(), newHeadPosition);  // Kopf zur Schlange hinzufügen

            if (!growSnake) snake.pop_back();  // Schlange wächst nicht -> letztes Segment entfernen
            else growSnake = false;  // Wachstum nach einmaligem Wachsen deaktivieren
        }
        moveClock.restart();  // Uhr zurücksetzen
    }
}

// RENDER
void Game::renderArena(sf::RenderWindow& window) {
    // Zeichnet das Spielfeld (abwechselnd farbige Blöcke)
    for (int i = 0; i < gb::arenaHeight; ++i) {
        for (int j = 0; j < gb::arenaWidth; ++j) {
            sf::RectangleShape block(sf::Vector2f(gb::blockSize, gb::blockSize));
            block.setPosition(getScreenPosition(j, i));
            block.setFillColor((i + j) % 2 == 0 ? gb::colArena1 : gb::colArena2);
            window.draw(block);
        }
    }
}

void Game::renderFruit(sf::RenderWindow& window) {
    window.draw(fruit);  // Zeichnet die Frucht
}

void Game::renderSnake(sf::RenderWindow& window) {
    for (const auto& segment : snake) {
        sf::RectangleShape snakeSegment(sf::Vector2f(gb::blockSize, gb::blockSize));
        snakeSegment.setPosition(getScreenPosition(segment.x, segment.y));
        snakeSegment.setFillColor(gb::colSnake);  // Schlange wird gezeichnet
        window.draw(snakeSegment);
    }
}

// Hilfsfunktion zur Umrechnung von Arena-Koordinaten in Bildschirmkoordinaten
sf::Vector2f Game::getScreenPosition(float x, float y) {
    return sf::Vector2f(x * gb::blockSize + gb::xOffset, y * gb::blockSize + gb::yOffset);
}

void Game::getName(sf::Event& event) {
    // Spielername-Eingabe bei Spielende (bis zu 6 Zeichen)
    if (event.type == sf::Event::TextEntered) {
        char enteredChar = static_cast<char>(event.text.unicode);

        if (enteredChar >= 'A' && enteredChar <= 'Z') {  // Großbuchstaben
            if (playerName.length() < 6) {
                playerName += enteredChar;
                nameText.setString("NAME: " + playerName);
            }
        }
        else if (enteredChar >= 'a' && enteredChar <= 'z') {  // Kleinbuchstaben -> Umwandeln in Großbuchstaben
            if (playerName.length() < 6) {
                playerName += static_cast<char>(enteredChar - 32);  // In Großbuchstaben umwandeln
                nameText.setString("NAME: " + playerName);
            }
        }
        else if (event.text.unicode == 8 && !playerName.empty()) {  // Rücktaste -> Letztes Zeichen löschen
            playerName.pop_back();
            nameText.setString("NAME: " + playerName);
        }
    }
}

// TEXT
void Game::initTextStrings() {
    font.loadFromFile("Fonts/Dimbo Regular.ttf");  // Schriftart laden
    initCenteredText(activeScoreText, "PUNKTE: 0", 70, gb::colTextOn, sf::Vector2f(gb::winWidth * 0.4, gb::winHeight * 0.1));
    initCenteredText(finalText, "SPIEL BEENDET!", 90, gb::colTextOn, sf::Vector2f(gb::winWidth * 0.5, gb::winHeight * 0.2));
    initCenteredText(finalScoreText, "PUNKTE: XX", 70, gb::colTextOff, sf::Vector2f(gb::winWidth * 0.5, gb::winHeight * 0.4));
    initCenteredText(nameText, "NAME:               ", 70, gb::colTextOff, sf::Vector2f(gb::winWidth * 0.5, gb::winHeight * 0.6));
    initCenteredText(helpText, "Enter = Eingabe bestätigen", 20, gb::colTextOff, sf::Vector2f(gb::winWidth * 0.5, gb::winHeight * 0.95));
}

// Hilfsfunktion zum Initialisieren zentrierter Textobjekte
void Game::initCenteredText(sf::Text& text, const std::string& string, unsigned int size, sf::Color color, sf::Vector2f position) {
    text.setFont(font);  // Schriftart setzen
    text.setString(string);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(position);
    sf::FloatRect textBounds = text.getLocalBounds();  // Berechnet die Textgröße
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);  // Zentriert den Text
    text.setPosition(position);  // Setzt die Position
}
