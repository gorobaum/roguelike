// External Dependencies
#include <ugdk/base/engine.h>           // needed for engine
#include <ugdk/graphic/videomanager.h>  // needed for SetVSync()

// Internal Dependencies
#include "game/base/gamecontroller.h"   // needed for new GameController::Initialize()

int main(int argc, char **argv) {
	ugdk::Configuration engine_config;
	engine_config.window_title = "Worst. Game. Ever.";
	engine_config.window_size = ugdk::Vector2D(1200.0, 900.0);
	engine_config.fullscreen = false;
    engine_config.base_path = "./data/";

    ugdk::Engine* engine = ugdk::Engine::reference();
    engine->Initialize(engine_config);
	engine->video_manager()->SetVSync(true);

	engine->PushScene(game::base::GameController::Initialize());
    engine->Run();

    engine->Release();
    return 0;
}