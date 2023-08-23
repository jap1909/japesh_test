FROM nexus.addverb.com:443/ubuntu_base:fms as builder
COPY . /exec
WORKDIR /exec
# RUN sh INSTALL_DEP
RUN rm -rf build && mkdir build
RUN cd build && cmake ..
WORKDIR /exec/build
RUN make -j8
