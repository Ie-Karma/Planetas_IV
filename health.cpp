#include "inputManager.h"
#include "scene.h"
#include "system.h"
#include "health.h"

int hp = 3;

int rest(){

    //llamar a cambio de alien
    //cambiar posicion alien
    hp--;

    return hp;
}
