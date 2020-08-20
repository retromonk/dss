Building On Ubuntu 20.04
===
Install pre-requisites
---
```sudo apt-get -y install python3-pip python3-setuptools build-essential cmake xorg-dev pkg-config libgl1-mesa-dev libxcb-render-util0-dev libxcb-xkb-dev libxcb-icccm4-dev libxcb-image0-dev libxcb-keysyms1-dev libxcb-xinerama0-dev xkb-data libsoil-dev```

Install Conan
---
```pip3 install conan```

```conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan```

Build
---
```mkdir build && cd build```

```cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release```

```cmake --build .```
