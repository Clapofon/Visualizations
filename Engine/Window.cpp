#include "Window.h"
#include "Error.h"

#include <windows.h>

#include <glew.h>

#include <imgui.h>
#include <backends/imgui_impl_sdl.h>
#include <backends/imgui_impl_opengl3.h>

extern "C" {
    _declspec(dllexport) DWORD NvOptimusEnablement = 1;
    _declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

namespace Engine
{
    Window::Window() : m_sdlWindow(nullptr)
    {}

    Window::~Window()
    {}

    int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags)
    {
        Uint32 flags = SDL_WINDOW_OPENGL;// | SDL_WINDOW_RESIZABLE;

        if (currentFlags & WindowFlags::INVISIBLE)
        {
            flags |= SDL_WINDOW_HIDDEN;
        }

        if (currentFlags & WindowFlags::FULLSCREEN)
        {
            flags |= SDL_WINDOW_FULLSCREEN;
        }

        if (currentFlags & WindowFlags::BORDERLESS)
        {
            flags |= SDL_WINDOW_BORDERLESS;
        }

        m_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);

        if (m_sdlWindow == nullptr)
        {
            fatalError("Window could not be created!...");
            return 1;
        }

        SDL_GLContext context = SDL_GL_CreateContext(m_sdlWindow);

        if (context == nullptr)
        {
            fatalError("SDL_GL_Context could not be created!...");
            return 1;
        }

        GLenum error = glewInit();

        if (error != GLEW_OK)
        {
            fatalError("Could not initialize glew!...");
            return 1;
        }

        printf("***  OpenGL Verion: %s  ***\n", glGetString(GL_VERSION));
        printf("***  OpenGL Vendor: %s  ***\n", glGetString(GL_VENDOR));
        printf("***  OpenGL Renderer: %s  ***\n", glGetString(GL_RENDERER));
        printf("***  OpenGL Shading Language Version: %s  ***\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
        //printf("***  OpenGL Verion: %s  ***\n", glGetString(GL_EXTENSIONS));

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImGui::StyleColorsDark();
        ImGui_ImplSDL2_InitForOpenGL(m_sdlWindow, context);
        ImGui_ImplOpenGL3_Init("#version 130");

        //glClearColor(0.258, 0.529, 0.96, 0.0);
        glClearColor(0.118, 0.118, 0.118, 0.0);

        SDL_GL_SetSwapInterval(0);

        //enable alpha blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        return 0;
    }

    SDL_Window* Window::get()
    {
        return m_sdlWindow;
    }

    void Window::swapBuffer()
    {
        SDL_GL_SwapWindow(m_sdlWindow);
    }
}






















