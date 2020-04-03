#include "Error.h"

void test_opengl_error(int x)
{
	GLenum err = glGetError();
	switch (err) {
	case GL_NO_ERROR: return;
	case GL_INVALID_ENUM:
		std::cerr << "GL_INVALID_ENUM\n";
		//exit(x);
		break;
	case GL_INVALID_VALUE:
		std::cerr << "GL_INVALID_VALUE\n";
		//exit(x);
		break;
	case GL_INVALID_OPERATION:
		std::cerr << "GL_INVALID_OPERATION\n";
		//exit(x);
		break;
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION\n";
		//exit(x);
		break;
	case GL_OUT_OF_MEMORY:
		std::cerr << "GL_OUT_OF_MEMORY\n";
		//exit(x);
		break;
	case GL_STACK_UNDERFLOW:
		std::cerr << "GL_STACK_UNDERFLOW\n";
		//exit(x);
		break;
	case GL_STACK_OVERFLOW:
		std::cerr << "GL_STACK_OVERFLOW\n";
		//exit(x);
		break;
	default:
		std::cerr << "UNKONWN ERROR\n";
		//exit(x);
		break;
	}
}