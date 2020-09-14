#pragma once

enum class ButtonState { BTN_IDLE = 0, BTN_HOVERED, BTN_PRESSED };

namespace gui
{
	float p2pX(float perc, const sf::VideoMode& vm);
	float p2pY(float perc, const sf::VideoMode& vm);
	unsigned calcCharSize(const sf::VideoMode& vm, unsigned modifier = 60);

	class Button
	{
	private:
		bool clickBlockade; // blokuje podwójne klikniêcia
		bool clicked; // prawda je¿eli przycisk zosta³ klikniêty w ci¹gu ostatniej klatki
		ButtonState state;
		unsigned short id;

		sf::RectangleShape rect;

		std::shared_ptr<sf::Font> font;
		sf::Text text;

		sf::Color idleColor, hoverColor, pressedColor;
		sf::Color outlineIdleColor, outlineHoverColor, outlinePressedColor;
		sf::Color textIdleColor, textHoverColor, textPressedColor;

	public:
		Button(
			float posX, float posY,
			float width, float height,
			std::shared_ptr<sf::Font> font, const std::string& text, int charSize,
			sf::Color idleColor, sf::Color hoverColor, sf::Color pressedColor,
			sf::Color outlineIdleColor, sf::Color outlineHoverColor, sf::Color outlinePressedColor,
			sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textPressedColor,
			float outlineThickness = 1.f, short unsigned id = 0
		);
		~Button();
		
		bool isClicked() const; // zwraca wartoœæ zmiennej "clicked"

		const std::string& getText() const;
		short unsigned getId() const;
		ButtonState getState() const;

		void setText(const std::string& text);
		void setId(short unsigned id);
		void setClickBlockade(bool blockade);
		void setIdle();
		void setHovered();

		void update(sf::Vector2i mousePosWindow);
		void render(sf::RenderTarget& target);
	};

	class Modifier
	{
	private:
		std::unordered_map<std::string, sf::Texture> axisTextures;
		std::unordered_map<std::string, sf::Texture> handleTextures;

		std::unordered_map<std::string, sf::Sprite> axes;
		std::unordered_map<std::string, sf::Sprite> handles;

		std::string state;

		bool maxOnLeft;
		bool minimizeToZero;

		float maxValue;
		float value;

	public:
		Modifier(
			float posX, float posY,
			float textureScale,
			float maxValue, bool maxOnLeft,
			const std::string& axis_idle_path, const std::string& handle_idle_path,
			const std::string& axis_hover_path, const std::string& handle_hover_path,
			const std::string& axis_pressed_path, const std::string& handle_pressed_path
		);
		~Modifier();

		float getValue() const;
		float getMaxValue() const;

		void setValue(float value);
		void setMinimizeToZero(bool minimizeToZero);

		void update(sf::Vector2i mousePosWindow);
		void render(sf::RenderTarget& target);
	};
}
