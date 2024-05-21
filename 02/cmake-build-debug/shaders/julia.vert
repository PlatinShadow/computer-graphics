#version 150

uniform float zoom = 1.0;
uniform vec2 zoomPosition = vec2(0.0, 0.0);

in vec2 position;
in vec2 complex;

out vec2 fragComplex;

void main()
{
    fragComplex = (complex - zoomPosition) / zoom + zoomPosition;

    vec2 scaledPosition = position * 2.0 - 1.0; // Convert from [0, 1] to [-1, 1]
    gl_Position = vec4(scaledPosition, 0, 1);
}
