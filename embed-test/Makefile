
all: cmake meson

.PHONY: sync
sync :
	mkdir -p subprojects/zen
	cp -ra ../CMakeLists.txt ../meson.build ../meson_options.txt ../zen subprojects/zen
	cd subprojects/zen && meson wrap install gtest

.PHONY: meson
meson:
	meson meson-build
	ninja -C meson-build
	rm -r meson-build

.PHONY: cmake
cmake:
	cmake -B cmake-build -G Ninja
	ninja -C cmake-build
	rm -r cmake-build

.PHONY: clean
clean:
	rm -r cmake-build
	rm -r meson-build
	rm -r subprojects/zen
