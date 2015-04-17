#version 330 core

in vec4 fPosition;
in vec3 fColor;
in vec2 fTexCoord;
in vec4 fNormal;

uniform sampler2D texWood;

out vec4 outColor;

void main()
{
    vec3 lightPos = vec3(0.0,1.0,0.0);
    vec4 l = vec4(lightPos - fPosition.xyz, 1.0);
    vec4 I = vec4(1.0,1.0,1.0,1.0) + vec4(fColor, 1.0)*(fNormal*l) + vec4(fColor, 1.0);

    outColor = I;
};
