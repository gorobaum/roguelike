// External Dependencies
#include <ugdk/base/engine.h>           // needed for various functions, includes <ugdk/base/configuration.h>
#include <ugdk/graphic/videomanager.h>  // needed for SetVSync(-)

// Internal Dependencies
#include "game/base/gamecontroller.h"   // needed for new GameController(-)

int main(int argc, char **argv) {
	ugdk::Configuration engine_config;
	engine_config.window_title = "Worst. Game. Ever.";
	engine_config.window_size = ugdk::Vector2D(800.0, 600.0);
	engine_config.fullscreen = false;

    ugdk::Engine* engine = ugdk::Engine::reference();
    engine->Initialize(engine_config);
	engine->video_manager()->SetVSync(true);

	engine->PushScene(new game::base::GameController() );

    engine->Run();
    engine->Release();
    return 0;
}