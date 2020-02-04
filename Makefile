
DEFAULT_ZEN_RELEASE_MODE = Release

ZEN_RELEASE_MODE ?= $(DEFAULT_ZEN_RELEASE_MODE)
ZEN_BUILD_DIR ?= build/$(ZEN_RELEASE_MODE)

ifeq ($(ZEN_RELEASE_MODE),Debug)
	ZEN_ENABLE_ASSERTIONS ?= 1
else ifeq ($(ZEN_RELEASE_MODE),RelWithDebInfo)
	ZEN_ENABLE_ASSERTIONS ?= 1
else
	ZEN_ENABLE_ASSERTIONS ?= 0
endif

ZEN_SHARED_LIBRARIES ?= 0

all:
	@echo "\
	You are running 'make' in the root directory of the Zen++ project. \n\
	By default, this does nothing. Below are instructions on how you can build these libraries. \n\
	\n\
	These are some of the available targets: \n\
	\n\
	  make install -- Build and then install the libraries to the default directory on your system \n\
	  make test    -- Build all components and run the full test suite \n\
	  make build   -- Only build the components, leaving them in the local build directory  \n\
	\n\
	Environmnent variables: \n\
	\n\
	  ZEN_SHARED_LIBRARIES (default: disabled) \n\
	\n\
	    When enabled, will cause CMake to build shared libraries of those components \n\
	    that support it. This is an experimental feature and might get removed in future \n\
	    versions. \n\
	\n\
	  ZEN_RELEASE_MODE (default: $(DEFAULT_ZEN_RELEASE_MODE)) \n\
	\n\
	    Determines what symbols and optimisations will be used. \n\
	\n\
	  ZEN_ENABLE_ASSERTIONS (default: only enabled in Debug builds) \n\
	\n\
	    Force compiling with assertions enables, resulting in slightly more \n\
	    bloated executables and a small performance penalty, but much better \n\
	    error messages. \
	"

$(ZEN_BUILD_DIR): CMakeLists.txt
	@echo "Generating build files ..."
	@mkdir -p $(ZEN_BUILD_DIR)/ && \
		cd $(ZEN_BUILD_DIR)/ && \
		cmake ../../ \
			-G Ninja \
			-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
			-DCMAKE_BUILD_TYPE=$(ZEN_RELEASE_MODE) \
			-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
			-DBUILD_SHARED_LIBS=$(ZEN_SHARED_LIBRARIES) \
			-DZEN_ENABLE_ASSERTIONS=$(ZEN_ENABLE_ASSERTIONS) \
			-DZEN_ENABLE_TESTS=ON

.PHONY: clean

clean:
	@echo "Cleaning up build artifacts ..."
	@rm -rf $(ZEN_BUILD_DIR)

.PHONY: debug
	ninja -C $(ZEN_BUILD_DIR) run_all_tests
	lldb -- $(ZEN_BUILD_DIR)/run_all_tests --gtest_color=yes

.PHONY: test
test: $(ZEN_BUILD_DIR); ninja -C $(ZEN_BUILD_DIR) check

.PHONY: build
build: $(ZEN_BUILD_DIR); ninja -C $(ZEN_BUILD_DIR) zen_full

