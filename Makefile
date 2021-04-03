CONFIG ?= release
BUILD_DIR_BASE = cmake-build
BUILD_DIR ?= $(BUILD_DIR_BASE)-$(CONFIG)

ifneq (,$(findstring clang,$(CXX)))
    LCOV = lcov --gcov-tool llvm-gcov.sh
else
    LCOV = lcov
endif
COVERAGE_DIR=$(BUILD_DIR_BASE)-coverage

CLANG_TIDY_ARGS += -clang-tidy-binary clang-tidy-12
CLANG_TIDY_ARGS += -clang-apply-replacements-binary clang-apply-replacements-12
CLANG_TIDY_ARGS += -j $(shell nproc) -quiet
CLANG_TIDY_ARGS += -p $(BUILD_DIR) -header-filter $(shell realpath ./etl)

.PHONY: all
all: config build test

.PHONY: config
config:
	cmake -S. -B$(BUILD_DIR) -D CMAKE_BUILD_TYPE:STRING=$(CONFIG) -D TOBANTEAUDIO_ETL_BUILD_CPP20=ON

.PHONY: build
build:
	cmake --build $(BUILD_DIR) --config $(CONFIG) -- -j6

.PHONY: test
test:
	cd $(BUILD_DIR) && ctest -C $(CONFIG) -j8


.PHONY: coverage
coverage:
	mkdir -p $(COVERAGE_DIR)
	cmake -S . -G Ninja -B$(COVERAGE_DIR) -D TOBANTEAUDIO_ETL_BUILD_COVERAGE=ON -D TOBANTEAUDIO_ETL_BUILD_CPP20=ON
	cmake --build $(COVERAGE_DIR) -- -j6
	cd $(COVERAGE_DIR) && $(LCOV) -c -i -d . --base-directory . -o base_cov.info
	cd $(COVERAGE_DIR) && ctest -j12
	cd $(COVERAGE_DIR) && $(LCOV) -c -d . --base-directory . -o test_cov.info
	cd $(COVERAGE_DIR) && $(LCOV) -a base_cov.info -a test_cov.info -o cov.info
	cd $(COVERAGE_DIR) && $(LCOV) --remove cov.info "*3rd_party/*" -o cov.info
	cd $(COVERAGE_DIR) && $(LCOV) --remove cov.info "*c++*" -o cov.info
	cd $(COVERAGE_DIR) && $(LCOV) --remove cov.info "*v1*" -o cov.info
	cd $(COVERAGE_DIR) && $(LCOV) --remove cov.info "*Xcode.app*" -o cov.info
	cd $(COVERAGE_DIR) && $(LCOV) --remove cov.info "*test_*" -o cov.info

.PHONY: report
report:
	cd $(COVERAGE_DIR) && genhtml cov.info --output-directory lcov

.PHONY: docs
docs:
	doxygen Doxyfile.in

.PHONY: tidy-check
tidy-check:
	 ./scripts/run-clang-tidy.py ${CLANG_TIDY_ARGS} $(shell realpath ./examples)
	 ./scripts/run-clang-tidy.py ${CLANG_TIDY_ARGS} $(shell realpath ./tests)

.PHONY: tidy-fix
tidy-fix:
	 ./scripts/run-clang-tidy.py -fix ${CLANG_TIDY_ARGS} $(shell realpath ./examples)
	 ./scripts/run-clang-tidy.py -fix ${CLANG_TIDY_ARGS} $(shell realpath ./tests)


.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	rm -rf build_avr
	rm -rf build-doc

.PHONY: stats
stats:
	cloc --by-file cmake docs etl fuzzing tests README.md

.PHONY: format
format:
	find etl -iname '*.hpp' -o -iname '*.cpp' | xargs clang-format-12 -i
	find examples -iname '*.hpp' -o -iname '*.cpp' | xargs clang-format-12 -i
	find tests -iname '*.hpp' -o -iname '*.cpp' | xargs clang-format-12 -i