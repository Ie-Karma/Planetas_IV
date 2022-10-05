#include "collider.h"
#include "object.h"

Box2D::Box2D(){

}

bool Box2D::collision(BV* _b2){
	Box2D* b2=(Box2D*)_b2;	
	
        if((xMin<b2->xMax && xMin>b2->xMin)&&(yMin<b2->yMax &&yMin>b2->yMin)) return true;
        if((xMin<b2->xMax && xMin>b2->xMin)&&(yMax<b2->yMax &&yMax>b2->yMin)) return true;
        if((xMax<b2->xMax && xMax>b2->xMin)&&(yMin<b2->yMax &&yMin>b2->yMin)) return true;
        if((xMax<b2->xMax && xMax>b2->xMin)&&(yMax<b2->yMax &&yMax>b2->yMin)) return true;
	
	return false;
}

void Box2D::init(Object* obj,int triangleIdx){
	this->obj=obj;
	this->triangleIdx=triangleIdx;
	update();
}


void Box2D::update(){
	
		std::vector<vertex_t>* vertexList=obj->mesh->vertexList;
		std::vector<int>* faceList=obj->mesh->faceList;
        obj->computeMatrix();
        
        glm::mat4 m=obj->getMatrix();
		int numVertex=vertexList->size();
		glm::vec4 newPos;

        vertex_t v=vertexList->data()[faceList->data()[triangleIdx*3]];
        
        
        newPos=m*v.posicion;

        xMin=xMax=newPos.x;
        yMin=yMax=newPos.y;

		for(int idV=(triangleIdx*3)+1; idV<(triangleIdx*3+3); idV++)
		{   
			vertex_t v=vertexList->data()[faceList->data()[idV]];
			newPos=m*v.posicion;
			
			if(xMin>newPos.x)xMin=newPos.x;
			else if(xMax<newPos.x)xMax=newPos.x;
			
			if(yMin>newPos.y)yMin=newPos.y;
			else if(yMax<newPos.y)yMax=newPos.y;
		}
}



Collider::Collider(Object* obj)
{

	boxList=new std::vector<BV*>();
	int numTriangles=obj->mesh->faceList->size()/3;
	//newBox->init(obj);
	for(int i=0;i<numTriangles;i++)
	{	
		BV* newBox=new Box2D();
		newBox->init(obj, i);
		boxList->push_back(newBox);
	}
	
}
	
void Collider::update(){
	for(auto it=boxList->begin();it!=boxList->end();it++)
		(*it)->update();	
}

bool Collider::collision(Collider* c2){
        auto it1=boxList->begin();

        bool collision=false;
        while(!collision && it1!=boxList->end())
		{
			auto it2=c2->boxList->begin();
			while(!collision && it2!=c2->boxList->end())
			{
		        collision=(*it1)->collision(*it2)||(*it2)->collision(*it1) ;
				it2++;
			}
			it1++;
		
        }
        return collision;
	
}




