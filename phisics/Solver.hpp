#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Object.hpp"

#include "Global.hpp"

using namespace sf;

inline Vector2f getIntersect(const Vector2f& aa, const Vector2f& ab, const Vector2f& ba, const Vector2f& bb)
{
    float pX = (aa.x * ab.y - aa.y * ab.x) * (ba.x - bb.x) -
        (ba.x * bb.y - ba.y * bb.x) * (aa.x - ab.x);
    float pY = (aa.x * ab.y - aa.y * ab.x) * (ba.y - bb.y) -
        (ba.x * bb.y - ba.y * bb.x) * (aa.y - ab.y);
    float denominator = (aa.x - ab.x) * (ba.y - bb.y) -
        (aa.y - ab.y) * (ba.x - bb.x);

    return Vector2f(pX / denominator, pY / denominator);
}


inline float dot(const Vector2f& lv, const Vector2f& rv)
{
    return lv.x * rv.x + lv.y * rv.y;
}


inline float length(const Vector2f& source)
{
    return std::sqrt(dot(source, source));
}


struct Solver
{

    Vector2f gravity = { 0.0f, 1500.0f };
    Vector2f squareConstraint = {400.f, 400.f};
    float circleConstraint = 250.0f;

    void Update() {
        const unsigned int substeps = 2;
        const float substep_dt = dt / substeps;
        for (unsigned int i(substeps); i--;)
        {
            for (Object& obj : Objects)
            {
                applySquareConstraint(obj);
                //applyGravity(obj);
                applyColision(obj);

                obj.updatePosition(substep_dt);
            }
        }

    }

    void applyGravity(Object& obj) {
        obj.acceleration += gravity;
    }

    void applyCircleConstraint(Object& obj) {
        //Circle Circle Colison
        // n = sqrt(ball.x² + ball.y²) / (constraint_radius - ball_radius)

        float dist = length(obj.position);

        if (dist > circleConstraint - obj.radius) {
            float n = (circleConstraint - obj.radius) / dist;

            obj.position *= n;
        }
    }

    void applySquareConstraint(Object& obj) {
        //Circle Square Colision
         
        /*
        * Math:
        * n.x = v1.x * v2.
        * 
        */


        const Vector2f constr = squareConstraint / 2.f;

        const float cBottom = 
        const float cTop = obj.position.y + obj.radius;
        const float cLeft = obj.position.x - obj.radius;
        const float cRight = obj.position.x + obj.radius;


        const float bottom = obj.position.y - obj.radius;
        const float top = obj.position.y + obj.radius;
        const float left = obj.position.x - obj.radius;
        const float right = obj.position.x + obj.radius;

        if (bottom > constr.y || top < -constr.y || right > constr.x || left < -constr.x) {
            const Vector2f intersect = getIntersect();

        }
    }

    void applyColision(Object& obj) {
        for (Object& other : Objects)
        {
            if (&obj == &other) continue;

            const Vector2f colision_axis = obj.position - other.position;
            const float dist = length(colision_axis);

            if (dist < obj.radius + other.radius) {
                const Vector2f n = colision_axis / dist;
                const float delta = obj.radius + other.radius - dist;
                obj.position += 0.5f * delta * n;
                other.position -= 0.5f * delta * n;
            }
        }
    }

};

