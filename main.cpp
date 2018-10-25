#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "interpolation_functions.hpp"
#include <iostream>
#include <sstream>
#include <math.h>
#include "Point.h"

using namespace std;

sf::RenderTexture renderTexture;
sf::RenderWindow app(sf::VideoMode(850, 480), "Lab4");
sf::Font font;

void drawLines(double, double);
void plot();
double test_function(double x, double y) {
    return x*x - 2*y;
}

int main()
{


            if (!font.loadFromFile("arial.ttf"))
            return EXIT_FAILURE;

    drawLines(1, 1);
    plot();
    sf::String playerInput = "";
    sf::Text playerText;
    playerText.setPosition(620, 40);
    playerText.setFont(font);
    playerText.setColor(sf::Color::Red);
    const sf::Texture& texture = renderTexture.getTexture();
    sf::Sprite sprite(texture);

    while (app.isOpen()) {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
            else if (event.type == sf::Event::TextEntered) {
                playerInput +=event.text.unicode;

                playerText.setString(playerInput);

            }
        }
        app.clear(sf::Color::White);
        app.draw(sprite);
        app.draw(playerText);
        app.display();

    }
    return EXIT_SUCCESS;
}

void plot() {
    double startX = 0;
    double startY = 200;
    for (double x = -15; x < 15; x = x + 0.001) {
        double y = sin(x);
        sf::VertexArray lines(sf::LinesStrip, 2);
        lines[0].position = sf::Vector2f(startX, startY);
        lines[1].position = sf::Vector2f(x*20, 200 - y*20);
        renderTexture.draw(lines);
        startX = x*20;
        startY = 200-y*20;
    }
    renderTexture.display();
}

std::string int2Str(double x)
	{
		std::stringstream type;
		type << x;
		return type.str();
	}

void drawLines(double scaleX, double scaleY) {
    renderTexture.create(600, 400, true);
    renderTexture.clear();
    sf::VertexArray lines(sf::LinesStrip, 2);
    lines[0].position = sf::Vector2f(0, 200);
    lines[1].position = sf::Vector2f(600, 200);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(300, 0);
    lines[1].position = sf::Vector2f(300, 400);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(593, 196);
    lines[1].position = sf::Vector2f(600, 200);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(593, 204);
    lines[1].position = sf::Vector2f(600, 200);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(0, 200);
    lines[1].position = sf::Vector2f(600, 200);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(296, 7);
    lines[1].position = sf::Vector2f(300, 0);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(304, 7);
    lines[1].position = sf::Vector2f(300, 0);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(20, 203);
    lines[1].position = sf::Vector2f(20, 197);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(40, 203);
    lines[1].position = sf::Vector2f(40, 197);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(60, 203);
    lines[1].position = sf::Vector2f(60, 197);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(80, 203);
    lines[1].position = sf::Vector2f(80, 197);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(100, 203);
    lines[1].position = sf::Vector2f(100, 197);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(120, 203);
    lines[1].position = sf::Vector2f(120, 197);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(140, 203);
    lines[1].position = sf::Vector2f(140, 197);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(160, 203);
    lines[1].position = sf::Vector2f(160, 197);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(180, 203);
    lines[1].position = sf::Vector2f(180, 197);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(200, 203);
    lines[1].position = sf::Vector2f(200, 197);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(220, 203);
    lines[1].position = sf::Vector2f(220, 197);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(240, 203);
    lines[1].position = sf::Vector2f(240, 197);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(260, 203);
    lines[1].position = sf::Vector2f(260, 197);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(280, 203);
    lines[1].position = sf::Vector2f(280, 197);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(320, 203);
    lines[1].position = sf::Vector2f(320, 197);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(340, 203);
    lines[1].position = sf::Vector2f(340, 197);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(360, 203);
    lines[1].position = sf::Vector2f(360, 197);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(380, 203);
    lines[1].position = sf::Vector2f(380, 197);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(400, 203);
    lines[1].position = sf::Vector2f(400, 197);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(420, 203);
    lines[1].position = sf::Vector2f(420, 197);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(440, 203);
    lines[1].position = sf::Vector2f(440, 197);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(460, 203);
    lines[1].position = sf::Vector2f(460, 197);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(480, 203);
    lines[1].position = sf::Vector2f(480, 197);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(500, 203);
    lines[1].position = sf::Vector2f(500, 197);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(520, 203);
    lines[1].position = sf::Vector2f(520, 197);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(540, 203);
    lines[1].position = sf::Vector2f(540, 197);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(560, 203);
    lines[1].position = sf::Vector2f(560, 197);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(580, 203);
    lines[1].position = sf::Vector2f(580, 197);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(297, 20);
    lines[1].position = sf::Vector2f(303, 20);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(297, 40);
    lines[1].position = sf::Vector2f(303, 40);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(297, 60);
    lines[1].position = sf::Vector2f(303, 60);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(297, 80);
    lines[1].position = sf::Vector2f(303, 80);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(297, 100);
    lines[1].position = sf::Vector2f(303, 100);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(297, 120);
    lines[1].position = sf::Vector2f(303, 120);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(297, 140);
    lines[1].position = sf::Vector2f(303, 140);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(297, 160);
    lines[1].position = sf::Vector2f(303, 160);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(297, 180);
    lines[1].position = sf::Vector2f(303, 180);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(297, 200);
    lines[1].position = sf::Vector2f(303, 200);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(297, 220);
    lines[1].position = sf::Vector2f(303, 220);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(297, 240);
    lines[1].position = sf::Vector2f(303, 240);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(297, 260);
    lines[1].position = sf::Vector2f(303, 260);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(297, 280);
    lines[1].position = sf::Vector2f(303, 280);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(297, 300);
    lines[1].position = sf::Vector2f(303, 300);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(297, 320);
    lines[1].position = sf::Vector2f(303, 320);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(297, 340);
    lines[1].position = sf::Vector2f(303, 340);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(297, 360);
    lines[1].position = sf::Vector2f(303, 360);
    renderTexture.draw(lines);
    lines[0].position = sf::Vector2f(297, 380);
    lines[1].position = sf::Vector2f(303, 380);
    renderTexture.draw(lines);
    sf::String number;
    sf::Text txt;
    txt.setFont(font);
    txt.setCharacterSize(9);
    number = "0";
    txt.setPosition(302, 201);
    txt.setString(number);
    renderTexture.draw(txt);
    for (int i = -14; i <= 14; ++i) {
        if (i != 0) {
            number = int2Str(i*scaleX);
            txt.setPosition(296 + i*20, 203);
            txt.setString(number);
            renderTexture.draw(txt);
        }
    }
    for (int i = -9; i <= 9; ++i) {
        if (i != 0) {
            number = int2Str(-i*scaleY);
            txt.setPosition(305, 194+i*20);
            txt.setString(number);
            renderTexture.draw(txt);
        }
    }
    renderTexture.display();

}
