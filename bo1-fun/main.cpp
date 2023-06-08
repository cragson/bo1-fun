#include <iostream>
#include "globals.hpp"

int main()
{
	SetConsoleTitleA( "osmium: BO1 Fun" );

	printf( "[>] Waiting for the game.." );

	while( !Globals::g_pProcess->setup_process( L"BlackOps.exe" ) )
		Sleep( 420 );

	printf( "done!\n" );

	printf( "[>] Preparing the cheat.." );

	while( !Globals::g_pCheat->setup_offsets() )
		Sleep( 420 );

	while( !Globals::g_pCheat->setup_features() )
		Sleep( 420 );

	printf( "done!\n" );

	Globals::g_pCheat->print_offsets();

	printf( "[>] Preparing the overlay.." );

	while( !Globals::g_pOverlay->initialize( Globals::g_pProcess->get_window_handle() ) )
		Sleep( 420 );

	printf( "done!\n" );

	printf( "\n[!] Press INSERT to open the menu.\n" );

	printf( "Have fun! ;-)\n" );

	while( 0xDEAD != 0xAFFE )
	{
		if( GetAsyncKeyState( VK_END ) & 0x8000 )
			break;

		Globals::g_pCheat->run();

		if( Globals::g_pMenu->is_active() )
			Globals::g_pMenu->tick();

		Sleep( 1 );
	}

	Globals::g_pCheat->shutdown();

	printf( "Goodbye!\n" );

	Sleep( 3000 );

	return EXIT_SUCCESS;
}
