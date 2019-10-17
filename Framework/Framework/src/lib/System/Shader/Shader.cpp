#include "Shader.h"
#include "Engine\EngineMacro.h"

GLuint CShader::Compile(GLuint type, const std::string &text)
{
	//shader�̐���
	GLuint shader = glCreateShader(type);

	const char* text_ptr = text.c_str();
	//char**���K�v
	//�I�u�W�F�N�g�փV�F�[�_�[��n��
	glShaderSource(shader, 1, &text_ptr, 0);
	//�R���p�C��
	glCompileShader(shader);
#if DEBUG_ENABLE
	//�R���p�C���G���[�`�F�b�N
	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_FALSE) {
		GLint length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		//�G���[���e���o��
		std::string log(length + 1, ' ');
		glGetShaderInfoLog(shader, length, &length, &log[0]);
		std::cout << "Compaile Error:" << log << std::endl;

		return GL_FALSE;
	}
#endif // _DEBUG
	return shader;
}
void CShader::Setup(const GLuint program, const std::string &v_source, const std::string &f_source) {
	//�V�F�[�_�[�̃R���p�C��
	GLint status;
	GLuint vertex_shader = Compile(GL_VERTEX_SHADER, v_source);
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
#if DEBUG_ENABLE
		std::cout << "VertexShader Compile is Failed " << std::endl;
#endif
		system("pause");

		return;
	}

	GLuint fragment_shader = Compile(GL_FRAGMENT_SHADER, f_source);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
#if DEBUG_ENABLE
		std::cout << "FragmentShader Compile is Failed " << std::endl;
#endif
		system("pause");

		return;
	}

	//�I�u�W�F�N�g�ɃV�F�[�_�[�I�u�W�F�N�g���A�^�b�`����
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	//�V�F�[�_�[�̃����N
	glLinkProgram(program);
#if DEBUG_ENABLE
	//�����N�G���[�`�F�b�N
	//GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLint length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

		//�G���[�o��
		std::string log(length + 1, ' ');
		glGetProgramInfoLog(program, length, &length, &log[0]);
		std::cout << "Link Error:" << log << std::endl;
	}
#endif // _DEBUG
	//�����N�����猳�f�[�^���������
	if (vertex_shader) {
		//�V�F�[�_�[����؂藣��
		glDetachShader(program, vertex_shader);
		//�V�F�[�_�[�̔j��
		glDeleteShader(vertex_shader);
	}
	if (fragment_shader) {
		//�V�F�[�_�[����؂藣��
		glDetachShader(program, fragment_shader);
		//�V�F�[�_�[�̔j��
		glDeleteShader(fragment_shader);
	}
}
	//�ǂݍ���
GLuint CShader::Read(const std::string &file) {
	//vertexshader�̓ǂݍ���(.vsh)
	std::string vsh_path = "./data/shader/" + file + ".vsh";
	std::ifstream vsh_fs(vsh_path);
	//�ǂݍ��݃G���[
	if (!vsh_fs) {
		return (GLuint)-1;
	}
	//�e�L�X�g�f�[�^��string�^�ɕϊ�
	std::string v_source((std::istreambuf_iterator<char>(vsh_fs)), std::istreambuf_iterator<char>());

	//fragmentshader�̓ǂݍ���(.fsh)
	std::string fsh_path = "./data/shader/" + file + ".fsh";
	std::ifstream fsh_fs(fsh_path);
	//�ǂݍ��݃G���[
	if (!fsh_fs) {
		return (GLuint)-1;
	}
	//�e�L�X�g�f�[�^��string�^�ɕϊ�
	std::string f_source((std::
		istreambuf_iterator<char>(fsh_fs)), std::istreambuf_iterator<char>());

	//�v���O�������ʎq�𐶐�
	GLuint program = glCreateProgram();
	//vertex��fragment�̃V�F�[�_�[�̐���
	Setup(program, v_source, f_source);
	id = program;
	return program;
}
GLint CShader::Attrib(const std::string &name) {
	return glGetAttribLocation(id, name.c_str());
}
//�V�F�[�_�[�����j�t�H�[���ϐ��̎��ʎq���擾
GLint CShader::Uniform(const std::string &name) {
	return glGetUniformLocation(id, name.data());
}
//�V�F�[�_�[�v���O�����̎g�p�J�n
void CShader::Use() {
	glUseProgram(id);
}
GLuint CShader::GetID() const
{
	return id;
}
CShader::CShader()
{
}