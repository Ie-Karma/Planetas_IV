#pragma once
#include "common.h"
#include <iostream>
class GLShader{
public:
	unsigned int programID=0xFFFFFFFF;
	std::string vshader,fshader,tesControlShader,tesEvalShader;
	
	void checkCompileError(unsigned int program);
	void checkLinkError(unsigned int program);
	
	GLShader(std::string vshader, std::string fshader);
	GLShader(std::string vshader, std::string fshader, std::string tesControlShader, std::string tesEvalShader);
	
	std::string readFile(std::string fileName);
	
	void compileShaders();
	
	
};
