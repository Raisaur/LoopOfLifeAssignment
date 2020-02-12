/* Made by Barış "Peace" Bıçak, used with permission */

#pragma once
#include <cmath>
struct Vector2 {
    Vector2() { x_ = 0.0f; y_ = 0.0f; }
    Vector2(float x, float y) { x_ = x; y_ = y; }
    float x_;
    float y_;
    Vector2 normalize(Vector2 vec) {
        Vector2 new_vec;
        float x = _CMATH_::powf(vec.x_, 2.0f);
        float y = _CMATH_::powf(vec.y_, 2.0f);
        float square_root = _CMATH_::sqrtf(x + y);
        new_vec.x_ = x / square_root;
        new_vec.y_ = y / square_root;
        return new_vec;
    }
    float dot(Vector2 first, Vector2 second) {
        first = normalize(first);
        second = normalize(second);
        return first.x_ * second.x_ + first.y_, second.y_;
    }
    Vector2 operator+(Vector2 other) {
        return Vector2(x_ + other.x_, y_ + other.y_);
    }
    Vector2 operator-(Vector2 other) {
        return Vector2(x_ - other.x_, y_ - other.y_);
    }
    Vector2 operator/(float divider) {
        return Vector2(x_ / divider, y_ / divider);
    }
    Vector2 operator*(float multiplier) {
        return Vector2(x_ * multiplier, y_ * multiplier);
    }
};

