
#define	IDM_MAINMENU	128

#define	MAKE_MENUID(a, b)	((a << 16) | b)

// --------------------------------------------------------------- system menu

enum {
	IDM_APPLE			= 128,
	IDM_EMULATE			= 129,
    IDM_EDIT			= 131,
	IDM_FDD1			= 132,
	IDM_FDD2			= 133,
	IDM_HDD				= 134,
	IDM_SASI1			= 135,
	IDM_SASI2			= 136,
	IDM_SCSI0			= 145,
	IDM_SCSI1			= 146,
	IDM_SCSI2			= 147,
	IDM_SCSI3			= 148,
	IDM_SCREEN			= 137,
	IDM_DEVICE			= 138,
	IDM_KEYBOARD		= 139,
	IDM_SOUND			= 140,
	IDM_MEMORY			= 141,
	IDM_OTHER			= 142,
	IDM_HELP			= 143,

#ifndef COMPILING_REZ
	IDM_ABOUT			= MAKE_MENUID(IDM_APPLE, 1),

	IDM_RESET			= MAKE_MENUID(IDM_EMULATE, 1),
	IDM_CONFIGURE		= MAKE_MENUID(IDM_EMULATE, 3),
	IDM_NEWDISK			= MAKE_MENUID(IDM_EMULATE, 4),
	IDM_FONT			= MAKE_MENUID(IDM_EMULATE, 5),
	IDM_EXIT			= MAKE_MENUID(IDM_EMULATE, 7),

	IDM_FDD1OPEN		= MAKE_MENUID(IDM_FDD1, 1),
	IDM_FDD1EJECT		= MAKE_MENUID(IDM_FDD1, 3),

	IDM_FDD2OPEN		= MAKE_MENUID(IDM_FDD2, 1),
	IDM_FDD2EJECT		= MAKE_MENUID(IDM_FDD2, 3),

	IDM_SASI1OPEN		= MAKE_MENUID(IDM_SASI1, 1),
	IDM_SASI1REMOVE		= MAKE_MENUID(IDM_SASI1, 3),

	IDM_SASI2OPEN		= MAKE_MENUID(IDM_SASI2, 1),
	IDM_SASI2REMOVE		= MAKE_MENUID(IDM_SASI2, 3),

	IDM_SCSI0OPEN		= MAKE_MENUID(IDM_SCSI0, 1),
	IDM_SCSI0REMOVE		= MAKE_MENUID(IDM_SCSI0, 3),

	IDM_SCSI1OPEN		= MAKE_MENUID(IDM_SCSI1, 1),
	IDM_SCSI1REMOVE		= MAKE_MENUID(IDM_SCSI1, 3),

	IDM_SCSI2OPEN		= MAKE_MENUID(IDM_SCSI2, 1),
	IDM_SCSI2REMOVE		= MAKE_MENUID(IDM_SCSI2, 3),

	IDM_SCSI3OPEN		= MAKE_MENUID(IDM_SCSI3, 1),
	IDM_SCSI3REMOVE		= MAKE_MENUID(IDM_SCSI3, 3),

	IDM_FULLSCREEN		= MAKE_MENUID(IDM_SCREEN, 1),
	IDM_ROLNORMAL		= MAKE_MENUID(IDM_SCREEN, 1+2),
	IDM_ROLLEFT			= MAKE_MENUID(IDM_SCREEN, 2+2),
	IDM_ROLRIGHT		= MAKE_MENUID(IDM_SCREEN, 3+2),
	IDM_DISPSYNC		= MAKE_MENUID(IDM_SCREEN, 5+2),
	IDM_RASTER			= MAKE_MENUID(IDM_SCREEN, 6+2),
	IDM_NOWAIT			= MAKE_MENUID(IDM_SCREEN, 7+2),
	IDM_AUTOFPS			= MAKE_MENUID(IDM_SCREEN, 8+2),
	IDM_60FPS			= MAKE_MENUID(IDM_SCREEN, 9+2),
	IDM_30FPS			= MAKE_MENUID(IDM_SCREEN, 10+2),
	IDM_20FPS			= MAKE_MENUID(IDM_SCREEN, 11+2),
	IDM_15FPS			= MAKE_MENUID(IDM_SCREEN, 12+2),
	IDM_SCREENOPT		= MAKE_MENUID(IDM_SCREEN, 14+2),

	IDM_MOUSE			= MAKE_MENUID(IDM_DEVICE, 4),
	IDM_SEROPT			= MAKE_MENUID(IDM_DEVICE, 6),
	IDM_MIDIOPT			= MAKE_MENUID(IDM_DEVICE, 8),
	IDM_MIDIPANIC		= MAKE_MENUID(IDM_DEVICE, 9),
	IDM_SNDOPT			= MAKE_MENUID(IDM_DEVICE, 11),

	IDM_KEY				= MAKE_MENUID(IDM_KEYBOARD, 1),
	IDM_JOY1			= MAKE_MENUID(IDM_KEYBOARD, 2),
	IDM_JOY2			= MAKE_MENUID(IDM_KEYBOARD, 3),
	IDM_MOUSEKEY		= MAKE_MENUID(IDM_KEYBOARD, 4),
	IDM_XSHIFT			= MAKE_MENUID(IDM_KEYBOARD, 6),
	IDM_XCTRL			= MAKE_MENUID(IDM_KEYBOARD, 7),
	IDM_XGRPH			= MAKE_MENUID(IDM_KEYBOARD, 8),
	IDM_F11KANA			= MAKE_MENUID(IDM_KEYBOARD, 10),
	IDM_F11STOP			= MAKE_MENUID(IDM_KEYBOARD, 11),
	IDM_F11EQU			= MAKE_MENUID(IDM_KEYBOARD, 12),
	IDM_F11NFER			= MAKE_MENUID(IDM_KEYBOARD, 13),
	IDM_F11USER			= MAKE_MENUID(IDM_KEYBOARD, 14),
	IDM_F12MOUSE		= MAKE_MENUID(IDM_KEYBOARD, 16),
	IDM_F12COPY			= MAKE_MENUID(IDM_KEYBOARD, 17),
	IDM_F12COMMA		= MAKE_MENUID(IDM_KEYBOARD, 18),
	IDM_F12XFER			= MAKE_MENUID(IDM_KEYBOARD, 19),
	IDM_F12USER			= MAKE_MENUID(IDM_KEYBOARD, 20),

	IDM_BEEPOFF			= MAKE_MENUID(IDM_SOUND, 1),
	IDM_BEEPLOW			= MAKE_MENUID(IDM_SOUND, 2),
	IDM_BEEPMID			= MAKE_MENUID(IDM_SOUND, 3),
	IDM_BEEPHIGH		= MAKE_MENUID(IDM_SOUND, 4),
	IDM_NOSOUND			= MAKE_MENUID(IDM_SOUND, 6),
	IDM_PC9801_14		= MAKE_MENUID(IDM_SOUND, 7),
	IDM_PC9801_26K		= MAKE_MENUID(IDM_SOUND, 8),
	IDM_PC9801_86		= MAKE_MENUID(IDM_SOUND, 9),
	IDM_PC9801_26_86	= MAKE_MENUID(IDM_SOUND, 10),
	IDM_PC9801_86_CB	= MAKE_MENUID(IDM_SOUND, 11),
	IDM_PC9801_118		= MAKE_MENUID(IDM_SOUND, 12),
	IDM_SPEAKBOARD		= MAKE_MENUID(IDM_SOUND, 13),
	IDM_SPARKBOARD		= MAKE_MENUID(IDM_SOUND, 14),
	IDM_AMD98			= MAKE_MENUID(IDM_SOUND, 15),
	IDM_JASTSOUND		= MAKE_MENUID(IDM_SOUND, 16),
	IDM_SEEKSND			= MAKE_MENUID(IDM_SOUND, 18),

	IDM_MEM640			= MAKE_MENUID(IDM_MEMORY, 1),
	IDM_MEM16			= MAKE_MENUID(IDM_MEMORY, 2),
	IDM_MEM36			= MAKE_MENUID(IDM_MEMORY, 3),
	IDM_MEM76			= MAKE_MENUID(IDM_MEMORY, 4),
	IDM_MEM116			= MAKE_MENUID(IDM_MEMORY, 5),
	IDM_MEM136			= MAKE_MENUID(IDM_MEMORY, 6),

	IDM_BMPSAVE			= MAKE_MENUID(IDM_OTHER, 1),
	IDM_S98LOGGING		= MAKE_MENUID(IDM_OTHER, 2),
	IDM_CALENDAR		= MAKE_MENUID(IDM_OTHER, 3),
	IDM_DISPCLOCK		= MAKE_MENUID(IDM_OTHER, 4),
	IDM_DISPFLAME		= MAKE_MENUID(IDM_OTHER, 5),
	IDM_JOYX			= MAKE_MENUID(IDM_OTHER, 6),
	IDM_RAPID			= MAKE_MENUID(IDM_OTHER, 7),
	IDM_MSRAPID			= MAKE_MENUID(IDM_OTHER, 8),
    IDM_RECORDING		= MAKE_MENUID(IDM_OTHER, 10),
	IDM_KEYDISP			= MAKE_MENUID(IDM_OTHER, 11),
	IDM_SOFTKBD			= MAKE_MENUID(IDM_OTHER, 12),
	IDM_I286SAVE		= MAKE_MENUID(IDM_OTHER, 13),
	
	IDM_NP2HELP			= MAKE_MENUID(IDM_HELP, 1),
#endif
};

// -------------------------------------------------------------------- dialog

#define	IDOK				1
#define	IDCANCEL			2

#define	IDD_ABOUT			128

#define	IDD_NEWDISK			129

#define	IDC_DISKLABEL		4
#define	IDC_MAKE2DD			6
#define	IDC_MAKE2HD			7


#define	IDD_NEWHDDDISK		130

#define	IDC_HDDSIZE			3
#define	IDD_VERSION			4


// ------------------------------------------------------------------ Messages

#define	IDT_TITLE			128
#define	IDT_NEWDISK			129
#define	IDT_NEWHDDDISK		130

