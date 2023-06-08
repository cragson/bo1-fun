#include "ft_teleport.hpp"

#include "game_structs.hpp"
#include "offsets.hpp"
#include "globals.hpp"

void ft_teleport::tick()
{
	if( Globals::g_pMenu->get_value_of_setting< bool >( "Teleport", "KdT - Power" ) )
	{
		Globals::g_pProcess->write< Vector3 >( Offsets::idk_list + 0x24, { -481.f, 1268.f, -16.f } );

		Globals::g_pMenu->set_value_of_setting< bool >( "Teleport", "KdT - Power", false );

		Sleep( 250 );
	}

	if( Globals::g_pMenu->get_value_of_setting< bool >( "Teleport", "KdT - PackAPunch" ) )
	{
		Globals::g_pProcess->write< Vector3 >( Offsets::idk_list + 0x24, { 9.f, -417.f, 320.f } );

		Globals::g_pMenu->set_value_of_setting< bool >( "Teleport", "KdT - PackAPunch", false );

		Sleep( 250 );
	}

	if( Globals::g_pMenu->get_value_of_setting< bool >( "Teleport", "KdT - Airstuck" ) )
	{
		Globals::g_pProcess->write< Vector3 >( Offsets::idk_list + 0x24, { -1, 940.f, 86.f } );

		Globals::g_pMenu->set_value_of_setting< bool >( "Teleport", "KdT - Airstuck", false );

		Sleep( 250 );
	}
}
