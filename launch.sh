#/bin/sh

#./simulation/launch

#cp ./simulation/testTrace_exe  ./sample/exemple_exe
#cp ./simulation/testTrace ./sample/example
cd ./tool/
./compile.sh
./Construction
cd ..
mv ./scores_example_data ./hel_lib/scores_example_data.cpp
cd ./hel_lib/
make
./test

