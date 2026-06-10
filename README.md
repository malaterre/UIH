# UIH

vcpkg install boost-serialization

cmake -B build -S . \
  -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake \
  -DVCPKG_TARGET_TRIPLET=x64-windows


gdcmraw -t 0065,106c input.dcm uih.raw

./inspect uih.raw
