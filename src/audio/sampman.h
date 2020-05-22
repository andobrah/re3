#pragma once
#include "common.h"
#include "AudioSamples.h"

#define MAX_VOLUME 127
#define MAX_FREQ   22050

struct tSample {
	int32 nOffset;
	uint32 nSize;
	int32 nFrequency;
	int32 nLoopStart;
	int32 nLoopEnd;
};

enum
{
	SAMPLEBANK_MAIN,
	SAMPLEBANK_PED,
	MAX_SAMPLEBANKS,
	SAMPLEBANK_INVALID
};

#define MAX_PEDSFX                 7
#define PED_BLOCKSIZE              79000

#define MAXPROVIDERS               64

#define MAXCHANNELS                28
#define MAXCHANNELS_SURROUND       24
#define MAX2DCHANNELS              1
#define CHANNEL2D                  MAXCHANNELS

#define MAX_STREAMS                2

#define DIGITALRATE                32000
#define DIGITALBITS                16
#define DIGITALCHANNELS            2

#define MAX_DIGITAL_MIXER_CHANNELS 32

class cSampleManager
{
	uint8   m_nEffectsVolume;
	uint8   m_nMusicVolume;
	uint8   m_nEffectsFadeVolume;
	uint8   m_nMusicFadeVolume;
	uint8   m_nMonoMode;
	char	unk;
	char    m_szCDRomRootPath[80];
	bool    m_bInitialised;
	uint8   m_nNumberOfProviders;
	char   *m_aAudioProviders[MAXPROVIDERS];
	tSample m_aSamples[TOTAL_AUDIO_SAMPLES];

public:
	
	

	cSampleManager(void);
	~cSampleManager(void);
	
	void SetSpeakerConfig(int32 nConfig);
	uint32 GetMaximumSupportedChannels(void);
	
	uint32 GetNum3DProvidersAvailable(void);
	void SetNum3DProvidersAvailable(uint32 num);
	
	char *Get3DProviderName(uint8 id);
	void Set3DProviderName(uint8 id, char *name);
	
	int8 GetCurrent3DProviderIndex(void);
	int8 SetCurrent3DProvider(uint8 which);
	
	bool IsMP3RadioChannelAvailable(void);
	
	void ReleaseDigitalHandle  (void);
	void ReacquireDigitalHandle(void);
	
	bool Initialise(void);
	void Terminate (void);
	
#ifdef AUDIO_OAL
	void UpdateSoundBuffers(void);
#endif
	
	bool CheckForAnAudioFileOnCD(void);
	char GetCDAudioDriveLetter  (void);
	
	void UpdateEffectsVolume(void);

	void SetEffectsMasterVolume(uint8 nVolume);
	void SetMusicMasterVolume  (uint8 nVolume);
	void SetEffectsFadeVolume  (uint8 nVolume);
	void SetMusicFadeVolume    (uint8 nVolume);
	void SetMonoMode           (uint8 nMode);
	
	bool LoadSampleBank    (uint8 nBank);
	void UnloadSampleBank  (uint8 nBank);
	bool IsSampleBankLoaded(uint8 nBank);
	
	bool IsPedCommentLoaded(uint32 nComment);
	bool LoadPedComment    (uint32 nComment);
	int32 GetBankContainingSound(uint32 offset);

	int32 _GetPedCommentSlot(uint32 nComment);
	
	int32  GetSampleBaseFrequency  (uint32 nSample);
	int32  GetSampleLoopStartOffset(uint32 nSample);
	int32  GetSampleLoopEndOffset  (uint32 nSample);
	uint32 GetSampleLength         (uint32 nSample);
	
	bool  UpdateReverb(void);
	
	void  SetChannelReverbFlag    (uint32 nChannel, uint8 nReverbFlag);
	bool  InitialiseChannel       (uint32 nChannel, uint32 nSfx, uint8 nBank);
	void  SetChannelEmittingVolume(uint32 nChannel, uint32 nVolume);
	void  SetChannel3DPosition    (uint32 nChannel, float fX, float fY, float fZ);
	void  SetChannel3DDistances   (uint32 nChannel, float fMax, float fMin);
	void  SetChannelVolume        (uint32 nChannel, uint32 nVolume);
	void  SetChannelPan           (uint32 nChannel, uint32 nPan);
	void  SetChannelFrequency     (uint32 nChannel, uint32 nFreq);
	void  SetChannelLoopPoints    (uint32 nChannel, uint32 nLoopStart, int32 nLoopEnd);
	void  SetChannelLoopCount     (uint32 nChannel, uint32 nLoopCount);
	bool  GetChannelUsedFlag      (uint32 nChannel);
	void  StartChannel            (uint32 nChannel);
	void  StopChannel             (uint32 nChannel);
	
	void  PreloadStreamedFile                                     (uint8 nFile, uint8 nStream);
	void  PauseStream                                        (uint8 nPauseFlag, uint8 nStream);
	void  StartPreloadedStreamedFile                                           (uint8 nStream);
	bool  StartStreamedFile                          (uint8 nFile, uint32 nPos, uint8 nStream);
	void  StopStreamedFile                                                     (uint8 nStream);
	int32 GetStreamedFilePosition                                              (uint8 nStream);
	void  SetStreamedVolumeAndPan(uint8 nVolume, uint8 nPan, uint8 nEffectFlag, uint8 nStream);
	int32 GetStreamedFileLength                                                (uint8 nStream);
	bool  IsStreamPlaying                                                      (uint8 nStream);
#ifdef AUDIO_OAL
	void  Service(void);
#endif
	bool  InitialiseSampleBanks(void);
};

extern cSampleManager SampleManager;
extern uint32 BankStartOffset[MAX_SAMPLEBANKS];

#ifdef AUDIO_OPUS
static char StreamedNameTable[][25] = {
    "AUDIO\\HEAD.OPUS",    "AUDIO\\CLASS.OPUS",   "AUDIO\\KJAH.OPUS",    "AUDIO\\RISE.OPUS",    "AUDIO\\LIPS.OPUS",    "AUDIO\\GAME.OPUS",
    "AUDIO\\MSX.OPUS",     "AUDIO\\FLASH.OPUS",   "AUDIO\\CHAT.OPUS",    "AUDIO\\HEAD.OPUS",    "AUDIO\\POLICE.OPUS",  "AUDIO\\CITY.OPUS",
    "AUDIO\\WATER.OPUS",   "AUDIO\\COMOPEN.OPUS", "AUDIO\\SUBOPEN.OPUS", "AUDIO\\JB.OPUS",      "AUDIO\\BET.OPUS",     "AUDIO\\L1_LG.OPUS",
    "AUDIO\\L2_DSB.OPUS",  "AUDIO\\L3_DM.OPUS",   "AUDIO\\L4_PAP.OPUS",  "AUDIO\\L5_TFB.OPUS",  "AUDIO\\J0_DM2.OPUS",  "AUDIO\\J1_LFL.OPUS",
    "AUDIO\\J2_KCL.OPUS",  "AUDIO\\J3_VH.OPUS",   "AUDIO\\J4_ETH.OPUS",  "AUDIO\\J5_DST.OPUS",  "AUDIO\\J6_TBJ.OPUS",  "AUDIO\\T1_TOL.OPUS",
    "AUDIO\\T2_TPU.OPUS",  "AUDIO\\T3_MAS.OPUS",  "AUDIO\\T4_TAT.OPUS",  "AUDIO\\T5_BF.OPUS",   "AUDIO\\S0_MAS.OPUS",  "AUDIO\\S1_PF.OPUS",
    "AUDIO\\S2_CTG.OPUS",  "AUDIO\\S3_RTC.OPUS",  "AUDIO\\S5_LRQ.OPUS",  "AUDIO\\S4_BDBA.OPUS", "AUDIO\\S4_BDBB.OPUS", "AUDIO\\S2_CTG2.OPUS",
    "AUDIO\\S4_BDBD.OPUS", "AUDIO\\S5_LRQB.OPUS", "AUDIO\\S5_LRQC.OPUS", "AUDIO\\A1_SSO.OPUS",  "AUDIO\\A2_PP.OPUS",   "AUDIO\\A3_SS.OPUS",
    "AUDIO\\A4_PDR.OPUS",  "AUDIO\\A5_K2FT.OPUS", "AUDIO\\K1_KBO.OPUS",  "AUDIO\\K2_GIS.OPUS",  "AUDIO\\K3_DS.OPUS",   "AUDIO\\K4_SHI.OPUS",
    "AUDIO\\K5_SD.OPUS",   "AUDIO\\R0_PDR2.OPUS", "AUDIO\\R1_SW.OPUS",   "AUDIO\\R2_AP.OPUS",   "AUDIO\\R3_ED.OPUS",   "AUDIO\\R4_GF.OPUS",
    "AUDIO\\R5_PB.OPUS",   "AUDIO\\R6_MM.OPUS",   "AUDIO\\D1_STOG.OPUS", "AUDIO\\D2_KK.OPUS",   "AUDIO\\D3_ADO.OPUS",  "AUDIO\\D5_ES.OPUS",
    "AUDIO\\D7_MLD.OPUS",  "AUDIO\\D4_GTA.OPUS",  "AUDIO\\D4_GTA2.OPUS", "AUDIO\\D6_STS.OPUS",  "AUDIO\\A6_BAIT.OPUS", "AUDIO\\A7_ETG.OPUS",
    "AUDIO\\A8_PS.OPUS",   "AUDIO\\A9_ASD.OPUS",  "AUDIO\\K4_SHI2.OPUS", "AUDIO\\C1_TEX.OPUS",  "AUDIO\\EL_PH1.OPUS",  "AUDIO\\EL_PH2.OPUS",
    "AUDIO\\EL_PH3.OPUS",  "AUDIO\\EL_PH4.OPUS",  "AUDIO\\YD_PH1.OPUS",  "AUDIO\\YD_PH2.OPUS",  "AUDIO\\YD_PH3.OPUS",  "AUDIO\\YD_PH4.OPUS",
    "AUDIO\\HD_PH1.OPUS",  "AUDIO\\HD_PH2.OPUS",  "AUDIO\\HD_PH3.OPUS",  "AUDIO\\HD_PH4.OPUS",  "AUDIO\\HD_PH5.OPUS",  "AUDIO\\MT_PH1.OPUS",
    "AUDIO\\MT_PH2.OPUS",  "AUDIO\\MT_PH3.OPUS",  "AUDIO\\MT_PH4.OPUS",  "AUDIO\\MISCOM.OPUS",  "AUDIO\\END.OPUS",     "AUDIO\\lib_a1.OPUS",
    "AUDIO\\lib_a2.OPUS",  "AUDIO\\lib_a.OPUS",   "AUDIO\\lib_b.OPUS",   "AUDIO\\lib_c.OPUS",   "AUDIO\\lib_d.OPUS",   "AUDIO\\l2_a.OPUS",
    "AUDIO\\j4t_1.OPUS",   "AUDIO\\j4t_2.OPUS",   "AUDIO\\j4t_3.OPUS",   "AUDIO\\j4t_4.OPUS",   "AUDIO\\j4_a.OPUS",    "AUDIO\\j4_b.OPUS",
    "AUDIO\\j4_c.OPUS",    "AUDIO\\j4_d.OPUS",    "AUDIO\\j4_e.OPUS",    "AUDIO\\j4_f.OPUS",    "AUDIO\\j6_1.OPUS",    "AUDIO\\j6_a.OPUS",
    "AUDIO\\j6_b.OPUS",    "AUDIO\\j6_c.OPUS",    "AUDIO\\j6_d.OPUS",    "AUDIO\\t4_a.OPUS",    "AUDIO\\s1_a.OPUS",    "AUDIO\\s1_a1.OPUS",
    "AUDIO\\s1_b.OPUS",    "AUDIO\\s1_c.OPUS",    "AUDIO\\s1_c1.OPUS",   "AUDIO\\s1_d.OPUS",    "AUDIO\\s1_e.OPUS",    "AUDIO\\s1_f.OPUS",
    "AUDIO\\s1_g.OPUS",    "AUDIO\\s1_h.OPUS",    "AUDIO\\s1_i.OPUS",    "AUDIO\\s1_j.OPUS",    "AUDIO\\s1_k.OPUS",    "AUDIO\\s1_l.OPUS",
    "AUDIO\\s3_a.OPUS",    "AUDIO\\s3_b.OPUS",    "AUDIO\\el3_a.OPUS",   "AUDIO\\mf1_a.OPUS",   "AUDIO\\mf2_a.OPUS",   "AUDIO\\mf3_a.OPUS",
    "AUDIO\\mf3_b.OPUS",   "AUDIO\\mf3_b1.OPUS",  "AUDIO\\mf3_c.OPUS",   "AUDIO\\mf4_a.OPUS",   "AUDIO\\mf4_b.OPUS",   "AUDIO\\mf4_c.OPUS",
    "AUDIO\\a1_a.OPUS",    "AUDIO\\a3_a.OPUS",    "AUDIO\\a5_a.OPUS",    "AUDIO\\a4_a.OPUS",    "AUDIO\\a4_b.OPUS",    "AUDIO\\a4_c.OPUS",
    "AUDIO\\a4_d.OPUS",    "AUDIO\\k1_a.OPUS",    "AUDIO\\k3_a.OPUS",    "AUDIO\\r1_a.OPUS",    "AUDIO\\r2_a.OPUS",    "AUDIO\\r2_b.OPUS",
    "AUDIO\\r2_c.OPUS",    "AUDIO\\r2_d.OPUS",    "AUDIO\\r2_e.OPUS",    "AUDIO\\r2_f.OPUS",    "AUDIO\\r2_g.OPUS",    "AUDIO\\r2_h.OPUS",
    "AUDIO\\r5_a.OPUS",    "AUDIO\\r6_a.OPUS",    "AUDIO\\r6_a1.OPUS",   "AUDIO\\r6_b.OPUS",    "AUDIO\\lo2_a.OPUS",   "AUDIO\\lo6_a.OPUS",
    "AUDIO\\yd2_a.OPUS",   "AUDIO\\yd2_b.OPUS",   "AUDIO\\yd2_c.OPUS",   "AUDIO\\yd2_c1.OPUS",  "AUDIO\\yd2_d.OPUS",   "AUDIO\\yd2_e.OPUS",
    "AUDIO\\yd2_f.OPUS",   "AUDIO\\yd2_g.OPUS",   "AUDIO\\yd2_h.OPUS",   "AUDIO\\yd2_ass.OPUS", "AUDIO\\yd2_ok.OPUS",  "AUDIO\\h5_a.OPUS",
    "AUDIO\\h5_b.OPUS",    "AUDIO\\h5_c.OPUS",    "AUDIO\\ammu_a.OPUS",  "AUDIO\\ammu_b.OPUS",  "AUDIO\\ammu_c.OPUS",  "AUDIO\\door_1.OPUS",
    "AUDIO\\door_2.OPUS",  "AUDIO\\door_3.OPUS",  "AUDIO\\door_4.OPUS",  "AUDIO\\door_5.OPUS",  "AUDIO\\door_6.OPUS",  "AUDIO\\t3_a.OPUS",
    "AUDIO\\t3_b.OPUS",    "AUDIO\\t3_c.OPUS",    "AUDIO\\k1_b.OPUS",    "AUDIO\\cat1.OPUS"};
#else
static char StreamedNameTable[][25]=
{
	"AUDIO\\HEAD.WAV",
	"AUDIO\\CLASS.WAV",
	"AUDIO\\KJAH.WAV",
	"AUDIO\\RISE.WAV",
	"AUDIO\\LIPS.WAV",
	"AUDIO\\GAME.WAV",
	"AUDIO\\MSX.WAV",
	"AUDIO\\FLASH.WAV",
	"AUDIO\\CHAT.WAV",
	"AUDIO\\HEAD.WAV",
	"AUDIO\\POLICE.WAV",
	"AUDIO\\CITY.WAV",
	"AUDIO\\WATER.WAV",
	"AUDIO\\COMOPEN.WAV",
	"AUDIO\\SUBOPEN.WAV",
	"AUDIO\\JB.MP3",
	"AUDIO\\BET.MP3",
	"AUDIO\\L1_LG.MP3",
	"AUDIO\\L2_DSB.MP3",
	"AUDIO\\L3_DM.MP3",
	"AUDIO\\L4_PAP.MP3",
	"AUDIO\\L5_TFB.MP3",
	"AUDIO\\J0_DM2.MP3",
	"AUDIO\\J1_LFL.MP3",
	"AUDIO\\J2_KCL.MP3",
	"AUDIO\\J3_VH.MP3",
	"AUDIO\\J4_ETH.MP3",
	"AUDIO\\J5_DST.MP3",
	"AUDIO\\J6_TBJ.MP3",
	"AUDIO\\T1_TOL.MP3",
	"AUDIO\\T2_TPU.MP3",
	"AUDIO\\T3_MAS.MP3",
	"AUDIO\\T4_TAT.MP3",
	"AUDIO\\T5_BF.MP3",
	"AUDIO\\S0_MAS.MP3",
	"AUDIO\\S1_PF.MP3",
	"AUDIO\\S2_CTG.MP3",
	"AUDIO\\S3_RTC.MP3",
	"AUDIO\\S5_LRQ.MP3",
	"AUDIO\\S4_BDBA.MP3",
	"AUDIO\\S4_BDBB.MP3",
	"AUDIO\\S2_CTG2.MP3",
	"AUDIO\\S4_BDBD.MP3",
	"AUDIO\\S5_LRQB.MP3",
	"AUDIO\\S5_LRQC.MP3",
	"AUDIO\\A1_SSO.WAV",
	"AUDIO\\A2_PP.WAV",
	"AUDIO\\A3_SS.WAV",
	"AUDIO\\A4_PDR.WAV",
	"AUDIO\\A5_K2FT.WAV",
	"AUDIO\\K1_KBO.MP3",
	"AUDIO\\K2_GIS.MP3",
	"AUDIO\\K3_DS.MP3",
	"AUDIO\\K4_SHI.MP3",
	"AUDIO\\K5_SD.MP3",
	"AUDIO\\R0_PDR2.MP3",
	"AUDIO\\R1_SW.MP3",
	"AUDIO\\R2_AP.MP3",
	"AUDIO\\R3_ED.MP3",
	"AUDIO\\R4_GF.MP3",
	"AUDIO\\R5_PB.MP3",
	"AUDIO\\R6_MM.MP3",
	"AUDIO\\D1_STOG.MP3",
	"AUDIO\\D2_KK.MP3",
	"AUDIO\\D3_ADO.MP3",
	"AUDIO\\D5_ES.MP3",
	"AUDIO\\D7_MLD.MP3",
	"AUDIO\\D4_GTA.MP3",
	"AUDIO\\D4_GTA2.MP3",
	"AUDIO\\D6_STS.MP3",
	"AUDIO\\A6_BAIT.WAV",
	"AUDIO\\A7_ETG.WAV",
	"AUDIO\\A8_PS.WAV",
	"AUDIO\\A9_ASD.WAV",
	"AUDIO\\K4_SHI2.MP3",
	"AUDIO\\C1_TEX.MP3",
	"AUDIO\\EL_PH1.MP3",
	"AUDIO\\EL_PH2.MP3",
	"AUDIO\\EL_PH3.MP3",
	"AUDIO\\EL_PH4.MP3",
	"AUDIO\\YD_PH1.MP3",
	"AUDIO\\YD_PH2.MP3",
	"AUDIO\\YD_PH3.MP3",
	"AUDIO\\YD_PH4.MP3",
	"AUDIO\\HD_PH1.MP3",
	"AUDIO\\HD_PH2.MP3",
	"AUDIO\\HD_PH3.MP3",
	"AUDIO\\HD_PH4.MP3",
	"AUDIO\\HD_PH5.MP3",
	"AUDIO\\MT_PH1.MP3",
	"AUDIO\\MT_PH2.MP3",
	"AUDIO\\MT_PH3.MP3",
	"AUDIO\\MT_PH4.MP3",
	"AUDIO\\MISCOM.WAV",
	"AUDIO\\END.MP3",
	"AUDIO\\lib_a1.WAV",
	"AUDIO\\lib_a2.WAV",
	"AUDIO\\lib_a.WAV",
	"AUDIO\\lib_b.WAV",
	"AUDIO\\lib_c.WAV",
	"AUDIO\\lib_d.WAV",
	"AUDIO\\l2_a.WAV",
	"AUDIO\\j4t_1.WAV",
	"AUDIO\\j4t_2.WAV",
	"AUDIO\\j4t_3.WAV",
	"AUDIO\\j4t_4.WAV",
	"AUDIO\\j4_a.WAV",
	"AUDIO\\j4_b.WAV",
	"AUDIO\\j4_c.WAV",
	"AUDIO\\j4_d.WAV",
	"AUDIO\\j4_e.WAV",
	"AUDIO\\j4_f.WAV",
	"AUDIO\\j6_1.WAV",
	"AUDIO\\j6_a.WAV",
	"AUDIO\\j6_b.WAV",
	"AUDIO\\j6_c.WAV",
	"AUDIO\\j6_d.WAV",
	"AUDIO\\t4_a.WAV",
	"AUDIO\\s1_a.WAV",
	"AUDIO\\s1_a1.WAV",
	"AUDIO\\s1_b.WAV",
	"AUDIO\\s1_c.WAV",
	"AUDIO\\s1_c1.WAV",
	"AUDIO\\s1_d.WAV",
	"AUDIO\\s1_e.WAV",
	"AUDIO\\s1_f.WAV",
	"AUDIO\\s1_g.WAV",
	"AUDIO\\s1_h.WAV",
	"AUDIO\\s1_i.WAV",
	"AUDIO\\s1_j.WAV",
	"AUDIO\\s1_k.WAV",
	"AUDIO\\s1_l.WAV",
	"AUDIO\\s3_a.WAV",
	"AUDIO\\s3_b.WAV",
	"AUDIO\\el3_a.WAV",
	"AUDIO\\mf1_a.WAV",
	"AUDIO\\mf2_a.WAV",
	"AUDIO\\mf3_a.WAV",
	"AUDIO\\mf3_b.WAV",
	"AUDIO\\mf3_b1.WAV",
	"AUDIO\\mf3_c.WAV",
	"AUDIO\\mf4_a.WAV",
	"AUDIO\\mf4_b.WAV",
	"AUDIO\\mf4_c.WAV",
	"AUDIO\\a1_a.WAV",
	"AUDIO\\a3_a.WAV",
	"AUDIO\\a5_a.WAV",
	"AUDIO\\a4_a.WAV",
	"AUDIO\\a4_b.WAV",
	"AUDIO\\a4_c.WAV",
	"AUDIO\\a4_d.WAV",
	"AUDIO\\k1_a.WAV",
	"AUDIO\\k3_a.WAV",
	"AUDIO\\r1_a.WAV",
	"AUDIO\\r2_a.WAV",
	"AUDIO\\r2_b.WAV",
	"AUDIO\\r2_c.WAV",
	"AUDIO\\r2_d.WAV",
	"AUDIO\\r2_e.WAV",
	"AUDIO\\r2_f.WAV",
	"AUDIO\\r2_g.WAV",
	"AUDIO\\r2_h.WAV",
	"AUDIO\\r5_a.WAV",
	"AUDIO\\r6_a.WAV",
	"AUDIO\\r6_a1.WAV",
	"AUDIO\\r6_b.WAV",
	"AUDIO\\lo2_a.WAV",
	"AUDIO\\lo6_a.WAV",
	"AUDIO\\yd2_a.WAV",
	"AUDIO\\yd2_b.WAV",
	"AUDIO\\yd2_c.WAV",
	"AUDIO\\yd2_c1.WAV",
	"AUDIO\\yd2_d.WAV",
	"AUDIO\\yd2_e.WAV",
	"AUDIO\\yd2_f.WAV",
	"AUDIO\\yd2_g.WAV",
	"AUDIO\\yd2_h.WAV",
	"AUDIO\\yd2_ass.WAV",
	"AUDIO\\yd2_ok.WAV",
	"AUDIO\\h5_a.WAV",
	"AUDIO\\h5_b.WAV",
	"AUDIO\\h5_c.WAV",
	"AUDIO\\ammu_a.WAV",
	"AUDIO\\ammu_b.WAV",
	"AUDIO\\ammu_c.WAV",
	"AUDIO\\door_1.WAV",
	"AUDIO\\door_2.WAV",
	"AUDIO\\door_3.WAV",
	"AUDIO\\door_4.WAV",
	"AUDIO\\door_5.WAV",
	"AUDIO\\door_6.WAV",
	"AUDIO\\t3_a.WAV",
	"AUDIO\\t3_b.WAV",
	"AUDIO\\t3_c.WAV",
	"AUDIO\\k1_b.WAV",
	"AUDIO\\cat1.WAV"
};
#endif