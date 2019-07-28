#ifndef ROBOTLIBUTIL_H
#define ROBOTLIBUTIL_H

class RLUtil {
public:
    /*
        Returns val clamped between min and max

        @param val - value to clamp
        @param min - minimum value
        @param max - maximum value
        @return the value clamped between min and max
    */
    static float clamp(float val, float min, float max)
    {
        if(val > max)
        {
            return max;
        }
        else if(val < min)
        {
            return min;
        }
        return val;
    }

    /*
        Linearly interpolates from v0 to v1.

        @param v0 - start value
        @param v1 - end value
        @param t - interpolation parameter
        @return the interpolated value
    */
    static float lerp(float v0, float v1, float t)
    {
        return (1 - t) * v0 + t * v1;
    }

    /*
        Smooth Step interpolates from v0 to v1.

        @param v0 - start value
        @param v1 - end value
        @param t - interpolation parameter
        @return the interpolated value
    */
    static float slerp(float v0, float v1, float t)
    {
        return lerp(v0, v1, t * t * (3 - 2 * t));
    }
};

#endif