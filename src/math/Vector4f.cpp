//
// Created by Israel on 22/03/2022.
//

#include "../../include/vox-engine/math/Vector4f.h"

const Vector4f Vector4f::ZERO = Vector4f(0, 0, 0, 0);
const Vector4f Vector4f::ONE = Vector4f(1, 1, 1, 1);
const Vector4f Vector4f::UNIT_X = Vector4f(1, 0, 0, 0);
const Vector4f Vector4f::UNIT_Y = Vector4f(0, 1, 0, 0);
const Vector4f Vector4f::UNIT_Z = Vector4f(0, 0, 1, 0);
const Vector4f Vector4f::UNIT_W = Vector4f(0, 0, 0, 1);

Vector4f Vector4f::lerp(Vector4f start, Vector4f target, float percent) {
    return {
            start.x() + percent * (target.x() - start.x()),
            start.y() + percent * (target.y() - start.y()),
            start.z() + percent * (target.z() - start.z()),
            start.w() + percent * (target.w() - start.w())
    };
}