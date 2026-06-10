# UIH

vcpkg install boost-serialization

cmake -B build -S . \
  -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake \
  -DVCPKG_TARGET_TRIPLET=x64-windows


gdcmraw -t 0065,106c input.dcm uih.raw

./Debug/inspect.exe uih.raw

lib version: 14
22 serialization::archive 20 0 0 0 0 2 0 0 0 11 CoilCombine -1 0  0 13 CardiacT2MOCO 1 4 MOCO 0
lib version: 20
22 serialization::archive 20 0 0 0 0 2 0 0 0 11 CoilCombine -1 0  0 13 CardiacT2MOCO 1 4 MOCO 0
