#include "Backend.h"
#include "Game.h"
#include "Renderer.h"
#include <iostream>
#include <glad/glad.h>

//5 main folders (AssetManager, Game, World, Backend, Renderer) 

//AssetManager - Loads shaders,textures, etc...
// Renderer - renders whatever assetmanager loads.
// Game - Camera stuff, 

int main() {

    //1.  Initilaze backend (Backend)
    if (!Backend::Init(API::OPENGL, WindowedMode::WINDOWED)) {
        std::cerr << "Backend::Init() FAILED!\n";
        return -1;
    }

    //2.  (Game, AssetManager, Renderer, World)
    Game game;
    game.Init();


    //3.  (Backend, Game, World, Physics, Player)
    while (!Backend::WindowShouldClose()) {
        Backend::UpdateSubSystems();
        Backend::BeginFrame();

        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float deltaTime = Backend::GetDeltaTime();
        game.Update(deltaTime);
        game.Render();

        Backend::EndFrame();
    }
    // Cleanup (Renderer)
    Renderer::Shutdown();
    return 0;
}
