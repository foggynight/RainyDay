#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include <chrono>
#include <cstdlib>

#include "globals.cc"
#include "Raindrop.hh"

class Rain : public olc::PixelGameEngine {
public:
	Raindrop drop_array[1];

public:
	Rain() {
		sAppName = "Rain";
	}

	bool OnUserCreate() override {
		auto duration = std::chrono::system_clock::now().time_since_epoch();
		srand(std::chrono::duration_cast<std::chrono::milliseconds>(duration).count());

		return true;
	}

	bool OnUserUpdate(float delta) override {
		Clear(olc::BLACK);
		for (auto &drop : drop_array) {
			Draw(drop.pos.x, drop.pos.y);
			drop.step(delta);
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
