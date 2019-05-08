#! /bin/bash

real_path=$(realpath $0)
dir_name=`dirname "${real_path}"`
echo "real_path: ${real_path}"
echo "dir_name: ${dir_name}"

data_dir="testdata"
if [[ ! -d ${dir_name}/${data_dir} ]]; then
	echo "data directory does not exist: ${data_dir}"
	ln -s ${dir_name}/./../../${data_dir} ${dir_name}
else
	echo "data directory already exists: ${data_dir}"
fi

new_dir_name=${dir_name}/build
mkdir -p ${new_dir_name}

# build yaml-cpp
echo "########## start build yaml-cpp ##########"
yaml_cpp_path=${dir_name}/../../src/yaml-cpp
mkdir -p ${yaml_cpp_path}/build
cd ${yaml_cpp_path}/build
cmake ..
make
echo "########## finish build yaml-cpp ##########"

cd -
cp -a ${yaml_cpp_path}/build/libyaml-cpp.a ${new_dir_name}

cd ${new_dir_name}
cmake ..
make

cd -

