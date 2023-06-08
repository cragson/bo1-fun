#include "ft_debug.hpp"

#include "game_structs.hpp"
#include "offsets.hpp"
#include "globals.hpp"

void ft_debug::on_render()
{
	if( !Globals::g_pMenu->get_value_of_setting< bool >( "Dev", "Show debug info" ) )
		return;

	const auto overlay_width  = Globals::g_pOverlay->get_overlay_width();
	const auto overlay_height = Globals::g_pOverlay->get_overlay_height();

	const auto current_snapshot = Globals::g_pProcess->read< uint32_t >( Offsets::current_snapshot );
	Globals::g_pOverlay->draw_string(
		std::vformat( "Current snapshot: {}({})", std::make_format_args( current_snapshot, current_snapshot & 0xF ) ),
		overlay_width - overlay_height / 4, 60, 255, 255, 0
	);

	Globals::g_pOverlay->draw_string(
		std::vformat( "Localplayer: {:#8x}", std::make_format_args( Offsets::entity_list ) ),
		overlay_width - overlay_height / 4, 75, 255, 255, 0
	);

	const auto is_enemy_in_crosshair = Globals::g_pProcess->read< int32_t >(
		Offsets::entity_state_list + offsetof( entity_state, m_iAction )
	) & ACTION_STATE_ENTITY_IN_CROSSHAIR;
	Globals::g_pOverlay->draw_string(
		std::vformat( "Enemy in Crosshair: {}", std::make_format_args( is_enemy_in_crosshair ? "YES" : "NO" ) ),
		overlay_width - overlay_height / 4, 90, 255, 255, 0
	);

	const auto enemy_count = Globals::g_pProcess->read< int32_t >( Offsets::entity_list_count );
	Globals::g_pOverlay->draw_string( std::vformat( "Existing objects: {}", std::make_format_args( enemy_count ) ),
	                                  overlay_width - overlay_height / 4, 105, 255, 255, 0
	);

	const auto player_pos = Globals::g_pProcess->read<
		Vector3 >( Offsets::entity_list + offsetof( entity, m_vecPos1 ) );
	Globals::g_pOverlay->draw_string(
		std::vformat( "X: {:.2f} Y: {:.2f} Z: {:.2f}", std::make_format_args( player_pos.x, player_pos.y, player_pos.z )
		), overlay_width - overlay_height / 4, 120, 255, 255, 0
	);
}
