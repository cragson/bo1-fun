#pragma once
#include "osmium/Cheat/Feature/feature.hpp"

class ft_esp : public feature
{
public:
	void on_first_activation() override {}
	void on_enable() override {}
	void on_disable() override {}
	void tick() override {}
	void on_shutdown() override {}
	void on_render() override;
};
