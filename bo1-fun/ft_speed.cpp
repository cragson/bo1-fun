#include "ft_speed.hpp"

#include "offsets.hpp"
#include "globals.hpp"

void ft_speed::tick()
{
	const auto speed_ptr = Globals::g_pProcess->read< std::uintptr_t >( Offsets::g_speed );

	const auto speed = Globals::g_pProcess->read< int32_t >( speed_ptr + 0x18 );

	if( Globals::g_pMenu->get_value_of_setting< bool >( "Player", "Increased Speed" ) && speed != 420 )
	{
		Globals::g_pProcess->write< int32_t >( speed_ptr + 0x18, 420 );
	}
	else if( !Globals::g_pMenu->get_value_of_setting< bool >( "Player", "Increased Speed" ) && speed != 190 )
	{
		Globals::g_pProcess->write< int32_t >( speed_ptr + 0x18, 190 );
	}
}
