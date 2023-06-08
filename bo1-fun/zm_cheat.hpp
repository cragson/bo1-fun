#pragma once
#include "osmium/Cheat/cheat.hpp"

class zm_cheat : public cheat
{
public:
	[[nodiscard]] bool setup_features() override;

	[[nodiscard]] bool setup_offsets() override;

	void print_features() override;

	void print_offsets() override;

	void run() override;

	void shutdown() override;
};
