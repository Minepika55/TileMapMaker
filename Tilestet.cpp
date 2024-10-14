#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include "TileMap.h"
#include <fstream>
#include <sstream>

bool Mapaload(TileMap& map, const std::string& tileset, sf::Vector2u tileSize, const std::string& filename, unsigned int width, unsigned int height)
{
    //Carreguem el fitxer
    std::ifstream fitxer(filename);
    if (!fitxer.is_open())
        return false;

    //Guardar el mapa actual
    std::vector<int> level;
    std::string line;

    //Llegir el fitxer
    while (std::getline(fitxer, line))
    {
        std::stringstream ss(line);
        int tile;
        while (ss >> tile)
        {
            level.push_back(tile);
            //Ignora les comes o els espais del tetx
            if (ss.peek() == ',' || ss.peek() == ' ')
                ss.ignore();
        }
    }

    //Mirar que sigui correcte el fitxer
    if (level.size() != width * height)
        return false;

    //Carregar el mapa
    return map.load(tileset, tileSize, level.data(), width, height);
}


int main()
{
    //Crear la finestra
    sf::RenderWindow window(sf::VideoMode(512, 256), "MAPES");

    //Vector amb els mapes
    std::vector<std::string> mapas = { "mapa1.txt", "mapa2.txt", "mapa3.txt" };
    unsigned int Mapacurrent = 0;

    //Crear el tilemap
    TileMap mapa;
    if (!Mapaload(mapa, "tileset.png", sf::Vector2u(32, 32), mapas[Mapacurrent], 16, 8))
        return -1;

    // run the main loop
    while (window.isOpen())
    {
        // run events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            //Canviar de mapa amb les fletxes
            else if (event.type == sf::Event::KeyPressed)
            {   
                Mapacurrent = (Mapacurrent + 1) % mapas.size();

                if (event.key.code == sf::Keyboard::Right)
                {
                    Mapaload(mapa, "tileset2.png", sf::Vector2u(32, 32), mapas[Mapacurrent], 16, 8);
                }
                else if (event.key.code == sf::Keyboard::Left)
                {

                    Mapaload(mapa, "tileset3.png", sf::Vector2u(32, 32), mapas[Mapacurrent], 16, 8);
                }
                else if (event.key.code == sf::Keyboard::Down)
                {

                    Mapaload(mapa, "tileset1.png", sf::Vector2u(32, 32), mapas[Mapacurrent], 16, 8);
                }
            }
        }

        // draw the map
        window.clear();
        window.draw(mapa);
        window.display();
    }

    return 0;
}
