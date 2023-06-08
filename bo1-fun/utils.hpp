#pragma once

#include <cstdint>

#include <Windows.h>
#include <system_error>


namespace utils
{
	inline bool is_key_pressed( const int32_t virtual_key_code )
	{
		return GetAsyncKeyState( virtual_key_code ) & 0x8000;
	}

	// cc: https://stackoverflow.com/a/38107083
	inline std::string virtual_key_as_string( const int16_t vk_code )
	{
		UINT scanCode = MapVirtualKey( vk_code, MAPVK_VK_TO_VSC );

		CHAR szName[ 128 ];
		int  result = 0;
		switch( vk_code )
		{
			case VK_LEFT:
			case VK_UP:
			case VK_RIGHT:
			case VK_DOWN:
			case VK_RCONTROL:
			case VK_RMENU:
			case VK_LWIN:
			case VK_RWIN:
			case VK_APPS:
			case VK_PRIOR:
			case VK_NEXT:
			case VK_END:
			case VK_HOME:
			case VK_INSERT:
			case VK_DELETE:
			case VK_DIVIDE:
			case VK_NUMLOCK:
				scanCode |= KF_EXTENDED;
			default:
				result = GetKeyNameTextA( scanCode << 16, szName, 128 );
		}
		if( result == 0 )
			throw std::system_error( std::error_code( GetLastError(), std::system_category() ), "WinAPI Error occured."
			);
		return szName;
	}
}
