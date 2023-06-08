#include "zm_overlay.hpp"
#include "globals.hpp"

#include "offsets.hpp"

#include "utils.hpp"

void zm_overlay::render()
{
	this->m_Device->BeginScene();

	const auto fg_hwnd = GetForegroundWindow();

	if( fg_hwnd == this->m_TargetWindow )
	{
		this->draw_rect( 10, 20, 134, 21, 255, 0, 0 );

		this->draw_string( "osmium: BO1 Fun", 12, 22, 255, 255, 255 );

		if( utils::is_key_pressed( Globals::g_pMenu->get_virtual_key_code() ) )
		{
			Globals::g_pMenu->toggle();

			Sleep( 150 );
		}

		if( Globals::g_pMenu->is_active() )
			Globals::g_pMenu->on_render();

		const auto features = Globals::g_pCheat->get_features_as_ptr();

		for( auto it = features->begin(); it != features->end(); ++it )
		{
			const auto current_feature = it->get();

			if( !current_feature->should_be_drawn() )
				continue;

			if( current_feature->is_active() )
			{
				current_feature->on_render();

				Sleep( 1 );
			}
		}
	}

	this->m_Device->EndScene();
	this->m_Device->PresentEx( nullptr, nullptr, nullptr, nullptr, NULL );
	this->m_Device->Clear( NULL, nullptr, D3DCLEAR_TARGET, D3DCOLOR_ARGB( 0, 0, 0, 0 ), 1.0f, NULL );
}
