/*#include "GUI.h"


namespace Engine
{

	CEGUI::OpenGL3Renderer* GUI::m_renderer = nullptr;

	void GUI::init(const std::string& resourceDisrectory)
	{
		if (m_renderer == nullptr)
		{
			m_renderer = &CEGUI::OpenGL3Renderer::bootstrapSystem();

			CEGUI::DefaultResourceProvider* resourceProvider = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());

			resourceProvider->setResourceGroupDirectory("imagesets", resourceDisrectory + "/imagesets/");
			resourceProvider->setResourceGroupDirectory("schemes", resourceDisrectory + "/schemes/");
			resourceProvider->setResourceGroupDirectory("fonts", resourceDisrectory + "/fonts/");
			resourceProvider->setResourceGroupDirectory("layouts", resourceDisrectory + "/layouts/");
			resourceProvider->setResourceGroupDirectory("looknfeel", resourceDisrectory + "/looknfeel/");
			resourceProvider->setResourceGroupDirectory("lua_scripts", resourceDisrectory + "/lua_scripts/");

			CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
			CEGUI::Scheme::setDefaultResourceGroup("schemes");
			CEGUI::Font::setDefaultResourceGroup("fonts");
			CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeel");
			CEGUI::WindowManager::setDefaultResourceGroup("layouts");
			CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
		}

		m_context = &CEGUI::System::getSingleton().createGUIContext(m_renderer->getDefaultRenderTarget());
		m_rootWindow = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "root");
		m_context->setRootWindow(m_rootWindow);
	}

	void GUI::cleanup()
	{
		CEGUI::System::getSingleton().destroyGUIContext(*m_context);
	}

	void GUI::draw()
	{
		m_renderer->beginRendering();
		m_context->draw();
		m_renderer->endRendering();
		glDisable(GL_SCISSOR_TEST);
	}

	void GUI::loadScheme(const std::string& schemeFile)
	{
		CEGUI::SchemeManager::getSingleton().createFromFile(schemeFile);
	}

	void GUI::setFont(const std::string& font)
	{
		CEGUI::FontManager::getSingleton().createFromFile(font + ".font");
		m_context->setDefaultFont(font);
	}

	CEGUI::Window* GUI::createWidget(const std::string& type, const glm::vec4& destRectPerc, const glm::vec4& destRectPix, const std::string& name)
	{
		CEGUI::Window* newWindow = CEGUI::WindowManager::getSingleton().createWindow(type, name);
		setWidgetDestRect(newWindow, destRectPerc, destRectPix);
		m_rootWindow->addChild(newWindow);
		return newWindow;
	}

	void GUI::setWidgetDestRect(CEGUI::Window* window, const glm::vec4& destRectPerc, const glm::vec4& destRectPix)
	{
		window->setPosition(CEGUI::UVector2(CEGUI::UDim(destRectPerc.x, destRectPix.x), CEGUI::UDim(destRectPerc.y, destRectPix.y)));
		window->setSize(CEGUI::USize(CEGUI::UDim(destRectPerc.z, destRectPix.z), CEGUI::UDim(destRectPerc.y, destRectPix.y)));
	}
}*/