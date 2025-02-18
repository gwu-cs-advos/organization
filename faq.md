# Questions asked during System Design Reviews

## `xv6`

> What is the file-descriptor type in `file.h` (e.g. `FD_PIPE`), and don't FD 0, 1, 2 have to do with stdin/out/err?

These are part of the file descriptor structure, and are used to record the type of the file descriptor, not the fd number.
In Linux, instead of a type like this, and a switch statement to take the correct action for a `read`/`write`/etc, the `struct file` has a set of function pointers that are overwritten by pipe, file, dev, etc...-specific functions depending on the type of the file.

> Is this a minimal number of system calls? Why don't all OSes have a minimal number?

"Minimal" is *real hard* to define, and is specific to a set of required applications.
What if your system has to support almost *every single application*?

> What is this doing?

```c
        (*f0)->type     = FD_PIPE;
        (*f0)->readable = 1;
        (*f0)->writable = 0;
        (*f0)->pipe     = pi;
        (*f1)->type     = FD_PIPE;
        (*f1)->readable = 0;
        (*f1)->writable = 1;
        (*f1)->pipe     = pi;
```

Each file has a readable and writable field that define the allowed operations on that file descriptor.
When `read` or `write` are used on an fd, the kernel checks these values to see if the operation is allowed, or should error out.
Because we're setting the type of `FD_PIPE`, `->pipe` is set to the struct pipe.

> How hard is it to add threads to xv6?

Ask the undergrads: that's homework 3 in CSCI 3411.

> Why not networking?

We didn't have it in the 1978 world of UNIX!
We could absolutely add it, but it would take a lot of work.

> Why aren't `fork` and `exec` bundled together!?

This is not how UNIX works.
`fork` creates new processes, and `exec` loads a new program into an existing process.
`posix_spawn` and the `CreateProcess` comparable function in Windows couple both into a single call.
We'll talk a lot about this later in the class.

> What's with the UART support?

The serial device/bus is pretty pervasive in a lot of systems, and is often used to connect to a terminal for input and output.
In xv6, all output goes to the serial device, and all input (from the keyboard) comes from it.

> Why does the xv6 shell restart after execution, and doesn't that impact performance?

The developers likely determined that it was the simplest way accomplish the goals of the shell.
It is likely slower to recreate the process rather than just "loop", but has the benefit that it can avoid bugs carrying over across shell invocations (e.g. memory leaks).
Restarting processes has been called "poor man's garbage collection" for this reason.

> Why no `creat` in `xv6`?

`open` with the `O_CREATE` flag can create a file, so the developers didn't implement a separate `creat` call.
What are the trade-offs with this?

> Doesn't this do most of what we need? Why are systems more complex?

This gives us "bare minimum" UNIX.
But with only these minimal abstractions we cannot have nice interactive behavior, GUIs, networking, efficient multi-threading, power management, etc...
When you need to support all of databases *and* web browsers *and* video games *and* webservers *and* embedded computations *and* legacy support, the complexity proliferates.

> It is surprising that `dup` returns the lowest available fd #. What is `dup` used for?

POSIX specifies that file descriptors should always be allocated such that the lowest numerical file descriptor that isn't in use is returned for a few `file`.
By strategically `close()`ing file descriptors `0`, `1`, and `2`, we can use `dup` to duplicate specific file descriptors into the stdin/out/err.
See the `init` and `shell` programs for examples.

As it turns out, this is pretty limiting, so Linux supports `dup2` which lets you *choose* the file descriptor you want to allocate.

> Why spinlocks over mutexes? Why mutexes over spinlocks?

There are contexts in which you *cannot block* such as during ISR (interrupt service routine) execution where you're technically executing in a random processes context.
In such cases, you *must* use spinlocks.
In many other cases, you want to block on contention, and use mutexes.

There is a performance question here that underlies the choice:
If it takes longer to block a thread, switch to another, and eventually switch back to and resume the thread (i.e. as in a mutex), than to spin awaiting entry to a critical section, then it is likely better to use a spinlock.
However, if you anticipate spinning to get into the critical section for *more* time than all of the thread manipulation and scheduling, you want to use a mutex.
So a core question is: how long is the critical section versus the system costs of thread block/wakeup/switch?

> Why is the stack below the heap in `xv6`?

I don't know why it was designed this way, but one benefit is that a stack overrun won't accidentally spill or overwrite onto the heap.
Recall that stacks grow from higher to lower addresses, so in the following:

```c
void foo(void) { foo(); }
```

...each successive recursive call to `foo` will grow the stack from higher virtual addresses to lower ones.
If the stack is at lower addresses than the heap, then the above code won't overwrite the heap!

> Why does `kmalloc` use `5` instead of `0` in initializing its new page?

The core question is, "what does the system do if it forgets to initialize the memory returned from `kmalloc`.
Initializing it all to `5` will make errors have a higher likelihood of crashing the system.
This is better than silently failing.
`0` can mask a lot of errors as it is the same as `NULL`, whereas `5` is more likely to cause logic errors.

> Why would init.c use dup(0) for both the stderr and stdout?

Even more, in `init.c`, all of the first three file descriptors are the same!

```c
	if (open("console", O_RDWR) < 0) {
		mknod("console", CONSOLE, 0);
		open("console", O_RDWR);
	}
	dup(0); // stdout
	dup(0); // stderr
```

File descriptor `0` is the terminal device/console, which can be both read and written.
`dup`ing it into both `1` and `2` means that all of stdin/out/err are all the same console device.
Reading from that device reads from the console (the command line).
Writing to it, outputs to the console.
So it makes sense that we'd want this as a default.

This does oddly mean that you can write to `stdin` and read from `stdout`!

> Can a process get rid of its stdin/stdout/stderr? If so, can get them back?

Yes, you can `close()` any file descriptor you have access to.
You cannot get them back if you don't have another file descriptor that links to them.
If they are backed by a file, or some resource you can name in the FS, then you can re-open the file.
But as a general rule, when you `close()` an fd, you cannot get it back -- even if it is fd `0-2`.

> Are all of the user programs stored in the same place as kernel code?

The kernel allocates memory for user-level computations from its own memory pool (in a normal OS, using a buddy allocator).
It then pieces the application together using page-tables to make the physical memory contiguous.
In the end, user programs are fragmented across the kernel as they execute, but page-tables make it work.
In the riscv version of `xv6`, the kernel is loaded at relatively low virtual address and is in *its own page-table*.
This means that the kernel's addresses overlap with user-level addresses as the kernel uses a separate page-table from application code.

Most kernels are *not* designed this way (including the x86 `xv6` kernel).
Instead, the kernel is loaded into very high addresses (often using the upper-half of the page-tables).
The kernel is therefore present in each process' virtual memory, but the user-bit (`PTE_U`) is set on the user-level mappings, and not on the kernel mappings.
Thus the kernel mappings, though they are in the page-table of the application as it executes, are not accessible.

Why use one design over the other?

- A separate page-table for the kernel has the benefit that virtual addresses can be the same as physical addresses.
  Physical addresses are used in page-tables, when programming the page-table base register (`satp`), or when talking to a device to do DMA.
- A separate page-table for the kernel has the downside that when the kernel receives a virtual address as a system call argument, it must translate that virtual address into memory that the kernel can dereference (i.e. it must translate from user-virtual into physical), which practically means it must walk the user's page-table -- see `copyin` and `copyout` in `vm.c`.
  This is relatively complex and expensive.
- If the kernel shares the same page-table as the application, the benefit is that it can directly access addresses provided for system calls (doing this is *very hard* as user level might provide *incorrect* pointers such as `NULL`), which is fast.
- If the kernel shares the same page-table as the application, the kernel will be loaded into virtual addresses that aren't identical (an "identity mapping") to physical memory, so any calculation of physical addresses (for page-tables, the page-table base register, or DMA) must manually convert to physical addresses usually using simple subtraction (i.e. `phys_addr = virt_addr - KERNEL_BASE_VIRT_ADDR`).

On balance, the cost of copying user syscall arguments is too high, so most systems will use a shared page-table.

...but as with all things in this class, that is not always true.
The meltdown bug, mean that kernels needed to use separate page-tables when security was a core concern, thus Linux uses [page-table isolation](https://en.wikipedia.org/wiki/Kernel_page-table_isolation).

## `busybox`

> How is busybox optimized for embedded systems?

All of busybox and its applets are compiled together into a single binary.
This enables the compiler and linker to get rid of objects and functions it doesn't require.
It also enables code and data to appear once in the busybox binary, rather than being replicated across different binaries.
Note, that many busybox systems focus on *static linking* of binaries, thus why this technique is useful.

> What is the `INIT_G` in most programs?

A macro to initialize the globals for the program.

> Why have a `global` struct, and `INIT_G` macro for its initialization in many of the programs?

This might be an attempt to avoid symbol namespace pollution.
The ELF objects/binaries will only have a single symbol for the global variable, rather than a separate symbol for each global variable.
If any of those variables are *not* `static`, this is important as it prevents two symbols in different "programs" (.o files) from having a symbol conflict that would prevent linking.
This is a somewhat typical C practice, but it is very important in busybox where many logically separate programs are linked together.

It could also simply just be a convention that they use.

> What are all of the "//config" statements in the code?

The kconfig system is a way to configure the features you want present in a source code base.
It is often manually configured using `make menuconfig` (i.e. this is a key part of building the Linux kernel.
The `Makefile` [parses out](https://github.com/brgl/busybox/blob/master/Makefile#L362-L365) all of those statements, and generates config files from them.
These are read in when one executes `make menuconfig` to present to you the options to include or not those configuration options.
Your choice determines essentially if a `#define OPTION` is created in a shared include file (I believe in `applets.h`).
As such, if you decide to enable `OPTION`, it will generate the header that includes that option, thus triggers the compilation of all code within `#ifdef OPTION...#endif` guards.

In short: only generate code that you actually want!
Note that plan9 has a different perspective/mechanism for doing this.

> Why couple the daemons with the rest of the code?

They absolutely *do* share some library code and data with other applets (programs).
So including them is meant to avoid replicating that in memory across binaries.
Daemons are also the code that is least likely to have a performance impact from the busybox organization.
They startup once (and go through the whole applet selection code), and execute for the duration of the system.
Thus, they pay the startup cost once, as opposed to command line programs (e.g. `ls`) that must pay that cost on each execution.

> `inetd` uses `vfork` then `exec`; doesn't this overwrite the memory of the parent?

`vfork` avoids copying all memory from the parent, thus its *only valid use* is to shortly thereafter call `exec`.
The child is treated as a separate process that simply shares the same address space (kinda like a thread, but one that shares the *stack* of the parent).
Thus when it calls `exec`, it will only overwrite the child process, which effectively means the parent is the only process still accessing the original memory.

> How does `init` support SysV runlevels?

It [does not](https://github.com/gwu-cs-advos/busybox/blob/master/init/init.c#L1244-L1246)!
It supports a simple inittab.
It is perhaps less appropriate for larger, complex systems that could use the modularity of rc scripts.

> Why so many macros?

To enable configurability of which features are included in the resulting binary.
Remember that a small footprint is a core goal of busybox!

> When `init` runs, are the filesystems and console assumed to be already set up?

No!
`init` runs a ram-based file system as it is loaded into memory by the bootloader along with the kernel.
Thus, the FS that is accessible upon `init` execution is quite limited to the ram image.
`init`'s job is the `mount` the appropriate file system to ensure that the rest of the actual FS is available.
But...where is this happening?
EC for finding out!

Where is the console?
`init` uses the console in `/dev/tty`, I believe.

> Where is `setsid` defined?

Note that `busybox` is *not* standalone!
It still requires a libc to execution successfully.
Often it is used with `musl` libc as it shares the goal of simplicity and minimal footprint.

> Why does `inetd` use `vfork` instead of `fork`?

While `vfork` is more efficient, the reason is likely that busybox wants to be able to execute on systems that *don't have an MMU!!!*
That means that there is no address virtualization.
`fork` simply cannot exist in such a system.

> How does `busybox` work since it is all one binary: where is the kernel?

`busybox` depends only on having a libc, but also a working kernel!
`busybox` is only a user-level program.

## Plan 9

> There seems like a hard separation between creating threads and processes.

This is true in the plan9 adaptation to Linux as user-level libraries, but is *not* the case in the Plan 9 source.
`rfork` will make a new thread if `RFMEM` is passed as one of the bits in `flags`, otherwise copying memory.

> What does it mean to "import from a remote system"?

We are taking a directory in the file system hierarchy on a *remote host*, and mounting it locally into our system so that we can see it as if it is local (i.e. if you do `ls`, you'll see its contents).

> Everything is a file and some of the FS operations in Plan 9 seem powerful, why aren't they more used?

Linux's FUSE has been doing similar things (exposing application state in the FS) for a long time.
You've likely used it without knowing!
9p was also used for a long time as the "file-level protocol" of choice for virtual machines (via `virtio-9p`).

> Isn't there a significant performance penalty to having FS operations all use 9p and potentially user-level computations?

Yes!
This turns all FS accesses into IPC, and, similar to microkernels, if IPC isn't optimized, it can significantly slow down your system.
Plan 9 never had a significant focus on performance as it was deemed "fast enough".

> Does the per-process namespace make it easier to implement containers in Plan 9?

Yes!
This, combined with the fact that there aren't that many namespaces -- mostly focused on the hierarchical FS namespace -- containers are pretty trivial in 9p.
Even better, one almost doesn't need containers as you can simply mount the file system hierarchy you want your "container" to have *from a remote system*.

> There are terms in the source that aren't quite acceptable anymore, for example the `slave` function in exportfs...how have software norms around this changed over time?

There was a significant movement to rename the `master` branch that was the default in `git` and `github` to `main` a few years back.
As social norms change, they sometimes impact software.
It is more common for them to impact the interface we use to software as many more users see that, but sometimes it impacts how we *develop* software as well.

> Where is `rfork` implemented? This is so hard to find!

Most system call layers in OSes will take a system call `X` and call a function like `sysX` as the first step to executing the system call.
Often that function will call another function `X` in the code, but not always.
So the core implementation is in [`sysrfork`](https://github.com/gwu-cs-advos/plan9/blob/7524062cfa4689019a4ed6fc22500ec209522ef0/sys/src/9/port/sysproc.c#L24-L207) in this case.

> How does `exportfs` handle resource exhaustion if it creates too many processes to handle `read`/`write`/`open` requests?

It doesn't!
The hope is that you scale up the number of threads you need to match the maximum concurrency, and hope that the difference between average and maximum isn't that much, or that the maximum is commonly used.
Note also that Plan 9 threads don't have *too much state*, so they hopefully won't hog too much memory.
However, most modern thread pools do indeed, enable themselves to be shrunk so that they can both increase in size to handle transient bursts of high concurrency, *and* shrink themselves down to conserve resources (mainly memory) during periods of low concurrency.

Note that if you don't shrink your thread pool, it opens the system up for a resource exhaustion attack where an adversary attempts to create unreasonably large concurrency to force the allocation of many (millions) of threads.
Putting an upper bound on the thread pool size is a somewhat hacky way to prevent this.

> How does `exportfs` ensure consistent file updates when they are performed across concurrent threads?

It is worse!
File modifications might also be done by *other programs* on the system that hosts the filesystem!
It looks like there is very little done to ensure consistency of various updates.
However, this is similar to file updates in UNIX!
Concurrent modifications can have strange results:

Process 0:
```c
write(fd, "1", 1);
write(fd, "2", 1);
```

Process 1:
```c
write(fd, "3", 1);
write(fd, "4", 1);
```

Can result in a file with contents:

```
32
```

...with no atomicity.

File locking can help prevent this, but it is *opt-in*, not portable, and somewhat broken.
See the book for examples.

In short, we don't really expect that two processes updating the same file will ever work!
Programs that require this (e.g. sqlite) require their own locking primitives layered on top of the file accesses -- a semantic gap!

> Why does Plan 9 use per-processes namespaces instead of a single global namespace?

This enables
- security in the sense that processes in a *separate namespace* cannot access VFS updates/changes made by other processes (e.g. if the sets of processes belong to different users),
- containers in which the VFS API of different processes is tailored to what they require (i.e. the development image they need), and
- it enables the distributed processing model of the system as different nodes are by-default separated in namespaces, but those namespaces can be merged to access remote resources using an access model consistent with local access.

> Is Plan 9 mainly an exemplar of a system created around the 9p protocol?

It is more.
Without per-process namespaces, the abstractions in Plan 9 wouldn't really work.
Without services like the plumber and applications like Acme to demonstrate how far the abstraction can be pushed, it would be under-motivated.
Without the meticulous API design around, for example, the `mount` system call, 9P couldn't be deeply integrated into the system as a core structuring primitive.
Without the strong push to ensure that everything is a file (e.g. including networking), the composability of the system would be greatly diminished.
Without the granular resource sharing options in `rfork`, namespaces and the VFS couldn't be used to construct abstractions nor secure systems.

All of these are in some way related to 9P and "everything is the VFS", but they are separate innovations.
It is clear that many of these innovations were *more popular* than 9P: Linux has integrated most of them in a hackey way, but 9P is the one aspect that isn't really used!!!

> Why does `rfork` start the process in user-mode?

There's no reason for the process to, once switched to by the scheduler, execute in the kernel.
All of the kernel computation for setting up the process is done in `rfork` not when we run that new process.
Thus, the process is setup such that when the scheduler first runs the new process, it will essentially just "resume" it at user-level.

> As each process can have its own namespace in Plan 9, does this effectively mean that each process can be its own container?

Yes.
Namespaces largely center around the VFS, but include other factors as well in Plan 9.
As these can be intentionally shaped by `bind`, `mount`, and `rfork` flags, we can *design* the namespaces in accordance with some specification...like a docker file!
Containers also contain the specifications of the file systems, but I'm sure that they can be implemented relatively simply in Plan 9.
Note that Linux relies on UnionFS to enable files to be added into a shared set of directories from different collections of files or images.
The core question with this is if the same file exists in two images, which version from which image should you use.
Plan 9 was the first system I know of to enable this support through the [`flags` to `mount`](https://9p.io/magic/man2html/2/bind): `MREPL` and `MBEFORE`.

> If processes in Plan 9 are treated as files can they be copied like a file?

Yes!
You can even do this in Linux: `cp /proc/self/mem my_memory`!
The direct access to process memory file the VFS is one of the main ways that debuggers are implemented!
When you print out a variable in a debugger, you're reaching into the memory (or a register) of the process through the VFS interface to get its value!

> How does rendezvous work in Plan 9?

[Rendezvous](https://en.wikipedia.org/wiki/Rendezvous_(Plan_9)) enables a process to block awaiting synchronization on a `tag` from another.
Another process can call `rendezvous`, and if the `tag` matches that of the previous process, they will exchange values.
You can see in `exportfs` how it is used to pass the "work" to be done to a thread in the thread pool.

These `tag`s are a namespace that can be shared or not when a new process is created.

The rendezvous mechanism is very similar to the `chan_*` API in xv6...which was written by one of the core authors of Plan 9!

> If each process has its own view of the filesystem in Plan 9, doesn't this cause massive memory consumption?

The kernel has to track each of the places where directories (mount points) in the VFS are created, which corresponds to each directory used in `mount` and `bind`.
It seems like there's the low-tens of mount/bind points in a typical process, which isn't a large data-structure to track.
Note that just because you see your own namespace, it doesn't mean that the resources in that namespace aren't shared.
Two processes might separately see directories `/blah/` and `/foo/`, but the same 9P stream (e.g. from `import`) is mounted into the separate directories.
Thus, the two processes see different namespaces, but within those namespaces, the contents of those files is identical.
What namespace you see is orthogonal to resource sharing.
This is a *required* feature of containers because you want to be able to run many containers and have them mostly share the underlying files (at least read-only, or copy-on-write).

> Interesting that they maintain separate bodies of code for each architecture in Plan 9 instead of using `#define`s.

Yes, they have very strong opinions about avoiding `#ifdef` hell.
I believe their C variant doesn't even support them!
Generally, if you can separate out specific features into functions, and use the build system to use the appropriate one, "normal code" can be cleaner.
However, it can also mean you have to understand the build system to understand which version is being used which can be annoying.
This is generally solvable so long as you provide build-system introspection into which files/objects are being used for a compilation.

## `go`

> How is the channel implementation synchronized? Isn't the mutex being used for the blocking path?

Locks are used to protect `go`'s core run-time data-structures in many places.
Since each `m` can be preempted at any point by the kernel, all data-structures either have to be updated with atomic instructions (where the logic allows), or protected with a lock.
Those locks certainly can block (they are backed by `futex`es), but this source of blocking is seen as a different from the controlled concurrency and blocking of goroutines.
It is simply a "cost of doing business" within the `go` runtime.
Note that the span of the critical sections for such locks is *not impacted* by the application's code and is entirely a runtime-specific implementation detail.

> Does goroutine stealing mean that each `p` has access to each other's runqueue?

Yes!
In the end, the runtime uses shared memory between each `p`, so they can access each other's runqueues.
Of course, this requires synchronization, so the runqueues have to either be lock-free, or use locks.
In `go`'s case, you can see that it [relies on atomic instructions](https://github.com/gwu-cs-advos/go/blob/6da16013ba4444e0d71540f68279f0283a92d05d/src/runtime/proc.go#L6865-L6886) and lock-free structures.

> How does spinning threads avoid throughput issues?

Threads actually don't spin in the `schedule` loop!
The `mPark` function will block an OS thread (an `m`), so each iteration through the schedule loop will block a thread.
The intuition is strong: if we can't find a goroutine to execute, then we have too many actual OS threads, so block one, perhaps to be woken later when we need more.

> How does `go` schedule goroutines especially relative to channel operations?

Generally, the `schedule()` function tries to look at all of the goroutines associated with a `p` (though it does look "globally" as well), and choose which to execute.
The channel logic may `gopark` the current goroutine if it must block, which will eventually change the goroutine state (away from "running"), add the goroutine to a `sudog` -- a block/wakeup tracking datastructure, and call `schedule()` to choose another goroutine to run.

> I didn't see a preemptive scheduler. Isn't this an issue?

`go` leverages OS threads that are preemptive at the OS level, but uses cooperative scheduling by default between goroutines with some facilities for preemption through timer signals.
So preemptions happen, but they happen within the OS kernel, not in the `go` runtime.
You might think about it this way: `go` creates multiple OS threads (`m`), which are preemptive, so the `go` runtime must assume that a preeemption can happen *at any time*!
Go relies on timer events (I believe delivered with signals) to provide the equivalent of timer interrupts for the system.
The `schedule()` function will choose which goroutine to execute at any point.
Note that one of `go`'s goals is to ensure that there is only a single OS thread running for each core on the system, which will decrease the chance of preeemptions *within the go runtime*.
It can't do this perfect because it doesn't control when OS threads are blocked (e.g. on a demand-paging load/store) or when they wakeup (e.g. from a blocking system call).

> How does `go` avoid the additional overheads of context switching?

`go` attempts to avoid OS thread context switching costs by trying to have a single OS thread on each core, and instead manage the context switches between goroutines within the user-level runtime.
The core idea is to use M:N threading, emphasizing the hopefully lower costs of scheduling and switching between goroutines.

> What does `go` look like from the OS's perspective?

Like a normal multi-threaded process.
Nothing special.
So the OS simply schedules its own OS threads, and execute system calls as normal.
The `go` runtime tries to use the normal OS abstractions to provide this M:N threading model on top.

> Why are there both global and local runqueues?

The local runqueue is for a specific processor (`p`).
When you call `schedule()`, you're doing so in a specific goroutine, that is associated with a specific `p`.
So that will use the local runqueue for that `p` by default.
The global runqueue is a single runqueue for the entire runtime.
A goroutine is only in a single one of these runqueues at any point (or is executing).
By default when we switch to another goroutine, we'll keep the previous goroutine in the local runqueue (unless it is blocking).
This will maintain some locality of reference: maybe the next time we run that goroutine, some of its data is still in that processor's cache, making it faster.
When a goroutine executes a blocking system call, when it wakes up it will likely be placed into the global runqueue so that it will later be "moved" into a local runqueue and executed in a `p`.

> What if we choose the number of `p` (`GOMAXPROCS`) to be larger than the number of cores on the system?

This will lead to one or more cores on the system to run *multiple OS threads* within a single `go` runtime.
Thus, `go` will no longer have some power to control which goroutine is actually running on a core at a time, and will suffer the preemption costs of multiple OS threads.
Put another way: `go` tries hard to make sure that there is at most a single OS thread running per core in the `go` runtime so that *it can control concurrency and scheduling*.
This proposal would break its ability to do so.

> Why is there a null pointer dereference at the end of `main`?

The preceding `exit` shouldn't return.
If it does because of some bug somewhere, it would be really nice to catch the bug, and this is one way to do so.
It might be that they didn't want to trust the printing or tracing machinery if a bug already happened, so a simple segmentation fault can be a trustworthy way to report an error.
Alternatively, it might be the case that they are trying to make the `go` compiler understand that this code should not be executed.
This would depend on assumptions within the compiler that I don't understand, so this might not be a motivation.

> What does the work stealing actually do?

Work stealing is a general workload management technique mean to solve the problem of workload imbalances.
What if there are many goroutines running on a single `p`, and none on the other?
We have to "rebalance" the goroutines (the work) between `p`s.
Work stealing is a historically powerful approach in which a core (`p`), when it doesn't have work to do, can "steal" work from another `p`.
There are proofs that stealing from a *random* other `p` is optimal, which is what `go` does!

> What are the drawbacks and benefits of M:N threading?

These systems attempt to be able to switch between threads solely at user-level.
Thus thread coordination (e.g. via channels) can be much faster, in theory.
However, they have a lot of complexity in trying to manage the number `N` of OS threads used in the system as different OS threads (running user-level threads, or goroutines) block and wakeup.
If you are frequently changing between OS threads (because of blocking or other kernel coordination), then you're paying the price of that kernel overhead *and* the user-level overhead for the user-level scheduling (that we saw in the code this week).

> What is the advantage of using channels over more conventional coordination (e.g. monitors in Java)?

There's a lot of literature written on this, and a lot of strong opinions.
One argument is that when you're using channels, you are avoiding shared data-structures.
Using locks to protect data-structures is really hard and can cause bad performance problems, or deadlock.
Channels are another way to design parallel systems.
It might also be argued that in network-facing systems (that are `go`'s core purpose), channels better capture request processing than locked data-structures.
There are also trade-offs between thread-based or event-based concurrency control systems that are related to this, but beyond what I want to get into here.

> Why are channels more efficient than alternatives?
> If a goroutine wants to send data into a full channel it will block, or if a goroutine receives data in an empty channel, the same.
> Don't we pay the cost of blocking either way?

Recall that all of this logic is in user-level, including the `go` runtime.
So even if a goroutine blocks, it doesn't need to call into the kernel.
Instead, the `go` runtime can simply switch to another goroutine directly!
Because we aren't calling into the kernel, we can likely have less overhead, even in the blocking cases, compared to kernel operations.
However, there are *many* cases where channels will not require blocking (e.g. receiving from a channel with data in it), and these are pretty common cases.
In those cases, we're again avoiding any system calls, and quickly interacting with the channel

## `libuv`

> What happens if a handler queue runs out of space

Usually these are vectors, thus dynamically expanded, or any handlers that overflow.
In some cases, runtimes will use a linked list representation to hold "overflow".

> Are flags a good way to pass information about the types of different options?

`flags` in C (and C++) are usually used as efficient *sets*.
They are a single word, thus don't require dynamic memory allocation, and operations such as checking membership and adding to the set are simple bit operations (`|` and `&`).
`enum`s or `#define` constants assign a name to a separate bit so that set operations are easier to read.
The downside is that you cannot support more items in the set than you have bits.
I'd imagine that here they are useful as they avoid memory allocation.

> Do event-based systems handle high loads well?

Yes, they are designed for this case.
In a thread-based system to handle concurrency, you might have thousands of threads to handle the different connections, and the memory and CPU overhead for this might overwhelm the system.
Instead, each "client" is encoded in an event that is passed through functions as it is processed.
The inner loop of an event-based system uses `epoll` to multiplex the events.

The downside of event-driven systems is that they make very hard to understand code.
It is said that they "rip the stack" apart as what would normally be a sequence of function calls in a single sequential segment of code turns into code split across functions, with state serialized into events.

Some programming languages (C#, javascript, and Rust) provide `async` and `await` keywords and promises that enable the *language* to define the event handlers and event data transparently.
This tries to be "the best of both worlds" -- you get to write thread-like code that is easy to read and the events are created by the language -- but has software engineering issues.

> Why does `libuv` abstract the event multiplexing mechanism (including `kqueue`, `IOCP`, etc...) instead of always using `uio_ring` on Linux?

`uio_ring` is not supported on older Linux kernels, and is not supported on other OSes!
`kqueue` is a BSD mechanism, and `IOCP` is Window's mechanism.

> Where is the `backend_fd`? I don't see it in the `uv_loop_t` structure?

It is pulled in with `UV_LOOP_PRIVATE_FIELDS` (in `include/uv/unix.h`).
This is a way for `libuv` to provide easy access to the publicly accessible fields (as part of the API to clients), and to "hide" the private fields that should only be accessed by the internals of `libuv`.
C doesn't provide visibility modifiers to `struct`s so, this is a hackey way to convey to the user the intent of the fields.

> What's the diference between `poll` and `epoll`?

There are many differences, a couple of the big ones:
1. `poll` is level-triggered, so will return all file descriptors that are readable/writable when called, whereas `epoll` is event-triggered so will only tell you which file descriptors have *become* readable/writeable since the last time `epoll` was called.
   As such, `poll` is slightly easier to use (processes can track less state).
2. `poll` takes $N$ arguments (for $N$ file-descriptors) that can lead to a lot of copying between user and kernel, while `epoll` (and `epoll_cntl`) always pass $1$ file descriptor of interest to and from the kernel, so `epoll` scales *much better* than `poll`.
   `epoll` is used in domains that care about performance (most of them).

> Does event-driven programming require fewer locks?
> I don't see any in the library?

Instead of using threads to manage concurrency, event-driven systems use events.
This is a much more *explicit* way for the system to track and control concurrency.
As you don't require multiple threads, you don't require locks!
**However**, If you want to use multiple cores, you will still require locks to coordinate between the cores.
Each of the `loop` constructs enable clients of `libuv` to manage multipl event loops, for example, one per core.
