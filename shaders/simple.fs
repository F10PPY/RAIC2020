#version 330 core
out vec4 FragColor;
  
uniform vec4 uni_shader_color; 

void main()
{
    FragColor = uni_shader_color;
  // FragColor = vec4(1.0f, 1.0f,0.0f,0.1);
}   
