#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;

void main()
{
    
    float horizontalOffset = sin(time * 0.05) * 4.0; // Aleteo rapido
    float verticalOffset = -cos(time * 6.0) * 0.04;// Asciende y desciende rapido

    
    float direccion = horizontalOffset >= 0.0 ? 1.0 : -1.0;

    
    vec4 position = vec4(aPos.x + horizontalOffset, aPos.y +verticalOffset, aPos.z, 1.0);
    
  
    gl_Position = projection * view * model * position;
    TexCoords = aTexCoords;
}
