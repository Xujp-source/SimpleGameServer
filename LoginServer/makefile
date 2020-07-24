CC=g++ -std=c++11
CC_INCLUDE=-I/usr/include
	 
MY_INCLUDE=-I/root/protobuf/protobuf-3.6.1/src/ \
		-I../include/mysql

CC_LIB=-L/usr/lib64/ \
	-L/usr/lib64/mysql/ \
	-lpthread -lmysqlclient -ldl

MY_LIB=-L/usr/lib64/ \
	-L/usr/local/lib \
	-lpthread -lprotobuf -ldl 

TARGET=DBServer

SRCS=$(wildcard *.cpp)
SRCS:=$(SRCS) $(wildcard ./ServerEngine/3rd/*.cpp) \
	$(wildcard ./ServerEngine/Common/*.cpp) \
	$(wildcard ./ServerEngine/DBInterFace/*.cpp)
SRCS2=$(wildcard ./protoc/*.cc)


OBJS=$(SRCS:.cpp=.o)
OBJS2=$(SRCS2:.cc=.o)
OBJS:=$(OBJS) $(OBJS2)

default:$(TARGET)

$(TARGET):$(OBJS)
	$(CC) -g -o $@ $^ $(MY_LIB) $(CC_LIB)
	#mv $(OBJS) ../Linux

%.o:%.cpp
	$(CC) -g -w -c $< -o $@ $(CC_INCLUDE) $(MY_INCLUDE)

%.o:%.cc
	$(CC) -g -w -c $< -o $@ $(CC_INCLUDE) $(MY_INCLUDE)

clean:
	rm $(OBJS) $(TARGET)
