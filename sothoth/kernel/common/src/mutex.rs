use spin::*;

pub unsafe fn force_acquire<T: ?Sized>(mutex: &Mutex<T>) -> MutexGuard<T> {
    let mut tried = mutex.try_lock();

    if !tried.is_some() {
        while !tried.is_some() {
            mutex.force_unlock();
            tried = mutex.try_lock();
        }
    }

    return tried.unwrap();
}
