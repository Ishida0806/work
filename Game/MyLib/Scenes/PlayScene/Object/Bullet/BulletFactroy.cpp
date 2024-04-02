//
//		File Name F BulletFactroy.cpp
//		ProductionF 2023/7/02
//		Author@@F Î“c ‹±ˆê
// 
//      ’e‚Ì¶¬‚ğ’S‚¤Hê
// 
#include "pch.h"
#include "BulletFactroy.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Bullet/Bullet.h"

const DirectX::SimpleMath::Color BulletFactory::PLAYER_BULLETS_COLOR = DirectX::SimpleMath::Color(0.8f, 0.8f, 0.8f);
const DirectX::SimpleMath::Color BulletFactory::ENEMY_BULLETS_COLOR  = DirectX::SimpleMath::Color(0.5f, 0.2f, 0.5f);
const DirectX::SimpleMath::Color BulletFactory::BOSS_BULLETS_COLOR   = DirectX::SimpleMath::Color(1.0f, 0.5f, 0.5f);

/// <summary>
/// ’e‚ğì¬‚·‚é
/// </summary>
/// <param name="ownerID">Š—LÒ</param>
/// <param name="number">ì‚Á‚½ŒÂ”</param>
/// <param name="position">À•W</param>
/// <param name="rotate">‰ñ“]Šp</param>
/// <param name="color">F</param>
/// <param name="scale">‘å‚«‚³</param>
/// <param name="used">g—p’†‚©</param>
/// <returns>Š—LÒ</returns>
std::unique_ptr<Bullet> BulletFactory::CreateBullets(
    OwnerID ownerID,
    const DirectX::SimpleMath::Vector3& position, 
    const DirectX::SimpleMath::Quaternion& rotate,
    const DirectX::SimpleMath::Color& color,
    int power,
    float scale,
    bool used
)
{
   using namespace DirectX::SimpleMath;
    //  ”z—ñ‚ÌéŒ¾
   std::unique_ptr<Bullet> bullet;
   // –C’e‚ğ¶¬‚·‚é
   bullet = std::make_unique<Bullet>(ownerID, position, rotate, color, power ,scale ,used);
   // –C’e‚ğ‰Šú‰»‚·‚é
   bullet->Initialize();
   // –C’e‚ğ•Ô‚·
   return move(bullet);
}

