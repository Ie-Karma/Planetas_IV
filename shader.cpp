#include "shader.h"
#include <fstream>
#include <sstream>

GLShader::	GLShader(std::string vshader, std::string fshader){

	this->vshader=vshader;
	this->fshader=fshader;
	this->tesControlShader = "";
	this->tesEvalShader = "";
	
	compileShaders();
}

GLShader::GLShader(std::string vshader, std::string fshader, std::string tesControlShader, std::string tesEvalShader) {

	this->vshader = vshader;
	this->fshader = fshader;
	this->tesControlShader = tesControlShader;
	this->tesEvalShader = tesEvalShader;

	compileShaders();
}




std::string GLShader::readFile(std::string fileName) {
	std::ifstream inFile;
	inFile.open(fileName); //open the input file

	std::stringstream strStream;
	strStream << inFile.rdbuf(); //read the file

	std::string str = strStream.str(); //str holds the content of the file
	return str;

}


void GLShader::checkCompileError(unsigned int program)
{

	GLint retCode;
	char errorLog[1024];
	glGetShaderiv(program, GL_LINK_STATUS, &retCode);
	if ( retCode == GL_FALSE ) {
		glGetProgramInfoLog(program, sizeof(errorLog), NULL, errorLog);
		std::cout<<errorLog<<std::endl;
	}

}


void GLShader::checkLinkError(unsigned int program)
{

	GLint retCode;
	char errorLog[1024];
	glGetProgramiv(program, GL_LINK_STATUS, &retCode);
	if ( retCode == GL_FALSE ) {
		glGetProgramInfoLog(program, sizeof(errorLog), NULL, errorLog);
		std::cout<<errorLog<<std::endl;
	}

}


void GLShader::compileShaders(){


	this->programID = glCreateProgram();
	std::string vertexCode=readFile(vshader);
	std::string fragmentCode=readFile(fshader);
	
	const char* v=vertexCode.c_str();
	const char* f=fragmentCode.c_str();

	int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID , 1, &v, nullptr);
	glCompileShader(vertexShaderID );
	
	checkCompileError(vertexShaderID);
	
	int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID , 1, &f, nullptr);
	glCompileShader(fragmentShaderID );
	
	checkCompileError(fragmentShaderID);
	
	if (this->tesControlShader != "" && this->tesEvalShader != "")
	{
		std::string tesControlShaderCode = readFile(this->tesControlShader);
		std::string tesEvalShaderCode = readFile(this->tesEvalShader);
		const char* tesc = tesControlShaderCode.c_str();
		const char* tese = tesEvalShaderCode.c_str();
		
		int tesControlShaderID = glCreateShader(GL_TESS_CONTROL_SHADER);
		glShaderSource(tesControlShaderID, 1, &tesc, nullptr);
		glCompileShader(tesControlShaderID);
		
		checkCompileError(tesControlShaderID);
		
		int tesEvalShaderID = glCreateShader(GL_TESS_EVALUATION_SHADER);
		glShaderSource(tesEvalShaderID, 1, &tese, nullptr);
		glCompileShader(tesEvalShaderID);
		
		checkCompileError(tesEvalShaderID);
		
		glAttachShader(this->programID, tesControlShaderID);
		glAttachShader(this->programID, tesEvalShaderID);
	}
	
	glAttachShader(programID, vertexShaderID );
	glAttachShader(programID, fragmentShaderID );
	
	glLinkProgram(programID);
	
	checkLinkError(programID);

}
