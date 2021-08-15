#include "Checkerboard.hpp"

Checkerboard::Checkerboard(sf::RenderWindow& window)
{
	initSquareArray(); // initialize the checker squares
}

Checkerboard::~Checkerboard()
{
	// delete the square pointers in the square array
	for(int i = 0; i < SQUARES_VERTICAL; ++i)
	{
		for(int j = 0; j < SQUARES_HORIZONTAL; ++j)
		{
			delete squareArray[i][j];
			squareArray[i][j] = nullptr;
		}
	}
}

// initialize the square array and determines if a square is occupied by a checker at start of game
void Checkerboard::initSquareArray()
{
	Square* tempSquare;
	int idNumber = 0; // Square 0 is drawn at (0, 0) and has id number 0

	for(int i = 0; i < SQUARES_VERTICAL; ++i)
	{	
		for(int j = 0; j < SQUARES_HORIZONTAL; ++j)
		{	
			// initialize arbitrary square objects
			tempSquare = new Square(sf::Vector2f(static_cast<float>(XOFFSET), static_cast<float>(YOFFSET)), i, j, idNumber++);
			squareArray[i][j] = tempSquare;
			
			if(((j % 2 != 0 && i % 2 == 0) || (j % 2 == 0 && i % 2 != 0)) && (i <= 2 || i >= 5)) // initialize all the black squares in rows 0-2, 5-7
				squareArray[i][j]->setOccupied(true);
			else
				squareArray[i][j]->setOccupied(false);
		}
	}
}

/*
*	Initializes an 8 by 8 square grid with an arbitrarily colored checkered pattern.
*	This version of drawGrid does not support nice magenta highlight, 
*	but it has a nice green highlight when a square is mouse-overed.
*/
void Checkerboard::drawGrid(sf::RenderWindow& window, int mouseOverX, int mouseOverY)
{
	int startingX = 0, startingY = 0;

	for(int i = 0; i < SQUARES_VERTICAL; ++i)
	{	
		for(int j = 0; j < SQUARES_HORIZONTAL; ++j)
		{
			if((j % 2 == 0 && i % 2 == 0) || (j % 2 != 0 && i % 2 != 0))
				squareArray[i][j]->setFillColor(sf::Color::White); 
			else
				squareArray[i][j]->setFillColor(sf::Color::Black); 
			
			// erase any previous green square highlight
			squareArray[i][j]->setOutlineThickness(0);
			squareArray[i][j]->setOutlineColor(sf::Color(0, 0, 0, 255));

			// find the square in the array that a player is currently mousing over (have to use long version instead of the offset because the offset keeps changing)
			if(squareArray[i][j] == findSquare(mouseOverX, mouseOverY))
			{
				// give it a nice green square highlight
				squareArray[i][j]->setOutlineThickness(-SQUARES_VERTICAL);
				squareArray[i][j]->setOutlineColor(sf::Color::Green);	
			}

			squareArray[i][j]->setPosition(static_cast<float>(startingX), static_cast<float>(startingY)); // set the position for drawing
			squareArray[i][j]->setSize(sf::Vector2f(static_cast<float>(XOFFSET), static_cast<float>(YOFFSET)));
			window.draw(*squareArray[i][j]); // performs the actual drawing of the checkerboard square

			startingX += XOFFSET;
		}

		startingY += YOFFSET;
		startingX = 0; // reset startingX to the far left (0, y).
	}
}

/*
*	Draws an 8 by 8 square grid with checkered color pattern and also highlights the current square (green) and a mouseover square (magenta).
*	The current and mouseOver values come from the CheckerGame, based upon where the player is pointing @ the board.
*/
void Checkerboard::drawGrid(sf::RenderWindow& window, int mouseOverX, int mouseOverY, int currentX, int currentY, bool selecting)
{
	Square* tempSquare;
	int startingX = 0, startingY = 0;
	sf::RectangleShape tempRect;
	tempRect.setPosition(static_cast<float>(currentX), static_cast<float>(currentY));

	for(int i = 0; i < SQUARES_VERTICAL; ++i)
	{	
		for(int j = 0; j < SQUARES_HORIZONTAL; ++j)
		{
			if((j % 2 == 0 && i % 2 == 0) || (j % 2 != 0 && i % 2 != 0))
				squareArray[i][j]->setFillColor(sf::Color::White); 
			else
				squareArray[i][j]->setFillColor(sf::Color::Black); 
			
			if(selecting)
			{
				// erase any previous color highlights from all squares
				squareArray[i][j]->setOutlineThickness(0);
				squareArray[i][j]->setOutlineColor(sf::Color(0, 0, 0, 255));

				// find the square in the array that a player is currently mousing over (have to use long version instead of the variable offsets because the offset keeps changing) 
				if(squareArray[i][j] == findSquare(mouseOverX, mouseOverY))
				{
					// give the selected square a nice green highlight
					squareArray[i][j]->setOutlineThickness(-SQUARES_VERTICAL);
					squareArray[i][j]->setOutlineColor(sf::Color::Green);	
				}
			}
			else if(!selecting)
			{
				// erase any previous color highlights from all squares
				squareArray[i][j]->setOutlineThickness(0);
				squareArray[i][j]->setOutlineColor(sf::Color(0, 0, 0, 255));

				// give the selected square a nice green square highlight
				tempSquare = findSquare(currentX, currentY);
				tempSquare->setOutlineThickness(-SQUARES_VERTICAL); // -8, (draws inward)
				tempSquare->setOutlineColor(sf::Color::Green);	

				// find the square in the array that a player is currently mousing over (have to use long version instead of the variable offsets because the offset keeps changing) 
				if(squareArray[i][j] == findSquare(mouseOverX, mouseOverY))
				{
					// give the move to square a nice magenta highlight
					squareArray[i][j]->setOutlineThickness(-SQUARES_VERTICAL);
					squareArray[i][j]->setOutlineColor(sf::Color::Magenta);	
				}
			}

			// prepare to draw
			squareArray[i][j]->setPosition(static_cast<float>(startingX), static_cast<float>(startingY));
			squareArray[i][j]->setSize(sf::Vector2f(static_cast<float>(XOFFSET), static_cast<float>(YOFFSET)));
			window.draw(*squareArray[i][j]);

			startingX += XOFFSET;
		}

		startingY += YOFFSET;
		startingX = 0;
	}
}

// print each square (#'s 0 thru 63) out on the console
void Checkerboard::printTheSquares()
{
	for(int i = 0; i < SQUARES_HORIZONTAL; ++i)
		for(int j = 0; j < SQUARES_VERTICAL; ++j)
			std::cout << std::endl << "Square #" << squareArray[i][j]->getIdNumber() << " " <<
				"Draw Coords: " << "(" << squareArray[i][j]->getPosition().x << ", " << squareArray[i][j]->getPosition().y << ") " << 
					"Square Occupied: " << squareArray[i][j]->getOccupied() << std::endl;
}
 
/*
*	Finds a square on the board by creating a temp shape with standard size, and starting coords (x, y).
*	We then start comparing squares in the squareArray until we find a match (intersection of coords).
*	This is useful when the player clicks a square and we want to find that matching square in the squareArray.
*/
Square* Checkerboard::findSquare(int x, int y)
{	
	sf::Vector2f size(static_cast<float>(XOFFSET), static_cast<float>(YOFFSET));
	sf::RectangleShape rect2;
	rect2.setPosition(static_cast<float>(x), static_cast<float>(y));
	rect2.setSize(size);

	for(int i = 0; i < SQUARES_VERTICAL; i++)
		for(int j = 0; j < SQUARES_HORIZONTAL; j++)
			if(intersects(*squareArray[i][j], rect2))
				return squareArray[i][j];					

	return nullptr;
}

// finds a square on the board by the square's id number
Square* Checkerboard::findSquare(int idNumber)
{
	for(int i = 0; i < SQUARES_HORIZONTAL; ++i)
		for(int j = 0; j < SQUARES_VERTICAL; ++j)
			if(squareArray[i][j]->getIdNumber() == idNumber)
				return squareArray[i][j];

	return nullptr;
}

/* 
*	find the square that's being jumped onto in the checker game (for when the user selects the checker to jump over = temp)
*	due to the computer coordinate system, the y coordinate may be subtracted when finding a checker in the downward direction
*/
Square* Checkerboard::findJumpOntoSquare(Square* temp, int generalDirection)
{
	// temp square is the square that the user selected to jump over (so find the square the user will land on (future) )
	sf::Vector2f size(static_cast<float>(XOFFSET), static_cast<float>(YOFFSET));
	sf::RectangleShape rect2;
	rect2.setSize(size);
	float x, y;

	switch(generalDirection)
	{
	case 0: // straight to the right
		x = temp->getPosition().x + XOFFSET;
		y = temp->getPosition().y;
		break;
	case 45: // to the right and upward
		x = temp->getPosition().x + XOFFSET;
		y = std::abs(temp->getPosition().y - YOFFSET);
		break;
	case 90: // straight upward
		x = temp->getPosition().x;
		y = std::abs(temp->getPosition().y - YOFFSET);
		break;
	case 135: // to the left and upwards
		// this is a temporary fix for the "kitty corner jump" bug (see Checkerboard.hpp for more info)
		if(temp->getPosition().x == 0) 
			return nullptr;
		else
		{
			x = std::abs(temp->getPosition().x - XOFFSET);
			y = std::abs(temp->getPosition().y - YOFFSET);
		}
		break;
	case 180: // straight to the left 
		x = std::abs(XOFFSET - temp->getPosition().x);
		y = temp->getPosition().y;
		break;
	case 225: // to the left and downwards 
		// this is a temporary fix for the "kitty corner jump" bug (see Checkerboard.hpp for more info)
		if(temp->getPosition().x == 0) 
			return nullptr;
		else
		{
			x = std::abs(XOFFSET - temp->getPosition().x);
			y = temp->getPosition().y + YOFFSET;
		}	
		break;
	case 270: // straight down 
		x = temp->getPosition().x;
		y = YOFFSET + temp->getPosition().y;
		break;
	case 315: // to the right and downward 
		x = temp->getPosition().x + XOFFSET;
		y = temp->getPosition().y + YOFFSET;
		break;
	default: std::cout << "CANNOT FIND JUMPONTOSQUARE, UNKNOWN GENERAL DIRECTION " << std::endl; return nullptr;
	}

	rect2.setPosition(x, y);

	for(int i = 0; i < SQUARES_HORIZONTAL; ++i)
		for(int j = 0; j < SQUARES_VERTICAL; ++j)
			if(intersects(*squareArray[i][j], rect2))
				return squareArray[i][j];

	return nullptr;
}

/*
* Find the square that the user's jumping over in the checker game (for when the user selects the square to land on following a jump).
* Due to the computer coordinate system, the y coordinate may be subtracted when finding a checker in the downward direction.
*/
Square* Checkerboard::findIntermSquare(Square* temp, int generalDirection)
{
	// temp square is the square that the use selected to land on (so find the intermediate square from current to future)
	sf::Vector2f size(static_cast<float>(XOFFSET), static_cast<float>(YOFFSET));
	sf::RectangleShape rect2;
	rect2.setSize(size);
	float x, y;

	switch(generalDirection)
	{
	case 0: // straight to the right
		x = std::abs(temp->getPosition().x - XOFFSET);
		y = temp->getPosition().y;
		break;
	case 45: // to the right and upward
		x = std::abs(temp->getPosition().x - XOFFSET);
		y = temp->getPosition().y + YOFFSET;
		break;
	case 90: // straight upward
		x = temp->getPosition().x;
		y = temp->getPosition().y + YOFFSET;
		break;
	case 135: // to the left and upwards
		x = XOFFSET + temp->getPosition().x;
		y = temp->getPosition().y + YOFFSET;
		break;
	case 180: // straight to the left 
		x = temp->getPosition().x + XOFFSET;
		y = temp->getPosition().y;
		break;
	case 225: // to the left and downwards 
		x = XOFFSET + temp->getPosition().x;
		y = std::abs(temp->getPosition().y - YOFFSET);
		break;
	case 270: // straight down 
		x = temp->getPosition().x;
		y = std::abs(temp->getPosition().y - YOFFSET);
		break;
	case 315: // to the right and downward 
		x = std::abs(XOFFSET - temp->getPosition().x);
		y = std::abs(temp->getPosition().y - YOFFSET);
		break;
	default: std::cout << "CANNOT FIND INTERMSQUARE, UNKNOWN GENERAL DIRECTION" << std::endl; return nullptr;
	}

	rect2.setPosition(x, y);

	for(int i = 0; i < SQUARES_HORIZONTAL; ++i)
		for(int j = 0; j < SQUARES_VERTICAL; ++j)
			if(intersects(*squareArray[i][j], rect2))
				return squareArray[i][j];

	return nullptr;
}

Square** Checkerboard::getSquareArray()
{
	return *squareArray;
}

// checks if shape1's pixels intersect the pixels of shape2
bool Checkerboard::intersects(const sf::RectangleShape shape1, const sf::RectangleShape shape2)
{
	sf::FloatRect r1 = shape1.getGlobalBounds();
	sf::FloatRect r2 = shape2.getGlobalBounds();
	return r1.intersects (r2);
}