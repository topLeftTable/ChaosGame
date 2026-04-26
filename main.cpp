/*
**************************************
Project By Logan Doose, Jalen Watkins,
Ezekiel Shahbaz, and Deaven Niccum
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
  bool update;

  // Seed the random number generator
  srand(time(nullptr));

  string selShape;

  // Create a video mode object
  VideoMode vm(1920, 1080);

  // Create and open a window for the game
  RenderWindow window(vm, "Chaos Game!!", Style::Default);

  // Coordinate points forming initial shape
  vector<Vector2f> vertices;
  // Random points generated during calculations
  vector<Vector2f> points;

  // Start the game loop
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
          std::cout << "mouse x: " << event.mouseButton.x << std::endl;
          std::cout << "mouse y: " << event.mouseButton.y << std::endl;

          // Possible vertices max out at 10
          if (vertices.size() < 10)
          {
            // store vertices of Left Mouse clicks
            vertices.push_back(
                Vector2f(event.mouseButton.x, event.mouseButton.y));
          }
        }
        else if (event.mouseButton.button == Mouse::Right && points.size() == 0)
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

    //    DEBUG: POINTERPOSY
    // cout << " Event Mousebutton: " << event.mouseButton.y << endl;
    //    cout << " Vector Mousebutton: " << vector2i.y << endl;

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
      /// select random vertex

      /// calculate midpoint between random vertex and the last point in the
      /// vector

      /// push back the newly generated coord.

      // NOT GONNA LIE WE ALL STRUGGLED AND WORKED ON THIS

      int randomInt;
      Vector2f randomVec;
      Vector2f randomVec2;
      Vector2f tempVec;

      /// select random vertex
      randomInt = rand() % vertices.size();
      randomVec = vertices[randomInt];

      // ratio formula for any polygon of n-corner points
      double r = vertices.size() / (vertices.size() + 3.0);

      /// calculate midpoint between random vertex
      /// and the last point in the vector
      tempVec.x = (randomVec.x + points[points.size() - 1].x) * r;
      tempVec.y = (randomVec.y + points[points.size() - 1].y) * r;

      /// push back the newly generated coord.
      points.push_back(tempVec);
    }

    /*
    ****************************************
    Draw
    ****************************************
    */

    window.clear();

    //    Ezekiel: Text Rendering or something
    //    Мрак привет

    //    UI Shape Text Selection
    //    Logic to Select Shape Name
    selShape = "Shape";
    switch (vertices.size())
    {
    case 3:
      selShape = "Triangle";
      break;
    case 4:
      selShape = "Square";
      break;
    case 5:
      selShape = "Pentagon";
      break;
    case 6:
      selShape = "Hexagon";
      break;
    case 7:
      selShape = "Heptagon";
      break;
    case 8:
      selShape = "Octagon";
      break;
    case 9:
      selShape = "Nonagon";
      break;
    case 10:
      selShape = "Decagon";
      break;
    }

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
          "\nRight Click to Draw a " + selShape;
    msg.setString(str);
    msgBounds = msg.getGlobalBounds();
    msgBackground.setSize(
        Vector2f(msgBounds.width + 16,
                 msgBounds.height + 16)); // 8px padding (Logan's idea)
    msgBackground.setPosition(Vector2f(msgBounds.left - 8, msgBounds.top - 8));

    for (int i = 0; i < vertices.size(); i++)
    {
      RectangleShape rect(Vector2f(5, 5));
      rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));

      rect.setFillColor(Color::Blue);
      window.draw(rect);
    }

    // points.push_back(Vector2f(15, 15));

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
