#include "ft_vac.hpp"

#include "offsets.hpp"
#include "globals.hpp"

void ft_vac::on_render()
{
	const auto ptr = Globals::g_pProcess->read< std::uintptr_t >( Offsets::sv_vac );

	if( !ptr )
		return;


	if( Globals::g_pProcess->read< int32_t >( ptr + 0x18 ) != 0 )
		Globals::g_pProcess->write< int32_t >( ptr + 0x18, 0 );

	Globals::g_pOverlay->draw_string( "VAC: DISABLED", Globals::g_pOverlay->get_overlay_width() - 300, 30, 255, 0, 0 );
}
