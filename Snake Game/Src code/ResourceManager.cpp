#include "stdafx.h"
#include "ResourceManager.h"

std::shared_ptr<sf::Texture> ResourceManager::acquireTexture(const std::string& path)
{
    const auto i = texturePtrs.find(path);

    if (i != texturePtrs.end())
        return i->second;
    else
    {
        auto pTex = std::make_shared<sf::Texture>();

        if (!pTex->loadFromFile(path))
        {
            std::cout << "ERROR: ResourceManager::acquireTexture: CANNOT LOAD: " << path << '\n';
            exit(41);
        }

        texturePtrs.insert({ path, pTex });
        return pTex;
    }
}

void ResourceManager::murderTextureOrphans()
{
    for (auto i = texturePtrs.begin(); i != texturePtrs.end();)
    {
        if (i->second.unique())
            i = texturePtrs.erase(i);
        else
            i++;
    }
}

std::shared_ptr<sf::Font> ResourceManager::acquireFont(const std::string& path)
{
    const auto i = fontPtrs.find(path);

    if (i != fontPtrs.end())
        return i->second;
    else
    {
        auto pFont = std::make_shared<sf::Font>();

        if (!pFont->loadFromFile(path))
        {
            std::cout << "ERROR: ResourceManager::acquireFont: CANNOT LOAD: " << path << '\n';
            exit(41);
        }

        fontPtrs.insert({ path, pFont });
        return pFont;
    }
}

void ResourceManager::murderFontOrphans()
{
    for (auto i = fontPtrs.begin(); i != fontPtrs.end();)
    {
        if (i->second.unique())
            i = fontPtrs.erase(i);
        else
            i++;
    }
}
