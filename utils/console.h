#pragma once
#include "console_abstract.h"

namespace Utils
{

	class Console final
	{
	public:
		static void init();
		static void deinit();
		static ConsoleAbstract * instance() { return m_pConsole; }

	private:
		static ConsoleAbstract * m_pConsole;
	};

}