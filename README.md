# haul

Haul (/hɔːl/). According to
[thesaurus.com](https://www.thesaurus.com/browse/haul), is one of the synonyms
for the word cargo.

## Usage

**Create new project**

``` sh
haul new project_name
cd project_name
```

**Install new dependencies**

Executed automatically with `haul new`. Only needed when `vcpkg.json`
dependencies are updated and for freshly cloned projects.

``` sh
haul install
```

**Configure**

Does not build. May be needed if cmake configuration changes.

``` sh
haul configure
```

**Build**

Runs `haul configure` if needed.

``` sh
haul build
```

**Clean**

Remove compiled artifacts

``` sh
haul clean
```

For Details on how to configure the project see [cpp-init
wiki](https://github.com/dk949/cpp-init/wiki)

## Build and install

Note: to change install directory, add
`-DCMAKE_INSTALL_PREFIX=yourInstallPrefix` to the `cmake -B` command. On Linux
`bin` will be appended to the prefix, so use `-DCMAKE_INSTALL_PREFIX=~/.local/`
to install to `~/.local/bin/haul`.

``` sh
git clone "https://github.com/Microsoft/vcpkg.git"
./vcpkg/bootstrap-vcpkg.sh  -disableMetrics
./vcpkg/vcpkg install

cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
cmake --install build
```

## Things I'd add if I had more time

* [ ] Should be able to run the executable (e.g. `haul run`)
* [ ] `haul ...` should be runnable in any project subdirectory (currently only
  works in project root).
* [ ] Should be able to change cmake options, like generator and build type
  (currently both default)
* [ ] NPM style user defined scripts.
