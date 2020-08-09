using System;
using SFML.Graphics;
using SFML.Window;

namespace Game
{
    public class SfmlApplication
    {
        RenderWindow window;

        // static ScoreKeeper keeper = new ScoreKeeper();
        
        // static Board CheckerBoard = new Board();
        // Player[2] Players;



        



        public SfmlApplication(string title, UInt16 x, UInt16 y) {
            window = new RenderWindow(new VideoMode(x, y), title);

        }

        public void start() {

            window.Clear();

            while (window.IsOpen) {

                window.DispatchEvents();

                window.Display();

            }
        }

        public void close() {
            window.Close();
        }

    }
}
