CC	=	gcc

NAME	=	s21_matrix
TARGET	?=	$(NAME).a
TEST_EXE	?=	test
TEST_TARGET	?=	test_$(TARGET)
TEST_GCOV_EXE	?=	test_gcov
GCOV_TARGET	=	./coverage
GCOV_INFO	=	coverage.info

SRC_DIR	?=	.
TEST_SRC_DIR	?=	./tests

OBJ_DIR	?=	./objs
TEST_OBJ_DIR	?=	./tests/objs

INC	:=	$(shell	find	$(SRC_DIR)	-maxdepth	1	-name	"s21_*.h")
SRC	:=	$(shell	find	$(SRC_DIR)	-maxdepth	1	-name	"*.c")

TEST_INC	:=	$(shell	find	$(TEST_SRC_DIR)	-maxdepth	1	-name	"*.h")
TEST_SRC	:=	$(shell find	$(TEST_SRC_DIR)	-maxdepth	1	-name	"s21_*.c")

OBJS	:=	$(addprefix	$(OBJ_DIR)/,	$(notdir	$(SRC:.c=.o)))
TEST_OBJS	:=	$(addprefix	$(TEST_OBJ_DIR)/,	$(notdir	$(TEST_SRC:.c=.o)))
GCOV_OBJS	:=	$(addprefix	$(TEST_OBJ_DIR)/,	$(notdir	$(SRC:.c=.o)))

GCDA	:=	$(shell	find	$(TEST_OBJ_DIR)	-maxdepth	1	-name	"*.gcda")
GCNO    :=  $(shell find    $(TEST_OBJ_DIR) -maxdepth   1   -name   "*.gcno")

AR	:=	ar	rc
RAN	:=	ranlib
RM	:=	rm	-f
MK	:=	mkdir	-p

ASAN	:=	#-fsanitize=address	-static-libasan	-g
STDFLAGS	:=	-c	-Wall	-Werror	-Wextra	-std=c11	-pedantic	-g
CFLAGS	?=	$(STDFLAGS)	$(ASAN)
TST_CFLAGS	:=	-g	$(STDFLAGS)	$(shell pkg-config --cflags check)
GCOV_FLAGS	?=	-fprofile-arcs	-ftest-coverage
TST_LIBS	?=	-lcheck	-lm	
ifeq	($(shell uname), Linux)
TST_LIBS	=	-lcheck_pic	$(shell	pkg-config	--libs	check)	-lpthread	-lrt	-lm	-lsubunit
endif

all:	$(TARGET)	test	#gcov_report

gcov_obj:	$(GCOV_OBJ)	Makefile

$(TARGET):	$(OBJS)	Makefile
	$(AR)	$(TARGET)	$(OBJS)
	$(RAN)	$(TARGET)

$(TEST_TARGET):	$(GCOV_OBJS)	$(INC)
	$(AR)	$(TEST_TARGET)	$(GCOV_OBJS)
	$(RAN)	$(TEST_TARGET)

test:	$(TARGET)	$(TEST_OBJ_DIR)/test.o	$(TEST_OBJS)	$(TEST_INC)	Makefile
	$(CC)	$(TEST_OBJS)	$(TEST_OBJ_DIR)/test.o	$(GCOV_FLAGS)	-o	$(TEST_SRC_DIR)/$(TEST_EXE)	$(TST_LIBS)	-L.	$(TARGET)
	$(TEST_SRC_DIR)/test

test_gcov:	$(TEST_TARGET)	 $(TEST_OBJ_DIR)/test.o	$(TEST_OBJS)
	$(CC)	$(TEST_OBJS)	$(TEST_OBJ_DIR)/test.o	$(GCOV_FLAGS)	-o	$(TEST_SRC_DIR)/$(TEST_GCOV_EXE)	$(TST_LIBS)	-L.	$(TEST_TARGET)
#	$(TEST_SRC_DIR)/test_gcov

$(TEST_OBJ_DIR)/test.o:	tests/test.c
	@$(MK) $(TEST_OBJ_DIR)
	$(CC) $(CFLAGS) -o $(TEST_OBJ_DIR)/test.o tests/test.c

$(TEST_OBJ_DIR)%.o: $(TEST_SRC_DIR)%.c $(TEST_INC) 
	@$(MK)	$(TEST_OBJ_DIR)
	$(CC)	$(TST_CFLAGS)	-o	$@	-c	$<

$(OBJS): $(OBJ_DIR)%.o:	$(SRC_DIR)%.c	$(INC)
	@$(MK)	$(OBJ_DIR)
	$(CC)	$(CFLAGS)	-o	$@	-c	$<

$(GCOV_OBJS):	$(TEST_OBJ_DIR)%.o:	$(SRC_DIR)%.c	$(TEST_INC)
	@$(MK)	$(TEST_OBJ_DIR)
	$(CC)	$(CFLAGS)	-o	$@	-c	$<

gcov_report:	$(GCOV_TARGET)	open

$(GCOV_TARGET):	CFLAGS	+=	$(GCOV_FLAGS)
$(GCOV_TARGET):	$(GCOV_INFO)
	genhtml	$(GCOV_INFO)	-o	$(GCOV_TARGET)

$(GCOV_INFO):	test_gcov
	./$(TEST_SRC_DIR)/$(TEST_GCOV_EXE)
	geninfo	$(TEST_OBJ_DIR)	-b	.	-o	./$(GCOV_INFO)


open:
	open	coverage/index.html

leaks:
	leaks -atExit -- $(TEST_SRC_DIR)

valgrind:
	valgrind --leak-check=full $(TEST_SRC_DIR)/$(TEST_EXE)

clean:
	$(RM)	$(wildcard *.a)
#	$(RM)	-r	$(TEST_OBJ_DIR)
	$(RM)	$(OBJS)
	$(RM)	$(GCDA)
	$(RM)	$(GCNO)
	$(RM)	$(TEST_OBJS)
	$(RM)	$(GCOV_OBJS)
	$(RM)	$(TEST_SRC_DIR)/$(TEST_EXE)	$(TEST_SRC_DIR)/$(TEST_GCOV_EXE)
	$(RM)	$(GCOV_INFO)
	$(RM)	-r	coverage
