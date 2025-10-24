
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

    // Set the model for this turret from the spawnArgs
    SetModel(spawnArgs.GetString("model"));

    // Set up physics so it’s solid and doesn’t fall through the floor
    physicsObj.SetContents(CONTENTS_SOLID);
    physicsObj.SetClipModel(new idClipModel(GetPhysics()->GetClipModel()->Handle(), 0), 1.0f);
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
    d
