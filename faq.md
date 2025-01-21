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
- If the kenrel shares the same page-table as the application, the kernel will be loaded into virtual addresses that aren't identical (an "identity mapping") to physical memory, so any calculation of physical addresses (for page-tables, the page-table base register, or DMA) must manually convert to physical addresses usually using simple subtraction (i.e. `phys_addr = virt_addr - KERNEL_BASE_VIRT_ADDR`).

On balance, the cost of copying user syscall arguments is too high, so most systems will use a shared page-table.

...but as with all things in this class, that is not always true.
The meltdown bug, mean that kernels needed to use separate page-tables when security was a core concern, thus Linux uses [page-table isolation](https://en.wikipedia.org/wiki/Kernel_page-table_isolation).
