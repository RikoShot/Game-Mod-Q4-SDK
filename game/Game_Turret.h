#ifndef _GAME_TURRET_H_
#define _GAME_TURRET_H_

#include "Game_local.h"

class idDeployTurret : public idEntity
{
public:

    CLASS_PROTOTYPE(idDeployTurret);

    idDeployTurret();

    virtual void spawn(void);
    virtual void Think(void);
    virtual void FireAtTarget(idEntity* target);
    virtual void Save(idSaveGame* savefile) const;
    virtual void Restore(idRestoreGame* savefile);

private:

    int nextFireTime;
    float fireRate;
    float dmamge;

    void InitTurret(void);

    idPhysics_RigidBody physicsObj;
};

#endif