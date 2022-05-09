/*
 This code powered by ©Demands.
 at 5/9/2022
 */

class MathUtility
{
    static Vector rotateAroundAxisX(Vector vector, double angle) {
        double cos = Math.Cos(angle);
        double sin = Math.Sin(angle);
        double y = vector[1] * cos - vector[2] * sin;
        double z = vector[1] * sin + vector[2] * cos;
        return Vector(vector[0], y, z);
    };

    static Vector rotateAroundAxisY(Vector vector, double angle) {
        double cos = Math.Cos(angle);
        double sin = Math.Sin(angle);
        double x = vector[0] * cos + vector[2] * sin;
        double z = vector[0] * -sin + vector[2] * cos;
        return Vector(x, vector[1], z);
    };

    static Vector rotateAroundAxisZ(Vector vector, double angle) {
        double cos = Math.Cos(angle);
        double sin = Math.Sin(angle);
        double x = vector[0] * cos - vector[1] * sin;
        double y = vector[0] * sin + vector[1] * cos;
        return Vector(x, y, vector[2]);
    };
};