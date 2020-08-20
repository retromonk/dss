# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.134.0/containers/cpp/.devcontainer/base.Dockerfile
ARG VARIANT="buster"
FROM mcr.microsoft.com/vscode/devcontainers/cpp:0-${VARIANT}

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends python3-pip python3-setuptools \
    build-essential cmake xorg-dev pkg-config libgl1-mesa-dev libxcb-render-util0-dev \
    libxcb-xkb-dev libxcb-icccm4-dev libxcb-image0-dev libxcb-keysyms1-dev \
    libxcb-xinerama0-dev xkb-data libsoil-dev libftgl-dev

RUN pip3 install conan
RUN conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan