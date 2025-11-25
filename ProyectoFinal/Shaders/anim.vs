#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

const float amplitude = 0.05; // Mayor amplitud
const float frequency = 2.0;
const float PI = 3.14159;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;

// Función hash para obtener un valor pseudoaleatorio
float hash(vec2 p) {
    return fract(sin(dot(p, vec2(12.9898, 78.233))) * 43758.5453);
}

void main()
{
    float normalizedHeight = aPos.y * 0.3; 
    float windWave = sin(aPos.x * frequency + aPos.z * 1.5 + time * 10.0);
    
    float displacement = amplitude * windWave * normalizedHeight;  //desplazamiento.

    vec3 newPos = aPos;
    newPos.x += displacement;
    newPos.z += displacement * 0.5; // Un desplazamiento un poco menor en Z

    gl_Position = projection * view * model * vec4(newPos, 1.0);
    TexCoords = aTexCoords;
}