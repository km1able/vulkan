#version 450

layout(location=0)in vec3 fragColor;

layout(location=0)out vec4 outColor;

void main(){
    vec3 new = fragColor; 
    new.x = fragColor.y*fragColor[2];
    outColor=vec4(new,1.);
}