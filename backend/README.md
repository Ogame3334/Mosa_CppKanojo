# MOSA_backend(仮)
## 概要
これはハックツハッカソン モサカップ チーム C++の彼女は?年収は?調べてみました!の作品のbackendです。
## ビルド方法
```bash
# boostをinstallする aptでも、ソースからビルドするでもよし
# debian系
apt install libboost-dev
yum install boost boost-devel
cd backend
mkdir bld
cmake ../
make
./MosaBackend
```