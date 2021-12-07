/*#pragma once

#include "CEGUI/CEGUI.h"
#include "CEGUI/RendererModules/OpenGL/GL3Renderer.h"
#include <glm.hpp>

namespace Engine
{
	class GUI
	{
	public:

		void init(const std::string& resourceDisrectory);
		void cleanup();

		void draw();
		void loadScheme(const std::string& schemeFile);
		void setFont(const std::string& font);
		CEGUI::Window* createWidget(const std::string& type, const glm::vec4& destRectPerc, const glm::vec4& destRectPix, const std::string& name = "");
		static void setWidgetDestRect(CEGUI::Window* window, const glm::vec4& destRectPerc, const glm::vec4& destRectPix);

		static CEGUI::OpenGL3Renderer* getRenderer() { return m_renderer; }
		const CEGUI::GUIContext* getContext() { return m_context; }

	private:

		static CEGUI::OpenGL3Renderer* m_renderer;
		CEGUI::GUIContext* m_context = nullptr;
		CEGUI::Window* m_rootWindow = nullptr;
	};

}
*/