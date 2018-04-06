#include "console.hpp"
#include "console_windows.hpp"

namespace Utils
{

	ConsoleAbstract * Console::m_pConsole = nullptr;

	void Console::init()
	{
		if (m_pConsole)
			return;

#ifdef _WIN32
		m_pConsole = new ConsoleWindows();
#else
		static_assert(false, "Implement a console for this platform!");
#endif
	}

	void Console::deinit()
	{
		delete m_pConsole;
		m_pConsole = nullptr;
	}

} // namespace Utils
