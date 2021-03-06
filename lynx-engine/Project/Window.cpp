#include "Window.h"
#include <GL/glew.h>
#include "Log.h"
#include "Config.h"
using namespace lynx;



Window::Window() {}


Window::~Window() {}



void Window::init() {
	this->isFullscreen = Config::getBool("window.fullscreen");
	this->title = Config::getString("window.title");
	/**
	 * DEFAULT SFML WINDOW SETTINGS
	 * sf::ContextSettings settings;
	 * settings.depthBits = 24;
	 * settings.stencilBits = 0;
	 * settings.antialiasingLevel = 0;
	 * settings.majorVersion = 4;
	 * settings.minorVersion = 4;
	 */	
	GLuint style = sf::Style::Default;
	if (isFullscreen) style = sf::Style::Fullscreen;
	create(sf::VideoMode(Config::getInt("window.width"), Config::getInt("window.height")), title.c_str(), style);
	/**
	 * Sometimes, when your application runs fast, you may notice visual
	 * artifacts such as tearing. The reason is that your application's
	 * refresh rate is not synchronized with the vertical frequency of the
	 * monitor, and as a result, the bottom of the previous frame is mixed
	 * with the top of the next one. The solution to this problem is to
	 * activate vertical synchronization. It is automatically handled by 
	 * the graphics card, and can easily be switched on and off with the 
	 * setVerticalSyncEnabled function. After this call, your application
	 * will run at the same frequency as the monitor, so approximately 
	 * 60 frames per second.
	 *
	 * Example: setVerticalSyncEnabled(true);
	 *
	 * In other situations, you may also want your application to run at a given
	 * framerate, instead of the monitor's frequency. This can be done by calling
	 * setFramerateLimit. Unlike setVerticalSyncEnabled, this feature is
	 * implemented by SFML itself, using a combination of sf::Clock and sf::sleep.
	 * An important consequence is that it is not 100% reliable, especially for high
	 * framerates: sf::sleep's resolution depends on the underlying OS, and can be as
	 * high as 10 or 15 milliseconds. Don't rely on this feature to implement precise
	 * timing. Never use both setVerticalSyncEnabled and setFramerateLimit at the same
	 * time! They would badly mix and make things worse.
	 *
	 * Example: setFramerateLimit(60);
	 */
	setVerticalSyncEnabled(true); // This results in high CPU usage and is very smooth
	//setFramerateLimit(60); // This results in <1% CPU usage, but is not as smooth as above
}

void Window::onCreate() {
	Log::info("Window || window initialized");
	Log::info("Window || title = " + title);
	Log::info("Window || fullscreen = " + std::to_string(isFullscreen));
	Log::info("Window || width = " + std::to_string(getSize().x));
	Log::info("Window || height = " + std::to_string(getSize().y));
	/*
	GLEW has a problem with core contexts. It calls
	glGetString(GL_EXTENSIONS), which causes GL_INVALID_ENUM
	on GL3.2 core context as soon as glewInit() is called.
	It also doesn't fetch the function pointers. The solution
	is for GLEW to use glGetStringi instead. The current version
	of GLEW is 1.10.0 but they still haven't correct it.
	The glError() is #1280.
	*/
	glewExperimental = GL_TRUE; // Needed in core profile.
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		//Problem: glewInit failed, something is seriously wrong.
		Log::fatal("Window || glewInit() failed");
	}

	// Enable default OpenGL stuff.
	glEnable(GL_DEPTH_TEST);
	Log::info("Window || default enabled: GL_DEPTH_TEST");
	//glEnable(GL_CULL_FACE);
	// Accept fragment if it's closer to the camera than the former one.
	glDepthFunc(GL_LESS);
	Log::info("Window || default glDepthFunc: GL_LESS");



	Log::info("Window || OpenGL Vendor: " + std::string(((char*)glGetString(GL_VENDOR))));
	Log::info("Window || OpenGL Renderer: " + std::string(((char*)glGetString(GL_RENDERER))));
	Log::info("Window || OpenGL Version: " + std::string(((char*)glGetString(GL_VERSION))));
	Log::info("Window || OpenGL Shading Language Version: " + std::string(((char*)glGetString(GL_SHADING_LANGUAGE_VERSION))));
}
