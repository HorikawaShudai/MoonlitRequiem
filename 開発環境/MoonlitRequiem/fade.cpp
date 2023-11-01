//===========================================================
//
//�t�F�[�h�̏�������
//Author:�x�씋��
//
//===========================================================
#include "fade.h"
#include "main.h"
#include "game.h"
#include "Renderer.h"
//#include "sound.h"


CFade::CFade()
{

}
CFade::~CFade()
{

}
//=========================================================================================================
//�t�F�[�h�̏���������
//=========================================================================================================
HRESULT CFade::Init(void)
{
	

	m_Fade = FADE_NONE;
	m_ColorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffFade,
		NULL);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuffFade->Unlock();
	return S_OK;
}

//=========================================================================================================
//�t�F�[�h�̏I������
//=========================================================================================================
void CFade::Uninit(void)
{
	if (m_pVtxBuffFade != NULL)
	{
		m_pVtxBuffFade->Release();
		m_pVtxBuffFade = NULL;
	}
}

//�t�F�[�h�̍X�V����
void CFade::Update(void)
{
	if (m_Fade != FADE_NONE)
	{
		if (m_Fade == FADE_IN)
		{
			m_ColorFade.a -= 0.5f;
			if (m_ColorFade.a <= 0.0f)
			{
				m_ColorFade.a = 0.0f;
				m_Fade = FADE_NONE;
			}
		}
		else if (m_Fade == FADE_OUT)
		{
			m_ColorFade.a += 0.5f;
			if (m_ColorFade.a >= 1.0f)
			{
				m_ColorFade.a = 1.0f;
				m_Fade = FADE_IN;
				CManager::GetInstance()->SetMode(m_ModeNext);
			}
		}

		VERTEX_2D *pVtx;
		//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
		m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);
		//���_�J���[�̐ݒ�
		pVtx[0].col = m_ColorFade;
		pVtx[1].col = m_ColorFade;
		pVtx[2].col = m_ColorFade;
		pVtx[3].col = m_ColorFade;
		//���_�o�b�t�@���A�����b�N����
		m_pVtxBuffFade->Unlock();
	
	}
}

//=========================================================================================================
//�t�F�[�h�̕`�揈��
//=========================================================================================================
void CFade::Draw(void)
{
	CManager Renderer;
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();


	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, NULL);

	//�|���S��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

void CFade::SetFade(CScene::MODE ModeNext, float Fade)
{
	m_Fade = FADE_OUT;
	m_FadeCount = Fade;
	m_ModeNext = ModeNext;
	m_ColorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

CFade::FADE CFade::GetFade(void)
{
	return m_Fade;
}

CFade *CFade::Create(void)
{
	CFade *pObject = NULL;

	pObject = new CFade;
	pObject->Init();

	return pObject;
}