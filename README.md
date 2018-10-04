# Badhron: Readable Tests for Impala

## Example
```rust
extern fn main(i32, &[&[u8]]) -> i32 {
	with brn in badhron_suite() {
		with brn.group("pending") {
			brn.pending("my_function1");
		}

		with brn.group("assertions") {
			with brn.subgroup("bool") {
				with brn.assert_true()      { 1 == 1 }
				with brn.assert_false()     { 1 == 2 }
				with brn.assert_bool(true)  { 1 == 1 }
			}

			with brn.subgroup("int") {
				with brn.assert_i64(42_i64) { 2_i64 * 21_i64 }
				with brn.assert_i32(42    ) { 2     * 21     }
				with brn.assert_i16(42_i16) { 2_i16 * 21_i16 }
				with brn.assert_i8 (42_i8 ) { 2_i8  * 21_i8  }
			}

			with brn.subgroup("uint") {
				with brn.assert_u64(42_u64) { 2_u64 * 21_u64 }
				with brn.assert_u32(42_u32) { 2u    * 21u    }
				with brn.assert_u16(42_u16) { 2_u16 * 21_u16 }
				with brn.assert_u8 (42_u8 ) { 2_u8  * 21_u8  }
			}

			with brn.subgroup("float") {
				with brn.assert_f64(42.0)   { 4.0 * 10.5  }
				with brn.assert_f32(42.f)   { 4.f * 10.5f }
			}
		}
	}
}
```
