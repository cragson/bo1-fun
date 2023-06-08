#pragma once
#include "game_structs.hpp"
#include "globals.hpp"
#include "offsets.hpp"


namespace EngineMath
{
	[[nodiscard]] inline bool world_to_screen( Vector3 world, Vector2& screen )
	{
		const auto ptr    = Globals::g_pProcess->read< std::uintptr_t >( Offsets::refdef_ptr );
		const auto refdef = ptr + Offsets::refdef_offset;

		const auto player_pos = Globals::g_pProcess->read< Vector3 >( refdef + offsetof( refdef_t, m_vecPos ) );

		const float delta_x = world.x - player_pos.x;
		const float delta_y = world.y - player_pos.y;
		const float delta_z = world.z - player_pos.z;

		const Vector3 Delta = { delta_x, delta_y, delta_z };

		const auto matrix = Globals::g_pProcess->read< Matrix3x3 >( refdef + offsetof( refdef_t, m_mViewMatrix ) );

		constexpr auto DotProduct = []( Vector3 a, Vector3 b )
		{
			return a.x * b.x + a.y * b.y + a.z * b.z;
		};

		const auto trans_x = DotProduct( Delta, matrix.b );
		const auto trans_y = DotProduct( Delta, matrix.c );
		const auto trans_z = DotProduct( Delta, matrix.a );

		if( trans_z < 0.1f )
			return false;

		const auto center_x = Globals::g_pOverlay->get_overlay_width() / 2;
		const auto center_y = Globals::g_pOverlay->get_overlay_height() / 2;

		const auto fov = Globals::g_pProcess->read< Vector2 >( refdef + offsetof( refdef_t, m_vecFov ) );

		screen.x = center_x * ( 1.f - ( trans_x / fov.x ) / trans_z );
		screen.y = center_y * ( 1.f - ( trans_y / fov.y ) / trans_z );

		return true;
	}

	[[nodiscard]] inline float entity_distance_to_player( Vector3 entity_pos )
	{
		const auto ptr    = Globals::g_pProcess->read< std::uintptr_t >( Offsets::refdef_ptr );
		const auto refdef = ptr + Offsets::refdef_offset;

		const auto player_pos = Globals::g_pProcess->read< Vector3 >( refdef + offsetof( refdef_t, m_vecPos ) );

		const float delta_x = entity_pos.x - player_pos.x;
		const float delta_y = entity_pos.y - player_pos.y;
		const float delta_z = entity_pos.z - player_pos.z;

		return sqrtf( delta_x * delta_x + delta_y * delta_y + delta_z * delta_z );
	}
}
