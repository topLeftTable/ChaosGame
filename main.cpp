// Include important C++ libraries here

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

// Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
  srand(time(0));
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

      if (event.type == Event::Closed)
      {
        // Quit the game when the window is closed
        window.close();
      }

      if (event.type == sf::Event::MouseButtonPressed)
      {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
          std::cout << "the left button was pressed" << std::endl;
          std::cout << "mouse x: " << event.mouseButton.x << std::endl;
          std::cout << "mouse y: " << event.mouseButton.y << std::endl;
          if (vertices.size() < 10)
          {
            vertices.push_back(
                Vector2f(event.mouseButton.x, event.mouseButton.y));
          }
        }
        else if (event.mouseButton.button == sf::Mouse::Right && points.size() == 0)
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
      /// select random vertex

      /// calculate midpoint between random vertex and the last point in the
      /// vector

      /// push back the newly generated coord.

      // NOT GONNA LIE WE ALL STRUGGLED AND WORKED ON THIS

        int vert = vertices.size();
        double r;

        switch (vert)
        {

            case 3:
             r = .5;
              break;

            case 4:
              r = .5;
              break;

            case 5:
              r = .618;
              break;

             case 6:
              r = .667;
               break;

             case 7:
               r = .692;
                break;

             case 8:
               r = .707;
               break;

             case 9:
               r = .742;
               break;

             case 10:
               r = .764;
               break;

               default:
               break;              

        }




      int randomInt;
      Vector2f randomVec;
      Vector2f randomVec2;
      Vector2f tempVec;
      
      randomInt = rand() % (vertices.size());
      randomVec = vertices[randomInt];
      

      tempVec.x = (randomVec.x + points[points.size() - 1].x) * r;
      tempVec.y = (randomVec.y + points[points.size() - 1].y) * r;

      points.push_back(tempVec);
    }

    /*
    ****************************************
    Draw
    ****************************************
    */

    window.clear();

    for (int i = 0; i < vertices.size(); i++)
    {
      RectangleShape rect(Vector2f(10, 10));
      rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));

      rect.setFillColor(Color::Blue);
      window.draw(rect);
    }

    //points.push_back(Vector2f(15, 15));

    /// TODO:  Draw points
    if (points.size() > 0)
    {
      for (Vector2f point : points)
      {
        RectangleShape rect(Vector2f(10, 10));
        rect.setPosition(point);
        rect.setFillColor(Color::Green);
        window.draw(rect);
      }
    }

    window.display();
  }
}
