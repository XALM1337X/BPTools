#!/bin/bash

SOURCE_PATH=$1
pushd $SOURCE_PATH > /dev/null
rm -f $SOURCE_PATH/lib/*

for f in *.cpp; do
	file_name=$(echo $f | cut -d "." -f 1)
	gcc  -Wall -O2 -std=c++17 -I"$SOURCE_PATH/include" -c "$SOURCE_PATH/$f" -fPIC -o $SOURCE_PATH/obj/Release/$file_name.o
	if [[ ! $? -eq 0 ]]; then
		echo "Failed to compile $f exiting build"
		exit 1
	fi
	echo "Succesfully compiled $f."
done

pushd $SOURCE_PATH/obj/Release/ > /dev/null
for f in *.o; do
	object_file+=( $f )
done

#Redhat Linux linking
#/usr/lib/gcc/x86_64-redhad-linux/8 This is the path to gcc/c++ ".so" library files
echo "Linking BPTools."
gcc -shared -o $SOURCE_PATH/lib/libBPTools.so "${object_file[@]}"
if [[ ! $? -eq 0 ]]; then
	echo "Failed to link objects, build failed for BPTools."
	exit 1
fi

if [[ ! -f /etc/ld.so.conf.d/BPTools.conf ]]; then
	echo "Creating linker configuration file in /etc/ld.so.conf.d/BPTools.conf"
	echo "$SOURCE_PATH/lib" > /etc/ld.so.conf.d/BPTools.conf
	ldconfig
fi
echo "Succesfully built BPTools.so"