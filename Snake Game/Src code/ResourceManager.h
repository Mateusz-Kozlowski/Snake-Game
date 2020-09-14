#pragma once

class ResourceManager
{
private:
	static std::unordered_map<std::string, std::shared_ptr<sf::Texture> > texturePtrs;
	static std::unordered_map<std::string, std::shared_ptr<sf::Font> > fontPtrs;

public:
	static std::shared_ptr<sf::Texture> acquireTexture(const std::string& path);
	static void murderTextureOrphans();

	static std::shared_ptr<sf::Font> acquireFont(const std::string& path);
	static void murderFontOrphans();
};
