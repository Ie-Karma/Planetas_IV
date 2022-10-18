#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(std::string filename) {

    //Generacion texture ID
    unsigned char* data = NULL;
    glGenTextures(1,&glId);

    //Carga de fichero
    data = stbi_load(filename.c_str(),&w,&h, nullptr,4);

    //carga de datos en GPU
    glBindTexture(GL_TEXTURE_2D, glId);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,w,h,0,GL_RGBA,GL_UNSIGNED_BYTE,data);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    //liberar datos? cuando se dejende usar
    stbi_image_free(data);


}

void Texture::bind(int textureunitIdx) {
    glActiveTexture(GL_TEXTURE0+textureunitIdx);
    glBindTexture(GL_TEXTURE_2D,glId);
}

//void Texture::setPixel(int x, int y, char r, char g, char b, char a){
//    data[y*w*4+x*4] = r;
//}

//void Texture::updateTexture(){
//    //data a public
//    glBindTexture(GL_TEXTURE_2D, glId);
//    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,w,h,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
//
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
//}