#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iostream>

#include "Bird.h"
#include "Pipe.h"
#include "Text.h"
#include "Point.h"

void resetGame(
    Bird&,
    unsigned int&,
    std::string*,
    Text&,
    std::vector<Pipe>&,
    std::vector<Point>&,
    Text*&,
    Text*&,
    sf::Clock&
);
void makeMenu (
    Text*&, 
    Text*&, 
    Text*&, 
    sf::Font&,
    unsigned int,
    unsigned int
);
void drawMenu(
    Text*&,
    Text*&,
    Text*&,
    sf::RenderWindow&
);
void cleanMenu(
    Text*&,
    Text*&,
    Text*&
);

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 800), "Flappy Bird");
    window.setFramerateLimit(60);

    sf::Vector2u windowSize = window.getSize();
    
    unsigned int screen_width = windowSize.x;
    unsigned int screen_height = windowSize.y;

    srand(static_cast<unsigned int>(time(nullptr)));

    sf::Font font;
    if (!font.loadFromFile("Resources/FSEX300.ttf")) {
        std::cout << "Error loading font!" << std::endl;
    }

    unsigned int score = 0;
    std::string txt = "Score: " + std::to_string(score);

    bool running = false;

    Text text(txt, font, 0.f, -10.f, 60);
    Text* over_text = nullptr;
    Text* retry_text = nullptr;

    Text* main_text = nullptr;
    Text* start_text = nullptr; 
    Text* high_score_text = nullptr; 
    makeMenu(main_text, start_text, high_score_text, font, screen_width, screen_height);

    sf::Clock clock;
    sf::Clock pipeClock;

    float pipe_spawn_delay = 1.5f;

    std::vector<Pipe> pipes;
    std::vector<Point> points;
    
    Bird bird(100.f, 100.f, 45.f);

    Pipe pipe_top(110.f, 550.f); 
    Pipe pipe_bot(110.f, 550.f);
    Point point(50, 300.f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed &&
                 event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }

            if (!running &&
                event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Enter) {
                running = true;
                cleanMenu(main_text, start_text, high_score_text);
                resetGame(bird, score, &txt, text, pipes, points, over_text, retry_text, pipeClock);
            }

            if (over_text != nullptr &&
                event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::R) {
                resetGame(bird, score, &txt, text, pipes, points, over_text, retry_text, pipeClock);
                running = true;
            }
            else if (over_text != nullptr &&
                event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::M) {
                running = false;
                makeMenu(main_text, start_text, high_score_text, font, screen_width, screen_height);
            }
        }

        window.clear(sf::Color(30, 30, 30));
        if (running) {
            if (pipeClock.getElapsedTime().asSeconds() >= pipe_spawn_delay) {
                float offset = -static_cast<float>(rand() % 451);
                float gap = 300.f;

                pipe_top.setPos(static_cast<float>(screen_width), offset);
                point.setPos(static_cast<float>(screen_width), offset + 550.f);
                pipe_bot.setPos(static_cast<float>(screen_width), pipe_top.getHeight() + pipe_top.getPositionY() + gap);

                pipes.push_back(pipe_top);
                pipes.push_back(pipe_bot);
                points.push_back(point);
                pipeClock.restart();
            }

            // Move pipes and check collisions
            for (auto& pipe : pipes) {
                pipe.move();
                if (bird.getRect().intersects(pipe.getRect())) {
                    bird.status = false;
                }
            }

            // Spawn gameover texts when bird dies
            if (bird.status == false && over_text == nullptr && retry_text == nullptr) {
                over_text = new Text("Gameover", font, 
                    static_cast<float>(screen_width / 2 - 150),
                    static_cast<float>(screen_height / 2 - 40),
                    80);
                over_text->changeColor(255, 0, 82);
                retry_text = new Text("Press R to restart. (M for Menu)", font, 
                    static_cast<float>(screen_width / 2 - 315),
                    static_cast<float>(screen_height / 2 + 30),
                    40);
                retry_text->changeColor(200, 200, 200);
            }

            // Move points and award score
            for (auto& point : points) {
                point.move();
                if (!point.scored && bird.getRect().intersects(point.getRect())) {
                    score++;
                    point.scored = true;
                    txt = "Score: " + std::to_string(score);
                    text.updateText(&txt);
                }
            }

            // Remove pipes and points
            pipes.erase(std::remove_if(pipes.begin(), pipes.end(),
                [](const Pipe& p) { return p.getPositionX() <= -110; }),
                pipes.end());

            points.erase(std::remove_if(points.begin(), points.end(),
                [](const Point& p) { return p.getPositionX() <= -110; }),
                points.end());

            // Bird movement
            if (bird.status) {
                bird.handleInput(screen_height);
            }

            bird.update();

            // Drawing
            bird.draw(window);

            for (auto& pipe : pipes) {
                pipe.draw(window);
            }

            for (auto& point : points) {
                point.draw(window);
            }

            text.draw(window);

            if (over_text != nullptr) over_text->draw(window);
            if (retry_text != nullptr) retry_text->draw(window);
        }
        else { // menu
            drawMenu(main_text, start_text, high_score_text, window);
        }

        window.display();
    }

    delete retry_text;
    delete over_text;
    cleanMenu(main_text, start_text, high_score_text);

    return 0;
}

void resetGame(
    Bird& bird,
    unsigned int& score,
    std::string* txt,
    Text& text,
    std::vector<Pipe>& pipes,
    std::vector<Point>& points,
    Text*& over_text,
    Text*& retry_text,
    sf::Clock& pipeClock
) {
    bird.reset(100.f, 100.f, 45.f);
    bird.status = true;

    score = 0;
    *txt = "Score: " + std::to_string(score);
    text.updateText(txt);

    pipes.clear();
    points.clear();

    delete over_text;
    delete retry_text;
    over_text = nullptr;
    retry_text = nullptr;

    pipeClock.restart();
}

void makeMenu (
    Text*& main_text, 
    Text*& start_text, 
    Text*& high_score_text, 
    sf::Font& font,
    unsigned int screen_width,
    unsigned int screen_height
) {
    main_text = new Text("Jumpy Circle", font, static_cast<float>(screen_width/2 - 200), static_cast<float>(screen_height/2 - 100), 80);
    start_text = new Text("Press Enter to Start", font, static_cast<float>(screen_width/2 - 210), static_cast<float>(screen_height/2), 45);
    high_score_text = new Text("Highscore: 0", font, static_cast<float>(screen_width/2 - 100), static_cast<float>(screen_height/2 + 60), 40);
    
    main_text->changeColor(207, 200, 72);
    start_text->changeColor(2, 184, 184);
    high_score_text->changeColor(200, 200, 200);
}

void drawMenu (
    Text*& main_text,
    Text*& start_text,
    Text*& high_score_text,
    sf::RenderWindow& window
) {
    if (main_text) main_text->draw(window);
    if (start_text) start_text->draw(window);
    if (high_score_text) high_score_text->draw(window);
}

void cleanMenu(
    Text*& main_text,
    Text*& start_text,
    Text*& high_score_text
) {
    delete main_text;
    delete start_text;
    delete high_score_text;

    main_text = nullptr;
    start_text = nullptr;
    high_score_text = nullptr;
}
