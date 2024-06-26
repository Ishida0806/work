//
//		File Name ： BulletFactroy.cpp
//		Production： 2023/7/02
//		Author　　： 石田 恭一
// 
//      弾の生成を担う工場
// 
#include "pch.h"
#include "BulletFactroy.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Bullet/Bullet.h"

const DirectX::SimpleMath::Color BulletFactory::PLAYER_BULLETS_COLOR = DirectX::SimpleMath::Color(0.8f, 0.8f, 0.8f);
const DirectX::SimpleMath::Color BulletFactory::ENEMY_BULLETS_COLOR  = DirectX::SimpleMath::Color(0.5f, 0.2f, 0.5f);
const DirectX::SimpleMath::Color BulletFactory::BOSS_BULLETS_COLOR   = DirectX::SimpleMath::Color(1.0f, 0.5f, 0.5f);

/// <summary>
/// 弾を作成する
/// </summary>
/// <param name="ownerID">所有者</param>
/// <param name="number">作った個数</param>
/// <param name="position">座標</param>
/// <param name="rotate">回転角</param>
/// <param name="color">色</param>
/// <param name="scale">大きさ</param>
/// <param name="used">使用中か</param>
/// <returns>所有者</returns>
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
    //  配列の宣言
   std::unique_ptr<Bullet> bullet;
   // 砲弾を生成する
   bullet = std::make_unique<Bullet>(ownerID, position, rotate, color, power ,scale ,used);
   // 砲弾を初期化する
   bullet->Initialize();
   // 砲弾を返す
   return move(bullet);
}

