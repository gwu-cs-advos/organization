# Advanced OS

The GWU advanced OS class dives into the details of trade-offs in the design and implementation of complex code-bases, with a focus on microkernels and hypervisors.
This repo includes the syllabus and other organizational aspects of the Advanced OS class.

## Educational Objectives

In this class, students will:

- Learn how to optimize for writing readable code.
- Understand how to do a deep, detailed dive into a code-base, and practice this in multiple code-bases with related goals.
- Understand how security guarantees are *engineered* into systems.
- Understand the trade-offs involved in designing for effective parallelism.
- Implement an OS on top of a microkernel.

## Prerequisites and Student Responsibilities

Graduate students should have taken the Architecture class, while undergraduates should have taken the OS class.
This class is quite detailed and focused on the C implementation of various systems.
If you don't have a decent grasp of C, this class will be quite challenging.
If you can effectively read C code, but still feel a little shakey with the language, you'll likely be in good company in the class.

Students must be active in class, especially in group discussion times.
Everyone must discuss what they learn in different code-bases.
If you're uncomfortable with this, this class might not be for you.

There is an implementation aspect to the class which requires a large degree of autonomy.
If you aren't comfortable with under-specified assignments, and with needing to exercise creativity in defining your goals, this class might not be for you.
If you aren't willing to dive into various code-bases to try and understand the underlying design, this class might not be for you.
I don't expect that anyone will have the experience to do this effectively coming into the class, and the class is designed around giving you practice in this.

## Lectures

Most lecture information will be in [slides](https://gwu-cs-advos.github.io/organization/).
These are generated from markdown [in the book's repo](https://github.com/gwu-cs-advos/docs/tree/main/slides).

## Calendar

Please fill out the required form for deadlines by noon on the day of the deadline -- i.e. around 2.33 hours *before* the class.

| Date  | Class topic                  | Due                                                                                                                       |
|-------|------------------------------|---------------------------------------------------------------------------------------------------------------------------|
| T1.14 | organization, reading code   |                                                                                                                           |
| R1.16 | complexity                   |                                                                                                                           |
| T1.21 | xv6 + busybox                | [xv6](https://github.com/gwu-cs-advos/organization/blob/main/class.md#2-xv6)                                              |
| R1.23 | abstraction                  |                                                                                                                           |
| T1.28 | plan9 + busybox + systemd    | [busybox](https://github.com/gwu-cs-advos/organization/blob/main/class.md#3-busybox)                                      |
| R1.30 | organizing components        |                                                                                                                           |
| T2.04 | plan9 + go                   | [plan9](https://github.com/gwu-cs-advos/organization/blob/main/class.md#4-plan9)                                          |
| R2.06 | organizing components        |                                                                                                                           |
| T2.11 | go + libuv + node            | [go](https://github.com/gwu-cs-advos/organization/blob/main/class.md#5-go)                                                |
| R2.13 | isolation                    |                                                                                                                           |
| T2.18 | libuv + demikernel           | [libuv](https://github.com/gwu-cs-advos/organization/blob/main/class.md#6-libuv)                                          |
| R2.20 | isolation                    |                                                                                                                           |
| T2.25 | composite design             | [demikernel](https://github.com/gwu-cs-advos/organization/blob/main/class.md#7-demikernel)                                |
| R2.27 | isolation                    |                                                                                                                           |
| T3.04 | composite runtime            |                                                                                                                           |
| R3.06 | interface design             | [UNIX Service](https://github.com/gwu-cs-advos/organization/blob/main/class.md#1-unix-service)                            |
| T3.11 | Spring recess                |                                                                                                                           |
| R3.13 | Spring recess                |                                                                                                                           |
| T3.18 | unikraft + composite         | [composite kernel](https://github.com/gwu-cs-advos/organization/blob/main/class.md#9-composite-kernel)                    |
| R3.20 | specialization               |                                                                                                                           |
| T3.25 | unikraft + nova              | [unikraft](https://github.com/gwu-cs-advos/organization/blob/main/class.md#10-unikraft)                                   |
| R3.27 | composite                    |                                                                                                                           |
| T4.01 | nova                         | [composite libs](https://github.com/gwu-cs-advos/organization/blob/main/class.md#11-composite-libs)                       |
| R4.03 | interface & component design |                                                                                                                           |
| T4.08 | nova + nickel                | [nova](https://github.com/gwu-cs-advos/organization/blob/main/class.md#12-nova)                                           |
| R4.10 | interface & component design |                                                                                                                           |
| T4.15 | nickel + komodo              | [nickel](https://github.com/gwu-cs-advos/organization/blob/main/class.md#13-nickel)                                       |
| R4.17 | security                     |                                                                                                                           |
| T4.22 | komodo                       | [komodo](https://github.com/gwu-cs-advos/organization/blob/main/class.md#14-komodo)                                       |
| R4.24 | close                        | [System Investigation](https://github.com/gwu-cs-advos/organization/blob/main/class.md#2-system-enhancement-andor-design) |

# Systems

We'll discuss and investigate a number of systems in this class.
These include:

- [Composite](https://github.com/gwsystems/composite/tree/v4) - our microkernel based on fine-grained isolation, user-level configurable policies, and component-based design.
- [libuv](https://github.com/gwu-cs-advos/libuv) - the core concurrency library underlying Node.js.
- [go](https://github.com/gwu-cs-advos/go) - a popular programming language that excels at managing complexity.
- [demikernel](https://github.com/gwu-cs-advos/demikernel) - a library-OS focused on extremely fast dataplanes in deep cloud infrastructure.
- [xv6](https://github.com/gwu-cs-advos/xv6-riscv) - a simple UNIX clone focused on pedagogy.
- [plan9](https://github.com/gwu-cs-advos/plan9) - a "UNIX done right" OS with a strong focus on "everthing is a file" and other composable abstractions.
- [busybox](https://github.com/gwu-cs-advos/busybox) - a POSIX user-level runtime that is in almost every embedded system including the bootup programs (e.g. `init`), and a set of common programs (e.g. `ls`).
- [unikraft](https://github.com/gwu-cs-advos/unikraft) - a library OS focused on providing a simple execution environment for a single application.
- [komodo](https://github.com/gwu-cs-advos/Komodo) - a minimal OS to create an enclave execution environment for an application.
- [nickel](https://github.com/gwu-cs-advos/nickel) - a security-focused OS that provides non-interference.
- [nova](https://github.com/gwu-cs-advos/NOVA) - a beautifully written microkernel focused on virtualization.

# Schedule

See the links to the code of the systems above.

## 2: xv6

`xv6` is a simple UNIX, copying the '77 version on which Lions based his [famous book](resources/unix6.pdf).
As such, it is a simple code-base to use to dive into the core of UNIX design.

- Where is the `init` program and what does it do?
- How expensive is the `fork` call?
  What are the main contributors to that cost?
- What file descriptor number is returned when a pipe or file is created?
- How many system calls does the OS have?

High level questions for discussion class:
- What choices and coding techniques enable `xv6` to be so simple?
- What choices enable it to avoid the complexity of other systems that have five orders of magnitude more code?

## 3: busybox

Busybox is a great example of relatively simple software that is pervasively deployed (in embedded systems) as a POSIX environment for a user-level bootup and shell execution.
It has a *very strange* execution model in which every shell program (`ls`, `cat`, etc...) is actually implemented as a *single* binary, and each program (e.g. `/bin/ls`) is aliased via links to that binary.
When the busybox binary runs, it will look at `argv[0]`, and run the corresponding "program" the user is trying to execute.
As such, the code is a little strange to go through as there is effectively a *single* program where you'd expect there to be multiple.

- Where is the `init` computation in Busybox, and what does it do to boot up a system?
- What does `inetd` do, and where is its core event loop?
- Why is busybox designed to be a single binary and emulate running separate binaries?

High level questions for discussion in class:
- What is the core difference between `inetd`, `cron`, and `initrc` in terms of their software structure?
- `systemd` is a super daemon (or collection of daemons) that actively manages a running system -- from bootup, to coordination, closer to `initd` than to `initrc`.
  Most modern systems use `systemd` or something like it (`launchd` in OSX) instead of a simple `init`...why?

## 4: plan9

Plan 9 is an OS that takes the idea of "everything is a file" very seriously.
For example, network sockets are integrated into the hierarchical file system namespace (i.e. there are no `socket` and `listen` system calls!).
One of the most interesting advances is that even *applications and application state can be represented in the FS*!
It is hard to really understand what this means, so please watch a brief video on a text editor that exposes its state via the FS, [acme](https://youtu.be/dP1xVpMPn8M?t=743).

First, lets dive into Plan 9's kernel a little bit, and understand one of its interesting innovations: `rfork`.
`rfork` enables different processes to see different versions (i.e. application-specific versions) of the FS.

Second, we want to understand the equivalent of the VFS layer in Plan 9 that enables user-level definition of FSes: the 9p protocol.
What would it take to write a service in Plan 9?
First, the library for helping services interact with the 9p protocol:

- [9p.h](https://github.com/gwu-cs-advos/plan9/blob/master/sys/include/9p.h), and
- [the library](https://github.com/gwu-cs-advos/plan9/tree/master/sys/src/lib9p)
- including a [ramfs](https://github.com/gwu-cs-advos/plan9/blob/master/sys/src/lib9p/ramfs.c) example

Then, two of the main consumers of the API:

- [exportfs](https://github.com/gwu-cs-advos/plan9/blob/master/sys/src/cmd/exportfs/) (this takes a local namespace and exposes them over a 9p channel, served over the network), and
- [import](https://github.com/gwu-cs-advos/plan9/blob/master/sys/src/cmd/import.c) (this contacts a 9p channel over the network, and exposes its namespace in the local namespace via mount).

Questions:

1. Where is `rfork`, and how does it differ from the normal `fork`?
	Why is it more general?
2. What does `import` do?
	Where are the calls to the `9p` library?
	Where is the logic for maintaining the namespace, and other functionality?
3. Exportfs can handle many concurrent client requests at the same time, even though the local namespace has blocking read and write.
	First, identify where the actual read operation (in response to a `TREAD` 9p request) is conducted, and then answer how `exportfs` is written to enable multiple client requests to be handled concurrently even if one of them blocks.

For discussion in class:
- How are namespaces and system organization used in plan9 to promote composability?
- What are the trade-offs in enabling apps to interact with each other through their own exported FS interface?

## 5: go

The `go` language (created by the people who designed Plan 9!) is a simple language with garbage collection that has a model of concurrency based on easily creating new threads ("goroutines"), and coordinating between them with channels. Instead of UNIX programs that coordinate using file-descriptors, "channels" are a first-class abstraction in go.

The go runtime (the code used to provide the execution environment for go programs) source is complex, and much of it is written in go itself!
Given this, I'll provide more hints for where to dive in to the code.
You'll likely want to do a little research into what programming with go and go channels looks like.

This one is going to be hard.
We do hard things to push ourselves ☺.

Some interesting code entry points:
- `go` has three execution abstractions: `g` which is a goroutine (registers + stack), `m` is an OS thread (e.g. a `pthread`), and `p` is a logical processor (think "real core").
	A decent high-level [overview](https://povilasv.me/go-scheduler/) with links and [docs](https://github.com/gwu-cs-advos/go/blob/master/src/runtime/proc.go#L22).
	The go runtime is an approximation of an M:N threading model (it maps goroutines onto threads, and -- to some degree -- those onto cores).
	The `runtime2.go` file introduces these abstractions, for example, `g`, the [goroutine structure](https://github.com/gwu-cs-advos/go/blob/master/src/runtime/runtime2.go#L396) (and later `m` and `p`).
- The core logic for [handling execution abstractions](https://github.com/gwu-cs-advos/go/blob/master/src/runtime/proc.go) and scheduling.
  - Condition variable blocking on [`gopark`](https://github.com/gwu-cs-advos/go/blob/master/src/runtime/proc.go#L418)
  - [Scheduling!](https://github.com/gwu-cs-advos/go/blob/master/src/runtime/proc.go#L3988)
- [Channel send](https://github.com/gwu-cs-advos/go/blob/master/src/runtime/chan.go#L176)
There are a lot of details about garbage collection here (memory barriers, tracing, "stopping the world", etc...), that should instantly be mentally "pruned" in your pass through the code.

Questions:
- Where is the main function for the `go` program called?
  The runtime must execute and initialize, then call into the application's `main` function.
- What scheduling policy does the runtime use (i.e. how does it decide what to run)?
- Try and assess the fastpath for channel send/receive.
  What is the common case control flow for channels?

For discussion in class:
- What abstractions for concurrency does `go` provide to programs?
- What semantic gaps between go programs and the OS interface exist?

## 6: libuv

Javascript is a language that handles concurrently entirely through event-based means.
This means that it is generally a single-threaded environment (ignoring "workers").
Old-style javascript says "when this event happens, invoke this closure", and modern javascript uses `async`/`await` syntax support (originally created in C#).
Managing concurrency with events rather than with separate threads means that system calls that would otherwise be blocking (e.g. `read` on a socket) must either be set to be *non-blocking*, or must be sent to a thread-pool for system calls that cannot be made non-blocking (e.g. `open`).
This is a lot of code and complexity!

`libuv` is the library underlying `node.js` that provides all of this logic and exposes a callback model to the C code that is used to implement the javascript runtime.
It is cross-platform and we can focus mainly on the POSIX/Linux part of it.

Questions for `libuv`:

1. What APIs are necessary for a client to read from a network socket?
	The tests are likely going to be quite helpful in understanding this.
2. What Linux *system calls* are used for event multiplexing (which functions are they called from, where in code, etc...)?
	You need to be specific here and provide a link to the code, thus dive deep into the code.
3. What quick thoughts do you have about an event-based programming style?

It might help to start out by perusing the [tests](https://github.com/libuv/libuv/tree/v1.x/test) will give you a lot of context to dive in.

For discussion in class:
- What OS abstractions is this library trying to hide?
- Please describe the core abstractions provided by this library?

## 7: demikernel

The demikernel is a low-level library to provide abstractions to programs that want to *directly interact* with I/O.
It leverages user-level device drivers to directly interact with the DMA ring buffers, thus is focused on areas that require extreme performance, and don't care about security.
Concurrency is managed with co-routine-based threads, and an I/O model that enables asynchrony in the APIs.

Demikernel documentation that might be helpful:

- [Demikernel -- see Fig 3](https://irenezhang.net/papers/demikernel-hotos19.pdf) abstractions and API.
- [API](https://github.com/gwu-cs-advos/demikernel/blob/master/API.md) documentation

Questions:

1. What APIs does the DK use to issue requests to send or receive data, and get notified when there is an event?
	What APIs does a client use to "block" awaiting events?
2. DK does not *actually* block (despite having APIs labeled as blocking).
	I define blocking as "being removed from the scheduler runqueue to allow other threads to execute".
	Provide evidence of this in the code.
	Why do you think this is?

For discussion in class:
- In what ways are demikernel's design very specialized to its goals?
- What problem domains do you think are a good fit for the demikernel?

## 9: composite kernel

The Composite kernel has a number of kernel resources,
- [Threads](https://github.com/gwsystems/composite/blob/v4/src/kernel/include/thread.h#L97-L120)
- [Page-table nodes](https://github.com/gwsystems/composite/blob/v4/src/kernel/include/chal_pgtbl.h#L11-L18)
- [Capability-table nodes](https://github.com/gwsystems/composite/blob/v4/src/kernel/include/captbl.h#L10-L19)
- [Components](https://github.com/gwsystems/composite/blob/v4/src/kernel/include/component.h#L6-L13)
- And a few others related to scheduling and virtualization.

The source is organized as such:
- The different [resources](https://github.com/gwsystems/composite/blob/v4/src/components/lib/cos/cos_consts.h#L109-L129).
- The pages use the **retyping system** to be typed into the various [resources](https://github.com/gwsystems/composite/blob/v4/src/kernel/resources.c) of the kernel.
- The different [capability types](https://github.com/gwsystems/composite/blob/v4/src/components/lib/cos/cos_consts.h#L14-L35).
- The [*operations*](https://github.com/gwsystems/composite/blob/v4/src/components/lib/cos/cos_consts.h#L53-L79) that can be performed on capabilities that reference (name) those resources. These have logic that is generally defined in [cos.c](https://github.com/gwsystems/composite/blob/v4/src/kernel/cos.c). These include
  - Creating a [capability slot](https://github.com/gwsystems/composite/blob/v4/src/kernel/cos.c#L438-L459)
  - operations performed on [page-table nodes](https://github.com/gwsystems/composite/blob/v4/src/kernel/cos.c#L522-L597) such as mapping in memory, copying mappings, and [hooking](https://github.com/gwsystems/composite/blob/v4/src/kernel/cos.c#L583-L593) lower-levels in the page-table into higher-levels (and vice-versa).
  - The *fast-path* for Protected-Procedure Calls (i.e. IPC) includes both [invoking and returning](https://github.com/gwsystems/composite/blob/v4/src/kernel/include/ipc.h) -- the entire system is designed to make this fast.
- The [system call handler](https://github.com/gwsystems/composite/blob/v4/src/kernel/cos.c#L745-L753) -- the main entry point into the kernel.

Questions:

1. What thread operations are there? Summarize what they do.
2. Summarize what the PPC path does.
3. The retyping logic has to synchronize between cores.
   Any guesses how this is done?

## 10: unikraft

One direction that some OSes have taken is to support *system specialization*.
Can we remove both the semantic gap, and superfluous functionality that slows the system down if we
1. make the entire OS support *a single application* (similar to the demikernel), and
2. enable the OS to be specialized to that application in some way.

Popular systems over the past decade that focus on these two goals are *unikernels* - kernels that specialize for a single application.
A very cool unikernel is [unikraft](https://github.com/gwu-cs-advos/unikraft).

Read through the code and try to understand and answer the following questions:
1. In what ways can the system be customized/specialized?
2. How is the code written in a way that enables this specialization (this is ambiguous to enable to learn any interesting configuration methods in the system)?
3. Describe three of the libraries (in `lib/`) that are interesting to you.

## 11: composite libs

While we've discussed the Composite *kernel*, it is important to understand the user-level abstractions of the system as most of the interesting policies in the system are defined in user-level components.
This includes the libraries we use to abstract kernel resources and operations, and the components that provide the policies.
Remember that the kernel is quite hard to use: you have to use retyping syscalls to even be able get the memory to back capability and page-tables *before* being able to populate them!
The libraries in the system attempt to abstract some of this complexity.

Higher-level operations on Components through the `crt`, [Composite RunTime library](https://github.com/gwsystems/composite/blob/v4/src/components/lib/crt/crt.h):
- [Creating components](https://github.com/gwsystems/composite/blob/v4/src/components/lib/crt/crt.h#L167) from elf binaries (see the `elf_hdr` argument),
- [Creating synchronous invocations](https://github.com/gwsystems/composite/blob/v4/src/components/lib/crt/crt.h#L187) between them, and
- [Creating threads](https://github.com/gwsystems/composite/blob/v4/src/components/lib/crt/crt.h#L201) in components.

Scheduling with the `slm` (Scheduling Library, Minimized -- version 2 of a [scheduling](https://github.com/gwsystems/composite/blob/v4/src/components/lib/slm/slm_api.h) [library](https://github.com/gwsystems/composite/blob/v4/src/components/lib/slm/slm.h)):
- Enabling scheduler plugin policies for [scheduling](https://github.com/gwsystems/composite/blob/v4/src/components/lib/slm/fprr.c) and [timer management](https://github.com/gwsystems/composite/blob/v4/src/components/lib/slm/quantum.c),
- Synchronization within the scheduler around a per-core [critical section](https://github.com/gwsystems/composite/blob/v4/src/components/lib/slm/slm.h#L196-L298), and
- Handling [timer interrupts](https://github.com/gwsystems/composite/blob/v4/src/components/lib/slm/slm.c#L470-L569).

While it would be difficult to understand many of the components as they require more context, the [Capability and Memory Manager](https://github.com/gwsystems/composite/blob/v4/src/components/implementation/capmgr/simple/capmgr.c) is one we've discussed in class quite a bit:
- Allocating memory (e.g. providing the equivalent of `sbrk`),
- Sharing memory, and
- Creating threads.

To inspire your reading of the code, [Composite as an industrial song](https://github.com/user-attachments/assets/a99bf496-6185-43f4-bee7-e547ca636381) (also found in `resources/Capability\'s\ Cage.mp3` - share with your friends!) to lull you to sleep while thinking about capabilities (thanks Sean & Sonu).

Questions:

1. What are the core abstractions provided by the scheduling library?
2. What thoughts do you have on the similarities and differences of the `crt` interface versus something more conventional (like `fork`, `exec`, `pipe`, etc...).

## 12: nova

VMs are an integral and essential part of modern infrastructure.
Even serverless offers that try and abstract away from the core hardware completely rely entirely on VMs (see Firecracker).

For this, and the next code review, we're going to dive into Nova.
The [Nova](http://hypervisor.org/eurosys2010.pdf) [hypervisor](http://hypervisor.org/) is a L4-lineage microkernel that uses IPC based on synchronous IPC between threads.
It supports virtualization (e.g. of Linux) by using hardware virtualization extensions (called VMX in Intel chips, and SVM in AMD chips).
These hardware extensions enable a VM to be executed without trapping from the VM into the kernel for most operations.
For example, the hardware extensions enable

1. the VM to have its own version of page-tables, thus to perform address virtualization without interacting with the real kernel (they hypervisor of the VMM), and
2. the execution of a virtual user-level and kernel-level, and transitions between these modes (i.e. system calls, and exceptions) can proceed without trapping to the hypervisor.

In short, the hardware support makes many of the hardware's normal facilities be directly accessed and programmed within the VM.
However, some actions within the VM do cause traps outside of the VM.
These traps might be due to a request for I/O (to a virtualized device), or due to an access to a "physical page" that the hypervisor doesn't have a mapping for (e.g. if we're providing 1GiB RAM for the VM, and the VM accesses a physical address at 1.5GiB).
Nova transforms these traps into IPC to a server, than can handle the trap!
Thus, a normal server will handle VM traps, thus can provide virtualized I/O for the VM!

I'd like you to demystify the hardware interface for virtualization.
Much of the Intel support is in the corresponding [files](https://github.com/gwu-cs-advos/NOVA/blob/arm/inc/x86_64/vmx.hpp) for [VMX](https://github.com/gwu-cs-advos/NOVA/blob/arm/src/x86_64/vmx.cpp).

The [specification](https://github.com/gwu-cs-advos/NOVA/blob/arm/doc/specification.pdf) for Nova provides quite a bit documentation that might be helpful for you.

Questions:

- Nova has one of the fastest IPC implementations.
	Give me a summary of the flow of control through the system for a pair of `call` (from the client), and `reply` (to "reply & wait" from the server).
	What do you think makes this implementation so efficient?
- Nova uses hardware virtualization, e.g. VMX.
	What is your *rough* sense of how this hardware works, and how it interacts with the system?

References:

- Find the [list of system calls](https://github.com/gwu-cs-advos/NOVA/blob/arm/src/x86_64/syscall.cpp#L546-L564).
- The NOVA equivalent of [call](https://github.com/gwu-cs-advos/NOVA/blob/arm/src/x86_64/syscall.cpp#L111-L138) and [reply & wait](https://github.com/gwu-cs-advos/NOVA/blob/arm/src/x86_64/syscall.cpp#L171-L184).
- The [`ret_user_sysexit`](https://github.com/gwu-cs-advos/NOVA/blob/arm/src/x86_64/ec.cpp#L155) is some assembly to simply return from kernel-level to user-level.
	It is the "return" part of a system call.
- Some acronyms:

	- EC = execution context (e.g. thread!)
	- UTCB = user-level thread control block which is region of memory shared by user-level and the kernel that can hold, for example, arguments to an IPC -- and generally, a set of registers.
	- FPU = floating point unit -- the hardware that lets you do floating point computation (e.g. `float` and `double`).
	- `cont` in an EC = a "continuation" that holds a function pointer to how to continue executing the thread when we try and switch back to it. An example: When we reply to a client's IPC request, the client's continuation is simply `ret_user_sysexit`, which (you guessed it!) simply returns to user-level to continue the client's computation post-`call`.
	- An `rcap` is a "return capability" which is a capability that denotes the ability to return back to a client that is blocked `call`ing the server.
		It is used to return control back to the client.
	- `current` is the currently executing EC (thread).
	- `Kobject`s are generic kernel objects (think the base-class for all kernel objects).

## 13: nickel

Nickel is a research OS that aims to guarantee the lack of *covert channels* between different processes that should not be able to communicate.
Covert channels enable two processes that *should not be able to pass data (e.g. passwords)* to do so using implicit means.
A simple example: if there's a single namespace that is shared between processes, it can (potentially) be used to pass information between processes.
Imagine if there's a single process id, `pid` namespace.
A bit (`0` or `1`) can be passed between processes as such:
- At a specific time one process will create a process, then after a delay, will create a second process.
- The other process that is "transmitting" information will create a process during the delay if it wants to pass a `1`, or avoid creating a process to pass `0`.
- The first process will see the processes have pids `i` and `i+1` in the first case, and `i` and `i+2`

Of course, it is possible that something else in the system creates a process within the delay, thus accidental interpreting the signal as a `0`.
So all covert channel approaches need to filter out the signal from the noise (and there are algorithms for that).

The focus of Nickel is how to create an OS without covert channels.
The kernel has [architecture](https://github.com/gwu-cs-advos/nickel/tree/master/kernel) and [core code](https://github.com/gwu-cs-advos/nickel/tree/master/nikos2).
In many ways, it is even simpler than `xv6`!

Questions:

1. How does Nickel allocate `pid`s to avoid covert channels?
2. Where does Nickel use quotas, and how does it coordinate them when a process creates/spawns a new process?

References:
- Examples of how interfaces can cause covert channels are in Section 2 in [the paper](https://unsat.cs.washington.edu/papers/sigurbjarnarson-nickel.pdf).

## 14: komodo

Komodo is a security-focused system for running *enclaves*.
Enclaves are execution environments that *do not trust the kernel that provides them resources*!
The interface for the system is very simple: it focuses on enabling an application in the OS to create an enclave and run code in it.

![Komodo API](resources/komodo_api.png)

Parts of this API have strong similarities to the page-retyping we've discussed.
The main author of the work was involved in a microkernel that indeed used user-level retyping of kernel memory!
The OS APIs focus on creating the memory image for the enclave's execution, and `Finalise`-ing it, at which point the OS can no longer modify it.
The enclave, when it boots up, makes sure that the environment it executes in is "as expected".
That is to say, it uses the `Attest` and `Verify` calls to ensure that the memory the enclave has access to is the proper initial image, and the underlying page-table has the proper access rights.
Note, this still enables the OS (and a process in the OS) to share memory with the enclave, thus communicate.

You should read through the C code (there's Dafny code as well that provides a formal verification of the supervisor).

Questions:

1. What is your mental model for what the hierarchy of the system looks like?
   What components are there (certainly, at least the Linux OS, and its processes)?
   How are they organized?
2. What are the types that frames can have, and why do you think that this enclave system uses frame (page) retyping?

References:
- If the code is hard to reverse engineer, Section 4 of [the paper](https://www.microsoft.com/en-us/research/wp-content/uploads/2017/10/komodo.pdf) might help.

# Coding Projects

## 1: UNIX Service

For this, you'll implement a trusted UNIX daemon that provides services to the rest of the system.
Examples of existing similar technologies are `systemd` and `launchd`.
Simpler historical services include `inetd` and `init`, for example in `busybox`.

Your service must do all of the following:

1. Use UNIX domain sockets for communication with a known path for the *name* of the socket.
2. Use `accept` to create a connection-per-client as in [here](https://gwu-cs-advos.github.io/sysprog/#communication-with-multiple-clients).
3. Use event notification (epoll, poll, select, etc...) to manage concurrency as in [here](https://gwu-cs-advos.github.io/sysprog/#event-loops-and-poll).
4. Use domain socket facilities to get a trustworthy identity of the client (i.e. user id).
5. Pass file descriptors between the service and the client.

[The Linux Programming Interface](https://man7.org/tlpi/code/index.html) is a great resource for code for domain sockets and related technologies.
For example, see the [client](https://man7.org/tlpi/code/online/dist/sockets/ud_ucase_cl.c.html) and [server](https://man7.org/tlpi/code/online/dist/sockets/ud_ucase_sv.c.html) code for 1. getting authenticated client id, and 2. [passing](https://man7.org/tlpi/code/online/dist/sockets/scm_multi_send.c.html) [file-descriptors](https://man7.org/tlpi/code/online/dist/sockets/scm_multi_recv.c.html) from the service to the client.
You should implement your service in C/C++/or Rust as I'd like you to not use a language that drastically hides the APIs.

This set of requirements enables the service to have higher permissions than its clients (e.g. to run as `root`), thus have access to many resources, yet to provide a service in which a subset of those resources are given to clients based on their requests and their user ids.

Other than this set of requirements, you're free to do whatever you'd like!
Some examples:

- The service can host a database (e.g. SQLite) and provide its own policies for allowing clients to access different parts of the data-base.
- The service can play the role of a nameserver, enabling clients to find either other based on what services they offer (identified with a string), and which they want to leverage ( this is the core of how notifications work in Linux, for example power, wifi, etc...).
- Provide a routing service to connect a client to another program (similar to the nameserver), but with an emphasis on enabling this communication to be local (on the machine), or remote (via network sockets) based on where the other program is located.
- Provide something similar to a [9p service](https://en.wikipedia.org/wiki/9P_(protocol)) to access a virtual (user-level service controlled) file system image.
  The service speaks 9p with the client, and shares `fd`s to provide direct access to files.
- Provide an LLM service with per-client context and replies; the shared file descriptor might be a scratchpad of the entire conversation with each client.
- ...

Detail what you've done in the `README.md`, including who worked on what part.
Provide high-level context for what your service's goals are, what it is trying to do, how it uses 1-5 above, and some very high-level documentation into the design with links to the corresponding code.
Provide information about your testing of the project, and how I can run the tests.

## 2: System Enhancement and/or Design

Apply some of the concepts you've learned or we've discussed in the class in some systems domain.
You can take one of the systems we've discussed, and add a feature, port an application to them, or implement a service in them.
You can also propose to do something novel or interesting in another OS, or in systems-level code.
Please write a brief proposal, and send it to me via email, and when you do, ping me in the Discord DMs.

This is intentionally vague so that it gives you some lattitude to work one something of interest.
If you're already working on some systems project (or research), it is OK to propose that.

Examples within the systems we've discussed:

1. Install and use Unikraft in a VM on your system. Either
   a. compare the performance of an application in your system versus in unikraft (e.g. nginx, redis, ...)
   b. write and application that is a good fit for unikraft, for example, a simple MQTT broker.
2. Install Plan 9 in a VM, and write a file system server that does something interesting (this is similar to the first project, but in Plan 9).
3. Install/[build](https://github.com/microsoft/demikernel/blob/dev/doc/building.md) Demikernel and using catnap (that uses sockets from the underlying OS to back the demikernel logic), [run](https://github.com/microsoft/demikernel/blob/dev/doc/testing.md), and measure performance of an microbenchmarks.
4. Write a network-facing application (e.g. MQTT broker) using libuv.

As a first-cut expectation, I'd assume that you'd want to stick with a systems language: C, C++, Rust, go.

To submit, please:
1. fill out the same form you did for project one (in the class' google document),
2. Make sure to write a `README.md` in your repo with the design, a summary of what you'd completed, and instructions for building/testing, and
3. a video demonstrating you using/testing your program.

I'd prefer to simply watch the video, and then only dive into the rest if I have questions or concerns.

# Grading

## Grading Philosophy

This class very much leans into the idea that you'll get out of it what you put in.
The grading structure leans into this.

## Overall Grade

| Activity                 | % of your grade |
| ---                      | ---             |
| Code & Lecture Questions | 30%             |
| Class Participation      | 30%             |
| Homeworks + Project      | 40%             |

## System Design Reviews

You'll be reading a lot of code, and watching lectures throughout the class.
Each student starts the class with a code and lecture questions grade of between A-: 3.7.
The grade scale for each questionaire is:

|        | not sufficient | sufficient | significant insight |
|--------|----------------|------------|---------------------|
| points | `0`            | `1`        | `2`                 |

See the spreadsheet for your grade.
I must *completely subjectively* provide this assignment.
My goal is to discuss the material in class so that you understand what's expected.

Your final grade in this category is calcuated as $$\lceil 3.7 + \sum_{w_i} (0.1 \times (g_i - 1)) \rceil$$ for each week $w_i$ for the associated week's grade $g_i$.
That is to say, each 0 decreases your grade by 0.1 points, and each 2 increases it by 0.1.

I'll drop your lowest two scores to compensate for sickness and unplanned life complications.

*Transparency.*
The goal of this grading scale is to make it obvious what your grade is at any point.

## Class Participation

You have an A in participation to start the class.
I'll use peer evaluation via forms to assess participation and involvement for in-class group discussions.
Each student will give scores to each other in discussion of system code.
The final impact of any student's scores on another will be a normalized modifier based on the average score over all ratings (of other students).
So deviations from the average score are what modify people's grades.

I'll drop your lowest two scores to compensate for sickness and unplanned life complications.

If you fill out a form for someone outside of your group, each time you'll lose 10% of your participation grade.

I'll track participation during the class, and that will *increase* your grade.

*Transparency.*
I'll give you warnings if your scores are consistently low.

## Coding Projects

You can form a group of as many people as you'd like (or you can do it solo!).

The second coding project will be graded by Demo.
Again, A- is the baseline for completing the assigned task.
Your grade is modified up to A if you do a great job, and show significant thought in your implementation.
It is modified downwards if you

1. don't provide sufficient testing,
2. don't consider necessary cases, or
3. don't provide necessary functionality.

The deadlines are long enough into the future that emergencies and sickness should not impact them.
Contact me early if you anticipate significant issues.

I'll provide a single grade per group, so choose the people in your group wisely.

*Transparency.*
You should know at the end of your demo what your grade is, and why it is what it is.

## Late Work

No late work is accepted for the Code & Lecture Questions.
On the Homeworks and Project, you lose a letter grade a day if you're late.
The *last commit* to your repo is considered your submission.

## Academic Honesty

Full collaboration is encouraged in this class.
You're allowed to use LLMs and the full breadth of the Internet.
*However*,

1. you must be able to explain and understand any output you generate, and
2. if you use code from elsewhere, or if another student helps you out, you *must* acknowledge them with an appropriate comment in your code and/or documentation.
