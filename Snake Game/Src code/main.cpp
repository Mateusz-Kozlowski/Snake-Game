#include "stdafx.h"
#include "ResourceManager.h"
#include "App.h"

std::unordered_map<std::string, std::shared_ptr<sf::Texture> > ResourceManager::texturePtrs;
std::unordered_map<std::string, std::shared_ptr<sf::Font> > ResourceManager::fontPtrs;

int main()
{
    srand(static_cast<unsigned>(time(0)));
    App app;
    app.run();
}
