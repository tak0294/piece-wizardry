echo off
make -Cgraphics
make -Clib
copy /Y .\lib\tak.lib .\
make clean
echo on
make
make pex
