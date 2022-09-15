#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;


struct Object {
    Vector2f position;
    Vector2f old_position;

    Vector2f acceleration;

    float radius;

    Color color;

    Object(Vector2f pos, float size, Color color = Color::White) :
        position(pos), old_position(pos), radius(size), color(color)
    {
        acceleration = { 0, 0 };
    }

    void updatePosition(float dt) {
        Vector2f velocity = position - old_position;

        old_position = position;

        position = position + velocity + acceleration * dt * dt;

        acceleration = {};
    }

};