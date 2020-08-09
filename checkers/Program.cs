using System;

namespace checkers
{
    class Program
    {
        static void Main(string[] args)
        {
            var g = new Game.SfmlApplication("checkers", 1080, 720);
            g.start();
        }
    }
}
