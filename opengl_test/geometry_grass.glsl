#version 440
layout (points) in;
layout (triangle_strip, max_vertices = 21) out;

in vec3 normal[1];
in vec3 direction[1];
in float height[1];

uniform float g_height;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform float time;

uniform vec3 light_position;

out vec3 Normal;
out vec3 vertexPosition;

//direction = largeur de la tige, direction de la largeur;
//normal = direction de la tige, direction de la hauteur

void main()
{
    float grass_height = height[0] + g_height;
    vec3 time_coeff = vec3(((sin(time / 1000) * (1 + grass_height)) / 10) * sin(time / 500), 0, ((sin(time / 1000) * (1 + grass_height)) / 10) * cos(time / 500));
    int number_of_loops = 10;
    vec3 weight = vec3(0.0, -0.1, 0.0);
    vec3 cross_line = vec3(0, 0, 0);
    vec3 down_line = vec3(0, 0, 0);
    vec3 lightDirection = vec3(0, 0, 0);
    vec4 top_left = vec4(0, 0, 0, 1);
    vec4 top_right = vec4(0, 0, 0, 1);
    //vec4 points[20];
    //vec3 Normals[20];

    vec4 bottom_left = gl_in[0].gl_Position - vec4(direction[0], 0.0);
    vec4 bottom_right = gl_in[0].gl_Position + vec4(direction[0], 0.0);
    vec4 temp_top_left = bottom_left + vec4((normal[0] + time_coeff + weight) * grass_height, 0.0);
    Normal = normalize(mat3(transpose(inverse(model))) * cross(vec3(bottom_right - bottom_left), vec3(temp_top_left - bottom_left)));
    lightDirection = normalize(vec3(bottom_left) - light_position);
    if (dot(Normal, lightDirection) > 0)
        Normal *= -1;
    //Normals[0] = Normal;
    //points[0] = bottom_left;
    vertexPosition = vec3(model * bottom_left);
    gl_Position = projection * view * model * bottom_left;
    EmitVertex();

    vec4 temp_top_right = bottom_right + vec4((normal[0] + time_coeff + weight) * grass_height, 0.0);
    Normal = normalize(mat3(transpose(inverse(model))) * cross(vec3(temp_top_right - bottom_right), vec3(bottom_left - bottom_right)));
    lightDirection = normalize(vec3(bottom_right) - light_position);
    if (dot(Normal, lightDirection) > 0)
        Normal *= -1;
    //Normals[1] = Normal;
    //points[1] = bottom_right;
    vertexPosition = vec3(model * bottom_right);
    gl_Position = projection * view * model * bottom_right;
    EmitVertex();

    for (int i = 1; i < number_of_loops; i++)
    {
        top_left = bottom_left + (vec4(direction[0], 0.0) * exp(i-number_of_loops)) + vec4((normal[0] + time_coeff + weight) * grass_height, 0.0);
        cross_line = normalize(vec3(bottom_right - top_left));
        down_line = normalize(vec3(bottom_left - top_left));
        Normal = normalize(mat3(transpose(inverse(model))) * cross(down_line, cross_line));
        lightDirection = normalize(vec3(top_left) - light_position);
        if (dot(Normal, lightDirection) > 0)
            Normal *= -1;
        //Normals[i*2] = Normal;
        //points[i*2] = top_left;
        bottom_left = top_left;
        gl_Position = projection * view * model * top_left;
        vertexPosition = vec3(model * top_left);
        EmitVertex();

        top_right = bottom_right - (vec4(direction[0], 0.0) * exp(i- number_of_loops)) + vec4((normal[0] + time_coeff + weight) * grass_height, 0.0);
        cross_line = normalize(vec3(bottom_left - top_right));
        down_line = normalize(vec3(bottom_right - top_right));
        Normal = normalize(mat3(transpose(inverse(model))) * cross(cross_line, down_line));
        lightDirection = normalize(vec3(top_right) - light_position);
        if (dot(Normal, lightDirection) > 0)
            Normal *= -1;
        //Normals[i*2 + 1] = Normal;
        //points[i*2 + 1] = top_right;
        bottom_right = top_right;
        gl_Position = projection * view * model * top_right;
        vertexPosition = vec3(model * top_right);
        EmitVertex();

        weight += vec3(0.0, -grass_height*0.1, 0.0);
    }

    vec4 center = ((top_left + top_right) / 2) + vec4((normal[0] + time_coeff + weight) * grass_height, 0.0);
    vec3 right_line = normalize(vec3(top_right - center));
    vec3 left_line = normalize(vec3(top_left - center));
    Normal = normalize(mat3(transpose(inverse(model))) * cross(right_line, left_line));
    lightDirection = normalize(vec3(center) - light_position);
    if (dot(Normal, lightDirection) > 0)
        Normal *= -1;
    //Normals[i*2] = Normal;
    //points[i*2] = top_left;
    gl_Position = projection * view * model * center;
    vertexPosition = vec3(model * center);
    EmitVertex();

    EndPrimitive();
    
    /*for (int i = 0; i < 20; i++)
    {
        Normal = -Normals[i];
        vec4 point = points[i] + vec4(Normal*0.000001, 0);
        gl_Position = projection * view * model * point;
        vertexPosition = vec3(model * point);
        EmitVertex();
    }
    EndPrimitive();*/
}