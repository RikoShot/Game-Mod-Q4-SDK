#include "Game_local.h"
#include "Game_Turret.h"

CLASS_DECLARATION( idEntity, idDeployTurret )
END_CLASS

idDeployTurret::idDeployTurret()
{
    nextFireTime = 0;
    fireRate = 0.2f;
    damage = 20.0f;

}

void ideployTurret::Spawn( void )
{
    fireRate = spawnArgs.GetFloat( "fire_rate", "0.2" );
    damage = spawnArgs.GetFloat( "damage", "20" );
}

SetModel( spawnArgs.GetString( "model" ) );
{
    physicsObj.SetContents( CONTENTS_SOLID );
    physicsObj.SetClipModel( new idClipModel( GetAFPhysics()->GetClipModel() ->Handle(), 0 ), 1.0f );
    SetPhysics( &physicsObj );
    BecomeActive( TH_PHYSICS );

    gamelocal.Print("Plant Spwaned\n");
}

void idDeployTurret::Think(void)
{
    idEntity::Think();

    if (gameLocal.time < nextFireTime)
    {
        return;
    }

    idEntity* target = NULL();
    float closestDist = idMath::INFINITY;

    for (int i = 0; i < gameLocal.numClients; i++)
    {
        idPlayer* enemy = gameLocal.GetClientByNum(i);
        if(enemy && enemy != gameLocal.GetLocalPlayer())
        {
            float dist = (enemy->GetOrigin() - GetOrigin()).LengthSqr();
            if(dist < closestDist)
            {
                closestDist = dist;
                target = enemy;
            }
        }
    }

    if (target)
    {
       FireAtTarget(target);
         nextFireTime = gameLocal.time + static_cast<int>(fireRate * 10);
    }
}

void idDeployTurret::FireAtTarget(idEntity* target)
{
    idvec3 dir = target->GetOrigin() - GetOrigin();
    dir.Normalize();
    idProjectile* projectile = static_cast<idProjectile*>(gameLocal.SpawnEntityType(idProjectile::Type, NULL, NULL, GetOrigin(), dir.ToAngles()));
    target->Damage(this, this, dir * 100.0f, "damage_turret", 1.0f,);
}
