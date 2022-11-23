
#include "object.h"

int Object::idCounter=0;

Object::Object()
{

	this->id=idCounter;
	idCounter++;
	this->mesh=new Mesh();
	this->position=glm::vec4(0.0f,0.0f,0.0f,1.0f);
	this->modelMatrix=glm::mat4(1.0f);
	this->mesh->setColor(0,glm::vec4(1.0f,0.0f,0.0f,1.0f));
	this->mesh->setColor(1,glm::vec4(0.0f,1.0f,0.0f,1.0f));
	this->mesh->setColor(2,glm::vec4(0.0f,0.0f,1.0f,1.0f));
	this->collider=new Collider(this);

}

Object::Object(int vertex) {
	this->id = idCounter;
	idCounter++;
	this->mesh = new Mesh(vertex);
	this->shader = mesh->shader;
	this->modelMatrix = glm::mat4(1.0f);
	this->collider = new Collider(this);


}

Object::Object(std::string fileName)
{
	this->id=idCounter;
	idCounter++;
	this->mesh=new Mesh(fileName);
	this->shader=mesh->shader;	
	this->position=glm::vec4(0.0f,0.0f,0.0f,1.0f);
	this->modelMatrix=glm::mat4(1.0f);	
	this->collider=new Collider(this);
	
}

	
glm::mat4 Object::getMatrix()
{
	return this->modelMatrix;
}


void Object::computeMatrix(){
	
	glm::mat4 matT=glm::translate(glm::mat4(1.0f),this->position);
	matT=glm::rotate(matT,this->rotation.x,glm::vec3(1.0f,0,0));
	matT=glm::rotate(matT,this->rotation.y,glm::vec3(0,1.0f,0));
	matT=glm::rotate(matT,this->rotation.z,glm::vec3(0,0,1.0f));
	matT=glm::scale(matT,this->scale);
	
	this->modelMatrix=matT;
}


void Object::updateCollider(){
	collider->update();
}

void Object::step(){

	/*this->rotation.y+=0.01f;
	this->position.x+=0.01f;
	
	if(this->position.x>1.0f)
		this->position.x=-1.0f;		
		*/

}
