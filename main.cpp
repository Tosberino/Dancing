#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h> 
#include <time.h>
#include <math.h>

 sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight) {
    float windowRatio = windowWidth / (float) windowHeight;
    float viewRatio = view.getSize().x / (float) view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;
    bool horizontalSpacing = true;
    if (windowRatio < viewRatio)
        horizontalSpacing = false;
    if (horizontalSpacing) {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    }
    else {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }
    view.setViewport( sf::FloatRect(posX, posY, sizeX, sizeY) );
    return view;
}

int main(){

    const int scrwidth = 300;  //g++ -c main.cpp ; g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
    const int scrheight = 300;

    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(scrwidth, scrheight), "Kaut Kas");

    sf::Texture groundtex;
    if (!groundtex.loadFromFile("ground.png")){}
    groundtex.setRepeated(true);

    sf::Texture dance1;
        if (!dance1.loadFromFile("dance1.png")){}

    sf::Texture dance2;
        if (!dance2.loadFromFile("dance2.png")){}


    sf::Sprite ground;
    ground.setTextureRect(sf::IntRect(0,0,scrwidth,32));
    ground.setPosition(0, scrheight-32);
    ground.setTexture(groundtex);

    sf::Sprite dancer;
    dancer.setPosition(scrwidth/2-32, scrheight-96);
    dancer.setTexture(dance1);
    int frame = 0;
    bool isleft = true;

    sf::RectangleShape back(sf::Vector2f(scrwidth,scrheight));
    back.setFillColor(sf::Color(135, 206, 235));

    sf::View view;
    view.setSize( scrwidth, scrheight );
    view.setCenter( view.getSize().x / 2, view.getSize().y / 2 );
    view = getLetterboxView( view, scrwidth, scrheight );

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized)
                view = getLetterboxView( view, event.size.width, event.size.height );
        }

        if(frame == 0){
            dancer.setTexture(dance2);
            frame = 1;
            isleft = !isleft;
        }else if(frame == 1){
            dancer.setTexture(dance1);
            frame = 2;
        }else{
            dancer.setTexture(dance2);
            frame = 0;
        }

        if(!isleft){
            dancer.setTextureRect(sf::IntRect(64, 0, -64, 64));
        }else{
            dancer.setTextureRect(sf::IntRect(0, 0, 64, 64));
        }

        window.clear();

        window.draw(back);
        window.draw(ground);
        window.draw(dancer);

        window.setView(view); 
        window.display();

        sf::sleep(sf::milliseconds(260));
    }

    return 0;
}
