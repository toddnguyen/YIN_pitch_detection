#
# 'make depend' uses makedepend to automatically generate dependencies
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'pitchdetection'
# 'make clean'  removes all .o and executable files
#

# define the C compiler to use
CC = gcc

# define any compile-time flags
CFLAGS = -Wall -g #-Werror

# define any directories containing header files other than /usr/include
#
INCLUDES = -I/usr/local/lib -I/usr/local/include

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS = -L/usr/local/lib

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname
#   option, something like (this will link in libmylib.so and libm.so:
LIBS = -lsndfile

# define the C source files
SRCS = $(wildcard *.c)

# define the C object files
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
OBJS = $(SRCS:.c=.o)

# define the executable file
MAIN = pitchdetection

#
# The following part of the makefile is generic; it can be used to
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean

all:    $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(LIBS) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file)
# (see the gnu make manual section about automatic variables)
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN)

dep: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it

autocorrelation.o: autocorrelation.h /usr/local/include/sndfile.h
autocorrelation.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
autocorrelation.o: /usr/include/sys/_symbol_aliasing.h
autocorrelation.o: /usr/include/sys/_posix_availability.h
autocorrelation.o: /usr/include/Availability.h
autocorrelation.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
autocorrelation.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
autocorrelation.o: /usr/include/i386/_types.h
autocorrelation.o: /usr/include/sys/_pthread/_pthread_types.h
autocorrelation.o: /usr/include/sys/_types/_va_list.h
autocorrelation.o: /usr/include/sys/_types/_size_t.h
autocorrelation.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
autocorrelation.o: /usr/include/sys/_types/_off_t.h
autocorrelation.o: /usr/include/sys/_types/_ssize_t.h
autocorrelation.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
autocorrelation.o: /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
autocorrelation.o: /usr/include/machine/types.h /usr/include/i386/types.h
autocorrelation.o: /usr/include/sys/_types/_int8_t.h
autocorrelation.o: /usr/include/sys/_types/_int16_t.h
autocorrelation.o: /usr/include/sys/_types/_int32_t.h
autocorrelation.o: /usr/include/sys/_types/_int64_t.h
autocorrelation.o: /usr/include/sys/_types/_intptr_t.h
autocorrelation.o: /usr/include/sys/_types/_uintptr_t.h
autocorrelation.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
autocorrelation.o: /usr/include/sys/_endian.h
autocorrelation.o: /usr/include/libkern/_OSByteOrder.h
autocorrelation.o: /usr/include/libkern/i386/_OSByteOrder.h
autocorrelation.o: /usr/include/sys/_types/_dev_t.h
autocorrelation.o: /usr/include/sys/_types/_blkcnt_t.h
autocorrelation.o: /usr/include/sys/_types/_blksize_t.h
autocorrelation.o: /usr/include/sys/_types/_gid_t.h
autocorrelation.o: /usr/include/sys/_types/_in_addr_t.h
autocorrelation.o: /usr/include/sys/_types/_in_port_t.h
autocorrelation.o: /usr/include/sys/_types/_ino_t.h
autocorrelation.o: /usr/include/sys/_types/_ino64_t.h
autocorrelation.o: /usr/include/sys/_types/_key_t.h
autocorrelation.o: /usr/include/sys/_types/_mode_t.h
autocorrelation.o: /usr/include/sys/_types/_nlink_t.h
autocorrelation.o: /usr/include/sys/_types/_id_t.h
autocorrelation.o: /usr/include/sys/_types/_pid_t.h
autocorrelation.o: /usr/include/sys/_types/_uid_t.h
autocorrelation.o: /usr/include/sys/_types/_clock_t.h
autocorrelation.o: /usr/include/sys/_types/_time_t.h
autocorrelation.o: /usr/include/sys/_types/_useconds_t.h
autocorrelation.o: /usr/include/sys/_types/_suseconds_t.h
autocorrelation.o: /usr/include/sys/_types/_rsize_t.h
autocorrelation.o: /usr/include/sys/_types/_errno_t.h
autocorrelation.o: /usr/include/sys/_types/_fd_def.h
autocorrelation.o: /usr/include/sys/_types/_fd_setsize.h
autocorrelation.o: /usr/include/sys/_types/_fd_set.h
autocorrelation.o: /usr/include/sys/_types/_fd_clr.h
autocorrelation.o: /usr/include/sys/_types/_fd_zero.h
autocorrelation.o: /usr/include/sys/_types/_fd_isset.h
autocorrelation.o: /usr/include/sys/_types/_fd_copy.h
autocorrelation.o: /usr/include/sys/_pthread/_pthread_attr_t.h
autocorrelation.o: /usr/include/sys/_pthread/_pthread_cond_t.h
autocorrelation.o: /usr/include/sys/_pthread/_pthread_condattr_t.h
autocorrelation.o: /usr/include/sys/_pthread/_pthread_mutex_t.h
autocorrelation.o: /usr/include/sys/_pthread/_pthread_mutexattr_t.h
autocorrelation.o: /usr/include/sys/_pthread/_pthread_once_t.h
autocorrelation.o: /usr/include/sys/_pthread/_pthread_rwlock_t.h
autocorrelation.o: /usr/include/sys/_pthread/_pthread_rwlockattr_t.h
autocorrelation.o: /usr/include/sys/_pthread/_pthread_t.h
autocorrelation.o: /usr/include/sys/_pthread/_pthread_key_t.h
autocorrelation.o: /usr/include/sys/_types/_fsblkcnt_t.h
autocorrelation.o: /usr/include/sys/_types/_fsfilcnt_t.h
autocorrelation.o: /usr/include/stdlib.h /usr/include/sys/wait.h
autocorrelation.o: /usr/include/sys/signal.h /usr/include/machine/signal.h
autocorrelation.o: /usr/include/i386/signal.h
autocorrelation.o: /usr/include/machine/_mcontext.h
autocorrelation.o: /usr/include/i386/_mcontext.h
autocorrelation.o: /usr/include/mach/i386/_structs.h
autocorrelation.o: /usr/include/sys/_types/_sigaltstack.h
autocorrelation.o: /usr/include/sys/_types/_ucontext.h
autocorrelation.o: /usr/include/sys/_types/_sigset_t.h
autocorrelation.o: /usr/include/sys/resource.h /usr/include/stdint.h
autocorrelation.o: /usr/include/_types/_uint8_t.h
autocorrelation.o: /usr/include/_types/_uint16_t.h
autocorrelation.o: /usr/include/_types/_uint32_t.h
autocorrelation.o: /usr/include/_types/_uint64_t.h
autocorrelation.o: /usr/include/_types/_intmax_t.h
autocorrelation.o: /usr/include/_types/_uintmax_t.h
autocorrelation.o: /usr/include/sys/_types/_timeval.h /usr/include/alloca.h
autocorrelation.o: /usr/include/sys/_types/_ct_rune_t.h
autocorrelation.o: /usr/include/sys/_types/_rune_t.h
autocorrelation.o: /usr/include/sys/_types/_wchar_t.h /usr/include/string.h
autocorrelation.o: /usr/include/strings.h /usr/include/secure/_string.h
autocorrelation.o: /usr/include/tgmath.h /usr/include/math.h
autocorrelation.o: /usr/include/complex.h
pitchdetection.o: /usr/local/include/sndfile.h /usr/include/stdio.h
pitchdetection.o: /usr/include/sys/cdefs.h
pitchdetection.o: /usr/include/sys/_symbol_aliasing.h
pitchdetection.o: /usr/include/sys/_posix_availability.h
pitchdetection.o: /usr/include/Availability.h
pitchdetection.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
pitchdetection.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
pitchdetection.o: /usr/include/i386/_types.h
pitchdetection.o: /usr/include/sys/_pthread/_pthread_types.h
pitchdetection.o: /usr/include/sys/_types/_va_list.h
pitchdetection.o: /usr/include/sys/_types/_size_t.h
pitchdetection.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
pitchdetection.o: /usr/include/sys/_types/_off_t.h
pitchdetection.o: /usr/include/sys/_types/_ssize_t.h
pitchdetection.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
pitchdetection.o: /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
pitchdetection.o: /usr/include/machine/types.h /usr/include/i386/types.h
pitchdetection.o: /usr/include/sys/_types/_int8_t.h
pitchdetection.o: /usr/include/sys/_types/_int16_t.h
pitchdetection.o: /usr/include/sys/_types/_int32_t.h
pitchdetection.o: /usr/include/sys/_types/_int64_t.h
pitchdetection.o: /usr/include/sys/_types/_intptr_t.h
pitchdetection.o: /usr/include/sys/_types/_uintptr_t.h
pitchdetection.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
pitchdetection.o: /usr/include/sys/_endian.h
pitchdetection.o: /usr/include/libkern/_OSByteOrder.h
pitchdetection.o: /usr/include/libkern/i386/_OSByteOrder.h
pitchdetection.o: /usr/include/sys/_types/_dev_t.h
pitchdetection.o: /usr/include/sys/_types/_blkcnt_t.h
pitchdetection.o: /usr/include/sys/_types/_blksize_t.h
pitchdetection.o: /usr/include/sys/_types/_gid_t.h
pitchdetection.o: /usr/include/sys/_types/_in_addr_t.h
pitchdetection.o: /usr/include/sys/_types/_in_port_t.h
pitchdetection.o: /usr/include/sys/_types/_ino_t.h
pitchdetection.o: /usr/include/sys/_types/_ino64_t.h
pitchdetection.o: /usr/include/sys/_types/_key_t.h
pitchdetection.o: /usr/include/sys/_types/_mode_t.h
pitchdetection.o: /usr/include/sys/_types/_nlink_t.h
pitchdetection.o: /usr/include/sys/_types/_id_t.h
pitchdetection.o: /usr/include/sys/_types/_pid_t.h
pitchdetection.o: /usr/include/sys/_types/_uid_t.h
pitchdetection.o: /usr/include/sys/_types/_clock_t.h
pitchdetection.o: /usr/include/sys/_types/_time_t.h
pitchdetection.o: /usr/include/sys/_types/_useconds_t.h
pitchdetection.o: /usr/include/sys/_types/_suseconds_t.h
pitchdetection.o: /usr/include/sys/_types/_rsize_t.h
pitchdetection.o: /usr/include/sys/_types/_errno_t.h
pitchdetection.o: /usr/include/sys/_types/_fd_def.h
pitchdetection.o: /usr/include/sys/_types/_fd_setsize.h
pitchdetection.o: /usr/include/sys/_types/_fd_set.h
pitchdetection.o: /usr/include/sys/_types/_fd_clr.h
pitchdetection.o: /usr/include/sys/_types/_fd_zero.h
pitchdetection.o: /usr/include/sys/_types/_fd_isset.h
pitchdetection.o: /usr/include/sys/_types/_fd_copy.h
pitchdetection.o: /usr/include/sys/_pthread/_pthread_attr_t.h
pitchdetection.o: /usr/include/sys/_pthread/_pthread_cond_t.h
pitchdetection.o: /usr/include/sys/_pthread/_pthread_condattr_t.h
pitchdetection.o: /usr/include/sys/_pthread/_pthread_mutex_t.h
pitchdetection.o: /usr/include/sys/_pthread/_pthread_mutexattr_t.h
pitchdetection.o: /usr/include/sys/_pthread/_pthread_once_t.h
pitchdetection.o: /usr/include/sys/_pthread/_pthread_rwlock_t.h
pitchdetection.o: /usr/include/sys/_pthread/_pthread_rwlockattr_t.h
pitchdetection.o: /usr/include/sys/_pthread/_pthread_t.h
pitchdetection.o: /usr/include/sys/_pthread/_pthread_key_t.h
pitchdetection.o: /usr/include/sys/_types/_fsblkcnt_t.h
pitchdetection.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/stdlib.h
pitchdetection.o: /usr/include/sys/wait.h /usr/include/sys/signal.h
pitchdetection.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
pitchdetection.o: /usr/include/machine/_mcontext.h
pitchdetection.o: /usr/include/i386/_mcontext.h
pitchdetection.o: /usr/include/mach/i386/_structs.h
pitchdetection.o: /usr/include/sys/_types/_sigaltstack.h
pitchdetection.o: /usr/include/sys/_types/_ucontext.h
pitchdetection.o: /usr/include/sys/_types/_sigset_t.h
pitchdetection.o: /usr/include/sys/resource.h /usr/include/stdint.h
pitchdetection.o: /usr/include/_types/_uint8_t.h
pitchdetection.o: /usr/include/_types/_uint16_t.h
pitchdetection.o: /usr/include/_types/_uint32_t.h
pitchdetection.o: /usr/include/_types/_uint64_t.h
pitchdetection.o: /usr/include/_types/_intmax_t.h
pitchdetection.o: /usr/include/_types/_uintmax_t.h
pitchdetection.o: /usr/include/sys/_types/_timeval.h /usr/include/alloca.h
pitchdetection.o: /usr/include/sys/_types/_ct_rune_t.h
pitchdetection.o: /usr/include/sys/_types/_rune_t.h
pitchdetection.o: /usr/include/sys/_types/_wchar_t.h /usr/include/string.h
pitchdetection.o: /usr/include/strings.h /usr/include/secure/_string.h
pitchdetection.o: /usr/include/math.h autocorrelation.h /usr/include/tgmath.h
pitchdetection.o: /usr/include/complex.h
