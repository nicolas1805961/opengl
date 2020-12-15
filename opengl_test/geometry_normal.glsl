#version 440
layout (points) in;
layout (line_strip, max_vertices = 42) out;

in vec3 normal[1];
in vec3 direction[1];
in float height[1];

uniform float g_height;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform float time;

uniform vec3 light_position;

void main()
{
    float grass_height = height[0] + g_height;
    vec3 time_coeff = vec3(((sin(time / 1000) * (1 + grass_height)) / 10) * sin(time / 500), 0, ((sin(time / 1000) * (1 + grass_height)) / 10) * cos(time / 500));
    int number_of_loops = 10;
    vec3 weight = vec3(0.0, -0.1, 0.0);
    vec3 cross_line = vec3(0, 0, 0);
    vec3 down_line = vec3(0, 0, 0);
    vec3 norm = vec3(0, 0, 0);
    vec3 lightDirection = vec3(0, 0, 0);
    vec4 top_right = vec4(0, 0, 0, 1);
    vec4 top_left = vec4(0, 0, 0, 1);
    //vec3 norms[20];
    //vec4 points[20];

    vec4 bottom_left = gl_in[0].gl_Position - vec4(direction[0], 0.0);
    vec4 bottom_right = gl_in[0].gl_Position + vec4(direction[0], 0.0);
    vec4 temp_top_left = bottom_left + vec4((normal[0] + time_coeff + weight) * grass_height, 0.0);
    norm = normalize(mat3(transpose(inverse(model))) * cross(vec3(bottom_right - bottom_left), vec3(temp_top_left - bottom_left)));
    lightDirection = normalize(vec3(bottom_left) - light_position);
    if (dot(norm, lightDirection) > 0)
        norm *= -1;
    //norms[0] = norm;
    //points[0] = bottom_left;
    gl_Position = projection * view * model * bottom_left;
    EmitVertex();
    gl_Position = projection * view * model * ((vec4(norm, 0.0) * 0.01) + bottom_left);
    EmitVertex();
    EndPrimitive();

    vec4 temp_top_right = bottom_right + vec4((normal[0] + time_coeff + weight) * grass_height, 0.0);
    norm = normalize(mat3(transpose(inverse(model))) * cross(vec3(temp_top_right - bottom_right), vec3(bottom_left - bottom_right)));
    lightDirection = normalize(vec3(bottom_right) - light_position);
    if (dot(norm, lightDirection) > 0)
        norm *= -1;
    //norms[1] = norm;
    //points[1] = bottom_right;
    gl_Position = projection * view * model * bottom_right;
    EmitVertex();
    gl_Position = projection * view * model * ((vec4(norm, 0.0) * 0.01) + bottom_right);
    EmitVertex();
    EndPrimitive();

    for (int i = 1; i < number_of_loops; i++)
    {
        top_left = bottom_left + (vec4(direction[0], 0.0) * exp(i-number_of_loops)) + vec4((normal[0] + time_coeff + weight) * grass_height, 0.0);
        cross_line = normalize(vec3(bottom_right - top_left));
        down_line = normalize(vec3(bottom_left - top_left));
        norm = normalize(mat3(transpose(inverse(model))) * cross(down_line, cross_line));
        lightDirection = normalize(vec3(top_left) - light_position);
        if (dot(norm, lightDirection) > 0)
            norm *= -1;
        //norms[i*2] = norm;
        //points[i*2] = top_left;
        bottom_left = top_left;
        gl_Position = projection * view * model * top_left;
        EmitVertex();
        gl_Position = projection * view * model * ((vec4(norm, 0.0) * 0.01) + top_left);
        EmitVertex();
        EndPrimitive();

        top_right = bottom_right - (vec4(direction[0], 0.0) * exp(i- number_of_loops)) + vec4((normal[0] + time_coeff + weight) * grass_height, 0.0);
        cross_line = normalize(vec3(bottom_left - top_right));
        down_line = normalize(vec3(bottom_right - top_right));
        norm = normalize(mat3(transpose(inverse(model))) * cross(cross_line, down_line));
        lightDirection = normalize(vec3(top_right) - light_position);
        if (dot(norm, lightDirection) > 0)
            norm *= -1;
        //norms[i*2 + 1] = norm;
        //points[i*2 + 1] = top_right;
        bottom_right = top_right;
        gl_Position = projection * view * model * top_right;
        EmitVertex();
        gl_Position = projection * view * model * ((vec4(norm, 0.0) * 0.01) + top_right);
        EmitVertex();
        EndPrimitive();

        weight += vec3(0.0, -grass_height*0.1, 0.0);
    }

    vec4 center = ((top_left + top_right) / 2) + vec4((normal[0] + time_coeff + weight) * grass_height, 0.0);
    vec3 right_line = normalize(vec3(top_right - center));
    vec3 left_line = normalize(vec3(top_left - center));
    norm = normalize(mat3(transpose(inverse(model))) * cross(right_line, left_line));
    lightDirection = normalize(vec3(center) - light_position);
    if (dot(norm, lightDirection) > 0)
        norm *= -1;
    //norms[i*2] = norm;
    //points[i*2] = top_left;
    gl_Position = projection * view * model * center;
    EmitVertex();
    gl_Position = projection * view * model * ((vec4(norm, 0.0) * 0.01) + center);
    EmitVertex();
    EndPrimitive();

    /*for (int i = 0; i < 20; i++)
    {
        gl_Position = projection * view * model * points[i];
        EmitVertex();
        gl_Position = projection * view * model * ((vec4(-norms[i], 0.0) * 0.01) + points[i]);
        EmitVertex();
        EndPrimitive();
    }*/
}