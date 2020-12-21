#version 330 core
out vec4 FragColor;

in vec3 fColor;

void main()
{
   // FragColor = uni_shader_color;//vec4(fColor, 1.0);   
     FragColor = vec4(fColor, 1.0);  	
}
