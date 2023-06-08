#include "ft_money.hpp"

#include "offsets.hpp"
#include "globals.hpp"

void ft_money::tick()
{
	const auto ptr = Globals::g_pProcess->read< std::uintptr_t >( Offsets::money_ptrptr );

	const auto money = Globals::g_pProcess->read< int32_t >( ptr + 0xA0 );

	const auto menu_money = Globals::g_pMenu->get_value_of_setting< int32_t >( "Player", "Money" );

	if( money != menu_money )
	{
		Globals::g_pMenu->set_value_of_setting< int32_t >( "Player", "Money", menu_money + 1000 );
		Globals::g_pProcess->write< int32_t >(
			ptr + 0xA0, Globals::g_pMenu->get_value_of_setting< int32_t >( "Player", "Money" )
		);
	}
}
