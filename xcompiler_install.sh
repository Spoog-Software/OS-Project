apt install libgmp3-dev libmpfr-dev libmpc-dev
curl https://ftp.gnu.org/gnu/gcc/gcc-9.3.0/gcc-9.3.0.tar.gz --output gcc9.3.0.tar.gz
curl https://ftp.gnu.org/gnu/binutils/binutils-2.34.tar.gz --ouput binutils-2.34.tar.gz
mkdir gcc-source
tar -xf gcc9.3.0.tar.gz --directory gcc-source
tar -xf binutils-2.34.tar.gz --directory gcc-source
export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
cd gcc-source
mkdir build-binutils
cd build-binutils
../binutils-x.y.z/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make -j6
make install

cd ..
mkdir build-gcc
cd build-gcc
../gcc-x.y.z/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make -j6 all-gcc
make -j6 all-target-libgcc
make -j6 install-gcc
make -j6 install-target-libgcc