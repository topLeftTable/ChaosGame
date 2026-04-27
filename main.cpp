/*
**************************************
Project By LoganMD, jalenzwatkins,
WaitingKeptYouHuh, and deathsdebtor
**************************************
*/

// Include important C++ libraries here
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
	// Lookup Table Vector Thing
	//   Layout: data[0][x] = Shape Names | data[1][x] = Precomupted Ratios for
	//   Ratio 1 | data[2][x] = Precomputed Ratios for Ratio 2
	vector<vector<string>> data = {
		{"Shape", "Shape", "Shape", "Triangle", "Square", "Pentagon", "Hexagon",
		 "Heptagon", "Octagon", "Nonagon", "Decagon"},
		{"0.00", "0.00", "0.00", "0.50", "0.5714285714", "0.625", "0.6666667",
		 "0.70", "0.72727273", "0.75", "0.769207692"},
		{"0.00", "0.00", "0.00", "0.4285714286", "0.50", "0.555555556", "0.60",
		 "0.6363636364", "0.66666667", "0.6923076923", "0.714285713"}};

	//  Declarations and initialization for text renderer
	string str;
	Text msg;
	Font font;
	font.loadFromFile("fonts/IBMPlexMono-Regular.ttf");
	msg.setFont(font);
	msg.setCharacterSize(25);
	msg.setFillColor(Color::Magenta);
	msg.setPosition(50, 50);

	FloatRect msgBounds;
	RectangleShape msgBackground;
	msgBackground.setFillColor(Color::Black);

	int ptrPosX;
	int ptrPosY;

	int lastUsedIndex = -1;
	bool update = true;

	srand(time(nullptr));

	string selShape;
	int selPat = 1;

	// Create a video mode object
	VideoMode vm(1920, 1080);

	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);

	vector<Vector2f> vertices;
	vector<Vector2f> points;
	while (window.isOpen())
	{

		/*
		****************************************
		Handle the players input
		****************************************
		*/

		Event event;
		while (window.pollEvent(event))
		{
			// Press 'Tab' to Switch Between Patterns
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Key::Tab)
				{
					selPat = selPat == 2 ? selPat = 1 : selPat = 2;
				}
			}

			// press 'R' to reset the drawing
			if (Keyboard::isKeyPressed(Keyboard::R))
			{
				points.clear();
				vertices.clear();
			}

			if (event.type == Event::Closed)
			{
				// Quit the game when the window is closed
				window.close();
			}

			// Quit the game when ESC key is pressed
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}

			if (event.type == Event::MouseButtonPressed)
			{

				if (event.mouseButton.button == Mouse::Left)
				{
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x
							  << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y
							  << std::endl;
					if (vertices.size() < 10)
					{
						vertices.push_back(
							Vector2f(event.mouseButton.x, event.mouseButton.y));
					}
				}
				else if (event.mouseButton.button == Mouse::Right &&
						 points.size() == 0)
				{
					/// fourth click

					/// push back to points vector
					for (int i = 0; i < vertices.size(); i++)
					{
						points.push_back(vertices[i]);
					}
				}
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		/*
		****************************************
		Update
		****************************************
		*/

		if (points.size() > 0)
		{
			/// generate more point(s)
			///
			int randomInt;
			Vector2f randomVec;
			Vector2f tempVec;

			/// select random vertex except last iteration's vertex
			if (selPat == 2)
			{
				do
				{
					randomInt = rand() % vertices.size();
				} while (vertices.size() > 3 && randomInt == lastUsedIndex);
			}

			else if (selPat == 1)
			{
				randomInt = rand() % vertices.size();
			}
			randomVec = vertices[randomInt];
			lastUsedIndex = randomInt;

			// ratio formula for any polygon of n-corner points
			double r = stod(data[selPat][vertices.size()]);

			/// calculate midpoint between random vertex and the last point in
			/// the vector using ratio
			tempVec.x =
				((1 - r) * points[points.size() - 1].x) + (r * randomVec.x);
			tempVec.y =
				((1 - r) * points[points.size() - 1].y) + (r * randomVec.y);

			/// push back the newly generated coord.
			points.push_back(tempVec);
		}

		/*
		****************************************
		Draw
		****************************************
		*/

		window.clear();

		//    WaitingKeptYouHuh: Text Rendering or something
		//    Мрак привет

		//    UI Shape Text Selection
		//    Logic to Select Shape Name

		selShape = data[0][vertices.size()];

		//   Logic to Determine Whether or Not to Update ptrPos Text
		if (event.type == Event::MouseMoved)
		{
			update = true;
		}
		else if (event.type == Event::MouseLeft)
		{
			update = false;
		}

		if (event.type == Event::MouseMoved)
		{
			update = true;
		}
		else if (event.type == Event::MouseLeft)
		{
			update = false;
		}

		if (update)
		{
			if (event.type == Event::MouseButtonPressed ||
				event.type == Event::MouseButtonReleased)
			{
				ptrPosX = event.mouseButton.x;
				ptrPosY = event.mouseButton.y;
			}
			else
			{
				ptrPosX = event.mouseMove.x;
				ptrPosY = event.mouseMove.y;
			}
		}
		// cout << update << endl << endl;

		//    Printing
		str = "Pointer Position : " + to_string(ptrPosX) + "," +
			  to_string(ptrPosY) +
			  "\nAmount of Points: " + to_string(vertices.size()) +
			  "\nSelected Pattern Pattern: " + to_string(selPat) +
			  "\nRight Click to Draw a " + selShape;
		msg.setString(str);
		msgBounds = msg.getGlobalBounds();
		msgBackground.setSize(
			Vector2f(msgBounds.width + 16,
					 msgBounds.height + 16)); // 8px padding (Logan's idea)
		msgBackground.setPosition(
			Vector2f(msgBounds.left - 8, msgBounds.top - 8));

		for (int i = 0; i < vertices.size(); i++)
		{
			RectangleShape rect(Vector2f(5, 5));
			rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));

			rect.setFillColor(Color::Blue);
			window.draw(rect);
		}

		/// TODO:  Draw points
		if (points.size() > 0)
		{
			for (Vector2f point : points)
			{
				RectangleShape rect(Vector2f(1, 1));
				rect.setPosition(point);
				rect.setFillColor(Color::Green);
				window.draw(rect);
			}
		}

		window.draw(msgBackground);
		window.draw(msg);
		window.display();
	}
}
