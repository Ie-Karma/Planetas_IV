#include "render.h"
#include <cstdlib>


Render::Render(){
	glEnable(GL_DEPTH_TEST);
	glPatchParameteri(GL_PATCH_VERTICES, 3);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	
}


void Render::setupObject(Object* obj)
{

	bufferObject_t bo;
	glGenVertexArrays(1, &bo.abo);
	glBindVertexArray(bo.abo);
	
	glGenBuffers(1,&bo.vbo);
	glGenBuffers(1,&bo.ibo);

	glBindBuffer(GL_ARRAY_BUFFER,bo.vbo);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertex_t)*obj->mesh->vertexList->size(),
					obj->mesh->vertexList->data(),GL_STATIC_DRAW);
					
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,bo.ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(int)*obj->mesh->faceList->size(),
					obj->mesh->faceList->data(),GL_STATIC_DRAW);

	boList[obj->id]=bo;	
}


void Render::drawMesh(Mesh* mesh,glm::mat4 model){


	int numFaces=(int)mesh->faceList->size()/3;
	for(int i=0;i<numFaces;i++)
	{
	glBegin(GL_TRIANGLES);
		glm::vec4 newPos;	
		for(int idV=i*3; idV<(i*3+3); idV++)
		{   
			vertex_t v=mesh->vertexList->data()[mesh->faceList->data()[idV]];
			newPos=proj*view*model*v.posicion;
			glColor3f(v.color.r,v.color.g,v.color.b);
			glVertex3f(newPos.x,newPos.y,newPos.z);
		}
	
	glEnd();
	}
}


void Render::drawObject(Object* obj){
	obj->computeMatrix();
	drawMesh(obj->mesh,obj->getMatrix());	
}




void Render::drawObjectGL4(Object* obj){

	obj->computeMatrix();
	
	bufferObject_t bo=boList[obj->id];
	
	glBindVertexArray(bo.abo);
	glBindBuffer(GL_ARRAY_BUFFER, bo.vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.ibo);


	glUseProgram(obj->shader->programID);
	unsigned int vpos=0;
	glEnableVertexAttribArray(vpos);
	glVertexAttribPointer(vpos,4,GL_FLOAT,GL_FALSE,sizeof(vertex_t),(void*)offsetof(vertex_t,posicion));

	unsigned int vcolor=1;
	glEnableVertexAttribArray(vcolor);
	glVertexAttribPointer(vcolor,4,GL_FLOAT,GL_FALSE,sizeof(vertex_t),(void*)offsetof(vertex_t,color));

	unsigned int vnorm=2;
	glEnableVertexAttribArray(vnorm);
	glVertexAttribPointer(vnorm,4,GL_FLOAT,GL_FALSE,sizeof(vertex_t),(void*)offsetof(vertex_t,normal));
	
	glm::vec4 lightPos(0.0f,0.0f,3.0f,1.0f);
	glm::vec4 camPos(cam->getPosition(), 1.0f);

	int textureUnit = 0;
	obj->mesh->tex->bind(textureUnit);

	
	glUniformMatrix4fv(0,1,GL_FALSE,&(proj*view*obj->getMatrix())[0][0]);	
	glUniformMatrix4fv(1,1,GL_FALSE,&(obj->getMatrix())[0][0]);	
	glUniform4fv(2,1,&lightPos[0]);
	glUniform1i(3, textureUnit);
	glUniform1i(4, obj->mesh->tex->textType);
	glUniform4fv(5, 1, &camPos[0]);
	glUniform1f(6, obj->mesh->radius);	


	//Pintar lineas
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glDisable(GL_CULL_FACE);


	if (obj->mesh->tex->textType == 0) {
		glDrawElements(GL_PATCHES, obj->mesh->faceList->size(), GL_UNSIGNED_INT, nullptr);

	}

	if (obj->mesh->tex->textType == 2) {
		glDrawElements(GL_TRIANGLES, obj->mesh->faceList->size(), GL_UNSIGNED_INT, nullptr);
	}
}


void Render::drawScene(Scene* scene)
{

	Camera* cam=scene->getCamera();
	std::map<int,Object*> *addedObjList=scene->addedObjList;
	
	for(auto it=addedObjList->begin();
            it!=addedObjList->end();
            it++)
    {

        setupObject(it->second);
    }
    
	cam->computeMatrix();
	view=cam->getMatrix();
	proj=cam->getProjectionMatrix();
	std::map<int,Object*>* objList=scene->getObjList();	
	
	for(auto it=objList->begin();
		it!=objList->end();
		it++)
	{
		drawObjectGL4(it->second);
	}

}

void Render::setCamera(Camera* cam, GLFWwindow* window) {

	this->cam = cam;
	cam->window = window;
}









