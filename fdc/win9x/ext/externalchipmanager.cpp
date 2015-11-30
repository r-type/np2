/**
 * @file	externalchipmanager.cpp
 * @brief	�O���`�b�v�Ǘ��N���X�̓���̒�`���s���܂�
 */

#include "compiler.h"
#include "externalchipmanager.h"
#include <algorithm>
#include "np2.h"
#include "externalopna.h"

/*! �B��̃C���X�^���X�ł� */
CExternalChipManager CExternalChipManager::sm_instance;

/**
 * �R���X�g���N�^
 */
CExternalChipManager::CExternalChipManager()
{
}

/**
 * ������
 */
void CExternalChipManager::Initialize()
{
}

/**
 * ���
 */
void CExternalChipManager::Deinitialize()
{
	std::vector<IExternalChip*>::iterator it = m_chips.begin();
	while (it != m_chips.end())
	{
		IExternalChip* pChip = *it;
		it = m_chips.erase(it);

		pChip->Reset();
		delete pChip;
	}

	m_c86ctl.Deinitialize();
	m_juliet.Deinitialize();
	m_scci.Deinitialize();
}

/**
 * �`�b�v�m��
 * @param[in] nChipType �`�b�v �^�C�v
 * @param[in] nClock �`�b�v �N���b�N
 * @return �C���X�^���X
 */
IExternalChip* CExternalChipManager::GetInterface(IExternalChip::ChipType nChipType, UINT nClock)
{
	IExternalChip* pChip = GetInterfaceInner(nChipType, nClock);
	if (pChip == NULL)
	{
		if (nChipType == IExternalChip::kYMF288)
		{
			pChip = GetInterface(IExternalChip::kYM2608, nClock);
		}
		else if (nChipType == IExternalChip::kYM3438)
		{
			pChip = GetInterface(IExternalChip::kYMF288, nClock);
		}
	}
	return pChip;
}

/**
 * �`�b�v�m�� (Inner)
 * @param[in] nChipType �`�b�v �^�C�v
 * @param[in] nClock �`�b�v �N���b�N
 * @return �C���X�^���X
 */
IExternalChip* CExternalChipManager::GetInterfaceInner(IExternalChip::ChipType nChipType, UINT nClock)
{
	IExternalChip* pChip = NULL;

	if (np2oscfg.useromeo)
	{
		if (pChip == NULL)
		{
			pChip = m_juliet.GetInterface(nChipType, nClock);
		}
	}
	if (pChip == NULL)
	{
		pChip = m_scci.GetInterface(nChipType, nClock);
	}
	if (pChip == NULL)
	{
		pChip = m_c86ctl.GetInterface(nChipType, nClock);
	}

	// ���b�s���O
	if (pChip)
	{
		switch (nChipType)
		{
			case IExternalChip::kYM2608:
			case IExternalChip::kYM3438:
			case IExternalChip::kYMF288:
				pChip = new CExternalOpna(pChip);
				break;
		}
	}
	if (pChip)
	{
		m_chips.push_back(pChip);
	}
	return pChip;
}

/**
 * �`�b�v���
 * @param[in] pChip �`�b�v
 */
void CExternalChipManager::Release(IExternalChip* pChip)
{
	std::vector<IExternalChip*>::iterator it = std::find(m_chips.begin(), m_chips.end(), pChip);
	if (it != m_chips.end())
	{
		m_chips.erase(it);
		pChip->Reset();
		delete pChip;
	}
}

/**
 * �������Z�b�g
 */
void CExternalChipManager::Reset()
{
	for (std::vector<IExternalChip*>::iterator it = m_chips.begin(); it != m_chips.end(); ++it)
	{
		(*it)->Reset();
	}
}

/**
 * �~���[�g
 * @param[in] bMute �~���[�g
 */
void CExternalChipManager::Mute(bool bMute)
{
	for (std::vector<IExternalChip*>::iterator it = m_chips.begin(); it != m_chips.end(); ++it)
	{
		(*it)->Message(IExternalChip::kMute, static_cast<INTPTR>(bMute));
	}
}