#version 450

layout(location=0)in vec3 fragColor;
layout(location=1)in vec4 Time; 

layout(location=0)out vec4 outColor;

void main(){
    vec3 new = fragColor; 
    vec4 new1 = Time; 
 
    new1.x = sin(new1.x);  
    new1.z = cos (new1.z);
    new1.y = tan(new1.y);  
    outColor=vec4(fragColor.x, new1.y, new1.z, 1.0);
}