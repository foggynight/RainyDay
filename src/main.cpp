/* --- rain ---
 *
 * Interactive rain simulation.
 *
 * Copyright (C) 2020 Robert Coffey
 * Released under the GPLv2 license
 */

#include <chrono>
#include <cstdlib>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include "globals.h"
#include "Raindrop.h"

class Rain : public olc::PixelGameEngine
{
private:
	std::vector<Raindrop> raindrop_vec;
	std::vector<olc::Pixel> color_vec;

	bool display_ui;     // Display user interface.
	int raindrops;       // Number of raindrops to render.
	double acceleration; // Acceleration of the raindrops.
	int color;           // Color of the raindrops.
	float cooldown;      // Seconds between adding or removing a raindrop.

public:
	Rain()
	{
		sAppName = "Rain";
	}

	bool OnUserCreate() override
	{
		auto duration = std::chrono::system_clock::now().time_since_epoch();
		srand(std::chrono::duration_cast<std::chrono::milliseconds>(duration).count());

		raindrop_vec.reserve(max_raindrops);

		color_vec.push_back(olc::RED);
		color_vec.push_back(olc::GREEN);
		color_vec.push_back(olc::BLUE);
		color_vec.push_back(olc::YELLOW);
		color_vec.push_back(olc::WHITE);

		display_ui = false;
		raindrops = default_raindrops;
		acceleration = default_acceleration;
		color = 0;
		cooldown = 0.0F;

		return true;
	}

	bool OnUserUpdate(float delta) override
	{
		get_input();
		cooldown += delta;

		Clear(olc::BLACK);
		for (auto iter = raindrop_vec.begin(); iter < raindrop_vec.end(); ++iter) {
			olc::vi2d pos = iter->pos;
			Draw((int)pos.x, (int)pos.y, color_vec[color]);

			if (pos.y > screen_h) {
				if (raindrop_vec.size() > raindrops
				 && cooldown >= max_cooldown) {
					iter = raindrop_vec.erase(iter);
					cooldown = 0;
				}
				else {
					iter->reset();
				}
			}
			else {
				iter->step(acceleration, delta);
			}
		}

		if (raindrop_vec.size() < raindrops) {
			if (cooldown >= max_cooldown) {
				raindrop_vec.push_back(Raindrop());
				cooldown = 0;
			}
		}

		if (display_ui) {
			draw_ui();
		}

		return true;
	}

private:
	void get_input()
	{
		if (GetKey(olc::SPACE).bPressed) {
			display_ui = (display_ui) ? false : true;
		}

		if (raindrops < max_raindrops
		 && GetKey(olc::Key::UP).bHeld) {
			++raindrops;
		}
		else if (raindrops > 0
		 && GetKey(olc::Key::DOWN).bHeld) {
			--raindrops;
		}

		if (acceleration <= max_acceleration - 5.0F
		 && GetKey(olc::Key::RIGHT).bHeld) {
			acceleration += 5.0F;
		}
		else if (acceleration > 5.0F
		 && GetKey(olc::Key::LEFT).bHeld) {
			acceleration -= 5.0F;
		}

		if (GetKey(olc::Key::K1).bPressed) {
			color = 0;
		}
		else if (GetKey(olc::Key::K2).bPressed) {
			color = 1;
		}
		else if (GetKey(olc::Key::K3).bPressed) {
			color = 2;
		}
		else if (GetKey(olc::Key::K4).bPressed) {
			color = 3;
		}
		else if (GetKey(olc::Key::K5).bPressed) {
			color = 4;
		}

	}

	void draw_ui()
	{
		std::ostringstream text;
		text << "Number of Drops: " << raindrops;
		DrawString(2, ScreenHeight()-9, text.str());

		text.clear();
		text.str(std::string());
		text << "Acceleration: " << acceleration;
		DrawString(200, ScreenHeight()-9, text.str());

		std::string color_str;
		switch (color) {
		case 0:
			color_str.assign("Red", 3);
			break;
		case 1:
			color_str.assign("Green", 5);
			break;
		case 2:
			color_str.assign("Blue", 4);
			break;
		case 3:
			color_str.assign("Yellow", 6);
			break;
		case 4:
			color_str.assign("White", 5);
			break;
		}

		text.clear();
		text.str(std::string());
		text << "Color: " << color_str;
		DrawString(376, ScreenHeight()-9, text.str());
	}
};

int main()
{
	Rain rain;
	if (rain.Construct(screen_w, screen_h, pixel_w, pixel_h))
		rain.Start();

	return 0;
}
