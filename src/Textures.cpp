#include "Textures.hpp"

// for changing the working directory for Windows compatibility
#if _WIN32
#include <direct.h>
#endif //_WIN32

sf::Texture Textures::grass;
sf::Texture Textures::character;
sf::Texture Textures::water;
sf::Texture Textures::mountain;

void Textures::init() {

  /* need to change the directory path for Windows because it likes to screw
   * with file paths (executables are put an additional directory deep from what
   * linux does, so cd one directory up for the paths to work again
   */
#if _WIN32
  _chdir("../");
#endif // _WIN32

  // load the files
  grass.loadFromFile("../Assets/Grass.png");
  character.loadFromFile("../Assets/Character.png");
  water.loadFromFile("../Assets/Water.png");
  mountain.loadFromFile("../Assets/Mountain.png");
}