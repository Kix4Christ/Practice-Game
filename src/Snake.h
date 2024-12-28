#include <SFML/Graphics.hpp>

class Snake
{
private:
	struct segment
	{
		sf::Vector2i position;
		Direction dir;

	}head;

	std::vector<segment> segments;
	
	int length;
public:
	Snake();
	~Snake();
	void move(Direction dir);
};