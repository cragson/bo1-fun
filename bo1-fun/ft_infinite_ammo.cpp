#include "ft_infinite_ammo.hpp"

#include "offsets.hpp"
#include "globals.hpp"

void ft_infinite_ammo::tick()
{
	if( Globals::g_pMenu->get_value_of_setting< bool >( "Player", "Infinite Ammo" ) && Globals::g_pProcess->
		get_hook_ptr_by_address( Offsets::hook_infinite_ammo ) == nullptr )
	{
		// C7 40 04 A4 01 00 00 - mov [ eax + 04 ],000001A4
		if( Globals::g_pProcess->create_hook_x86( Offsets::hook_infinite_ammo, 5,
		                                          { 0xC7, 0x40, 0x04, 0xA4, 0x01, 0x00, 0x00 }
		) )
			printf( "[+] Created infinite ammo hook!\n" );
		else
			printf( "[!] Could not create infinite ammo hook!\n" );
	}

	else if( !Globals::g_pMenu->get_value_of_setting< bool >( "Player", "Infinite Ammo" ) && Globals::g_pProcess->
		get_hook_ptr_by_address( Offsets::hook_infinite_ammo ) != nullptr )
	{
		if( Globals::g_pProcess->destroy_hook_x86( Offsets::hook_infinite_ammo ) )
			printf( "[+] Unhooked infinite ammo hook!\n" );
		else
			printf( "[!] Could not unhook infinite ammo hook!\n" );
	}
}
