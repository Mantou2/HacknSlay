#version 330 core

in vec3 vPosition;
in vec3 vColor;
in vec3 vNormal;
in vec2 vTexCoord;

out vec4 fPosition;
out vec3 fColor;
out vec2 fTexCoord;
out vec4 fNormal;

uniform mat4 projMat;
uniform mat4 viewMat;
uniform mat4 scaleMat;
uniform mat4 rotateMat;

void main() {
   fColor = vColor;
   fTexCoord = vTexCoord;
   fNormal = normalize(projMat*viewMat*vec4(vNormal, 1.0));
   fPosition = projMat*viewMat*vec4(vPosition, 1.0);
   gl_Position = projMat*viewMat*vec4(vPosition, 1.0);
};
