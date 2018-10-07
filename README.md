# Badhron: Readable Tests for Impala

## Built-in assertions
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

## Add your own assertions for custom types
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
