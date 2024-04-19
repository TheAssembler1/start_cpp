original_dir=$(pwd)
external_dir="${original_dir}/external"
build_dir="${original_dir}/build"

rm -rf ${external_dir} 
rm -rf ${build_dir} 

mkdir ${external_dir}
mkdir ${build_dir}
mkdir "${external_dir}/sdl2"
mkdir "${external_dir}/sdl2_ttf"

# installing sdl2
cd build
git clone https://github.com/libsdl-org/SDL.git -b SDL2
cd SDL
mkdir build
cd build
../configure --prefix "${external_dir}/sdl2"
make install -j4
cd ${original_dir}

# install sdl2_ttf
cd build
curl -LO "https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.22.0/SDL2_ttf-2.22.0.tar.gz"
tar -zxvf "SDL2_ttf-2.22.0.tar.gz"
cd "SDL2_ttf-2.22.0"
./autogen.sh
./configure --prefix="${external_dir}/sdl2_ttf"
make
make install
cd ${original_dir}

