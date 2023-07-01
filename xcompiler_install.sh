curl https://ftp.gnu.org/gnu/gcc/gcc-9.3.0/gcc-9.3.0.tar.gz --output gcc9.3.0.tar.gz
mkdir gcc-source
apt install libgmp3-dev libmpfr-dev libmpc-dev
tar -xf gcc9.3.0.tar.gz --directory gcc-source
export PREFIX="$HOME/opt/xgcc-9.3.0"
cd gcc-source
mkdir build-gcc
cd build-gcc
../gcc-9.3.0/configure --prefix="$PREFIX" --disable-nls --enable-languages=c,c++
make