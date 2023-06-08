#pragma once

#include "menu.hpp"
#include "osmium/Memory/Process/process.hpp"

#include "zm_cheat.hpp"

#include "zm_overlay.hpp"

namespace Globals
{
	inline auto g_pProcess = std::make_unique< process >();

	inline auto g_pCheat = std::make_unique< zm_cheat >();

	inline auto g_pOverlay = std::make_unique< zm_overlay >();

	inline auto g_pMenu = std::make_unique< menu >();
}
