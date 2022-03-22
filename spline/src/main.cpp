#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <string>

using namespace std;

struct sPoint2D
{
	float x, y;
};

struct sSpline
{
	vector<sPoint2D> points;

	sPoint2D GetSplinePoint(float t, bool bLooped = false)
	{
		int p0, p1, p2, p3;

		if (!bLooped) 
		{
			p1 = (int)t + 1;
			p2 = p1 + 1;
			p3 = p2 + 1;
			p0 = p1 - 1;
		}

		else 
		{
			p1 = (int)t;
			p2 = (p1 + 1) % points.size();
			p3 = (p2 + 1) % points.size();
			p0 = p1 >= 1 ? p1 - 1 : points.size() - 1;
		}

		t = t - (int)t;

		float tt = t * t;
		float ttt = tt * t;

		// Fields of Influence
		float q1 = -ttt + 2.f * tt - t;
		float q2 = 3.f * ttt - 5.f * tt + 2.f;
		float q3 = -3.f * ttt + 4.f * tt + t;
		float q4 = ttt - tt;

		float tx = 0.5f * (points[p0].x * q1 + points[p1].x * q2 + points[p2].x * q3 + points[p3].x * q4);
		float ty = 0.5f * (points[p0].y * q1 + points[p1].y * q2 + points[p2].y * q3 + points[p3].y * q4);

		return { tx, ty };
	}
};

class Spline : public olc::PixelGameEngine
{
public:
	Spline()
	{
		sAppName = "Splines";
	}

private:
	sSpline path;

	int nSelectedPoint = 0;

public:
	bool OnUserCreate() override
	{
		path.points = { {10, 41}, {30, 41}, {50, 41}, {70,41}, {90, 41}, {110, 41}, {130,41}, {150, 41}, {170, 41}, {190, 41} };

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Clear Screen
		Clear(olc::VERY_DARK_BLUE);

		// Handle Input
		if (GetKey(olc::Key::X).bReleased)
		{
			nSelectedPoint++;
			if (nSelectedPoint >= path.points.size())
				nSelectedPoint = 0;
		}
		if (GetKey(olc::Key::Z).bReleased)
		{
			nSelectedPoint--;
			if (nSelectedPoint < 0)
				nSelectedPoint = path.points.size()-1;
		}
		if (GetMouse(1).bPressed)
		{
			for (int i = 0; i < path.points.size(); ++i)
			{
				if (GetMouseX() >= path.points[i].x - 2.01f && GetMouseX() <= path.points[i].x + 2.01f)
				{
					if (GetMouseY() >= path.points[i].y - 2.01f && GetMouseY() <= path.points[i].y + 2.01f)
					{
						nSelectedPoint = i;
						break;
					}
				}
			}
		}
		if (GetMouse(0).bHeld)
		{
			path.points[nSelectedPoint] = { float(GetMouseX()), float(GetMouseY()) };
		}



		// Draw Spline
		for (float t = 0.f; t < path.points.size()-3; t += 0.2f)
		{
			sPoint2D pos = path.GetSplinePoint(t, false);
			Draw(pos.x, pos.y, olc::WHITE);
		}


		// Draw Control Points
		for (int i = 0; i < path.points.size(); ++i)
		{
			FillCircle(int32_t(path.points[i].x), int32_t(path.points[i].y), 4, olc::RED);
			DrawString(int32_t(path.points[i].x), int32_t(path.points[i].y), to_string(i), olc::GREEN, 1);
		}

		// High Light selected control point
		FillCircle(int32_t(path.points[nSelectedPoint].x), int32_t(path.points[nSelectedPoint].y), 4, olc::YELLOW);
		DrawString(int32_t(path.points[nSelectedPoint].x), int32_t(path.points[nSelectedPoint].y), to_string(nSelectedPoint), olc::GREEN, 1);

		// Draws the Menu
		DrawString(int32_t(ScreenWidth() - 120), int32_t(10), "RIGHT - SELECT", olc::GREEN, 1);
		DrawString(int32_t(ScreenWidth() - 120), int32_t(20), "X - NEXT", olc::GREEN, 1);
		DrawString(int32_t(ScreenWidth() - 120), int32_t(30), "Z - BEFORE", olc::GREEN, 1);

		return true;
	}
};


int main()
{
	Spline demo;
	if (demo.Construct(400, 240, 2, 2))
		demo.Start();

	return 0;
}