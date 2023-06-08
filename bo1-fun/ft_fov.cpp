#include "ft_fov.hpp"

#include "offsets.hpp"
#include "globals.hpp"


void ft_fov::tick()
{
	const auto fov_ptr = Globals::g_pProcess->read< std::uintptr_t >( Offsets::cg_fov );

	const auto fov = Globals::g_pProcess->read< float >( fov_ptr + 0x18 );

	if( Globals::g_pMenu->get_value_of_setting< bool >( "Player", "Increased FoV" ) && fov != 105.f )
	{
		Globals::g_pProcess->write< float >( fov_ptr + 0x18, 105.f );
	}
	else if( !Globals::g_pMenu->get_value_of_setting< bool >( "Player", "Increased FoV" ) && fov != 65.f )
	{
		Globals::g_pProcess->write< float >( fov_ptr + 0x18, 65.f );
	}
}
