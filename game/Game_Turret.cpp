
#pragma hdrstop
#include "Game_local.h"
#include "Game_Turret.h"

CLASS_DECLARATION(idEntity, idDeployTurret)
END_CLASS


idDeployTurret::idDeployTurret() {
    nextFireTime = 0;
    fireRate = 0.2f;
    damage = 20.0f;
}


void idDeployTurret::Spawn(void) {
    fireRate = spawnArgs.GetFloat("fire_rate", "0.2");
    damage = spawnArgs.GetFloat("damage", "20");

  
    SetModel(spawnArgs.GetString("model"));


    physicsObj.SetContents(CONTENTS_SOLID);
    idClipModel* clip = new idClipModel(GetModelDefHandle());
    physicsObj.SetClipModel(clip, 1.0f);
    SetPhysics(&physicsObj);
    BecomeActive(TH_PHYSICS);

    gameLocal.Printf("Turret Spawned\n");
}


void idDeployTurret::Think(void) {
    idEntity::Think();

    // simple rate limiter
    if (gameLocal.time < nextFireTime) {
        return;
    }

    idEntity* target = NULL;
    float closestDist = idMath::INFINITY;

    // find closest enemy player
    for (int i = 0; i < gameLocal.numClients; i++) {
        idPlayer* enemy = gameLocal.GetClientByNum(i);
        if (enemy && enemy != gameLocal.GetLocalPlayer()) {
            float dist = (enemy->GetPhysics()->GetOrigin() - GetPhysics()->GetOrigin()).LengthSqr();
            if (dist < closestDist) {
                closestDist = dist;
                target = enemy;
            }
        }
    }

    // fire if target found
    if (target) {
        FireAtTarget(target);
        nextFireTime = gameLocal.time + static_cast<int>(fireRate * 1000);
    }
}


void idDeployTurret::FireAtTarget(idEntity* target) {
    idVec3 dir = target->GetPhysics()->GetOrigin() - GetPhysics()->GetOrigin();
}

void idDeployTurret::Save(idSaveGame* savefile) const {
    savefile->WriteInt(nextFireTime);
    savefile->WriteFloat(fireRate);
    savefile->WriteFloat(damage);
}

void idDeployTurret::Restore(idRestoreGame* savefile) {
    savefile->ReadInt(nextFireTime);
    savefile->ReadFloat(fireRate);
    savefile->ReadFloat(damage);
}
