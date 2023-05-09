
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <thread>
#include <chrono>
#include <cassert>
#include <iostream>

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"

using namespace sf;
using namespace mg;

using namespace std::chrono;

int main()
{
    unsigned int windowWidth = 800;
    unsigned int windowHeight = 600;

    // Window with OpenGL context
    Window window(VideoMode(windowWidth, windowHeight), "MGRenderer", Style::Default, ContextSettings(24, 0, 4, 3, 3, ContextSettings::Core));

    // Glad initialization
    GLenum glad_init = gladLoadGL();

    // Stop program if glad could not load properly
    assert(glad_init != 0);

    std::cout << glGetString(GL_VERSION) << std::endl;

    // Enable backface culling
    glEnable(GL_CULL_FACE);

	// Enable antialiasing
	glEnable(GL_MULTISAMPLE);

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Renderer renderer(windowWidth, windowHeight);

    glClearColor(0.1f, 0.1f, 0.1f, 1);

    // Delta time variables
    auto  chrono = high_resolution_clock();
    float target_time = 1.f / 60;
    float delta_time = target_time;

    window.setVerticalSyncEnabled(true);

    bool running = true;

    do
    {
        // Get time where frame started
        high_resolution_clock::time_point start = chrono.now();

        Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
				case Event::Closed:
				{
					running = false;
					break;
				}
            }
        }

        renderer.update();

        glClear(GL_COLOR_BUFFER_BIT);

        renderer.render();

        window.display();

        // Compute delta time
        float elapsed = duration<float>(chrono.now() - start).count();

        if (elapsed < target_time)
        {
            std::this_thread::sleep_for(duration<float>(target_time - elapsed));
        }

        delta_time = duration<float>(chrono.now() - start).count();

    } while (running);

    return 0;
}