#pragma once
#include <string>
#include <vector>

enum class ESettingType
{
	SET_NONE,
	SET_INT,
	SET_FLOAT,
	SET_BOOL,
	SET_PRIMARY
};

class SettingNone
{
public:
	SettingNone()
		: m_Name({})
		, m_Type(ESettingType::SET_NONE) {}

	[[nodiscard]] std::string get_name() const noexcept
	{
		return this->m_Name;
	}

	[[nodiscard]] bool is_primary() const noexcept
	{
		return this->m_Type == ESettingType::SET_PRIMARY;
	}

	[[nodiscard]] ESettingType get_type() const noexcept
	{
		return this->m_Type;
	}

	[[nodiscard]] std::string get_type_as_str() const noexcept
	{
		if (this->m_Type == ESettingType::SET_NONE)
			return "NONE";

		if (this->m_Type == ESettingType::SET_INT)
			return "INT";

		if (this->m_Type == ESettingType::SET_FLOAT)
			return "FLOAT";

		if (this->m_Type == ESettingType::SET_BOOL)
			return "BOOL";

		if (this->m_Type == ESettingType::SET_PRIMARY)
			return "PRIMARY";

		return "ERROR";
	}

	void set_name(const std::string& name) noexcept
	{
		this->m_Name = name;
	}

protected:
	std::string m_Name;
	ESettingType m_Type;
};

class SettingInt : public SettingNone
{
public:
	SettingInt() = delete;

	SettingInt(const std::string& name, const int32_t value)
	{
		this->m_Name = name;
		this->m_Value = value;
		this->m_Type = ESettingType::SET_INT;
	}

	[[nodiscard]] int32_t get_value() const noexcept
	{
		return this->m_Value;
	}

	void set_value(const int32_t value) noexcept
	{
		this->m_Value = value;
	}

private:
	int32_t m_Value;
};

class SettingFloat : public SettingNone
{
public:
	SettingFloat() = delete;

	SettingFloat(const std::string& name, const float value)
	{
		this->m_Name = name;
		this->m_Value = value;
		this->m_Type = ESettingType::SET_FLOAT;
	}

	[[nodiscard]] float get_value() const noexcept
	{
		return this->m_Value;
	}

	void set_value(const float value) noexcept
	{
		this->m_Value = value;
	}

private:
	float m_Value;
};

class SettingBool : public SettingNone
{
public:
	SettingBool() = delete;

	SettingBool(const std::string& name, const bool value)
	{
		this->m_Name = name;
		this->m_Value = value;
		this->m_Type = ESettingType::SET_BOOL;
	}

	[[nodiscard]] bool get_value() const noexcept
	{
		return this->m_Value;
	}

	void set_value(const bool value) noexcept
	{
		this->m_Value = value;
	}

private:
	bool m_Value;
};

class SettingPrimary : public SettingNone
{
public:
	SettingPrimary() = delete;

	SettingPrimary(const std::string& name)
	{
		this->m_Name = name;
		this->m_Type = ESettingType::SET_PRIMARY;
		this->m_Secondaries = {};
	}

	[[nodiscard]] size_t get_num_of_secondaries() const noexcept
	{
		return this->m_Secondaries.size();
	}

	[[nodiscard]] auto get_secondaries_ptr() noexcept
	{
		return &this->m_Secondaries;
	}

	template< typename T >
	bool add_secondary(const std::string& name, const T value)
	{
		if (std::is_same_v< T, int32_t >)
		{
			this->m_Secondaries.push_back(new SettingInt(name, value));

			return true;
		}

		if (std::is_same_v< T, float >)
		{
			this->m_Secondaries.push_back(new SettingFloat(name, value));

			return true;
		}

		if (std::is_same_v< T, bool >)
		{
			this->m_Secondaries.push_back(new SettingBool(name, value));

			return true;
		}

		return false;
	}

private:
	std::vector< SettingNone* > m_Secondaries;
};