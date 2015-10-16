/**
 * @file	externalopna.h
 * @brief	�O�� OPNA ���t�N���X�̐錾����уC���^�[�t�F�C�X�̒�`�����܂�
 */

#pragma once

class IExternalChip;

/**
 * @brief �O�� OPNA ���t�N���X
 */
class CExternalOpna
{
public:
	static CExternalOpna* GetInstance();

	CExternalOpna();
	void Initialize();
	void Deinitialize();
	bool IsEnabled() const;
	bool HasADPCM() const;
	bool IsBusy() const;
	void Reset() const;
	void WriteRegister(UINT nAddr, UINT8 cData);
	void Mute(bool bMute) const;
	void Restore(const UINT8* data, bool bOpna);

private:
	static CExternalOpna sm_instance;	//!< �B��̃C���X�^���X�ł�
	IExternalChip* m_module;			//!< ���W���[��
	bool m_bHasADPCM;					//!< ADPCM
	UINT8 m_cPsgMix;					//!< PSG �~�L�T�[
	UINT8 m_cAlgorithm[8];				//!< �A���S���Y�� �e�[�u��
	UINT8 m_cTtl[8 * 4];				//!< TTL �e�[�u��

	void WriteRegisterInner(UINT nAddr, UINT8 cData) const;
	void SetVolume(UINT nChannel, int nVolume) const;
};

/**
 * �C���X�^���X�𓾂�
 * @return �C���X�^���X
 */
inline CExternalOpna* CExternalOpna::GetInstance()
{
	return &sm_instance;
}

/**
 * �C���X�^���X�͗L��?
 * @retval true �L��
 * @retval false ����
 */
inline bool CExternalOpna::IsEnabled() const
{
	return (m_module != NULL);
}

/**
 * ADPCM �̃o�b�t�@�������Ă���?
 * @retval true �L��
 * @retval false ����
 */
inline bool CExternalOpna::HasADPCM() const
{
	return m_bHasADPCM;
}