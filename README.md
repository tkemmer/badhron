# Badhron: Readable Tests for Impala
Badhron is a simple test framwork for the [Impala](https://anydsl.github.io)
language with the goal of supporting the creation of readable and logically
organized test functions. It is loosely inspired by
[FactCheck.jl](https://github.com/JuliaAttic/FactCheck.jl).

Please bear in mind that this project is currently still in very early
development. Consequently, its interface might and - most probably - will be
subject to breaking changes every once in a while.


## Getting started

### Requirements
 * [CMake 3.12](https://cmake.org) (or above)
 * [GCC](https://gcc.gnu.org/) or [Clang](https://clang.llvm.org/)
   (C++17-compatible)
 * [AnyDSL Runtime Library](https://github.com/AnyDSL/runtime)

### Installation
```sh
git clone https://github.com/tkemmer/badhron.git
mkdir badhron/build
cd badhron/build
cmake ..
```


### Usage
The recommended way of using Badhron is as part of a CMake project. See
`doc/example` for an example application.


## Introduction

### Contexts
In Badhron, tests are logically organized into groups (e.g., I/O functions,
utility functions, etc.). Each group can be further partitioned into subgroups.

#### Test program
```rust
extern fn main(i32, &[&[u8]]) -> i32 {

	// initialize Badhron
	with suite in badhron_suite() {

		with suite.group("first group") {
			// ... some testing
		}

		with suite.group("second group") {
			// ... some more testing

			with suite.subgroup("a subgroup") {
				// ... these tests belong together
			}

			with suite.subgroup("another subgroup") {
				// ... so do these tests here
			}
		}
	}
}
```

#### Output
```sh
GRP first group
================================================================================
2 PASSED ✓

GRP second group
================================================================================
 > a subgroup (3 passed)
 > another subgroup (4 passed)
 + group checks (1 passed)
================================================================================
8 PASSED ✓
```


### Built-in assertions
Badhron ships with assert functions for all fundamental Impala data types:

```rust
extern fn main(i32, &[&[u8]]) -> i32 {
	with suite in badhron_suite() {
		with suite.group("pending") {
			suite.pending("some_function() still needs to be tested");
		}

		with suite.group("assertions") {
			with suite.subgroup("bool") {
				with suite.assert_true()      { 1 == 1 }
				with suite.assert_false()     { 1 == 2 }
				with suite.assert_bool(true)  { 1 == 1 }
			}

			with suite.subgroup("int") {
				with suite.assert_i64(42_i64) { 2_i64 * 21_i64 }
				with suite.assert_i32(42    ) { 2     * 21     }
				with suite.assert_i16(42_i16) { 2_i16 * 21_i16 }
				with suite.assert_i8 (42_i8 ) { 2_i8  * 21_i8  }
			}

			with suite.subgroup("uint") {
				with suite.assert_u64(42_u64) { 2_u64 * 21_u64 }
				with suite.assert_u32(42_u32) { 2u    * 21u    }
				with suite.assert_u16(42_u16) { 2_u16 * 21_u16 }
				with suite.assert_u8 (42_u8 ) { 2_u8  * 21_u8  }
			}

			with suite.subgroup("float") {
				with suite.assert_f64(42.0)   { 4.0 * 10.5  }
				with suite.assert_f32(42.f)   { 4.f * 10.5f }
			}
		}
	}
}
```


### Custom assertions
Add your own assertions for custom types:
```rust
struct Point2D {
	x: i32,
	y: i32
}

fn assert_point2d(exp: Point2D, obs: Point2D) -> BadhronCheckFn {
	BadhronCheckFn {
		name:   "assert_point2d",
		check:  || exp.x == obs.x && exp.y == obs.y,
		report: |r| {
			if exp.x != obs.x {
				r.add_int_report(
					"x-coordinate mismatch",
					exp.x as i64,
					obs.x as i64
				)
			}
			if exp.y != obs.y {
				r.add_int_report(
					"y-coordinate mismatch",
					exp.y as i64,
					obs.y as i64
				)
			}
		}
	}
}

extern fn main(i32, &[&[u8]]) -> i32 {
	with suite in badhron_suite() {
		with suite.group("custom assertions") {
			with suite.subgroup("Point2D") {
				let p1 = Point2D{x: 1, y: 2};
				let p2 = Point2D{x: 1, y: 2};
	
				with suite.assert() { assert_point2d(p1, p2) }
			}
		}
	}
}
```
