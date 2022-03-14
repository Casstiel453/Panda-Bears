#include "TextureManager.h"
#include <iostream>
#include "SFML/Graphics.hpp"


TextureManager::TextureManager() : ResourceManager("textures.txt") {};

TextureManager::~TextureManager()
{
}

sf::Texture* TextureManager::Load(const std::string& fileName)
{
    sf::Texture* text = new sf::Texture();
    //allocate memory on heap
    try
    {
        if (!text->loadFromFile(fileName))
        {
            delete text;
            text = NULL;
            throw FileMissingException();
        }
    }
    catch (const char* exception)
    {
        std::cout << exception << "\n";
    }
    //the texture
    return text;
}