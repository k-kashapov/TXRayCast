#include "TXLib.h"
#include <stdio.h>
#include <ctype.h>

#define _height 720.0
#define _width 1280.0

#define MOV_SPD 0.2
#define ROT_SPD 0.9
#define FOV 90.0
#define VLINES 430
#define DRAW_DIST 5.0
#define RECT_SIZE _width / VLINES

int main(int argc, char* argv[])
{
	int map[][5] = {
		{0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 1, 1, 1, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0},
	};

	float plr_x = 1, plr_y = 1;
	float plr_rot = 45;

	txCreateWindow(_width, _height);
	txBegin();

	while (1) {
		txSetFillColor(txColor(0, 0, 0));
		txClear();

		if (GetAsyncKeyState('A')) plr_rot -= ROT_SPD;
		if (GetAsyncKeyState('D')) plr_rot += ROT_SPD;
		if (GetAsyncKeyState('W')) {
			plr_x += cos(plr_rot / 180 * txPI) * MOV_SPD;
			plr_y += sin(plr_rot / 180 * txPI) * MOV_SPD;
		}
		if (GetAsyncKeyState('S')) {
			plr_x -= cos(plr_rot / 180 * txPI) * MOV_SPD;
			plr_y -= sin(plr_rot / 180 * txPI) * MOV_SPD;
		}

		txClearConsole();
		printf("FPS: %f\n", txGetFPS());

		for (float d_angle = -FOV / 2; d_angle <= FOV / 2; d_angle += FOV / VLINES) {
			
			float angle = (plr_rot + d_angle) / 180 * txPI;

			for (float dist = 0.001; dist < DRAW_DIST; dist += DRAW_DIST / 100) {
			
				int ray_x, ray_y;
				ray_x = static_cast<int>(plr_x + cos(angle) * dist) % 5;
				ray_y = static_cast<int>(plr_y + sin(angle) * dist) % 5;

				if (map[ray_x][ray_y] != 0) {

					float color = 1.0 * (1.0 - dist / DRAW_DIST);
					txSetFillColor(txColor(color, color, color));

					float rect_x = _width * (d_angle / FOV + 0.5);
					float rect_y_size = _height * 5 / 6 * 1.0 / dist / cos(d_angle / 180 * txPI);
					txRectangle(rect_x, _height / 2 - rect_y_size / 2, rect_x + RECT_SIZE, _height / 2 + rect_y_size / 2);
					break;
				}
			}
		}
		Sleep(1000.0 / 60);
		txRedrawWindow();
	}
}
