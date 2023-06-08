#include "zm_cheat.hpp"

#include "ft_aimbot.hpp"
#include "ft_debug.hpp"
#include "ft_esp.hpp"
#include "ft_fov.hpp"
#include "ft_godmode.hpp"
#include "ft_hooks.hpp"
#include "ft_infinite_ammo.hpp"
#include "ft_money.hpp"
#include "ft_speed.hpp"
#include "ft_teleport.hpp"
#include "ft_vac.hpp"
#include "ft_weapon.hpp"
#include "globals.hpp"
#include "utils.hpp"
#include "offsets.hpp"

bool zm_cheat::setup_features()
{
	auto esp = std::make_unique< ft_esp >();
	esp->enable_drawing();
	esp->set_status( true );

	auto god = std::make_unique< ft_godmode >();
	god->disable_drawing();
	god->set_status( true );

	auto ammo = std::make_unique< ft_infinite_ammo >();
	ammo->disable_drawing();
	ammo->set_status( true );

	auto hooks = std::make_unique< ft_hooks >();
	hooks->disable_drawing();
	hooks->set_status( true );

	auto vac = std::make_unique< ft_vac >();
	vac->enable_drawing();
	vac->set_status( true );

	auto money = std::make_unique< ft_money >();
	money->disable_drawing();
	money->set_status( true );

	auto fov = std::make_unique< ft_fov >();
	fov->disable_drawing();
	fov->set_status( true );

	auto speed = std::make_unique< ft_speed >();
	speed->disable_drawing();
	speed->set_status( true );

	auto aimbot = std::make_unique< ft_aimbot >();
	aimbot->enable_drawing();
	aimbot->set_status( true );

	auto debug = std::make_unique< ft_debug >();
	debug->enable_drawing();
	debug->set_status( true );

	auto weapon = std::make_unique< ft_weapon >();
	weapon->disable_drawing();
	weapon->set_status( true );

	auto teleport = std::make_unique< ft_teleport >();
	teleport->disable_drawing();
	teleport->set_status( true );

	this->m_features.push_back( std::move( esp ) );
	this->m_features.push_back( std::move( god ) );
	this->m_features.push_back( std::move( ammo ) );
	this->m_features.push_back( std::move( hooks ) );
	this->m_features.push_back( std::move( vac ) );
	this->m_features.push_back( std::move( money ) );
	this->m_features.push_back( std::move( fov ) );
	this->m_features.push_back( std::move( speed ) );
	//this->m_features.push_back( std::move( aimbot ) );
	this->m_features.push_back( std::move( debug ) );
	this->m_features.push_back( std::move( weapon ) );
	this->m_features.push_back( std::move( teleport ) );

	Globals::g_pMenu->set_virtual_key_code( VK_INSERT );
	Globals::g_pMenu->enable_drawing();

	return true;
}

bool zm_cheat::setup_offsets()
{
	const auto game = Globals::g_pProcess->get_image_ptr_by_name( L"BlackOps.exe" );

	if( !game )
		return false;

	const auto entlist = game->find_pattern( L"BE ? ? ? ? 7E 3A", false );

	if( !entlist )
	{
		printf( "[!] Could not find entity list!\n" );

		return false;
	}

	Offsets::entity_list = game->deref_address< std::uintptr_t >( entlist + 1 );

	const auto entlist_count = game->find_pattern( L"03 F1 A3 ? ? ? ? ", false );

	if( !entlist_count )
	{
		printf( "[!] Could not find entity list count!\n" );

		return false;
	}

	Offsets::entity_list_count = game->deref_address< std::uintptr_t >( entlist_count + 3 );

	const auto rd_ptr    = game->find_pattern( L"8B 11 A1 ? ? ? ? 89 90 ? ? ? ?", false );
	const auto rd_offset = game->find_pattern( L"55 89 90 ? ? ? ?", false );

	if( !rd_ptr || !rd_offset )
	{
		printf( "[!] Could not find refdef ptr or offset!\n" );

		return false;
	}

	Offsets::refdef_ptr    = game->deref_address< std::uintptr_t >( rd_ptr + 3 );
	Offsets::refdef_offset = game->deref_address< std::uintptr_t >( rd_offset + 3 ) - 8;

	const auto hk_ammo = game->find_pattern( L"23 D1 89 50 04 C3 8B", false );

	if( !hk_ammo )
	{
		printf( "[!] Could not find hook infinite ammo!\n" );

		return false;
	}

	Offsets::hook_infinite_ammo = hk_ammo;

	const auto svcheats = game->find_pattern( L"8B 15 ? ? ? ? 80 7A 18 00 75 10 ", false );

	if( !svcheats )
	{
		printf( "[!] Could not find sv_cheats!\n" );

		return false;
	}

	Offsets::sv_cheats = game->deref_address< std::uintptr_t >( svcheats + 2 );

	const auto sh_con = game->find_pattern( L"23 4C 24 08 89 0D", false );

	if( !sh_con )
	{
		printf( "[!] Could not find sh_con!\n" );

		return false;
	}

	Offsets::show_console = game->deref_address< std::uintptr_t >( sh_con + 6 );

	const auto vac = game->find_pattern( L"A1 ? ? ? ? 8A 40 18 33 C9", false );

	if( !vac )
	{
		printf( "[!] Could not find sv_vac!\n" );

		return false;
	}

	Offsets::sv_vac = game->deref_address< std::uintptr_t >( vac + 1 );

	const auto moneyptrptr = game->find_pattern( L"A3 ? ? ? ? E8 ? ? ? ? 6A 00 A3", false );

	if( !moneyptrptr )
	{
		printf( "[!] Could not find money ptr ptr!\n" );

		return false;
	}

	Offsets::money_ptrptr = game->deref_address< std::uintptr_t >( moneyptrptr + 1 );

	const auto cg_fov = game->find_pattern( L"F3 0F 2A 57 ?", false );

	if( !cg_fov )
	{
		printf( "[!] Could not find cg_fov!\n" );

		return false;
	}

	Offsets::cg_fov = game->deref_address< std::uintptr_t >( cg_fov + 7 );

	const auto speed = game->find_pattern( L"0F 28 C1 8B 0D ? ? ? ? F3 0F 2A 49 ?", false );

	if( !speed )
	{
		printf( "[!] Could not find g_speed!\n" );

		return false;
	}

	Offsets::g_speed = game->deref_address< std::uintptr_t >( speed + 5 );

	const auto state_list = game->find_pattern( L"81 C6 ? ? ? ? 57 8B 7C 24 14", false );

	if( !state_list )
	{
		printf( "[!] Could not find entity state list!\n" );

		return false;
	}

	Offsets::entity_state_list = game->deref_address< std::uintptr_t >( state_list + 2 );

	const auto view_angles = game->find_pattern( L"F3 0F 11 14 85 ? ? ? ?", false );

	if( !view_angles )
	{
		printf( "[!] Could not find view angles!\n" );

		return false;
	}

	Offsets::view_angles = game->deref_address< std::uintptr_t >( view_angles + 5 );

	const auto snaplist = game->find_pattern( L"81 C3 ? ? ? ? 83 3B 00", false );

	if( !snaplist )
	{
		printf( "[!] Could not find snapshot_list!\n" );

		return false;
	}

	Offsets::snapshot_list = game->deref_address< std::uintptr_t >( snaplist + 2 );

	const auto currentsnap = game->find_pattern( L"89 15 ? ? ? ? 55", false );

	if( !currentsnap )
	{
		printf( "[!] Could not find current_snap!\n" );

		return false;
	}

	Offsets::current_snapshot = game->deref_address< std::uintptr_t >( currentsnap + 2 );

	const auto idk = game->find_pattern( L"53 68 ? ? ? ? 89 15 ? ? ? ? E8 ? ? ? ?", false );

	if( !idk )
	{
		printf( "[!] Could not find idk_list!\n" );

		return false;
	}

	Offsets::idk_list = game->deref_address< std::uintptr_t >( idk + 2 );

	return true;
}

void zm_cheat::print_features()
{
	printf( "\n" );

	printf( "Feature-Name -> Feature-Hotkey\n" );

	for( const auto& feature : this->m_features )
		printf( "[>] %-25ws -> %s\n", feature->get_name().c_str(),
		        utils::virtual_key_as_string( feature->get_virtual_key_code() ).c_str()
		);

	printf( "\n" );
}

void zm_cheat::print_offsets()
{
	printf( "\n" );

	const auto msg = []( const std::string& name, const std::uintptr_t value )
	{
		printf( "[>] %-35s -> 0x%08X\n", name.c_str(), value );
	};

	msg( "entitylist", Offsets::entity_list );
	msg( "entitylist_count", Offsets::entity_list_count );
	msg( "refdef_ptr", Offsets::refdef_ptr );
	msg( "refdef_offset", Offsets::refdef_offset );
	msg( "hook_infinite_ammo", Offsets::hook_infinite_ammo );
	msg( "sv_cheats", Offsets::sv_cheats );
	msg( "show_console", Offsets::show_console );
	msg( "sv_vac", Offsets::sv_vac );
	msg( "moneyptrptr", Offsets::money_ptrptr );
	msg( "cg_fov", Offsets::cg_fov );
	msg( "g_speed", Offsets::g_speed );
	msg( "entity_state_list", Offsets::entity_state_list );
	msg( "view_angles", Offsets::view_angles );
	msg( "snapshot_list", Offsets::snapshot_list );
	msg( "current_snapshot", Offsets::current_snapshot );
	msg( "idk_list", Offsets::idk_list );

	printf( "\n" );
}

void zm_cheat::run()
{
	for( const auto& feature : this->m_features )
	{
		// before tick'ing the feature, check first if the state will eventually change
		if( GetAsyncKeyState( feature->get_virtual_key_code() ) & 0x8000 )
			feature->toggle();

		// let the feature tick() when active
		if( feature->is_active() )
			feature->tick();
	}
}

void zm_cheat::shutdown()
{
	// disable every feature here
	for( const auto& feature : this->m_features )
		if( feature->is_active() )
			feature->disable();

	// clear image map here
	if( Globals::g_pProcess )
		Globals::g_pProcess->clear_image_map();
}
