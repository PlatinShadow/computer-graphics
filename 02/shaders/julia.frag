#version 150

uniform float time = 0.2;

in vec2 fragComplex;

out vec4 outputColor;

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

vec2 multiply_complex(vec2 c0, vec2 c1) {
    return vec2(c0.x*c1.x - c0.y*c1.y, c0.y*c1.x + c0.x*c1.y);
}

void main()
{
    const int maxIteration = 128;
    const float bailout = 1e20;
    const vec2 cj0 = vec2(-0.835, -0.3842);
    const vec2 cj1 = vec2(-0.65176, 0.256);
    const vec3 color0 = vec3(0.0, 1.0, 1.0);  // HSV color for iteration 0
    const vec3 color1 = vec3(1.0, 1.0, 1.0);  // HSV color for maxIteration

    vec3 color = vec3(0.0);

    float tx = 0.5 * (cos(time) + 1.0);
    float ty = 0.5 * (sin(time * 0.777) + 1.0);

    vec2 z = fragComplex;
    vec2 c = vec2(mix(cj0.x, cj1.x, tx), mix(cj0.y, cj1.y, ty));

    int iteration;
    for (iteration = 0; iteration < maxIteration; ++iteration)
    {
        z = multiply_complex(z, z) + c;

        if (dot(z, z) > bailout)
            break;
    }

    if (iteration == maxIteration)
    {
        color = vec3(0.0); // Color for points inside the Julia set (black)
    }
    else
    {
        float ratio = float(iteration) / float(maxIteration);
        vec3 hsvColor = mix(color0, color1, ratio);
        color = hsv2rgb(hsvColor);
    }

    outputColor = vec4(color, 1.0);
}
