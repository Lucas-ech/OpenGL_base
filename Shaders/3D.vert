// Version du GLSL

#version 150 core


// Entr�es

in vec3 in_Vertex;


// Uniform

uniform mat4 projection;
uniform mat4 modelview;


// Sortie


// Fonction main

void main()
{
    // Position finale du vertex en 3D

    gl_Position = projection * modelview * vec4(in_Vertex, 1.0);


    // Envoi de la couleur au Fragment Shader

}
