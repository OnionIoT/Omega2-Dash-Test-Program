# How to compile omega2-dash-test-program using OpenWRT build system

> Instructions on compiling omega2-dash-test-program package for Omega2 platform from source code in github repo specified by `PKG_SOURCE_URL` variable in the `Makefile` in this directory.

Grab the path to this repo

```
cd <TOP LEVEL OF THIS REPO>
REPO_PATH=$(pwd)
```

First add this makefile to the Onion feed in the build system:

```
# assuming you're in the build system top directory
mkdir feeds/onion/omega2-dash-test-program
cp $REPO_PATH/src/openwrt/Makefile feeds/onion/omega2-dash-test-program/
```

Then install the package to the build system:

```
# assuming you're in the build system top directory
./scripts/feeds update onion
./scripts/feeds install omega2-dash-test-program
```

Then, you'll need to adjust the build system to enable the `omega2-dash-test-program` package.
Run `make menuconfig`, and go to Onion -> Utilities and select `omega2-dash-test-program` for compilation.

Finally build the package:

```
make package/omega2-dash-test-program/compile V=99
```

The output ipk file will be at `bin/packages/mipsel_24kc/onion/` it will be named something like `omega2-dash-test-program_0.0.1-1_mipsel_24kc.ipk`

Installing this package on an Omega2 device will install the compiled binary to `/usr/bin/omega2-dash-test-program`

# To build the package from local source

During development it is easier to work off a local copy of the source code.

First, run the regular make command for the package:

```
make package/omega2-dash-test-program/compile V=99
```

Then to switch to using the local source code

```
make package/omega2-dash-test-program/clean
make package/omega2-dash-test-program/prepare USE_SOURCE_DIR=$REPO_PATH V=s
make package/omega2-dash-test-program/compile V=99
```

On successful compilation, it will produce a file `bin/output` in the `omega2-dash-test-program` directory.

## To go back to using git repo

To move back to using the git repo to build the package:

```
rm -rf dl/omega2-dash-test-program*
make package/omega2-dash-test-program/clean
```

Any future compilations will download the source from the git repo and use that for compilation.
