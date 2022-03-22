//#define OLC_PGE_APPLICATION
//#include "olcPixelGameEngine.h"
//
//using namespace std;
//
//class Splines : public olc::PixelGameEngine
//{
//public:
//	Splines(const char* name)
//	{
//		sAppName = name;
//	}
//
//private:
//	float fBatPos = 20.0f;
//	float fBatWidth = 40.0f;
//	float fBatSpeed = float(ScreenWidth()) / 2.f;
//
//	olc::vf2d vBall = { float(ScreenWidth()) / 2.f, float(ScreenHeight()) / 2.f };
//	olc::vf2d vBallVel = { -300.f, 300.f };
//	float fBallRadius = 5.0f;
//
//public:
//	bool OnUserCreate() override
//	{
//
//		return true;
//	}
//
//	bool OnUserUpdate(float fElapsedTime) override
//	{
//		// Erase previous frame
//		Clear(olc::DARK_BLUE);
//
//		// Draw Boundary
//		DrawLine(10, 10, ScreenWidth() - 10, 10, olc::YELLOW);
//		DrawLine(10, 10, 10, ScreenHeight() - 10, olc::YELLOW);
//		DrawLine(ScreenWidth() - 10, 10, ScreenWidth() - 10, ScreenHeight() - 10, olc::YELLOW);
//
//		// Draw Bat
//		FillRect(int(fBatPos), ScreenHeight() - 20, int(fBatWidth), 10, olc::GREEN);
//
//		// Draw Ball
//		FillCircle(vBall, float(fBallRadius), olc::CYAN);
//
//		// Handle user Input
//		if (GetKey(olc::Key::LEFT).bHeld) fBatPos -= fBatSpeed * fElapsedTime;
//		if (GetKey(olc::Key::RIGHT).bHeld) fBatPos += fBatSpeed * fElapsedTime;
//
//		if (fBatPos < 11.f) fBatPos = 11.f;
//		if (fBatPos + fBatWidth > float(ScreenWidth()) - 10.0f) fBatPos = float(ScreenWidth()) - 10.0f - fBatWidth;
//
//		if (GetMouse(0).bHeld)
//		{
//			vBall = { float(GetMouseX()), float(GetMouseY()) };
//		}
//
//		if (GetMouseWheel() > 0) fBallRadius += 1.0f;
//		if (GetMouseWheel() < 0) fBallRadius -= 1.0f;
//		if (fBallRadius < 5.0f) fBallRadius = 5.0f;
//
//		// Update Ball
//		vBall += vBallVel * fElapsedTime;
//
//		// Really crude arena detection - this approach sucks
//		if (vBall.y <= 10.f) vBallVel.y *= -1;
//		if (vBall.x <= 10.f) vBallVel.x *= -1;
//		if (vBall.x > ScreenWidth() - 10) vBallVel.x *= -1;
//
//		// Check Bat
//		if (vBall.y >= (float(ScreenHeight()) - 20.0f) && (vBall.x > fBatPos) && (vBall.x < fBatPos + fBatWidth))
//			vBallVel.y *= -1.0f;
//
//		// Check if ball has gone off screen
//		else if (vBall.y > ScreenHeight())
//		{
//			// Reset ball location
//			vBall = { 200.0f, 200.0f };
//			vBallVel = { -300.f * cos(float(rand() % 180)), 300.f * sin(float(rand() % 180)) };
//		}
//
//		return true;
//	}
//};
//
//
//int Arkanoid()
//{
//	Splines demo("Spline");
//	if (demo.Construct(280, 260, 2, 2))
//		demo.Start();
//
//	return 0;
//}