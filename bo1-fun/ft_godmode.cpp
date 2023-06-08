#include "ft_godmode.hpp"

#include "game_structs.hpp"
#include "globals.hpp"
#include "offsets.hpp"

void ft_godmode::tick()
{
	if( Globals::g_pMenu->get_value_of_setting< bool >( "Player", "Godmode" ) )
	{
		const auto player_ptr = Offsets::entity_list;

		Globals::g_pProcess->write< int32_t >( player_ptr + offsetof( entity, m_iMaximumHealth ), 250 );

		Globals::g_pProcess->write< int32_t >( player_ptr + offsetof( entity, m_iHealth ), 250 );
	}
}
