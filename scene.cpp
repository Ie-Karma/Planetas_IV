#include "scene.h"


Scene::Scene(){

        objList=new std::map<int,Object*>();
        addedObjList=new std::map<int,Object*>();
        sceneGrid=new SpatialHashing(objList, 8,8 ,-1.0f ,-1.0f , 2.0f, 2.0f);
}

void Scene::setCamera(Camera* cam, GLFWwindow* window){

	this->cam=cam;
	cam->window = window;
}

Camera* Scene::getCamera(){
	return cam;
}




void Scene::deleteObject(Object* obj){
	
	auto it=objList->find(obj->id);
	it->second->markedDelete=true;

}


std::map<int,Object*> * Scene::getObjList(){
	return objList;
}


void Scene::addObject(Object* obj){
        (*addedObjList)[obj->id]=(obj);
        obj->computeMatrix();
}


void Scene::step(double timeStep)
{

	for(auto it=addedObjList->begin();
            it!=addedObjList->end();
            it++)
    {

        (*objList)[it->first]=it->second;
    }
    addedObjList->clear();


    for(auto it=objList->begin();
		it!=objList->end();
		it++)
	{
		it->second->updateCollider();	
	}
	
	sceneGrid->update();
	cam->step();
	for(auto it=objList->begin();
		it!=objList->end();
		it++)
	{
		it->second->step();	
	}

	for(auto it=objList->begin();
		it!=objList->end();
		)
	{
		if(it->second->markedDelete)
		{	delete it->second;
			it=objList->erase(it);
		}else{
			it++;
		}
	}


}




Scene::~Scene()
{
	for(auto it=objList->begin();
		it!=objList->end();
		it++)
	{
		delete it->second;
	}
	delete objList;
}


std::vector<Object*>* Scene::getCollisions(int idType, Object* obj)
{
	std::vector<Object*>* objects=new std::vector<Object*>();

	int numFilas=sceneGrid->numFilas;
	int numColumnas=sceneGrid->numColumnas;

	int coordX=(obj->position.x-sceneGrid->minX)/(sceneGrid->tamX/numColumnas);
	int coordY=(obj->position.y-sceneGrid->minY)/(sceneGrid->tamY/numFilas);
		
	for(int i=-1;i<2;i++)
	for(int j=-1;j<2;j++)
	{
	
		if((((coordX+j)>=0)&&(coordX+j)<numColumnas)&&
			(((coordY+i)>=0)&&(coordY+i)<numFilas))
		{
		
			for(auto it=sceneGrid->grid[i+coordY][j+coordX].begin();
					it!=sceneGrid->grid[i+coordY][j+coordX].end();
					it++)
				{
					if((it->second->typeObject==idType)&&(it->second->collider->collision(obj->collider))){
						objects->push_back(it->second);
					}
				}
		}
	}
	return objects;

}
















