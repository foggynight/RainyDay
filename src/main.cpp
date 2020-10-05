#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include <chrono>
#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>

#include "globals.h"
#include "Raindrop.h"

class Rain : public olc::PixelGameEngine
{
public:
	std::vector<Raindrop> raindrop_vec;
	std::vector<olc::Pixel> color_vec;

	struct {
		bool display_ui; // Display user interface.
		int raindrops; // Number of raindrops to render.
		double acceleration; // Acceleration of the raindrops.
		int color; // Color of the raindrops.
		float cooldown; // Seconds between adding or removing a raindrop.
	} options;

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

		options.display_ui = false;
		options.raindrops = default_raindrops;
		options.acceleration = default_acceleration;
		options.color = 0;
		options.cooldown = 0.0F;

		return true;
	}

	bool OnUserUpdate(float delta) override
	{
		get_input();
		update_raindrop_vec(delta);

		Clear(olc::BLACK);
		for (auto &raindrop : raindrop_vec) {
			Draw((int)raindrop.pos.x, (int)(raindrop.pos.y-1), color_vec[options.color]);
			Draw((int)raindrop.pos.x, (int)raindrop.pos.y, color_vec[options.color]);
			raindrop.step(delta, options.acceleration);
		}

		if (options.display_ui) {
			draw_ui();
		}

		return true;
	}

	void get_input()
	{
		if (GetKey(olc::SPACE).bPressed) {
			options.display_ui = (options.display_ui) ? false : true;
		}

		if (options.raindrops < max_raindrops
		 && GetKey(olc::Key::UP).bHeld) {
			++options.raindrops;
		}
		else if (options.raindrops > 0
		 && GetKey(olc::Key::DOWN).bHeld) {
			--options.raindrops;
		}

		if (options.acceleration <= max_acceleration - 5.0F
		 && GetKey(olc::Key::RIGHT).bHeld) {
			options.acceleration += 5.0F;
		}
		else if (options.acceleration > 5.0F
		 && GetKey(olc::Key::LEFT).bHeld) {
			options.acceleration -= 5.0F;
		}

		if (GetKey(olc::Key::K1).bPressed) {
			options.color = 0;
		}
		else if (GetKey(olc::Key::K2).bPressed) {
			options.color = 1;
		}
		else if (GetKey(olc::Key::K3).bPressed) {
			options.color = 2;
		}
	}

	void update_raindrop_vec(float delta)
	{
		if ((options.cooldown += delta) >= max_cooldown) {
			if (raindrop_vec.size() < options.raindrops) {
				raindrop_vec.push_back(Raindrop());
			}
			else if (raindrop_vec.size() > options.raindrops) {
				raindrop_vec.pop_back();
			}
			options.cooldown = 0;
		}
	}

	void draw_ui()
	{
		std::ostringstream text;
		text << "Number of Drops: " << options.raindrops;
		DrawString(2, ScreenHeight()-9, text.str());

		text.clear();
		text.str(std::string());
		text << "Acceleration: " << options.acceleration;
		DrawString(200, ScreenHeight()-9, text.str());

		std::string color;
		switch (options.color) {
		case 0:
			color.assign("Red", 3);
			break;
		case 1:
			color.assign("Green", 5);
			break;
		case 2:
			color.assign("Blue", 4);
			break;
		}

		text.clear();
		text.str(std::string());
		text << "Color: " << color;
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
