CC=g++
CFLAGS=-I.

all: Koder Dekoder
	.\Koder.exe

Koder: Koder.o Encoder.o Decoder.o Huffman.o Image.o ImagePrediction.o Utils.o matrix.o
	$(CC) -o Koder obj/Koder.o obj/Encoder.o obj/Decoder.o \
	obj/Huffman.o obj/Image.o obj/ImagePrediction.o obj/Utils.o obj/matrix.o

Dekoder: Dekoder.o Encoder.o Decoder.o Huffman.o Image.o ImagePrediction.o Utils.o matrix.o
	$(CC) -o Dekoder obj/Dekoder.o obj/Encoder.o obj/Decoder.o \
	obj/Huffman.o obj/Image.o obj/ImagePrediction.o obj/Utils.o obj/matrix.o

Dekoder.o: src/Dekoder.cpp
	$(CC) -c src/Dekoder.cpp -o obj/Dekoder.o

Koder.o: src/Koder.cpp
	$(CC) -c src/Koder.cpp -o obj/Koder.o

Encoder.o: src/Encoder.cpp include/Encoder.h
	$(CC) -c src/Encoder.cpp -o obj/Encoder.o

Decoder.o: src/Decoder.cpp include/Decoder.h
	$(CC) -c src/Decoder.cpp -o obj/Decoder.o

Huffman.o: src/Huffman.cpp include/Huffman.h
	$(CC) -c src/Huffman.cpp -o obj/Huffman.o

Image.o: src/Image.cpp include/Image.h
	$(CC) -c src/Image.cpp -o obj/Image.o

ImagePrediction.o: src/ImagePrediction.cpp include/ImagePrediction.h
	$(CC) -c src/ImagePrediction.cpp -o obj/ImagePrediction.o

Utils.o: src/Utils.cpp include/Utils.h
	$(CC) -c src/Utils.cpp -o obj/Utils.o

matrix.o: src/matrix.cpp include/matrix.h
	$(CC) -c src/matrix.cpp -o obj/matrix.o