#include "menu.hpp"

#include "globals.hpp"
#include "utils.hpp"

void menu::on_first_activation()
{
	auto aimbot = std::make_unique< SettingPrimary >( "Aimbot" );
	aimbot->add_secondary< bool >( "Enable", false );
	aimbot->add_secondary< int32_t >( "FoV", 100 );
	aimbot->add_secondary< bool >( "Rage Mode", false );
	aimbot->add_secondary< bool >( "Rage Only Visible", true );

	auto visuals = std::make_unique< SettingPrimary >( "Visuals" );
	visuals->add_secondary< bool >( "Zombie ESP", false );
	visuals->add_secondary< int32_t >( "Box Width", 1 );
	visuals->add_secondary< bool >( "Snapline", false );
	visuals->add_secondary< int32_t >( "Line Width", 1 );
	visuals->add_secondary< bool >( "Health Text", false );
	//visuals->add_secondary< bool >( "Crosshair", false );

	auto player = std::make_unique< SettingPrimary >( "Player" );
	player->add_secondary< int32_t >( "Money", 500 );
	player->add_secondary< bool >( "Godmode", false );
	player->add_secondary< bool >( "Infinite Ammo", false );
	player->add_secondary< bool >( "Increased Speed", false );
	player->add_secondary< bool >( "Increased FoV", false );
	player->add_secondary< bool >( "Give Ray-Gun", false );
	player->add_secondary< bool >( "Give Thunder-Gun", false );
	//player->add_secondary< bool >( "Decreased Gravity", false );

	auto zombies = std::make_unique< SettingPrimary >( "Zombies" );
	zombies->add_secondary< bool >( "Weak Zombies", false );
	zombies->add_secondary< bool >( "Teleport Zombies to Player", false );

	auto dev = std::make_unique< SettingPrimary >( "Dev" );
	dev->add_secondary< bool >( "Enable sv_cheats", false );
	dev->add_secondary< bool >( "Show console", false );
	dev->add_secondary< bool >( "Show debug info", false );
	dev->add_secondary< bool >( "Show entity pointer", false );

	auto teleport = std::make_unique< SettingPrimary >( "Teleport" );
	teleport->add_secondary< bool >( "KdT - Power", false );
	teleport->add_secondary< bool >( "KdT - PackAPunch", false );
	teleport->add_secondary< bool >( "KdT - Airstuck", false );

	//this->m_Settings.push_back( std::move( aimbot ) );
	this->m_Settings.push_back( std::move( visuals ) );
	this->m_Settings.push_back( std::move( player ) );
	this->m_Settings.push_back( std::move( zombies ) );
	this->m_Settings.push_back( std::move( teleport ) );
	this->m_Settings.push_back( std::move( dev ) );
}

void menu::on_enable() {}

void menu::on_disable() {}

void menu::tick()
{
	if( !this->m_status )
		return;

	const auto primary_amount = this->get_amount_of_primaries();

	static int32_t last_primary_index = 0;

	SettingNone* current_setting = nullptr;

	if( this->m_SelectedPrimaryName.empty() )
		current_setting = this->m_Settings.at( this->m_SelectedIndex ).get();
	else
		current_setting = reinterpret_cast< SettingPrimary* >( this->m_Settings.at( last_primary_index ).get() )->
		                  get_secondaries_ptr()->at( this->m_SelectedIndex );

	if( utils::is_key_pressed( VK_TAB ) )
	{
		if( current_setting->is_primary() && !last_primary_index && this->m_SelectedPrimaryName.empty() &&
			reinterpret_cast< SettingPrimary* >( current_setting )->get_num_of_secondaries() > 0 )
		{
			//printf("%s is primary!\n", current_setting->get_name().c_str());
			this->m_SelectedPrimaryName = this->m_Settings.at( this->m_SelectedIndex )->get_name();

			last_primary_index = this->m_SelectedIndex;

			this->m_SelectedIndex = 0;
		}

		Sleep( 200 );
	}

	if( utils::is_key_pressed( VK_SHIFT ) && !this->m_SelectedPrimaryName.empty() )
	{
		this->m_SelectedPrimaryName = "";

		this->m_SelectedIndex = last_primary_index;

		last_primary_index = 0;

		Sleep( 200 );
	}

	if( utils::is_key_pressed( VK_DOWN ) )
	{
		if( this->m_SelectedPrimaryName.empty() )
			this->m_SelectedIndex = this->m_SelectedIndex < primary_amount - 1
				                        ? this->m_SelectedIndex + 1
				                        : this->m_SelectedIndex;
		else
			this->m_SelectedIndex = this->m_SelectedIndex < reinterpret_cast< SettingPrimary* >( this->m_Settings.
				                        at( last_primary_index ).get() )->get_num_of_secondaries() - 1
				                        ? this->m_SelectedIndex + 1
				                        : this->m_SelectedIndex;

		Sleep( 200 );
	}

	if( utils::is_key_pressed( VK_UP ) )
	{
		if( this->m_SelectedPrimaryName.empty() )
			this->m_SelectedIndex = this->m_SelectedIndex > 0 ? this->m_SelectedIndex - 1 : this->m_SelectedIndex;
		else
			this->m_SelectedIndex = this->m_SelectedIndex > 0 ? this->m_SelectedIndex - 1 : this->m_SelectedIndex;

		Sleep( 200 );
	}

	if( utils::is_key_pressed( VK_LEFT ) )
	{
		if( !this->m_SelectedPrimaryName.empty() )
		{
			//printf("decrease %s as %s\n", current_setting->get_name().c_str(), current_setting->get_type_as_str().c_str());
			if( current_setting->get_type() == ESettingType::SET_BOOL )
				reinterpret_cast< SettingBool* >( current_setting )->set_value( false );

			if( current_setting->get_type() == ESettingType::SET_INT )
				reinterpret_cast< SettingInt* >( current_setting )->set_value(
					reinterpret_cast< SettingInt* >( current_setting )->get_value() - 1
				);

			if( current_setting->get_type() == ESettingType::SET_FLOAT )
				reinterpret_cast< SettingFloat* >( current_setting )->set_value(
					reinterpret_cast< SettingFloat* >( current_setting )->get_value() - 1.f
				);

			Sleep( 200 );
		}
	}

	if( utils::is_key_pressed( VK_RIGHT ) )
	{
		if( !this->m_SelectedPrimaryName.empty() )
		{
			//printf("increase %s as %s\n", current_setting->get_name().c_str(), current_setting->get_type_as_str().c_str());
			if( current_setting->get_type() == ESettingType::SET_BOOL )
				reinterpret_cast< SettingBool* >( current_setting )->set_value( true );

			if( current_setting->get_type() == ESettingType::SET_INT )
				reinterpret_cast< SettingInt* >( current_setting )->set_value(
					reinterpret_cast< SettingInt* >( current_setting )->get_value() + 1
				);

			if( current_setting->get_type() == ESettingType::SET_FLOAT )
				reinterpret_cast< SettingFloat* >( current_setting )->set_value(
					reinterpret_cast< SettingFloat* >( current_setting )->get_value() + 1.f
				);

			Sleep( 200 );
		}
	}
}

void menu::on_render()
{
	constexpr auto off_x = 240;
	auto           off_y = 80;

	const auto mid_w = Globals::g_pOverlay->get_overlay_width() / 2;

	const auto primary_amount = this->get_amount_of_primaries();

	// draw outline
	if( this->m_SelectedPrimaryName.empty() )
	{
		const auto height = this->m_Settings.size() * 50;

		Globals::g_pOverlay->draw_filled_rect( mid_w - ( off_x / 2 ) - 15, off_y - 50, off_x * 2 + 30, height + 30, 255,
		                                       255, 120
		);
	}
	else
	{
		for( const auto& setting : this->m_Settings )
			if( setting->get_name() == this->m_SelectedPrimaryName )
			{
				const auto secondary_amount = reinterpret_cast< SettingPrimary* >( setting.get() )->
					get_num_of_secondaries();
				const auto height = secondary_amount * 50;

				if( this->m_SelectedPrimaryName == "Zombies" )
					Globals::g_pOverlay->draw_filled_rect( mid_w - ( off_x / 2 ) - 15, off_y - 50, off_x * 2 + 30,
					                                       height + 30, 255, 0, 0
					);
				else if( this->m_SelectedPrimaryName == "Visuals" )
					Globals::g_pOverlay->draw_filled_rect( mid_w - ( off_x / 2 ) - 15, off_y - 50, off_x * 2 + 30,
					                                       height + 30, 0, 255, 0
					);
				else if( this->m_SelectedPrimaryName == "Player" )
					Globals::g_pOverlay->draw_filled_rect( mid_w - ( off_x / 2 ) - 15, off_y - 50, off_x * 2 + 30,
					                                       height + 30, 255, 0, 255
					);

				else if( this->m_SelectedPrimaryName == "Dev" )
					Globals::g_pOverlay->draw_filled_rect( mid_w - ( off_x / 2 ) - 15, off_y - 50, off_x * 2 + 30,
					                                       height + 30, 20, 255, 255
					);
				else if( this->m_SelectedPrimaryName == "Teleport" )
					Globals::g_pOverlay->draw_filled_rect( mid_w - ( off_x / 2 ) - 15, off_y - 50, off_x * 2 + 30,
					                                       height + 30, 255, 100, 255
					);
			}
	}

	// draw header
	Globals::g_pOverlay->draw_filled_rect( mid_w - ( off_x / 2 ), off_y - 40, off_x * 2, 40, 150, 150, 150 );
	Globals::g_pOverlay->draw_string( "bo1-fun by cragson", mid_w + ( off_x / 2 ) - 96, off_y - 30, 0, 0, 0 );

	// if no primary was selected
	if( this->m_SelectedPrimaryName.empty() )
	{
		// draw background
		Globals::g_pOverlay->draw_filled_rect( mid_w - ( off_x / 2 ), off_y, off_x * 2, primary_amount * 50 - off_y,
		                                       200, 200, 200
		);

		// draw settings
		for( auto i = 0; i < this->m_Settings.size(); i++ )
		{
			const auto setting = this->m_Settings.at( i ).get();

			constexpr auto off_x_dot = 24;

			Globals::g_pOverlay->draw_filled_rect( mid_w - ( off_x / 2 ), off_y, off_x * 2, 20, 140, 140, 140 );

			const auto is_selected = this->m_SelectedIndex == i;

			Globals::g_pOverlay->draw_filled_rect( mid_w - ( off_x / 2 ) + 5, off_y + 5, 10, 10,
			                                       is_selected ? 255 : 200, is_selected ? 0 : 200, is_selected ? 0 : 200
			);

			Globals::g_pOverlay->draw_string( setting->get_name(), mid_w + ( off_x / 2 ) - off_x_dot, off_y, 0, 0, 0 );

			off_y += 30;
		}
	}
	else
	{
		// get selected primary
		for( auto i = 0; i < this->m_Settings.size(); i++ )
			if( this->m_Settings.at( i )->get_name() == this->m_SelectedPrimaryName )
			{
				const auto current_setting = reinterpret_cast< SettingPrimary* >( this->m_Settings.at( i ).get() );

				const auto secondary_amount = current_setting->get_num_of_secondaries();

				for( auto j = 0; j < current_setting->get_num_of_secondaries(); j++ )
				{
					const auto sec_setting = current_setting->get_secondaries_ptr()->at( j );

					// draw background
					Globals::g_pOverlay->draw_filled_rect( mid_w - ( off_x / 2 ), off_y, off_x * 2,
					                                       secondary_amount * 50 - off_y, 200, 200, 200
					);

					// draw settings
					constexpr auto off_x_dot = 100;

					Globals::g_pOverlay->draw_filled_rect( mid_w - ( off_x / 2 ), off_y, off_x * 2, 20, 140, 140, 140 );

					const auto is_selected = this->m_SelectedIndex == j;

					Globals::g_pOverlay->draw_filled_rect( mid_w - ( off_x / 2 ) + 5, off_y + 5, 10, 10,
					                                       is_selected ? 255 : 200, is_selected ? 0 : 200,
					                                       is_selected ? 0 : 200
					);

					Globals::g_pOverlay->draw_string( sec_setting->get_name(), mid_w + ( off_x / 2 ) - off_x_dot, off_y,
					                                  0, 0, 0
					);

					if( sec_setting->get_type() == ESettingType::SET_BOOL )
						Globals::g_pOverlay->draw_string(
							std::vformat( "< {} >", std::make_format_args(
								              reinterpret_cast< SettingBool* >( sec_setting )->get_value()
									              ? "true"
									              : "false"
							              )
							), mid_w + ( off_x / 2 ) + 100, off_y, 20, 20, 20
						);

					if( sec_setting->get_type() == ESettingType::SET_INT )
						Globals::g_pOverlay->draw_string(
							std::vformat(
								"< {} >", std::make_format_args(
									reinterpret_cast< SettingInt* >( sec_setting )->get_value()
								)
							), mid_w + ( off_x / 2 ) + 100, off_y, 20, 20, 20
						);

					if( sec_setting->get_type() == ESettingType::SET_FLOAT )
						Globals::g_pOverlay->draw_string(
							std::vformat( "< {.2f} >",
							              std::make_format_args(
								              reinterpret_cast< SettingFloat* >( sec_setting )->get_value()
							              )
							), mid_w + ( off_x / 2 ) + 100, off_y, 20, 20, 20
						);
					const auto test = std::vformat( "{}", std::make_format_args( sec_setting->get_type_as_str() ) );
					off_y += 30;
				}
			}
	}
}
