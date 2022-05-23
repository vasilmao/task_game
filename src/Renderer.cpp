#include "Renderer.hpp"
#include <iostream>

void Renderer::DrawSegment(Vector2 p1, Vector2 p2, Color color) {
    int dx = abs(p2.GetX() - p1.GetX());
    int dy = -abs(p2.GetY() - p1.GetY());
    int sx = p1.GetX() < p2.GetX() ? 1 : -1;
    int sy = p1.GetY() < p2.GetY() ? 1 : -1;
    float error = dx + dy;

    int curx = p1.GetX();
    int cury = p1.GetY();

    int endx = p2.GetX();
    int endy = p2.GetY();

    while (true) {
        std::cout << curx << " " << cury << "\n";
        buffer_[curx + cury * width_] = int32_color(color);
        if (curx == endx && cury == endy) {
            break;
        }
        int e2 = 2 * error;
        if (e2 >= dy) {
            if (curx == endx) {
                break;
            }
            error += dy;
            curx += sx;
        }
        if (e2 <= dx) {
            if (cury == endy) {
                break;
            }
            error += dx;
            cury += sy;
        }
    }
    std::cout << "YES!\n";
}