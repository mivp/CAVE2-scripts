# xhost +si:localuser:root
# docker build -t electro .
# docker run --init --runtime=nvidia --name=electro --rm -i -v /tmp/.X11-unix/X0:/tmp/.X11-unix/X0 electro
# docker exec -ti electro glxgears

FROM ubuntu:18.04

#FROM nvidia/opengl:1.0-glvnd-runtime

#ENV NVIDIA_DRIVER_CAPABILITIES ${NVIDIA_DRIVER_CAPABILITIES},display

RUN apt-get update && apt-get install -y --no-install-recommends \
        libglu1 \
        libsm6 \
        libxv1 \
        x11-xkb-utils \
        xauth \
        xfonts-base \
        iputils-ping \
        bash-completion \
        build-essential \
        xorg-dev \
        ssh \
        curl \
        libfreetype6-dev \
        libpng-dev \
        libjpeg-dev \
        zlib1g-dev \
        libtiff-dev \
        libxft-dev \
        libgl1-mesa-dri \
        libgl1-mesa-glx \
        libglu1-mesa-dev \
        mesa-utils \
        rsync \
        vim \
        less \
        libsdl1.2-dev \
        liblua5.1-dev \
        libvorbis-dev \
        libogg-dev \
        libode-dev \
        libopenmpi-dev \
        openmpi-bin \
        xkb-data && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /Electro

RUN groupadd -g 999 cave && \
    useradd -r -u 999 -g cave cave

RUN chown cave:cave /Electro

USER cave

# Copy Electro src
COPY --chown=cave:cave files/ /Electro/

#clean & rebuild
RUN cd /Electro && \
    make clean && \
    make distclean && \
    make MPI=1 -j16

ENV DISPLAY :0.0

#ENTRYPOINT [""]


