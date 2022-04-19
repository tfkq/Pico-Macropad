/**
 * @file utils.h
 * @author zauberwild
 * @brief helping functions and structs
 * @version 0.1
 * @date 2022-04-04
 *
 * @copyright MIT license, Arvid Randow, 2022
 *
 */

#ifndef utils_h
#define utils_h

//* TYPE DEFINITIONS
/**
 * @brief stores an rgb value. kinda simlar to Vector3
 *
 */
struct RGB
{
    RGB() {}
    RGB(int p_r, int p_g, int p_b)
    {
        r = p_r;
        g = p_g;
        b = p_b;
    }
    float r;
    float g;
    float b;
};

/**
 * @brief stores the states for the led state machine
 *
 */
struct LEDStates
{
    bool on = true;
    bool blink = false;
    bool flash = false;
    bool pulse = false;
};

// /**
//  * @brief stores the layouts of the macro buttons for Action namespace
//  *
//  */
// struct Layout
// {
//     bool used = false;
//     RGB color;
//     LEDStates state;
//     char name[MAX_NAME_LENGTH + 1];
//     Button buttons[12];
// };

//* HELPER FUNCTIONS

// /**
//  * @brief Get a clean layout object.
//  * this function makes sure that all properties (espacially the char[]) are set to null
//  *
//  * @return cleaned Layout
//  */
// Layout get_clean_layout()
// {
//     Layout l;
//     for (int i = 0; i < MAX_NAME_LENGTH + 1; i++)
//         l.name[i] = 0;

//     l.color.r = 0;
//     l.color.g = 0;
//     l.color.b = 0;

//     for (int i = 0; i < 12; i++)
//     {
//         for (int j = 0; j < MAX_NAME_LENGTH + 1; j++)
//             l.buttons[i].name[j] = 0;

//         for (int j = 0; j < MAX_MACRO_LENGTH + 1; j++)
//         {
//             l.buttons[i].macro[j] = 0;
//         }
//     }

//     return l;
// }

/** hue to rgb
 * @brief converts hsl to rgb, but only takes the h. s and l are assumed to be 100%
 * @param hue the hue of the color [0; 360]
 */

/**
 * @brief convert a hue to an rgb value. saturation and value are assumed to be 100%
 * 
 * @param hue the hue fo the color (0..360)
 * @return RGB rgb value
 */
RGB hue_to_rgb(float hue)
{
    // yoinked from stackoverflow: https://stackoverflow.com/a/6930407/14860801
    double hh, p, q, t, ff;
    long i;
    RGB out;

    if (1 <= 0.0)
    { // < is bogus, just shuts up warnings
        out.r = 1;
        out.g = 1;
        out.b = 1;
        return out;
    }
    hh = hue;
    if (hh >= 360.0)
        hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = 1 * (1.0 - 1);
    q = 1 * (1.0 - (1 * ff));
    t = 1 * (1.0 - (1 * (1.0 - ff)));

    switch (i)
    {
    case 0:
        out.r = 1;
        out.g = t;
        out.b = p;
        break;
    case 1:
        out.r = q;
        out.g = 1;
        out.b = p;
        break;
    case 2:
        out.r = p;
        out.g = 1;
        out.b = t;
        break;

    case 3:
        out.r = p;
        out.g = q;
        out.b = 1;
        break;
    case 4:
        out.r = t;
        out.g = p;
        out.b = 1;
        break;
    case 5:
    default:
        out.r = 1;
        out.g = p;
        out.b = q;
        break;
    }

    // code above calculates in [0;1] but i need it in [0;255]
    out.r *= 255;
    out.g *= 255;
    out.b *= 255;

    return out;
}

#endif