#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include <chrono>
#include <cstdlib>
#include <vector>

#include "globals.cc"
#include "Raindrop.hh"

class Rain : public olc::PixelGameEngine {
public:
	std::vector<Raindrop> raindrop_vec;
	int option_raindrops;
	float cooldown;

public:
	Rain() {
		sAppName = "rainyday";

		raindrop_vec.reserve(max_raindrops);
		option_raindrops = default_raindrops;
		cooldown = 0.0F;
	}

	bool OnUserCreate() override {
		auto duration = std::chrono::system_clock::now().time_since_epoch();
		srand(std::chrono::duration_cast<std::chrono::milliseconds>(duration).count());

		return true;
	}

	bool OnUserUpdate(float delta) override {
		cooldown += delta;
		if (cooldown >= 0.3F && raindrop_vec.size() < option_raindrops) {
			raindrop_vec.push_back(Raindrop());
			raindrop_vec.push_back(Raindrop());
			cooldown = 0;
		}

		Clear(olc::BLACK);
		for (auto &raindrop : raindrop_vec) {
			Draw(raindrop.pos.x, raindrop.pos.y, olc::GREEN);
			raindrop.step(delta);
		}
		return true;
	}

	bool OnUserDestroy() override {
		return true;
	}
};

int main() {
	Rain rain;
	if (rain.Construct(screen_w, screen_h, pixel_w, pixel_h))
		rain.Start();

	return 0;
}
