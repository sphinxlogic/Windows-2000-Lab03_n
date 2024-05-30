#---------------------------------------------------------------------------
# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1999 Microsoft Corporation.  All rights reserved.
#
# This makefile builds both the producer and consumer.
#
# Targets:
#    producer.exe   -- Producer part of producer/consumer sample
#    consumer.exe   -- Consumer part of producer/consumer sample
#    clean          -- removes .objs and .baks
#    cleaner        -- does a clean, then removes producer.exe and consumer.exe
#
# Command-line arguments:
#    nodebug=1      -- force an optimized, retail build
#    tune=1         -- optimized build for Working Set Tuner
#    profile=1      -- optimized build for Call Attributed Profiler
#
# By default (without any command-line parameters), this makefile produces a
# debugging build.
#---------------------------------------------------------------------------

APPVER = 4.0
TARGETOS = BOTH

!include <win32.mak>

PRODUCER = producer
CONSUMER = consumer

all: $(PRODUCER).exe $(CONSUMER).exe


#-----------------------------------------------------------------------------
# Common rules for both Producer and Consumer.

# Inference rules
.cpp.obj:
   $(cc) $(cdebug) $(cflags) -GX $(cvars) $<


#-----------------------------------------------------------------------------
# Producer rules

PRODUCER_OBJS = producer.obj

# Dependencies
producer.obj: producer.cpp queue.h

$(PRODUCER).exe: $(PRODUCER_OBJS)
   $(link) $(ldebug) $(conlflags) \
   $(PRODUCER_OBJS) $(conlibs) libcp.lib user32.lib \
   -out:$(PRODUCER).exe


#-----------------------------------------------------------------------------
# Consumer rules

CONSUMER_OJBS = consumer.obj

# Dependencies
consumer.obj: consumer.cpp queue.h

$(CONSUMER).exe: $(CONSUMER_OJBS)
   $(link) $(ldebug) $(conlflags) \
   $(CONSUMER_OJBS) $(conlibs) libcp.lib user32.lib  \
   -out:$(CONSUMER).exe


#-----------------------------------------------------------------------------
# Clean-up targets
clean:
   del *.obj
   del *.bak

cleaner: clean
   del $(PRODUCER).exe
   del $(CONSUMER).exe

