#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

GLuint vao_id;
GLint program_id;

void test_opengl_error() {
    GLenum err = glGetError();
    switch (err) {
    case GL_NO_ERROR: return;
    case GL_INVALID_ENUM:
        std::cerr << "GL_INVALID_ENUM\n";
        break;
    case GL_INVALID_VALUE:
        std::cerr << "GL_INVALID_VALUE\n";
        break;
    case GL_INVALID_OPERATION:
        std::cerr << "GL_INVALID_OPERATION\n";
        break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION\n";
        break;
    case GL_OUT_OF_MEMORY:
        std::cerr << "GL_OUT_OF_MEMORY\n";
        break;
    case GL_STACK_UNDERFLOW:
        std::cerr << "GL_STACK_UNDERFLOW\n";
        break;
    case GL_STACK_OVERFLOW:
        std::cerr << "GL_STACK_OVERFLOW\n";
        break;
    default:
        std::cerr << "UNKONWN ERROR\n";
        break;
    }

}

void display() {
    glUseProgram(program_id);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(vao_id);
    glDrawArrays(GL_TRIANGLES, 0, 3 * 3);
    glBindVertexArray(0);
    glFinish();
    glutSwapBuffers();
    test_opengl_error();
}

void initGlut(int& argc, char* argv[]) {
    //glewExperimental = GL_TRUE;
    glutInit(&argc, argv);
    glutInitContextVersion(4, 0);
    glutInitContextProfile(GLUT_CORE_PROFILE | GLUT_DEBUG);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Test");
    glutDisplayFunc(display);
}

void initGlew() {
    if (glewInit()) {
        std::cerr << " Error while initializing glew";
    }
}

void initGL() {
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glViewport(0, 0, 512, 512);
    glClearColor(1.0, 0, 0, 1.0);
    test_opengl_error();
}

bool initShaders() {
    GLint compile_status = GL_TRUE;
    GLint link_result = GL_TRUE;
    GLint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    GLint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    program_id = glCreateProgram();
    if (vertex_shader_id == 0 || fragment_shader_id == 0 || program_id == 0) return false;
    const char* src_vertex_shader[] = { "#version 400\nlayout(location = 1) in vec3 vPos;\nvoid main() {\ngl_Position = vec4(vPos, 1.0);\n}" };
    const char* src_fragment_shader[] = { "#version 400\nout vec4 color;\nvoid main() {\ncolor = vec4(1.0,1.0,1.0,1.0);\n}" };
    glShaderSource(vertex_shader_id, 1, src_vertex_shader, 0);
    glShaderSource(fragment_shader_id, 1, src_fragment_shader, 0);
    glCompileShader(vertex_shader_id);
    glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &compile_status);
    if (compile_status != GL_TRUE) {
        GLint log_size;
        glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &log_size);
        char* shader_log = (char*)std::malloc(log_size + 1); /* +1 pour le caractere de fin de chaine '\0' */
        if (shader_log == 0) {
            return false;
        }
        glGetShaderInfoLog(vertex_shader_id, log_size, &log_size, shader_log);
        std::cerr << shader_log << std::endl;
        return false;
    }
    glCompileShader(fragment_shader_id);
    glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &compile_status);
    if (compile_status != GL_TRUE) {
        GLint log_size;
        glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &log_size);
        char* shader_log = (char*)std::malloc(log_size + 1); /* +1 pour le caractere de fin de chaine '\0' */
        if (shader_log == 0) {
            return false;
        }
        glGetShaderInfoLog(vertex_shader_id, log_size, &log_size, shader_log);
        std::cerr << shader_log << std::endl;
        return false;
    }

    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glLinkProgram(program_id);
    if (link_result != GL_TRUE) {
        GLint log_size;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_size);
        char* program_log = (char*)std::malloc(log_size + 1); /* +1 pour le caractere de fin de chaine '\0' */
        if (program_log == 0) {
            glDeleteProgram(program_id);
            program_id = 0;
            return false;
        }
        glGetProgramInfoLog(program_id, log_size, &log_size, program_log);
        std::cerr << program_log << std::endl;
        glDeleteProgram(program_id);
        return false;
    }
    return true;
}

void initData() {
    GLfloat vertex_list[] = { -1, -1, 0.0, 1, -1, 0.0, -1, 1, 0.0 };
    GLuint vbo_id;
    glGenVertexArrays(1, &vao_id);
    glBindVertexArray(vao_id);
    glGenBuffers(1, &vbo_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    glBufferData(GL_ARRAY_BUFFER, 3 * 3 * sizeof(GLfloat), vertex_list, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    test_opengl_error();
}

int main(int argc, char* argv[]) {
    std::cerr << "Glut init\n";
    initGlut(argc, argv);
    std::cerr << "Glut init Ok\n";
    std::cerr << "Glew init\n";
    initGlew();
    std::cerr << "Glew init Ok\n";
    std::cerr << "GL init\n";
    initGL();
    std::cerr << "GL init Ok\n";
    std::cerr << "GL init shaders\n";
    initShaders();
    std::cerr << "GL init shaders Ok\n";
    std::cerr << "GL init data\n";
    initData();
    std::cerr << "GL init data Ok\n";
    std::cerr << "Start\n";
    glutMainLoop();
    return 0;
}