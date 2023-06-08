#include "ft_esp.hpp"

#include "engine_math.hpp"
#include "game_structs.hpp"
#include "offsets.hpp"
#include "globals.hpp"

void ft_esp::on_render()
{
	const auto ent_count = Globals::g_pProcess->read< uint32_t >( Offsets::entity_list_count );


	if( ent_count > 0 )
	{
		for( int32_t idx = 0; idx < ent_count; idx++ )
		{
			// draw crosshair
			if( Globals::g_pMenu->get_value_of_setting< bool >( "Visuals", "Crosshair" ) )
			{
				const auto mid_w = Globals::g_pOverlay->get_overlay_width() / 2;
				const auto mid_h = Globals::g_pOverlay->get_overlay_height() / 2;

				Globals::g_pOverlay->draw_line( mid_w, mid_h - 10, mid_w, mid_h + 10, 255, 0, 0 );
				Globals::g_pOverlay->draw_line( mid_w - 10, mid_h, mid_w + 10, mid_h, 255, 0, 0 );
			}

			const auto ent_ptr = Offsets::entity_list + idx * sizeof( entity );
			const auto ent     = Globals::g_pProcess->read< entity >( ent_ptr );

			if( ent.m_iEntityType >= entity_types.size() || ent.m_iHealth <= 0 )
				continue;

			const auto type = entity_types.at( ent.m_iEntityType );

			if( type != "ET_ACTOR" )
				continue;

			if( Globals::g_pMenu->get_value_of_setting< bool >( "Zombies", "Weak Zombies" ) )
			{
				Globals::g_pProcess->write< int32_t >( ent_ptr + offsetof( entity, m_iHealth ), 1 );
				Globals::g_pProcess->write< int32_t >( ent_ptr + offsetof( entity, m_iMaximumHealth ), 1 );
			}


			Vector2 screen_pos, screen_pos2 = { 0.f, 0.f };

			if( EngineMath::world_to_screen( ent.m_vecPos1, screen_pos ) && EngineMath::world_to_screen(
				ent.m_VecPos3, screen_pos2
			) )
			{
				const auto height = static_cast< int32_t >( abs( screen_pos2.y - screen_pos.y ) );

				const auto width = height / 2 > 75 ? 75 : height / 2;

				// draw esp box
				if( Globals::g_pMenu->get_value_of_setting< bool >( "Visuals", "Zombie ESP" ) )
					Globals::g_pOverlay->draw_rect( screen_pos.x - width / 2, screen_pos.y - height, width, height, 255,
					                                0, 255, Globals::g_pMenu->get_value_of_setting< int32_t >(
						                                "Visuals", "Box Width"
					                                )
					);

				// draw snaplines
				if( Globals::g_pMenu->get_value_of_setting< bool >( "Visuals", "Snapline" ) )
				{
					const auto overlay_height = Globals::g_pOverlay->get_overlay_height();

					Globals::g_pOverlay->draw_line( Globals::g_pOverlay->get_overlay_width() / 2, overlay_height,
					                                screen_pos.x, screen_pos.y, 0, 255, 255,
					                                Globals::g_pMenu->get_value_of_setting< int32_t >(
						                                "Visuals", "Line Width"
					                                )
					);
				}

				// draw health text
				if( Globals::g_pMenu->get_value_of_setting< bool >( "Visuals", "Health Text" ) )
					Globals::g_pOverlay->draw_string(
						std::vformat( "{}/{}", std::make_format_args( ent.m_iHealth, ent.m_iMaximumHealth ) ),
						screen_pos.x + ( width * 1.f / 1.5f ), screen_pos2.y, 255, 0, 0
					);

				// draw debug entity ptr
				if( Globals::g_pMenu->get_value_of_setting< bool >( "Dev", "Show entity pointer" ) )
					Globals::g_pOverlay->draw_string( std::vformat( "{:#8x}", std::make_format_args( ent_ptr ) ),
					                                  screen_pos.x + ( width * 1.f / 1.5f ), screen_pos2.y + 15, 255,
					                                  255, 0
					);

				if( Globals::g_pMenu->get_value_of_setting< bool >( "Zombies", "Teleport Zombies to Player" ) )
				{
					auto player_pos = Globals::g_pProcess->read< Vector3 >(
						Offsets::entity_list + offsetof( entity, m_vecPos1 )
					);
					player_pos.x += 250.f;

					if( idx > 0 )
					{
						Globals::g_pProcess->write< Vector3 >( ent_ptr + offsetof( entity, m_vecPos4 ), player_pos );
					}
				}

				//Globals::g_pOverlay->draw_string(std::vformat("Type: {}", std::make_format_args(  type ) ), screen_pos.x, screen_pos.y + 10, 255, 0, 0);

				//printf( "[+] Drawed %08X\n", ent_ptr );
			}
		}
	}
}
