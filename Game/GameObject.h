#pragma once


class GameObject : public sf::Sprite
{
public:
	GameObject();
	GameObject(const GameObject& src);
	GameObject& operator=(const GameObject& rhs);
	void draw(sf::RenderWindow& window) const;
	virtual void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition);

	virtual void activate();
	virtual void deactivate();
	bool isActive() const;
	bool collidesWith(const GameObject& other) const;


	float getRotationAngleInRadians() const;
	void setRotationAngleRadians(const float angle);
	virtual void rotateInRadians(const float angle);

protected:
	float getAngleWith(const GameObject& other) const;
	bool active;
};

