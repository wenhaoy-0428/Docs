## Service/Stub/Proxy

1. `Service` and `Stub` are basiclly the same thing.
2. `Service` is **singleton** and therefore, there's only one corresponding `Stub`.
3. When a process tries to connect a `Service`, it first connects to `SystemAbilityManager`, then ask for the desired `Service`
~~4. `SystemAbilityManager` will return the `Stub` of that object and `IPC` will convert it to `IpcObjectProxy`.`~~