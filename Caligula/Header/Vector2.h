/* Written by Barış "Peace" Bıçak, used with permission */

#pragma once
#include <cmath>
struct Vector2 {
    Vector2() { x_ = 0.0f; y_ = 0.0f; }
    Vector2(float x, float y) { x_ = x; y_ = y; }
    float x_;
    float y_;
    float magnitude() {
        return _CMATH_::sqrtf((x_ * x_) + (y_ * y_));
    }
    void normalize() {
        float m = magnitude();
        x_ /= m;
        y_ /= m;
    }
    float dot(Vector2 first, Vector2 second) {
        first.normalize();
        second.normalize();
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
    bool operator==(Vector2 other) {
        if (x_ == other.x_ && y_ == other.y_) return true;
        else return false;
    }
    bool operator!=(Vector2 other) {
        if (x_ != other.x_ || y_ != other.y_) return true;
        return false;
    }
};
