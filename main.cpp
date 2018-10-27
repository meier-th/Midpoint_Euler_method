#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "interpolation_functions.hpp"
#include "differential_equation_functions.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <math.h>
#include "Point.h"

using namespace std;

sf::RenderTexture renderTexture;
sf::RenderWindow app(sf::VideoMode(850, 480), "Lab4");
sf::Font font;
std::string int2Str(long double x);
vector<long double>points_for_plot;
double c;

void drawLines(double, double);
void plot1();
double test_function1(double x, double y) {
    return x*x - 2*y /*x*pow(M_E, -x*x) - 2*x*y*//*pow(M_E, x)+y*/;
}

double answer_function(double x) {
    return 0.5*x*x-0.5*x+0.25+c/pow(M_E, 2*x)/*c*pow(M_E, -x*x)+x*x/(2*pow(M_E, x*x))*//*c*pow(M_E, x)+x*pow(M_E, x)*/;
}

int main()
{
    if (!font.loadFromFile("arial.ttf"))
        return EXIT_FAILURE;
    plot1();
    sf::String playerInput = "";
    sf::Text playerText;
    sf::Text reply;
    sf::Text realAnswer;
    realAnswer.setPosition(620, 100);
    realAnswer.setFont(font);
    realAnswer.setColor(sf::Color::Green);
    reply.setPosition(620, 70);
    reply.setFont(font);
    reply.setColor(sf::Color::Red);
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
                char ch = event.text.unicode;
                char last = *(playerInput.end()-1);
                //cout<<last<<endl;
                if (ch == '-' || isdigit(ch) || ch == '.' && last != '.')
                    playerInput +=ch;
                if (ch == 8) {
                    string s = playerInput;
                    playerInput = s.substr(0, s.size()-1);
                }
                playerText.setString(playerInput);
                string s = playerInput;
                if (s != ""  && s != "-") {
                    try {
                        double arg = std::stod(s);
                        sf::String ans = int2Str(interpolation_function(arg, points_for_plot));
                        sf::String trAns = int2Str(answer_function(arg));
                        realAnswer.setString(trAns);
                        reply.setString(ans);
                    } catch (const std::invalid_argument&) {
                        reply.setString("NaN");
                        realAnswer.setString("NaN");
                    } catch (const std::out_of_range&) {
                        reply.setString("Out of bounds");
                    }
                }
            }
        }

        app.clear(sf::Color::White);
        app.draw(sprite);
        app.draw(playerText);
        app.draw(reply);
        app.draw(realAnswer);
        app.display();

    }
    return EXIT_SUCCESS;
}

void plot1() {
    cout<<"Enter X0: ";
    double x0;
    cin>>x0;
    cout<<endl<<"Enter Y0: ";
    double y0;
    cin>>y0;
    c = pow(M_E, 2*x0)*(y0-0.5*x0*x0+0.5*x0-0.25)/*y0*pow(M_E, x0*x0)-x0*x0/(2*pow(M_E, x0*x0))*//*y0/pow(M_E, x0)-x0*pow(M_E, x0)*/;
    cout<<endl<<"Enter max x: ";
    double max_x;
    cin>>max_x;
    cout<<endl<<"Enter precision: ";
    double prec;
    cin>>prec;
    double x_sc = max(std::abs(max_x), std::abs(x0))/10;



    double auxX = 20/x_sc;

    vector<Point> vect = solve_equation(test_function1, x0, y0, max_x, prec);
    double y_max = std::abs(y0);
    for (size_t i = 0; i < vect.size(); ++i) {
        //cout<<std::abs(vect[i].Gety())<<endl;
        if (std::abs(vect[i].Gety()) > y_max)
            y_max = std::abs(vect[i].Gety());
    }
    double y_sc = y_max/8;
    double auxY = 20/y_sc;
    double startX = 300 + x0*20/x_sc;
    double startY = 200 - y0*20/y_sc;
    drawLines(x_sc, y_sc);
    vector<Point>pt;
    if (vect.size() > 20) {
        int num = round(vect.size()/20);
        for (int i = 0; i < vect.size(); ++i) {
            if (i % num == 0 || i == vect.size()-1)
                pt.push_back(vect[i]);
        }
    }
    else {
        pt = vect;
    }
    double yR = y0;
    double startYR = 200 - y0*20/y_sc;
    points_for_plot = count_function(pt);
    for (double x = x0; x < max_x; x = x + 0.001) {
        double y = interpolation_function(x, points_for_plot);
        yR = answer_function(x);
        sf::VertexArray lines(sf::LinesStrip, 2);
        sf::VertexArray reallines(sf::LinesStrip, 2);
        sf::VertexArray* pntr = &reallines;
        sf::Vertex* p1 = &((*pntr)[0]);
        p1->color = sf::Color::Green;
        p1 = &(*pntr)[1];
        p1->color = sf::Color::Green;
        reallines[0].position = sf::Vector2f(startX, startYR);
        reallines[1].position = sf::Vector2f(300 + x*auxX, 200 - yR*auxY);
        renderTexture.draw(reallines);
        lines[0].position = sf::Vector2f(startX, startY);
        lines[1].position = sf::Vector2f(300 + x*auxX, 200 - y*auxY);
        renderTexture.draw(lines);
        startX = 300 + x*auxX;
        startY = 200-y*auxY;
        startYR = 200-yR*auxY;
    }
    renderTexture.display();
}

std::string int2Str(long double x)
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
