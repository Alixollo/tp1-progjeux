#pragma once
class Hud
{
public:
	static const std::string POINTS_STRING;
	Hud();
	void draw(sf::RenderWindow& window)  const;
	void initialize();
	void update(const int points);
private:
	sf::View hudView;
	sf::Text gameTitle;

	sf::Text pointsText;
};

