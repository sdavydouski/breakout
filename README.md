## C++/OpenGL Breakout

My first attempt to create a game in C++. This project is heavily influenced by [this awesome tutorial](http://www.learnopengl.com/#!In-Practice/2D-Game/Breakout) written by Joey de Vries. It's not a blind copy/past replica though - I rather took main concepts and ideas and implemented them as I saw fit.

#### Gameplay example:
![Gameplay example](gameplay.gif)

#### Game assets
* background texture - [https://opengameart.org/content/sunset-temple-tiles](https://opengameart.org/content/sunset-temple-tiles)
* other textures - [https://opengameart.org/content/pixel-art-tiles-from-last-escape](https://opengameart.org/content/pixel-art-tiles-from-last-escape)
* background music - [https://opengameart.org/content/tower-defense-theme](https://opengameart.org/content/tower-defense-theme)

#### Build
All dependencies are presented as git submodules so you can simply download them and build the project. Tested on Visual C++ 14 and MinGW-w64 g++ compilers. Adjust `AssetsLoader::OFFSET` if needed. If you are a Windows user you can just [download](https://github.com/wiranoid/breakout/releases/download/1.0.0/breakout.zip) prebuilt game (commit 801d2c69900cbdc78cd19693414196a888308ab5).
