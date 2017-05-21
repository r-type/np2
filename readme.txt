
// ---- Definition

  Control to optimize the memory amount used.
    MEMOPTIMIZE = 0～2

    We're expecting the CPU to stay in the limit specified here.
      MEMOPTIMIZE Undefined … Celeron333A along with its second cache activated.
      MEMOPTIMIZE = 0   … x86
      MEMOPTIMIZE = 1   … PowerPC and other RISC desktop.
      MEMOPTIMIZE = 2   … StrongARM and other RISC embedded.


  Compiler arguments - Return values optimization
    If argument return values aren't using int, it cannot work effectively. 
    We generally use common.h.
      REG8 … UINT8 type / (sizeof(REG8) != 1)In that case we fill the superior bit with 0.
      REG16 … UINT16 type / (sizeof(REG16) != 2)In that case we fill the superior bit with 0.
　　　As we filled both values with 0, we'll consider doing the same when browsing.


  OS language selection.
    OSLANG_SJIS … Interpret Kanji code as Shift-JIS.
    OSLANG_EUC  … Interpret Kanji code as EUC.

    OSLINEBREAK_CR   … MacOS   "\r"
    OSLINEBREAK_LF   … Unix    "\n"
    OSLINEBREAK_CRLF … Windows "\r\n"

      ※Here we do particular case settings in the source code bellow.
        (Because of Windows API, there are \r\n cases along \n cases...)
        ・common/_memory.c
        ・debugsub.c
        ・statsave.c

    (milstr.h choice selection)
    SUPPORT_ANK      … ANK Character string processing function link.
    SUPPORT_SJIS     … SJIS Character string processing function link.
    SUPPORT_EUC      … EUC Character string processing function link.

      ※That's all we are setting in milstr.h at the moment.
        As ver0.73 we removed some definitions from milstr.h to place them into compiler.h.


　CPUCORE_IA32
　　IA32 architecture is used.
　　　Important notes when using i386c.
　　  ・CPU panic and other warning indication make use of msgbox() API.
　　　　Make the proper matched definition with compiler.h.
　　　・Architectures that don't handle sigsetjmp(3), siglongjmp(3) should use the following list of define
    and add them to compiler.h.
　　　　----------------------------------------------------------------------
        #define sigjmp_buf              jmp_buf
        #define sigsetjmp(env, mask)    setjmp(env)
        #define siglongjmp(env, val)    longjmp(env, val)
　　　　----------------------------------------------------------------------

  CPUSTRUC_MEMWAIT
　　　We move to cpucore structure at the cost of memory wait (vramop).

　SUPPORT_CRT15KHZ
　　　15.98kHz horizontal scan support (DIPSW1-1).

　SUPPORT_CRT31KHZ
　　　31.47kHz horizontal scan support.
　　　This is "Fellow" type.

　SUPPORT_PC9821
　　　PC-9821 expansion support.
　　　It's evident that 386 is required.
　　　Also SUPPORT_CRT31KHZ is needed as well (to support High-Res BIOS).

　SUPPORT_PC9861K
　　　PC-9861K(RS-232C expansion I/F) support.

　SUPPORT_IDEIO
　　　Support for IDE at I/O level.
　　　But we can only establish an ATA lead...

　SUPPORT_SASI
　　　SASI HDD support.
　　　If it's not defined it will run as IDE.

　SUPPORT_SCSI
　　　SCSI HDD support... not working completely.

　SUPPORT_S98
　　　Gain S98 log.

　SUPPORT_WAVEREC
　　Wave file writing support at Sound level.
　　Be advised sound will stop when in use, mostly used for debugging.


// ---- screen

  PC-9801 series screen standard resolution is 641x400.
  It's not in conformity with VGA but to make it compliant we force it to width + extend.
  8 < width < 640
  8 < height < 480
  extend = 0 or 1

typedef struct {
	BYTE	*ptr;		// VRAM pointer
	int		xalign;		// x direction offset
	int		yalign;		// y direction offset
	int		width;
	int		height;
	UINT	bpp;		// screen bit color
	int		extend;		// width extension
} SCRNSURF;

  Surface size is (width + extern) x height.


const SCRNSURF *scrnmng_surflock(void);
  Start screen drawing.

void scrnmng_surfunlock(const SCRNSURF *surf);
  End screen drawing (draw with that timing).


void scrnmng_setwidth(int posx, int width)
void scrnmng_setextend(int extend)
void scrnmng_setheight(int posy, int height)
  Screen size change.
  Window size change.
  If in Fullscreen, display area will change.
  We return this value with SCRNSURF. (?)
  posx, width are 8 multiples.

BOOL scrnmng_isfullscreen(void) … Unused in NP2 core.
  Get fullscreen status.
    return: if not zero, is fullscreen.

BOOL scrnmng_haveextend(void)
  Get width status.
    return: if not zero, has width extension support.

UINT scrnmng_getbpp(void)
  Get screen bit color value.
    return: bit(8/16/24/32)

void scrnmng_palchanged(void)
  Palette update notification (only when 8bit screen is supported).

RGB16 scrnmng_makepal16(RGB32 pal32)
  Draw from RGB32 to 16bit color (only when 16bit screen is supported).



// ---- sound

NP2 sound data functions bellow can be obtained from sound.c.
  const SINT32 *sound_pcmlock(void)
  void sound_pcmunlock(const SINT32 *hdl)


SOUND_CRITICAL  to insert a semaphore (see sndcsec.c).
SOUNDRESERVE    buffer size reservation (milliseconds).
  Assigned to fix sound crackling.
  If there is big delay in queue jumping use SOUNDRESERVE.
  (In the case of Win9x, it took care of watching after the ring buffer by itself, 
  checking regularly without break if the "sound writer" was comming. 
  It wasn't necessary to deal with that.)


UINT soundmng_create(UINT rate, UINT ms)
  Sound stream reservation.
    input:  rate    Sampling rate (11025/22050/44100).
            ms      Sampling buffer size (milliseconds).
    return: Sampling amount of acquired buffer.

            ms isn't obligatory (such things as SDL limit the buffer size).
            NP2 sound buffer processing uses the return value.


void soundmng_destroy(void)
  End sound stream.

void soundmng_reset(void)
  Reset sound stream.

void soundmng_play(void)
  Sound stream playback.

void soundmng_stop(void)
  Interrupt sound stream.

void soundmng_sync(void)
  Sound stream callback.

void soundmng_setreverse(BOOL reverse)
  Reverse sound stream output.
    input:  reverse If not 0, reverse left/right.

BOOL soundmng_pcmplay(UINT num, BOOL loop)
  PCM playback.
    input:  num     PCM number.
            loop    If not 0, loop.

void soundmng_pcmstop(UINT num)
  PCM interruption.
    input:  num     PCM number.



// ---- mouse

BYTE mousemng_getstat(SINT16 *x, SINT16 *y, int clear)
  Get mouse state.
    input:  clear   If not 0, reset the counter after getting the mouse state.
    output: *x      Count X-axis mouse movement since "clear".
            *y      Count Y-axis mouse movement since "clear".
    return: bit7    Left click status (0:pressed down)
            bit5    Right click status (0:pressed down)



// ---- serial/parallel/midi

COMMNG commng_create(UINT device)
  Open serial.
    input:  Device number.
    return: Handle (NULL if fails).


void commng_destroy(COMMNG hdl)
  Close serial.
    input:  Handle (NULL if fails).



// ---- joy stick

BYTE joymng_getstat(void)
  Get joystick status.

    return: bit0    UP state (0:pressed down).
            bit1    DOWN
            bit2    LEFT
            bit3    RIGHT
            bit4    Rapid-fire Button 1
            bit5    Rapid-fire Button 2
            bit6    Button 1
            bit7    Button 2


// ----

void sysmng_update(UINT bitmap)
  Called at state change.

void sysmng_cpureset(void)
  Called at Reset time.



void taskmng_exit(void)
  System termination.

