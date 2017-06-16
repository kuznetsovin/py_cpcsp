CC = gcc -g -Wall
RM = rm -rf
SIZEOF_VOID_P = -DSIZEOF_VOID_P=8
OUTPUT_DIR = build
OUTPUT_TEST_FILE = $(OUTPUT_DIR)/CpcspTest
OUTPUT_LIB_NAME = $(OUTPUT_DIR)/libsignature.so

CPSCP_PATH = src/cpcsp
SOURCES = $(CPSCP_PATH)/cpcsp.c $(CPSCP_PATH)/crl.c $(CPSCP_PATH)/cert.c $(CPSCP_PATH)/verify.c
PY_SOURCES = src/libsignature.c src/py_cpcsp.c
PY_TEST = python -m unittest discover . -v

LDFLAGS = -DUNIX -DHAVE_LIMITS_H -DHAVE_STDIN_H
LIBFLAGS = -fPIC -shared

PYTHON_LIB = `pkg-config --cflags --libs python-2.7`

CSP_PATH = /opt/cprocsp
CSP_INCLUDE = $(CSP_PATH)/include
INCLUDE_DIRS = -I$(CSP_INCLUDE) -I$(CSP_INCLUDE)/cpcsp -I$(CSP_INCLUDE)/pki

CSP_LIB = $(CSP_PATH)/lib
CSP_BIN = $(CSP_PATH)/bin/
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CSP_LIB = $(CSP_PATH)/lib/amd64
	PYTHON_LIB = -I/usr/include/python2.7 -lpython2.7
	CSP_BIN = $(CSP_PATH)/bin/amd64
endif

CSP_EXTRA_LIBS = -L$(CSP_LIB) -lrdrsup -lcapi20 -lpthread
# хранилища для теста
CSP_ROOT_STORE = -store uroot

CLEAN_STORE_CMD = $(CSP_BIN)/certmgr -delete -all $(CSP_ROOT_STORE)

all: build
test: build_c build_py clean


build_py: $(PY_SOURCES)
	mkdir -p $(OUTPUT_DIR)
	$(CC) $(LIBFLAGS) $(LDFLAGS) $(INCLUDE_DIRS) $(SIZEOF_VOID_P) -o $(OUTPUT_LIB_NAME) $(PYTHON_LIB) $(PY_SOURCES) $(SOURCES) $(CSP_EXTRA_LIBS)
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)/$(OUTPUT_DIR)
	$(PY_TEST)

build_c: $(SOURCES)
	mkdir -p $(OUTPUT_DIR)
	$(CC) $(LIBFLAGS) $(LDFLAGS) $(INCLUDE_DIRS) $(SIZEOF_VOID_P) -o $(OUTPUT_LIB_NAME) $(SOURCES) $(CSP_EXTRA_LIBS)
	$(CC) $(LDFLAGS) $(INCLUDE_DIRS)  $(SIZEOF_VOID_P)  $(CSP_EXTRA_LIBS) -o $(OUTPUT_TEST_FILE) -L./$(OUTPUT_DIR) $(CPSCP_PATH)/test.c -lsignature
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)/build
	./$(OUTPUT_TEST_FILE)

clean:	
	$(RM) $(OUTPUT_DIR)
	export LD_LIBRARY_PATH=
	$(CLEAN_STORE_CMD)
	$(CLEAN_STORE_CMD) -crl

