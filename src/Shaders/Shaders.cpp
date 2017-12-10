#include "Shaders.h"

using namespace Shaders;

void Shaders::LoadShader(const char* filename, GLuint shader_id)
{
    // Read GLSL file and put content in memory
    std::ifstream file;
    try {
        file.exceptions(std::ifstream::failbit);
        file.open(filename);
    } catch ( std::exception& e ) {
        fprintf(stderr, "ERROR: Cannot open file \"%s\".\n", filename);
        std::exit(EXIT_FAILURE);
    }
    std::stringstream shader;
    shader << file.rdbuf();
    std::string str = shader.str();
    const GLchar* shader_string = str.c_str();
    const GLint   shader_string_length = static_cast<GLint>( str.length() );

    // Identify the shader using the shader_id provided
    glShaderSource(shader_id, 1, &shader_string, &shader_string_length);

    // Compile the shader
    glCompileShader(shader_id);

    // Check for any error or warning in the compilation process
    GLint compiled_ok;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled_ok);

    GLint log_length = 0;
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);

    // Memory for the log message
    GLchar* log = new GLchar[log_length];
    glGetShaderInfoLog(shader_id, log_length, &log_length, log);

    // Prints error or warning in the terminal
    if (log_length != 0)
    {
        std::string  output;

        if (!compiled_ok)
        {
            output += "ERROR: OpenGL compilation of \"";
            output += filename;
            output += "\" failed.\n";
            output += "== Start of compilation log\n";
            output += log;
            output += "== End of compilation log\n";
        }
        else
        {
            output += "WARNING: OpenGL compilation of \"";
            output += filename;
            output += "\".\n";
            output += "== Start of compilation log\n";
            output += log;
            output += "== End of compilation log\n";
        }

        fprintf(stderr, "%s", output.c_str());
    }

    // Free memory
    delete [] log;
}

void Shaders::LoadShader_Vertex(const char* filename)
{
    vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    LoadShader(filename, vertex_shader_id);

}

void Shaders::LoadShader_Fragment(const char* filename)
{
    fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    LoadShader(filename, fragment_shader_id);
}

void Shaders::CreateGpuProgram(GLuint vertex_shader_id, GLuint fragment_shader_id)
{
    program_id = glCreateProgram();

    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);

    bindAttributes();

    // Linking process
    glLinkProgram(program_id);

    // Check for linking errors
    GLint linked_ok = GL_FALSE;
    glGetProgramiv(program_id, GL_LINK_STATUS, &linked_ok);

    // Prints error or warning in the terminal
    if ( linked_ok == GL_FALSE )
    {
        GLint log_length = 0;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_length);

        // Memory for the log message
        GLchar* log = new GLchar[log_length];

        glGetProgramInfoLog(program_id, log_length, &log_length, log);

        std::string output;

        output += "ERROR: OpenGL linking of program failed.\n";
        output += "== Start of link log\n";
        output += log;
        output += "\n== End of link log\n";

        // Free memory
        delete [] log;

        fprintf(stderr, "%s", output.c_str());
    }

}

void Shaders::start()
{
    glUseProgram(program_id);
}

void Shaders::stop()
{
    glUseProgram(0);
}

void Shaders::cleanUp()
{
    stop();
    glDetachShader(program_id, vertex_shader_id);
    glDetachShader(program_id, fragment_shader_id);
    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);
    glDeleteProgram(program_id);

}

void Shaders::bindAttributes()
{
    bindAttribute(POSITION, "model_coefficients");
    bindAttribute(COLOR, "color_coefficients");
    bindAttribute(NORMAL, "normal_coefficients");
    bindAttribute(TEXTURE, "texture_coefficients");

}

void Shaders::bindAttribute(AttributeLocation attribute, const char* variableName)
{
    glBindAttribLocation(program_id, attribute, variableName);
}

void Shaders::setup()
{
    LoadShader_Vertex(PATH_VERTEX_SHADER);
    LoadShader_Fragment(PATH_FRAGMENT_SHADER);
    CreateGpuProgram(vertex_shader_id, fragment_shader_id);
}

GLuint Shaders::getProgramID()
{
    return program_id;
}
