#include "ft_hooks.hpp"

#include "offsets.hpp"
#include "globals.hpp"

void ft_hooks::tick()
{
	if (!this->m_bCheats && Globals::g_pMenu->get_value_of_setting< bool >("Dev", "Enable sv_cheats"))
	{
		const auto ptr = Globals::g_pProcess->read< std::uintptr_t >(Offsets::sv_cheats);

		Globals::g_pProcess->write< std::uintptr_t >(ptr + 0x18, 1);

		this->m_bCheats = true;
	}

	else if (this->m_bCheats && !Globals::g_pMenu->get_value_of_setting< bool >("Dev", "Enable sv_cheats"))
	{
		const auto ptr = Globals::g_pProcess->read< std::uintptr_t >(Offsets::sv_cheats);

		Globals::g_pProcess->write< std::uintptr_t >(ptr + 0x18, 0);

		this->m_bCheats = false;
	}

	if ( !this->m_bShowConsole && Globals::g_pMenu->get_value_of_setting< bool >("Dev", "Show console"))
	{
		auto old = Globals::g_pProcess->read< std::uintptr_t >(Offsets::show_console);

		old |= 1;

		Globals::g_pProcess->write< std::uintptr_t >(Offsets::show_console,old);

		this->m_bShowConsole = true;
	}

	else if( this->m_bShowConsole && !Globals::g_pMenu->get_value_of_setting< bool >("Dev", "Show console"))
	{
		auto old = Globals::g_pProcess->read< std::uintptr_t >(Offsets::show_console);

		old &= ~1;

		Globals::g_pProcess->write< std::uintptr_t >(Offsets::show_console, old);

		this->m_bShowConsole = false;
	}

	
}
