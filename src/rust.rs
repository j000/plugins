use std::sync::atomic::{AtomicU32, Ordering};

#[allow(non_camel_case_types)]
pub struct Plugin_t {
    name: String,
}

impl Drop for Plugin_t {
    fn drop(&mut self) {
        println!("    {} destroyed", self.name);
    }
}

#[no_mangle]
pub extern "C"
fn plugin_create() -> *mut Plugin_t {
    let tmp = Plugin_t{
        name: String::from("rust"),
    };
    println!("    {} created", tmp.name);
    Box::into_raw(Box::new(tmp))
}

#[no_mangle]
pub extern "C"
fn plugin_destroy(plug_u: *mut Plugin_t) {
    assert!(!plug_u.is_null());
    unsafe {
        Box::from_raw(plug_u);
    }
}

#[no_mangle]
pub extern "C"
fn plugin_name(plug_u: *mut Plugin_t) -> *const u8 {
    assert!(!plug_u.is_null());
    let plug;
    unsafe {
        plug = plug_u.as_ref().unwrap();
    }
    plug.name.as_ptr()
}

#[no_mangle]
pub extern "C"
fn plugin_test(plug_u: *mut Plugin_t) {
    assert!(!plug_u.is_null());
    let plug;
    unsafe {
        plug = plug_u.as_ref().unwrap();
    }

    static COUNTER: AtomicU32 = AtomicU32::new(0);

    println!("    {} tested {} times", plug.name, COUNTER.fetch_add(1, Ordering::Relaxed));
}
