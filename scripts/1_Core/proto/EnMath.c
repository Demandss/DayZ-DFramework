/*
 This code powered by ©Demands.
 at 5/9/2022
 */

modded class Math
{
    static vector RotateAroundAxisX(vector vectr, float angle) {
        float cos = Cos(angle);
        float sin = Sin(angle);
        float y = vectr[1] * cos - vectr[2] * sin;
        float z = vectr[1] * sin + vectr[2] * cos;
        return Vector(vectr[0], y, z);
    };

    static vector RotateAroundAxisY(vector vectr, float angle) {
        float cos = Cos(angle);
        float sin = Sin(angle);
        float x = vectr[0] * cos + vectr[2] * sin;
        float z = vectr[0] * -sin + vectr[2] * cos;
        return Vector(x, vectr[1], z);
    };

    static vector RotateAroundAxisZ(vector vectr, float angle) {
        float cos = Cos(angle);
        float sin = Sin(angle);
        float x = vectr[0] * cos - vectr[1] * sin;
        float y = vectr[0] * sin + vectr[1] * cos;
        return Vector(x, y, vectr[2]);
    };
}