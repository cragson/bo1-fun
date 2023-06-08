#pragma once
#include "osmium/Cheat/Feature/feature.hpp"

class ft_hooks : public feature
{
public:

	ft_hooks() : m_bCheats{ false } {}

	void on_disable() override {}
	void on_enable() override {}
	void on_first_activation() override {}
	void on_render() override {}
	void on_shutdown() override {}
	void tick() override;

private:
	bool m_bCheats;
	bool m_bShowConsole;
};