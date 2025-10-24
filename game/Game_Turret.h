#ifndef _GAME_TURRET_H_
#define _GAME_TURRET_H_

#include "Game_local.h"

class idDeployTurret : public idEntity
{
public:

    CLASS_PROTOTYPE(idDeployTurret);

    idDeployTurret();

    void Spawn(void);
    void Think(void);
    void FireAtTarget(idEntity* target);
    void Save(idSaveGame* savefile) const;
    void Restore(idRestoreGame* savefile);

private:

    int nextFireTime;
    float fireRate;
    float damage;

    void InitTurret(void);

    idPhysics_RigidBody physicsObj;
};


#endif