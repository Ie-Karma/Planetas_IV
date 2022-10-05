#include "spatialHashing.h"

SpatialHashing::SpatialHashing(std::map<int,Object*> *objList,
	int numFilas,int numColumnas,
	float minX, float minY, 
	float tamX, float tamY )
{

	this->objList=objList;
	this->numFilas=numFilas;
	this->numColumnas=numColumnas;
	this->minX=minX;
	this->minY=minY;
	this->tamX=tamX;
	this->tamY=tamY;
	

	 grid=new std::map<int,Object*>*[numFilas];
	 
	 for(int i=0;i<numFilas;i++){
	 	grid[i]=new std::map<int,Object*>[numColumnas];
	 }
	 update();
}


void SpatialHashing::update(){

	 for(int i=0;i<numFilas;i++){
	 for(int j=0;j<numColumnas;j++){

	 	grid[i][j].clear();
	 }
	 }

	for(auto obj=objList->begin();obj!=objList->end();obj++)
	{
		int key=obj->first;
		Object* object=obj->second;
		
		int coordX=(object->position.x-minX)/(tamX/numColumnas);
		int coordY=(object->position.y-minY)/(tamY/numFilas);
	
		if(((coordX>=0)&&coordX<numColumnas)&&
			((coordY>=0)&&coordY<numFilas))
			{
			
				grid[coordY][coordX][key]=object;
			}
		
	}

}


