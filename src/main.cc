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
	std::vector<olc::Pixel> color_vec;

	int option_raindrops; // Number of raindrops to render.
	double option_acceleration; // Acceleration of the raindrops.
	int option_color; // Color of the raindrops.
	float cooldown; // Seconds between adding or removing a raindrop.

public:
	Rain() {
		sAppName = "rainyday";
	}

	bool OnUserCreate() override {
		auto duration = std::chrono::system_clock::now().time_since_epoch();
		srand(std::chrono::duration_cast<std::chrono::milliseconds>(duration).count());

		raindrop_vec.reserve(max_raindrops);

		color_vec.push_back(olc::RED);
		color_vec.push_back(olc::GREEN);
		color_vec.push_back(olc::BLUE);

		option_raindrops = default_raindrops;
		option_acceleration = default_acceleration;
		option_color = 0;
		cooldown = 0.0F;

		return true;
	}

	bool OnUserUpdate(float delta) override {
		get_options();
		update_raindrop_vec(delta);

		Clear(olc::BLACK);
		for (auto &raindrop : raindrop_vec) {
			Draw(raindrop.pos.x, raindrop.pos.y, color_vec[option_color]);
			raindrop.step(delta, option_acceleration);
		}

		return true;
	}

	bool OnUserDestroy() override {
		return true;
	}

	void get_options() {
		if (option_raindrops < max_raindrops
		 && GetKey(olc::Key::UP).bHeld) {
			++option_raindrops;
		} else if (option_raindrops > 0
		 && GetKey(olc::Key::DOWN).bHeld) {
			--option_raindrops;
		}

		if (option_acceleration <= max_acceleration - 5.0F
		 && GetKey(olc::Key::RIGHT).bHeld) {
			option_acceleration += 5.0F;
		} else if (option_acceleration > 5.0F
		 && GetKey(olc::Key::LEFT).bHeld) {
			option_acceleration -= 5.0F;
		}

		if (GetKey(olc::Key::K1).bHeld) {
			option_color = 0;
		} else if (GetKey(olc::Key::K2).bHeld) {
			option_color = 1;
		} else if (GetKey(olc::Key::K3).bHeld) {
			option_color = 2;
		}
	}

	void update_raindrop_vec(float delta) {
		if ((cooldown += delta) >= default_cooldown) {
			if (raindrop_vec.size() < option_raindrops) {
				raindrop_vec.push_back(Raindrop());
			} else if (raindrop_vec.size() > option_raindrops) {
				raindrop_vec.pop_back();
			}
			cooldown = 0;
		}
	}
};

int main() {
	Rain rain;
	if (rain.Construct(screen_w, screen_h, pixel_w, pixel_h))
		rain.Start();

	return 0;
}
