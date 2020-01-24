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

#Graphics files.
OBJS = title.o mons1.o battle.o

all : $(OBJS)
#	$(LD) $(LDFLAGS) -e$(PRGNAME).srf $(OBJS)

# 依存関係

# クリーンアップ
clean:
	-del *.o

