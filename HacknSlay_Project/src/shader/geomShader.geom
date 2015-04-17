#version 330 core

layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in vec4 gPosition[];
in vec3 gColor[];
in vec3 gNormal[];
in vec2 gTexCoord[];

out vec3 fPosition;
out vec3 fColor;
out vec3 fNormal;
out vec2 fTexCoord;

void emitVertex(vec4 position, vec3 color, vec3 normal){
    gl_Position = position;
    fPosition = position.xyz;
    fColor = color;
    fNormal = normal;
    EmitVertex();
};

void drawTriangle(vec4 vertexA, vec4 vertexB, vec4 vertexC, vec2 uvA, vec2 uvB, vec2 uvC){
    vec4 directionVec1 = vertexB-vertexA;
    vec4 directionVec2 = vertexC-vertexA;

    vec3 directionVec1_3D = directionVec1.xyz;
    vec3 directionVec2_3D = directionVec2.xyz;

    vec3 normal = normalize(cross(directionVec1_3D, directionVec2_3D));

    fTexCoord = uvA ;
    emitVertex(vertexA, vec3(0.0,1.0,1.0), normal);
    fTexCoord = uvB ;
    emitVertex(vertexB, vec3(1.0,0.0,1.0), normal);
    fTexCoord = uvC ;
    emitVertex(vertexC, vec3(1.0,1.0,0.0), normal);

    EndPrimitive();
}

void main() {

    fColor = gColor[0];
    vec4 directionVec1 = gPosition[1]-gPosition[0];
    vec4 directionVec2 = gPosition[2]-gPosition[0];

    vec3 directionVec1_3D = directionVec1.xyz;
    vec3 directionVec2_3D = directionVec2.xyz;

    vec3 normal = normalize(cross(directionVec1_3D, directionVec2_3D));

    gl_Position = gPosition[0];
    EmitVertex();
    gl_Position = gPosition[0] + normal;
    EmitVertex();

    EndPrimitive();

    gl_Position = gPosition[1];
    EmitVertex();
    gl_Position = gPosition[1] + normal;
    EmitVertex();

    EndPrimitive();

    gl_Position = gPosition[2];
    EmitVertex();
    gl_Position = gPosition[2] + normal;
    EmitVertex();

    EndPrimitive();


};
