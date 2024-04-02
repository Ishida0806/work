//
//		File Name �F BulletFactroy.cpp
//		Production�F 2023/7/02
//		Author�@�@�F �Γc ����
// 
//      �e�̐�����S���H��
// 
#include "pch.h"
#include "BulletFactroy.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Bullet/Bullet.h"

const DirectX::SimpleMath::Color BulletFactory::PLAYER_BULLETS_COLOR = DirectX::SimpleMath::Color(0.8f, 0.8f, 0.8f);
const DirectX::SimpleMath::Color BulletFactory::ENEMY_BULLETS_COLOR  = DirectX::SimpleMath::Color(0.5f, 0.2f, 0.5f);
const DirectX::SimpleMath::Color BulletFactory::BOSS_BULLETS_COLOR   = DirectX::SimpleMath::Color(1.0f, 0.5f, 0.5f);

/// <summary>
/// �e���쐬����
/// </summary>
/// <param name="ownerID">���L��</param>
/// <param name="number">�������</param>
/// <param name="position">���W</param>
/// <param name="rotate">��]�p</param>
/// <param name="color">�F</param>
/// <param name="scale">�傫��</param>
/// <param name="used">�g�p����</param>
/// <returns>���L��</returns>
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
    //  �z��̐錾
   std::unique_ptr<Bullet> bullet;
   // �C�e�𐶐�����
   bullet = std::make_unique<Bullet>(ownerID, position, rotate, color, power ,scale ,used);
   // �C�e������������
   bullet->Initialize();
   // �C�e��Ԃ�
   return move(bullet);
}

