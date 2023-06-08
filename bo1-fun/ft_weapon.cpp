#include "ft_weapon.hpp"

#include "offsets.hpp"
#include "globals.hpp"
#include "game_structs.hpp"

void ft_weapon::tick()
{
	if( Globals::g_pMenu->get_value_of_setting< bool >( "Player", "Give Ray-Gun" ) )
	{
		const auto current_id = Globals::g_pProcess->read< int32_t >( Offsets::idk_list + 0x144 );

		const auto primary_id = Globals::g_pProcess->read< int32_t >( Offsets::idk_list + 0x1F4 );

		if( current_id != primary_id )
			Globals::g_pProcess->write< int32_t >( Offsets::idk_list + 0x1F4, WEAPON_ID_RAYGUN_UPGRADED );
		else
			Globals::g_pProcess->write< int32_t >( Offsets::idk_list + 0x224, WEAPON_ID_RAYGUN_UPGRADED );


		Globals::g_pMenu->set_value_of_setting< bool >( "Player", "Give Ray-Gun", false );

		Sleep( 200 );
	}

	if( Globals::g_pMenu->get_value_of_setting< bool >( "Player", "Give Thunder-Gun" ) )
	{
		const auto current_id = Globals::g_pProcess->read< int32_t >( Offsets::idk_list + 0x144 );

		const auto primary_id = Globals::g_pProcess->read< int32_t >( Offsets::idk_list + 0x1F4 );

		if( current_id != primary_id )
			Globals::g_pProcess->write< int32_t >( Offsets::idk_list + 0x1F4, WEAPON_ID_DICKE_KANONE_UPGRADED );
		else
			Globals::g_pProcess->write< int32_t >( Offsets::idk_list + 0x224, WEAPON_ID_DICKE_KANONE_UPGRADED );

		Globals::g_pMenu->set_value_of_setting< bool >( "Player", "Give Thunder-Gun", false );

		Sleep( 200 );
	}
}
