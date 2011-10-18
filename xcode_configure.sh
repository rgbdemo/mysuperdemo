mkdir -p build
cd build && cmake -DNESTK_USE_OPENNI=1 -DNESTK_USE_PCL=1 -G "Xcode" ..
