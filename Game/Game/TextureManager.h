#ifndef TEXTUREMANAGER_H_INCLUDED
#define TEXTUREMANAGER_H_INCLUDED
#include <string>
#include <SFML/Graphics.hpp>
#include "ResourceManager.h" 

/** Class that derives from ResourceManager */
class TextureManager : public ResourceManager<TextureManager, sf::Texture>
{
public:

    /*constructor for TextureManager*/
    TextureManager();

    /*destructor for TextureManager*/
    ~TextureManager();

    /**The function load texture from file
    @param fileName name of the file
    */
    sf::Texture* Load(const std::string& fileName);

};

#endif  