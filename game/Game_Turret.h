#ifndef _GAME_TURRET_H_
#define _GAME_TURRET_H_

#include "Game_local.h"

class idDeployTurret : public idEntity
{
public:

    CLASS_STATES_PROTOTYPE(idDeployTurret);

    idDeployTurret();

    void spawn(void);
    void Think(void);
    void FireAtTarget(idEntity* target);

private:

    float nextFireTime;
    float fireRate;
    float dmamge;

};

#endif