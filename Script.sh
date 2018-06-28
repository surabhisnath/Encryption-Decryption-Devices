#! bin/bash
clear
mknod /dev/Encryption c 91 1
mknod /dev/Decryption c 92 1
chmod a+r+w /dev/Encryption
chmod a+r+w /dev/Decryption
make all
insmod Encrypt.ko
insmod Decrypt.ko
./Userspace
rmmod Encrypt.ko
rmmod Decrypt.ko
make clean