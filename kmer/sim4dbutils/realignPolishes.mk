TARGET  := realignPolishes
SOURCES := realignPolishes.C

SRC_INCDIRS := ../libutil ../libbio ../libseq ../libsim4

TGT_LDFLAGS := -L${TARGET_DIR}
TGT_LDLIBS  := -lseq -lsim4 -lbio -lutil
TGT_PREREQS := libseq.a libbio.a libutil.a libsim4.a
