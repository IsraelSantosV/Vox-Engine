//
// Created by Israel on 22/03/2022.
//

#include "../../include/vox-engine/math/Vector3f.h"

const Vector3f Vector3f::ZERO = Vector3f(0, 0, 0);
const Vector3f Vector3f::ONE = Vector3f(1, 1, 1);
const Vector3f Vector3f::UNIT_X = Vector3f(1, 0, 0);
const Vector3f Vector3f::UNIT_Y = Vector3f(0, 1, 0);
const Vector3f Vector3f::UNIT_Z = Vector3f(0, 0, 1);
const Vector3f Vector3f::UP = Vector3f(0, 1, 0);
const Vector3f Vector3f::DOWN = Vector3f(0, -1, 0);
const Vector3f Vector3f::LEFT = Vector3f(-1, 0, 0);
const Vector3f Vector3f::RIGHT = Vector3f(1, 0, 0);
const Vector3f Vector3f::FORWARD = Vector3f(0, 0, 1);
const Vector3f Vector3f::BACK = Vector3f(0, 0, -1);

Vector3f Vector3f::lerp(Vector3f start, Vector3f target, float percent) {
    return {
            start.x() + percent * (target.x() - start.x()),
            start.y() + percent * (target.y() - start.y()),
            start.z() + percent * (target.z() - start.z())
    };
}