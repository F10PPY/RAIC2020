#version 330 core
layout (points) in;
layout (line_strip, max_vertices = 2) out;
  
 uniform vec4 uni_offset;
 uniform vec3 uni_shader_color; 
  in VS_OUT {
    vec3 color;
} gs_in[];
out vec3 fColor;

  
void build_house(vec4 position)
{    
    gl_Position = gl_in[0].gl_Position + vec4(0.0+uni_offset.x, 0.0+uni_offset.y, 0.0, 0.0); 
    fColor = vec3(0.0, 1, 0.0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position +vec4(0.0+uni_offset.z, 0.0+uni_offset.w, 0.0, 0.0);
    fColor =uni_shader_color;// vec3(1, 0.0, 0.00);
    EmitVertex();

    EndPrimitive();
}

void main() {    
    build_house(gl_in[0].gl_Position);
}



