// Version du GLSL

#version 150 core


// Entrée

in vec2 coordTexture;


// Uniform

uniform sampler2D texture2D;


// Sortie

out vec4 out_Color;


// Fonction main

void main()
{
    // Couleur du pixel
    out_Color = texture(texture2D, coordTexture);
    out_Color = vec4(1, 1, 1, 1);
}
