#pragma once
#include <cstdint>
#include <unordered_map>

class Vector2
{
public:
	float x, y;
};

class Vector3
{
public:
	float x, y, z;

	float get_magnitude() const noexcept
	{
		return sqrtf( powf( this->x, 2 ) + powf( this->y, 2 ) + powf( this->z, 2 ) );
	}

	Vector3 get_normalized() const noexcept
	{
		const float magnitude = this->get_magnitude();

		return { this->x / magnitude, this->y / magnitude, this->z / magnitude };
	}

	void multiply( const Vector3& target )
	{
		this->x *= target.x;
		this->y *= target.y;
		this->z *= target.z;
	}
};

class Matrix3x3
{
public:
	Vector3 a, b, c;
};

class refdef_t
{
public:
	int32_t   m_iX; //0x0000
	int32_t   m_iY; //0x0004
	int32_t   m_iWidth; //0x0008
	int32_t   m_iHeight; //0x000C
	Vector2   m_vecFov; //0x0010
	char      pad_0018[ 8 ]; //0x0018
	Vector3   m_vecPos; //0x0020
	char      pad_002C[ 8 ]; //0x002C
	Matrix3x3 m_mViewMatrix; //0x0034
	char      pad_0058[ 52 ]; //0x0058
}; //Size: 0x008C

class entity
{
public:
	char    pad_0000[ 4 ]; //0x0000
	int32_t m_iState; //0x0004
	char    pad_0008[ 16 ]; //0x0008
	Vector3 m_vecPos1; //0x0018
	char    pad_0024[ 24 ]; //0x0024
	Vector2 idk1; //0x003C
	char    pad_0044[ 68 ]; //0x0044
	int32_t m_iClientNum; //0x0088
	char    pad_008C[ 50 ]; //0x008C
	int16_t m_iEntityType; //0x00BE
	char    pad_00C0[ 68 ]; //0x00C0
	Vector3 m_vecPos2; //0x0104
	Vector3 m_VecPos3; //0x0110
	Vector3 m_vecPos4; //0x011C
	char    pad_0128[ 92 ]; //0x0128
	int32_t m_iHealth; //0x0184
	int32_t m_iMaximumHealth; //0x0188
	char    pad_018C[ 448 ]; //0x018C
}; //Size: 0x034C

class entity_state
{
public:
	Vector3 m_vecPos; //0x0000
	Vector2 m_vecAngles; //0x000C
	char    pad_0014[ 16 ]; //0x0014
	int32_t m_iMovementState; //0x0024
	char    pad_0028[ 8 ]; //0x0028
	int32_t m_iAction; //0x0030
	char    pad_0034[ 4 ]; //0x0034
	float   m_flZoom; //0x0038
	char    pad_003C[ 3700 ]; //0x003C
}; //Size: 0x0EB0

inline constexpr auto ACTION_STATE_ENTITY_IN_CROSSHAIR = 1 << 4;

inline std::unordered_map< int32_t, std::string > entity_types = {
	{ 0, "ET_GENERAL" }, { 1, "ET_PLAYER" }, { 2, "ET_PLAYER_CORSPE" }, { 3, "ET_ITEM" }, { 4, "ET_MISSLE" },
	{ 5, "ET_INVISIBLE" }, { 6, "ET_SCRIPTMOVER" }, { 7, "ET_SOUND_BLEND" }, { 8, "ET_FX" }, { 9, "ET_LOOP_FX" },
	{ 10, "ET_PRIMARY_LIGHT" }, { 11, "ET_MG42" }, { 12, "ET_PLANE" }, { 13, "ET_VEHICLE" },
	{ 14, "ET_VEHICLE_CORPSE" }, { 15, "ET_VEHICLE_COLLMAP" }, { 16, "ET_ACTOR" }, { 17, "ET_ACTOR_SPAWNER" },
	{ 18, "ET_ACTOR_CORPSE" }, { 19, "ET_STREAMER_HINT" },
};

inline constexpr auto WEAPON_ID_RAYGUN_UPGRADED       = 72;
inline constexpr auto WEAPON_ID_DICKE_KANONE_UPGRADED = 73;
