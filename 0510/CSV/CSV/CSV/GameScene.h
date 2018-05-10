#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define MAP_HEIGHT 23
#define MAP_WIDTH 60
#define TIPSIZE 64

struct CUSTOMVERTEX
{
	FLOAT	x, y, z, rhw;
	DWORD	color;
	FLOAT	tu, tv;
};

struct PLAYERSTATE
{
	float PosX, PosY;
	float RectX, RectY;
	bool AnimReverse;
	bool SkyFlag;
	bool IsLeft;
};

enum GAME_TEXTURE
{
	BACKGROUND_TEX,
	MAP_GROUND_TEX,
	PLAYER_RIGHT_TEX,
	PLAYER_LEFT_TEX,
	GAMESCENE_MAX
};

enum KEYSTATE 
{
	PUSH,
	RELEASE,
	ON,
	OFF
};
enum KEYKIND 
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	FIRE,
	QUIT,
	KEYMAX
};

extern LPDIRECT3D9			g_pDirect3D;		// DirectX�I�u�W�F�N�g�̃|�C���^
extern LPDIRECT3DDEVICE9	g_pDirect3DDevice;	// DirectX�f�o�C�X�̃|�C���^

// �Q�[���V�[���̐���֐�
void GameSceneControl();

// �Q�[���V�[���̕`��֐�
void GameSceneDraw();

// �Q�[���V�[���̏������֐�
void GameSceneInit();

// �Q�[���V�[���̉���֐�
void GameSceneFree();

void MapLoad(const char* mapdata);

void MapDraw();

void PlayerDraw();
void KeyCheck(int VK, KEYKIND st);