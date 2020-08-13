#include <chrono>
#include <cstdlib>

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class Rain : public olc::PixelGameEngine {
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
		return true;
	}

	bool OnUserDestroy() override {
		return true;
	}
};

int main() {
	Rain rain;
	if (rain.Construct(256, 240, 4, 4))
		rain.Start();

	return 0;
}
