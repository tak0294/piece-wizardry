# Piece 用 makefile

# 拡張子の定義

.SUFFIXES:
.SUFFIXES:  .o .s .c

# 生成コマンド・オプションのマクロ

CC = pcc33
CFLAGS = -c -g -gp=0x0 -near -O2 -Wall
AS = pcc33
ASFLAGS = -c -g -gp=0x0 -near
LD = pcc33
LDFLAGS = -g -ls -lm

# 生成規則

.c.o:
	$(CC) $(CFLAGS) $<

.s.o:
	$(AS) $(ASFLAGS) $<

# 構成ファイル・生成ファイルのマクロ

PRGNAME = wizardry
FILENAME = wizardry
CAPTION = WIZARDRY
#Common files.
OBJS = tak.lib
#Graphics files.
OBJS += .\graphics\title.o .\graphics\mons1.o .\graphics\battle.o
#Project files.
OBJS += main.o chara_data.o dice.o monster.o item.o battle_manager.o party.o

$(PRGNAME).srf : $(OBJS)
	$(LD) $(LDFLAGS) -e$(PRGNAME).srf $(OBJS)

# 依存関係

# フラッシュ書き込みイメージ生成
pex : $(PRGNAME).srf
	ppack -e $(PRGNAME).srf -o$(FILENAME).pex -n$(CAPTION)

# クリーンアップ
clean:
	-del *.o
	-del *.pex
	-del *.srf
	-del *.sym
	-del *.map

