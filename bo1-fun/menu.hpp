#pragma once
#include "osmium/Cheat/Feature/feature.hpp"
#include "settings.hpp"

class menu : public feature
{
public:
	void on_first_activation() override;
	void on_enable() override;
	void on_disable() override;

	void tick() override;
	void on_render() override;
	void on_shutdown() override {}


	[[nodiscard]] size_t get_amount_of_primaries() const noexcept
	{
		if( this->m_Settings.empty() )
			return {};

		size_t ret = 0;

		for( const auto& setting : this->m_Settings )
			if( setting->is_primary() )
				ret++;

		return ret;
	}

	template< typename T >
	[[nodiscard]] T get_value_of_setting( const std::string& primary, const std::string& secondary )
	{
		if( primary.empty() || secondary.empty() )
			return T();

		for( const auto& setting : this->m_Settings )
		{
			if( setting->get_type() == ESettingType::SET_PRIMARY && setting->get_name() == primary )
			{
				const auto prim = reinterpret_cast< SettingPrimary* >( setting.get() );

				for( const auto& sec : *prim->get_secondaries_ptr() )
				{
					if( sec->get_name() == secondary )
					{
						if( sec->get_type() == ESettingType::SET_BOOL )
							return reinterpret_cast< SettingBool* >( sec )->get_value();

						if( sec->get_type() == ESettingType::SET_INT )
							return reinterpret_cast< SettingInt* >( sec )->get_value();

						if( sec->get_type() == ESettingType::SET_FLOAT )
							return reinterpret_cast< SettingFloat* >( sec )->get_value();
					}
				}
			}
		}
		return T();
	}

	template< typename T >
	void set_value_of_setting( const std::string& primary, const std::string& secondary, const T& value )
	{
		if( primary.empty() || secondary.empty() )
			return;

		for( const auto& setting : this->m_Settings )
		{
			if( setting->get_type() == ESettingType::SET_PRIMARY && setting->get_name() == primary )
			{
				const auto prim = reinterpret_cast< SettingPrimary* >( setting.get() );

				for( const auto& sec : *prim->get_secondaries_ptr() )
				{
					if( sec->get_name() == secondary )
					{
						if( sec->get_type() == ESettingType::SET_BOOL )
							reinterpret_cast< SettingBool* >( sec )->set_value( value );

						if( sec->get_type() == ESettingType::SET_INT )
							reinterpret_cast< SettingInt* >( sec )->set_value( value );

						if( sec->get_type() == ESettingType::SET_FLOAT )
							reinterpret_cast< SettingFloat* >( sec )->set_value( value );
					}
				}
			}
		}
	}

private:
	std::vector< std::unique_ptr< SettingNone > > m_Settings;

	int32_t m_SelectedIndex;

	std::string m_SelectedPrimaryName;

	bool m_PrimaryOpen;
};
