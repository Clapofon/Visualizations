#include "IMainGame.h"

#include <glew.h>
#include <windows.h>

#include <imgui.h>
#include <backends/imgui_impl_sdl.h>
#include <backends/imgui_impl_opengl3.h>

namespace Engine
{
    IMainGame::IMainGame()
    {
        m_screenList = std::make_unique<ScreenList>(this);
    }

    IMainGame::~IMainGame()
    {

    }

    void IMainGame::run()
    {
        if (!init()) return;

        m_isRunning = true;

        while (m_isRunning)
        {
            double currentTime = (double)SDL_GetTicks() / 1000.0;
            double passedTime = currentTime - m_lastTime;
            m_lastTime = currentTime;

            m_fpsTimeCounter += passedTime;
            m_updateTimer += passedTime;

            if (m_fpsTimeCounter >= 1.0)
            {
                m_msPerFrame = 1000.0 / (double)m_fps;
                //std::cout << "[ms]" << msPerFrame << " [fps]" << m_fps << std::endl;
                m_stat = std::to_string(m_fps);

                a = (double)m_fps / m_frameCap;

                m_fpsTimeCounter = 0;
                m_fps = 0;
            }

            bool shouldRender = false;
            while (m_updateTimer >= m_frameTime)
            {
                //handleInput();
                // begin scene update

                m_deltaTime = (m_msPerFrame / 1000.0) * a;

                update(m_deltaTime);

                // end scene update

                m_updateTimer -= m_frameTime;
                shouldRender = true;
            }

            if (shouldRender)
            {
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplSDL2_NewFrame(m_window.get());
                ImGui::NewFrame();

                // Begin scene render
                draw();

                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
                m_window.swapBuffer();
                // End scene render

                m_fps++;
            }
            else
            {
                SDL_Delay(1);
            }
        }
    }

    void IMainGame::exit()
    {
        if (m_currentScreen != nullptr)
        {
            m_currentScreen->onExit();
        }

        if (m_screenList)
        {
            m_screenList->destroy();
            m_screenList.reset();
        }

        m_audioEngine.Shutdown();
        m_isRunning = false;
        onExit();
    }

    bool IMainGame::init()
    {
        Engine::init();
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
        initSystems();
        onInit();
        addScreens();

        m_currentScreen = m_screenList->getCurrent();
        m_currentScreen->onEntry();
        m_currentScreen->setRunning();

        return true;
    }

    bool IMainGame::initSystems()
    {
        m_window.create(m_windowName, m_windowDimentions.x, m_windowDimentions.y, 0);
        m_audioEngine.Init();

        return true;
    }

    void IMainGame::update(double deltaTime)
    {
        m_inputManager.update();
        m_audioEngine.Update();

        if (m_currentScreen)
        {
            switch (m_currentScreen->getState())
            {
            case ScreenState::RUNNING:
                m_currentScreen->update(m_deltaTime);
                break;
            case ScreenState::CHANGE_NEXT:
                m_currentScreen->onExit();
                m_currentScreen = m_screenList->moveNext();
                if (m_currentScreen != nullptr)
                {
                    m_currentScreen->setRunning();
                    m_currentScreen->onEntry();
                }
                break;
            case ScreenState::CHANGE_PREVIOUS:
                m_currentScreen->onExit();
                m_currentScreen = m_screenList->movePrevious();
                if (m_currentScreen != nullptr)
                {
                    m_currentScreen->setRunning();
                    m_currentScreen->onEntry();
                }
                break;
            case ScreenState::EXIT_APPLICATION:
                exit();
                break;
            default:
                break;
            }
        }
        else
        {
            exit();
        }
    }

    void IMainGame::draw()
    {
        glClearDepth(1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        if (m_currentScreen && m_currentScreen->getState() == ScreenState::RUNNING)
        {
            m_currentScreen->draw();
        }
    }

    void IMainGame::onSDLEvent(SDL_Event& event)
    {
        ImGui_ImplSDL2_ProcessEvent(&event);


        switch (event.type)
        {
        case SDL_KEYDOWN:
            m_inputManager.onKeyDown(event.key.keysym.sym);
            break;
        case SDL_KEYUP:
            m_inputManager.onKeyUp(event.key.keysym.sym);
            break;
        case SDL_MOUSEBUTTONDOWN:
            m_inputManager.onKeyDown(event.button.button);
            break;
        case SDL_MOUSEBUTTONUP:
            m_inputManager.onKeyUp(event.button.button);
            break;
        case SDL_MOUSEMOTION:
            m_inputManager.onMouseMove(event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
            break;
        case SDL_WINDOWEVENT:
            switch (event.window.event)
            {
                case SDL_WINDOWEVENT_RESIZED:
                    m_windowDimentions = glm::vec2(event.window.data1, event.window.data1);
                    glViewport(0, 0, m_windowDimentions.x, m_windowDimentions.y);
                    break;
            }
            break;
        case SDL_QUIT:
            m_isRunning = false;
            break;
        }
    }


/*
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(WIN64)
#define OS_WINDOWS
#elif defined(__linux__)
#define OS_LINUX
#elif __cplusplus >= 201103L
#define OS_OTHER_CPP11
#else
#define OS_OTHER
#endif

#ifdef OS_WINDOWS
#include <Windows.h>
#include <iostream>
    static double g_freq;
    static bool g_timerInitialized = false;
#endif

#ifdef OS_LINUX
#include <sys/time.h>
    static const long NANOSECONDS_PER_SECOND = 1000000000L;
#endif

#ifdef OS_OTHER
#include <SDL.h>
#endif

#ifdef OS_OTHER_CPP11
#include <chrono>
    static std::chrono::system_clock::time_point m_epoch = std::chrono::high_resolution_clock::now();
#endif

    double IMainGame::getTime()
    {
#ifdef OS_WINDOWS
        if (!g_timerInitialized)
        {
            LARGE_INTEGER li;
            if (!QueryPerformanceFrequency(&li))
                std::cerr << "QueryPerformanceFrequency failed in timer initialization" << std::endl;

            g_freq = double(li.QuadPart);
            g_timerInitialized = true;
        }

        LARGE_INTEGER li;
        if (!QueryPerformanceCounter(&li))
            std::cerr << "QueryPerformanceCounter failed in get time!" << std::endl;

        return double(li.QuadPart) / g_freq;
#endif

#ifdef OS_LINUX
        timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        return (double)(((long)ts.tv_sec * NANOSECONDS_PER_SECOND) + ts.tv_nsec) / ((double)(NANOSECONDS_PER_SECOND));
#endif

#ifdef OS_OTHER_CPP11
        return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_epoch).count() / 1000000000.0;
#endif

#ifdef OS_OTHER
        return (double)SDL_GetTicks() / 1000.0;
#endif
    }*/
}