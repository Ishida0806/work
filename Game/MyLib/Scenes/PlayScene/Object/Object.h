//
//		File Name �F Object.h
//		Production�F 2023/6/03
//		Author�@�@�F �Γc ����	
//	
#pragma once

//	�C���^�[�t�F�C�X��錾����
interface IObject
{
	//	���z�f�X�g���N�^
	virtual ~IObject() = default;
	//	����������
	virtual void Initialize() = 0;
	//	�X�V����
	virtual void Update(const DX::StepTimer& timer) = 0;
	//	�`�揈��
	virtual void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) = 0;
	//	�I������	
	virtual void Finalize() = 0;
};

class Object : public IObject
{
	//	�񋓌^
public:

	// �I�u�W�F�N�g�̎��
	enum class ObjectType
	{
		NormalEnemy,
		TackleEnemy,
		BossEnemy,
		Bullet,
		Player,
		Sord,
		Item
	};

	// �R���W�����̌`��
	enum class ColisionShape
	{
		Sphere,
		Box,
		Capsule
	};

	//	�����蔻��̎��
	enum class ColisionType
	{
		NormalColision,
		AbilityColision,
		SearchColision,		
	};

	//	�ϐ�
private:
	//	���W
	DirectX::SimpleMath::Vector3									m_position;
	//	�傫��
	DirectX::SimpleMath::Vector3									m_scale;
	//	��]�p
	DirectX::SimpleMath::Quaternion								    m_rotate;
	//	�p�x
	float															m_angle;
	//	���ʎq	
	ObjectType														m_objType;
	//	������
	std::unordered_map<ColisionType, Collision::CollisionBehavior*> m_shapeColision;
		
	//	�A�N�Z�T
public:

	//	���W���擾����
	inline DirectX::SimpleMath::Vector3		GetPosition()   const { return m_position; }
	//	�傫�����擾����
	inline DirectX::SimpleMath::Vector3		GetScale()		const { return m_scale; }
	//	��]�p���擾����
	inline DirectX::SimpleMath::Quaternion  GetRotate()	    const { return m_rotate; }
	//	�p�x���擾����
	inline float							GetAngle()	    const { return m_angle; }
	//	ID���擾����
	inline ObjectType						GetType()	    const { return m_objType; }

	/// <summary>
	/// �ʏ�̓����蔻����擾����
	/// </summary>
	/// <param name="type">�����蔻��̎��</param>
	/// <param name="size">�傫��</param>
	/// <returns>�|�C���^�[<</returns>
	Collision::CollisionBehavior* GetColision(ColisionType type, unsigned int& size)	const;


	//	���W��ݒ肷��
	void SetPosition(const DirectX::SimpleMath::Vector3& position);
	//	�ړ��ʂ�ݒ肷��
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity);
	//	�傫����ݒ肷��
	void SetScale(const DirectX::SimpleMath::Vector3& scale);
	//	��]�p��ݒ肷��
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate);
	//	�p�x��ݒ肷��
	void SetAngle(const float& angle);
	//	���ʎq��o�^����
	void SetType(const Object::ObjectType& obj);

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Object();

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="position">���W</param>
	Object(const DirectX::SimpleMath::Vector3& position);

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="position">���W</param>
	/// <param name="rotate">��]�p</param>
	Object(const DirectX::SimpleMath::Vector3& position , const DirectX::SimpleMath::Quaternion rotate);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Object() override;

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	void Update(const DX::StepTimer& timer) override;

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="view">�r���[</param>
	/// <param name="proj">�v���W�F�N�V����</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// �����蔻���ǉ�����
	/// </summary>
	/// <param name="behavior">�����蔻��̃|�C���^�[</param>
	/// <param name="type">�����蔻��̎��</param>
	void AddColision(Collision::CollisionBehavior* behavior, ColisionType type)
	{
		m_shapeColision[type] = behavior;
	}
};