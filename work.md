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

## 2: xv6
## 3: busybox
## 4: plan9
## 5: go
## 6: libuv
## 7: demikernel
## 8: composite kernel
## 9: composite crt
## 10: composite slm
## 11: unikraft
## 12: nova
## 13: komodo
## 14: nickel

# Previous Content (Ignore)

The sections of the this document are either:

- **Lx** in which case they refer to a lecture, and provide a set of questions, or
- **Cx** in which case they references to code-bases, and include a set of questions associated with it.

References to "the book" refer to [this](https://github.com/gwu-cs-advos/advos_book).

## L0: Reading Code

No work needs to be done before this class!
However, what we'll cover is likely the most important part of the whole class.
If you only read one part of the material for the class, read this.

References:

- See Sections on "Reading Code" and "Writing Readable Code" in the book.

## L1: Constraining System Complexity

Remember that you're expected to share questions you have in the feedback, so make sure to write down your questions as you go through the videos.
Please watch the lecture video on [constraining complexity](https://youtu.be/a8V2d33KvaE).

Questions (complete in the provided form):

1. Give a few examples of modularity in desktop operating systems?
2. Give an example of essential and accidental complexity in code you've written (briefly), and explain why you separate essential and accidental for that task?
3. It is counter-intuitive that abstractions constrain the more chaotic behavior of lower-level interfaces, into higher level APIs.
	Thoughts on this?

References:

- Lecture video on [constraining complexity](https://youtu.be/a8V2d33KvaE).
- See Sections on "Complexity Management" in the book.

## C1: Reading Documentation, Event Management, and Zircon

This week is an exceptional week:
We have to get through a lecture before the next class.
It is necessary to understand the code in Zircon.
I lightened the code investigation load.
Question about the video on [system design concerns](https://youtu.be/dX3-pUvWnOk):

1. Why do you think that the system design concerns are seen more in system modules than in applications?
	For example, you might not care about parallelism, concurrency, nor naming in your application, but you must consider them in system modules.

How do you form your initial hypothesis about code-bases, and your initial goals?
Often, you start with the design documents, and documentation.
Lets start out "easy mode" and dive into a project with nice documentation.
Lets dive into the concurrency challenges discussed in class in google's new OS, Fuchsia!

Questions (complete in the provided form):

1. Describe signals and their relation to events.
2. What functions enable threads to block waiting for multiple concurrent events?
3. List some system objects that can generate events.

References:

- Lecture:

	- Lecture video on [system design concerns](https://youtu.be/dX3-pUvWnOk).
	- See Section "System Interface Design Considerations" in the book.

- Fuchsia:

	- [Fuchsia documentation ](https://fuchsia.dev/fuchsia-src/concepts).
		Starting point help: We want to focus on the *kernel*'s abstractions.
		You can find the documentation for the kernel on this page as well.
		You can start by understanding what calls are blocking, and which are non-blocking, then move on to how the zircon notion of *signalling* is tied to events.
	- Some of the [conventions](https://fuchsia.dev/fuchsia-src/concepts/api/system) make digesting the documentation easier.

## L2: Interface Properties

Today we're going to understand a number of properties of interfaces that we can use to understand what differentiates good interfaces, from those that are more difficult to use.
Keep in mind that there are no perfect interfaces out there, so all of this should be taken as a modus operandi.
Watch the [lecture](https://youtu.be/mKJcqvozfA8) and answer the questions below (remember: the form is linked from Piazza).

Questions (complete in the provided form):

1. Explain why locks don't compose.
	Does this mean that we should not use locks?
2. File `mmap` and `read`/`write`/`lseek` are not orthogonal.
	They both enable the user to modify file contents.
	`mmap` came after the other file access functions.
	Why do you think adding `mmap` was worth it over concerns of orthogonality?
3. Provide at least one example of code you've seen or written that is a good example of some of these properties (either expressing these properties well, or not well).

References:

- Lecture [video](https://youtu.be/mKJcqvozfA8).
- See Section on "Interface Design Properties" in the book.

## C2: Concurrency on Servers

We're going to learn more about event notification APIs by diving in to `libuv` or the `demikernel` API.
You should choose *one* of these systems to dive into.
The intention is that your group will have people to cover both APIs.
These are both systems that handle concurrency in different ways.
`libuv` is the library underlying `node.js` and exposes a callback model to C code.
It is cross-platform and we can focus mainly on the POSIX/Linux part of it.
The `demikernel` (DK) is a "library operating system" that avoids isolation, and instead provides a programming model much loser to the raw devices.

Questions for `libuv` (complete in the provided form):

1. What APIs are necessary for a client to read from a network socket?
	Tests are likely going to be quite helpful for this.
2. What Linux system calls are used for event multiplexing (which functions are they called from, where in code, etc...)?
	You need to be specific here, thus dive deep into the code.

Question for DK:

1. What APIs does the DK use to issue requests to send or receive data, and get notified when there is an event?
	What APIs does can a client use to "block" awaiting events?
2. DK does not *actually* block (despite having APIs labeled as blocking).
	I define blocking as "being removed from the scheduler runqueue to allow other threads to execute".
	Provide evidence of this in the code.
	Why do you think this is?

References:

- [libuv](https://github.com/libuv/libuv).

	- Starting out by perusing the [tests](https://github.com/libuv/libuv/tree/v1.x/test) will give you a lot of context to dive in.

- Demikernel:

	- [Demikernel -- see Fig 3](https://irenezhang.net/papers/demikernel-hotos19.pdf) abstractions and API.
	- [API](https://github.com/gwu-cs-advos/demikernel/blob/master/API.md) documentation

## L3: Capability Based OS Design I

Today we'll briefly play a mind game: What can we do to nearly minimally abstract hardware resources into a useable set of abstractions with which to build modular systems?
Watch the video, and answer the following questions.
I highly recommend that you read the chapter (in references) in the book.
It includes many definitions and more specific discussions to be more concrete than the recording.
There's also a fun analogy with high-performance jets.

Questions (complete in the provided form):

1. Where does a semantic gap exist between the abstractions provided by the discussed resources and some set of higher-level requirements?
    What would the system have a hard time doing?
2. What are the downsides of this design?

References:

- Lecture [video](https://youtu.be/aWHZaYwWRTM).
- See Section on "Example OS Design: Composite" in the book.

## C3: Composite Runtime

Lets dive into what the code looks like to actually create, modify, and use the kernel resources discussed in the previous video.
We're going to dive into the API for allocating and using those resources.
Your first project will use this API to implement the core of an RTOS, so time that you put into it now will pay off later.

Questions (complete in the provided form):

- Does this API create processes (i.e. components) in a manner closer to `posix_spawn` and `CreateProcessA`, or closer to `fork`?
- Can you summarize tersely why there are so many thread and "receive" APIs (see below what the `rcv` resources are)?
- What API enables the creation of shared memory?

References and hints:

- The [Composite Runtime](https://github.com/gwsystems/composite/tree/loader/src/components/lib/crt) (`crt`) attempts to provide a usable API to program the discussed resources.
	The names aren't always consistent with the video.
	A mapping:

	- *asynchronous activation endpoints* have a `rcv` that threads can suspend upon, and an `asnd` which other threads (and interrupts) can use to activate the thread associated with the `rcv`.
	- *synchronous invocation call-gate* are `sinv` (synchronous invocation) and `sret` (synchronous return).

- For now, I'd ignore the blockpoint, lock, and channel support.
- The system's documentation might be a good place to start (particularly sections 1.3 and 2 in the [dev manual](https://github.com/gwsystems/composite/blob/loader/doc/dev_manual/composite_dev_manual_v2020-07-04.pdf)), but the book for this class (especially the chapter "Example OS Design: Composite") covers the abstractions in a lot more detail.
- The API is best documented in [crt.c](https://github.com/gwsystems/composite/tree/loader/src/components/lib/crt/crt.c), and an example of its use can be seen in the system [constructor](https://github.com/gwsystems/composite/blob/loader/src/components/implementation/no_interface/llbooter/llbooter.c).
- You will *not* be able to understand the `cos_kernel_api` nor `cos_defkernel_api` APIs with the information you have, currently -- the resource table construction and retyping is confusing.
	You'll learn about this in L4.
	For now, view them as a wrapper around the kernel system call API that handle resource table allocation.

## L4: Capability Delegation and Revocation

Diving deeper into microkernel construction, lets address *why* you want to have simple user-level abstractions to compose protection and access hardware.
We need to enable complex systems to be built from various levels of mechanism and policy composed into higher-level abstractions.
This requires programmatically being able to define the subsets of resources that each module should have access to.
Fundamental to this in capability-based systems is the notion of how resources can be made accessible (the capability delegated) to other modules, and how they can later be revoked.

Questions (complete in the provided form):

1. Why is delegation necessary?
2. What are the trade-offs with revocation being recursive (as presented), or simply making revocation only remove the specific delegated capability (not none of the delegations made from there)?

Please focus on spending time providing good questions for this lecture.
I want the feedback to understand where confusions exist.

References:

- Lecture [video](https://youtu.be/krvJS01IrXE).
- See Section on "Capability-based Protection and Delegation and Revocation" and "Component-based Design on Composite" in the book.

## C4: Using the `crt` for System Construction

Read through:

- the [constructor](https://github.com/gwsystems/composite/blob/loader/src/components/implementation/no_interface/llbooter/llbooter.c) (whose job is to create the other system components), and
- the [capability manager](https://github.com/gwsystems/composite/blob/loader/src/components/implementation/capmgr/simple/capmgr.c).

These are the main users of the `crt` library as they manage the capability tables of themselves, and of other components.
There are a lot of rabbit holes to go down here.
Remember, three hours is enough ;-)

Questions (complete in the provided form):

- What's your hypothesis for what the `args_*` API is all about?
	You will **not** be able to have 100% certainty about this.
- Tersely describe (in as high of terms as possible) what the loader is doing, step by step.
- What aspects of the capability manager don't match your mental model (following class discussion) about what you'd expect the capability manager to do?

## L5: User-level Management of Kernel Memory

Finally, we'll address the question, "how do we allocate kernel data-structures, and control the access rights to the system's memory"?
The mechanisms behind this are highly unintuitive, and very clever.
Lets dive into memory retyping and the user-level management of kernel memory.
Questions (complete in the provided form):

1. Summarize the motivations for the discussed design?
	Why not use a more conventional approach?
2. Summarize your understanding of why kernel integrity is ensured using the discussed design.

References:

- Lecture [video](https://www.youtube.com/watch?v=b1ARRd3b8dY).
- See Section on "Memory Management" in the book.

## C5: A Break!

No questions, no code to be read!

## L6: UNIX

Lets dive into how existing systems approach providing abstractions for system resources.
You are all at least familiar with the cosmetic aspects of UNIX, but this week we'll dive into more details.
Read the chapter on UNIX (section 5.1 and all of its subsections) in the book.
Sorry, no video this time!

Questions (complete in the provided form):

- When do you think that pipeline computation on bit-streams is useful?
	When are typed interfaces useful?
- If UNIX has all of the discussed problems, why do you think that it is so ubiquitous?
	If none of these problems have prevented UNIX from being as useful as it has been, what do you think has been their negative impacts?

References:

- Chapter 5.1 on UNIX, and the associated links it provides.

## C6: VFS

The Virtual File System (VFS) layer is essential to enable the uniform access to system resources through a hierarchical file-system namespace.
Today we're simply going to dive into the VFS implementation in various systems.
Lets start out with the most complicated, Linux.
Fair warning: you will *not* understand all of the VFS layer, all of the context in Linux, nor all of the implementation of a simple VFS module!
Lets start with the Linux [VFS documentation](https://www.kernel.org/doc/html/latest/filesystems/vfs.html) and then dive into the VFS being used in the [ramfs](https://elixir.bootlin.com/linux/latest/source/fs/ramfs) (a "in-memory file system", i.e. one that does not actually use the disk at all).
Compare that to the trivial VFS layer in `xv6`.
Note that most xv6 system calls start with `sys_*`, and you can find those entrypoints  [here](https://github.com/gwu-cs-os/gwu-xv6/blob/master/sysfile.c).

Questions (complete in the provided form):

1. In the Linux example `ramfs`, where is the logic for `read` implemented (i.e. the code that executes that is specific to the `ramfs`)?
	Where is the data copied from the `ramfs`'s data-structures to user-level?
2. What is your idea about how control flows through the system to get to that `read` implementation?
3. Where does `xv6` discriminate between pipes and files?

Note that you will *not* be able to perfectly answer question 2.
Please "cut yourself off" when you're at diminishing returns, or you've expended your time allocated to this.

A wild and crazy question that we'll discuss in class:
Imagine that we replace `fork` and `exec` with `open`ing a file!
If we open a binary (e.g. `/bin/ls`), instead of doing the traditional "open" operation, instead it will execute the program as a new process (i.e. instead of `open` $\to$ `exec`).
In that case, perhaps `write`ing to the process' `fd` will feed into its `stdin`, and `read`ing from the `fd` will read from its `stdout`.
Why might this be better than our current implementation?
Why might this be worse than our current implementation?
We'll discuss.

## L7: Beyond UNIX

Please read [section 5.2 of the book on UNIX Counterpoints](https://github.com/gwu-cs-advos/advos_book/blob/main/doc/c04_case_studies.md#unix-counterpoints).
The question we're now approaching is how should we think about modern software development that seems to depart so far from the UNIX philosophy.
As with everything in systems, you'll dive into the *trade-offs* to understand how to think about system design.

Questions (complete in the provided form):

- Is Linux a microkernel now?
	In what ways "yes", in what ways "no"?
- What do you think the main trade-offs are between UNIX-style, user-composition of "do one thing well" modules, and the composition into monolithic application from many libraries and frameworks?

## C7:

Day off!

## L8: Plan 9

Today, we Plan 9!
Please read section 5.3 in the book on Plan 9.

Questions (complete in the provided form):

- What are the downsides of the Plan 9 approach?
	Why might it not be ideal to have everything be a file, and to use 9p as an organizing principle?
- What is unintuitive or interesting about the given examples?

## C8: Plan 9

Lets dive into Plan 9, and its equivalent of the VFS layer: the 9p protocol.
What would it take to write a service in Plan 9?
First, the library for helping services interact with the 9p protocol:

- [9p.h](https://github.com/gwu-cs-advos/plan9/blob/master/sys/include/9p.h), and
- [the library](https://github.com/gwu-cs-advos/plan9/tree/master/sys/src/lib9p)
- including a [ramfs](https://github.com/gwu-cs-advos/plan9/blob/master/sys/src/lib9p/ramfs.c) example

Then, two of the main consumers of the API:

- [exportfs](https://github.com/gwu-cs-advos/plan9/blob/master/sys/src/cmd/exportfs/) (remember, this takes a local namespace and exposes them over a 9p channel, served over the network), and
- [import](https://github.com/gwu-cs-advos/plan9/blob/master/sys/src/cmd/import.c) (remember, this contacts a 9p channel over the network, and exposes its namespace in the local namespace via mount).

Questions (complete in the provided form):

- Assess the ramfs example that uses the 9p library versus the ramfs we saw in Linux.
	How do they compare in terms of simplicity, and why is one simple versus the other?
	Speculate how do they compare in terms of performance (you likely won't understand this from the code).
- Why is `import` code so simple?
	Where are the calls to the `9p` library?
	Where is the logic for maintaining the namespace, and other functionality?
- Exportfs can handle many concurrent client requests at the same time, even though the local namespace has blocking read and write.
	First, identify where the actual read operation (in response to a `TREAD` 9p request) is conducted, and then answer how `exportfs` is written to enable multiple client requests to be handled concurrently even if one of them blocks.

## L9: Microkernel IPC Optimization

IPC is a foundational mechanism for composition of abstract resources provided by other modules.
We've seen it again and again, in pipes, DBus, Plan 9 & 9P, and, of course, in Composite.
Lets dive into how to make it real fast, and the challenges that presents.
Questions (complete in the provided form):

- Think of some cases in which you'd want to use asynchronous IPC between threads, and some cases when you'd want to use synchronous IPC.
	(I know, not really a question; I want see your brainstorming!)
- We talked about a lot of mechanisms, but they all have some downsides.
	Which do you think makes the best set of trade-offs?
	If you need to specify for which *systems* they are *best*, feel free.

References:

- Lecture [video](https://youtu.be/wCoLTnHUwEY).

## C9: Microkernel + VM IPC

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

The [specification](https://github.com/udosteinberg/NOVA/blob/arm/doc/specification.pdf) for Nova provides quite a bit documentation that might be helpful for you.
If you are going to use github's searching interface, you can use the [original repository](https://github.com/udosteinberg/NOVA/).

Questions (complete in the provided form):

- Nova has one of the fastest IPC implementations.
	Give me a summary of the flow of control through the system for a pair of `call` (from the client), and `reply` (to "reply & wait" from the server).
	What do you think makes this implementation so efficient?
- Summarize the implementation of capability delegation and revocation (they have slightly different names in Nova).
	Hint: delegation is performed as *part of synchronous IPC*.

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

## L10: Security Foundations

We now pivot into security!
Lets start with how to think about security: read section 6.2 of the book.

Questions (complete in the provided form):

- Using the definitions and principals in the book, compare and contrast the security of VMs, processes, and containers in Linux.
	Be terse.
	We'll discuss this in groups.
- In which ways do you think that Linux adheres to the principles for system design?
- How tamperproof do you think Linux is?

References:

- See Section 6.2 in the book.

## C10: Defense in Depth

Do some research into OpenBSD.
BSD is similar to Linux in that it is an implementation of POSIX plus a surrounding ecosystem.
There are many BSD variants similar (but not identical to) how there are many Linux distributions (Ubuntu, Gentoo, Arch).
OpenBSD is a BSD variant that focuses on security.
It still has a large monolithic kernel, but they attempt to make the system as secure as possible by simplifying the system, and adding defense in depth.
For the questions today, you don't need to reference code, and can likely find many answers and mailing lists, webpages, and papers.

Today you'll simply provide three examples of technical techniques in which OpenBSD designs the system explicitly for security.
Write your responses in a way that demonstrates that you have some understanding of the technique, rather than simply cut and pasted it.
Use your own words.
I expect that finding a number of techniques won't take more than 5 minutes, but understanding them will take longer.

Questions (complete in the provided form):

- Example 1
- Example 2
- Example 3

References:

- OpenBSD [webpage](https://www.openbsd.org/).
	This is one potential starting point for your investigation.

## L11: No questions

N/A

## C11: No questions (see L12)

N/A

## L12: Nova VMX Interface

Lets dive deeper into NOVA!
Today we're going to understand what it takes for an OS to interface with the [hardware virtualization acceleration](https://en.wikipedia.org/wiki/X86_virtualization), in this case Intel's Virtual Machine Extensions (VMX or, sometimes, VT-x).

Specifically, we want to understand the security properties of hypervisors (the kernel), VMMs (virtual machine monitors) that provide virtualization of I/O devices, and other hardware that VMX doesn't emulate.
Nova's initial claim to fame was that the VMM could be implemented in user-level (remember: microkernel!), thus leaving only the interface to VMX in the kernel.

VMX virtualizes quite a significant set of hardware features.
These include

- page-tables (thus the virtual, guest kernel can directly access page-table support within the "physical memory" provided to it by the hypervisor) through Extended Page-Tables (EPT),
- dual-mode protection (thus system calls, exceptions, and many sensitive instructions can occur in the VM without interacting with -- i.e. trapping to -- the hypervisor), and
- even interrupts can sometimes be vectored directly to the VM.

This is fine, but sounds quite like magic.
What does this hardware actually look like, and how does an OS interface with it?
At its core, VMX defines a Virtual Machine Control Block (VMCB) which is simple a chunk of memory that holds the virtual hardware state of the VM, and a set of instructions to using it.
For example: `VMPTRLD` and `VMPTRST`setup the VMCB, `VMREAD` and `VMWRITE` manipulate the page, `VMLAUNCH`, and `VMRESUME` execute the VM in various ways (see [Vol. 1, section 5.22](https://software.intel.com/content/www/us/en/develop/download/intel-64-and-ia-32-architectures-sdm-combined-volumes-1-2a-2b-2c-2d-3a-3b-3c-3d-and-4.html)).
Find the documentation for how software can interact with the VMCB in [Vol. 3C, section 24.11](https://software.intel.com/content/www/us/en/develop/download/intel-64-and-ia-32-architectures-sdm-combined-volumes-1-2a-2b-2c-2d-3a-3b-3c-3d-and-4.html).
When the VM executes and executes an instruction that VMX doesn't know how to virtualize, it can cause a `vmexit` which is an exception that triggers the hypervisor (which should handle the operation).

The references below contain most of the code you need to know about.
Recall our previous discussion of the NOVA source code.

Questions (complete in the provided form):

- Please piece together the sequence of code that gets executed from a `vmexit` (that triggers a `handle_vmx`, and often `vmx_exception`) which triggers IPC to a server thread, and then eventually returns to continue execution in the VM.

References:

- See the [nova](https://github.com/gwu-cs-advos/NOVA/) source code (see the source repo if you want to use github's searchable interface)
- VMX code includes:

	- [vmcb](https://github.com/gwu-cs-advos/NOVA/blob/arm/inc/x86_64/vmx.hpp#L26),
	- some [operations](https://github.com/gwu-cs-advos/NOVA/blob/arm/inc/x86_64/vmx.hpp#L398-L423) on the vmcb,
	- and its [initialization](https://github.com/gwu-cs-advos/NOVA/blob/arm/src/x86_64/vmx.cpp#L48-L142),
	- integration of the control flow of VMs (e.g. `vmexit` turns into IPC) into the [execution contexts](https://github.com/gwu-cs-advos/NOVA/blob/arm/src/x86_64/ec_vmx.cpp) of NOVA,
	- and [starting and resuming](https://github.com/gwu-cs-advos/NOVA/blob/arm/src/x86_64/ec.cpp#L178-L232) VMs.

- Don't forget that [`send_msg`](https://github.com/gwu-cs-advos/NOVA/blob/arm/src/x86_64/syscall.cpp#L81-L109) is very general and uses template magic to contain the continuation to use for execution when you *return to the calling ec (thread)*.
- Also remember that the "arguments" and return values are passed from the client into the server's `utcb` (user-level thread control block).

## C13: `memcached`

One of the most common pieces of cloud infrastructure is distributed caches.
When accessing some object (a post on social media, a user profile, a product, etc...), it can be *very* expensive to go out to the database.
Instead, cloud systems will *cache* these values in dedicated machines.
Thus, only when the caches don't hold an item, do you need to go out to the database.
One of the most common distributed caches is [`memcached`](https://github.com/memcached/memcached).
`memcached` is, at its core, just

1. a hash table mapping keys to values for fast access, and
2. a "least-recently used" caching policy that will drop items that were accessed furthest into the past when the cache runs out of room.

To enable the maximum number if items to be stored, `memcached` also provides its own [slab allocator](https://www.youtube.com/watch?v=DRAHRJEAEso).
`memcached` is multithreaded and can be used across many cores.
Thus, it attempts to provide a scalable implementation.

Questions (complete in the provided form):

- In a common operation on the hashtable (get or put), how are locks used?
    How does the system attempt to use locks in a way that is scalable?
    You can avoid looking into the use of locks for things like maintanance, hash-table resizing, etc...

References:

- Most relevant code is in thread.c, items.c, and assoc.c

# Project

The purpose of the project is to dive into a core system technology and answer a set of questions:

- Summarize the project, what it is, what its goals are, and why it exists.
- What is the target *domain* of the system?
	Where is it valuable, and where is it not a good fit?
	These are all implemented in an engineering domain, thus are the product of trade-offs.
	No system solves all problems (despite the claims of marketing material).
- What are the "modules" of the system (see early lectures), and how do they relate?
	Where are isolation boundaries present?
	How do the modules communicate with each other?
	What performance implications does this structure have?
- What are the core abstractions that the system aims to provide.
	How and why do they depart from other systems?
- In what conditions is the performance of the system "good" and in which is it "bad"?
	How does its performance compare to a Linux baseline (this discussion can be quantitative or qualitative)?
- What are the core technologies involved, and how are they composed?
- What are the security properties of the system?
	How does it adhere to the principles for secure system design?
	What is the reference monitor in the system, and how does it provide complete mediation, tamperproof-ness, and how does it argue trustworthiness?
- What optimizations exist in the system?
	What are the "key operations" that the system treats as a fast-path that deserve optimization?
	How does it go about optimizing them?
- Subjective: What do you like, and what don't you like about the system?
	What could be done better were you to re-design it?

It is your responsibility to approach "marketing" claims of each project with extreme skepticism, and to *substantiate your claims about each system with 3rd party (or scientific) evaluations, and with references to the code*.

## Timeline

| date | item                                                                                               |
| ---  | ---                                                                                                |
| 3.25 | Group Members Determined (~4): github classroom team repo created                                  |
| 3.30 | Due 10am: `proposed_topic.md` file proposing project topic (or just listing title from below)      |
| 4.01 | Project "OK", or office hours discussion with Gabe                                                 |
| 4.06 | `hypothesis.md` containing you hypothesis gleaned from documentation, `research.md` progress       |
| 4.15 | `research.md` fleshed out with references to code, experiments, and papers.  <br>  Please annotate each part of `research.md` with *who* did that portion of research. <br> This includes a list of hypothesis that have been confirmed or refuted, with details.    |
| 4.20 | `report.md` with a thorough analysis of the system, motivated by the questions above. <br> This should include references to code, papers, and experiments throughout to validate statements. <br> At the end, include a summary of who did what. Everyone *must* agree with what is written here. <br> Contact Gabe if there are any conflicts.              |
| 4.22 | Final presentations, including presentation files in `presentation/`                               |

Your repository for this project will contain at least the following at the time of completion:

- `README.md` to simply summarize the structure of the repo.
	If you don't depart from this prescribed structure, it can simply be a list similar to above.
- `research.md` which includes a dump of all of the research you've done.
	You might also have a `research/` directory if you need to store materials or additional information.
- `hypothesis.md` which includes your initial hypothesis about the project from the documentation and a cursory overview of the project.
	For many people, the material in this would be close to a final "project report" (though normally in a more refined format), but in this project, you'll go steps further to confirm/refute your hypothesis, and dive into the details.
- `proposed_topic.md` the initial project proposal.
- `report.md` the final report
- `resources/` which can contain any additional resources you'd like.
	For example, to include images in your final report, you might store them here.
	Remember that you can use `pandoc` to generate a nice pdf if you'd like.
	In that case, feel free to also include a `Makefile` to guide compilation.
- `presentation/` which includes relevant files for the presentation.

**Grading.**
Grades will be assigned based on:

1. Accuracy of investigation (statements substantiated with references).
2. Depth of investigation (strong statements about the system).
	The final report should be around 10 pages (or more).
3. Polish on the final report and presentation.

I'm sorry this is subjective,
Everyone starts off at an "A", and decreases from there where any of the above are lacking.
All team member's grades are coupled, unless the stated work distribution (in `research.md` shows imbalances).

## Example Systems

You can propose any system you'd like to dive into.
Here are a few examples.

### Firecracker VM

Firecracker is the core of the serverless (function) platforms in Amazon's EC2.
It is a "virtualization minimized" infrastructure that uses Linux's KVM support for hardware accelerated virtualization.
It also takes an unconventional approach: only support the bare minimum of hardware in the hypervisor necessary for cloud-based execution.
This pairs down the KVM hypervisor a huge amount (compared to, for example, `qemu`).
Note that firecracker is written in Rust, so it will be hard to dive into if you aren't willing to explore that language.

- [homepage](https://firecracker-microvm.github.io/)
- [paper](https://www.usenix.org/conference/nsdi20/presentation/agache)
- [github](https://github.com/firecracker-microvm/firecracker)

### Xen

The workhorse of Amazon EC2 for over ten years, Xen provides virtualization based around having a highly privileged VM (Dom0) to do most system administration.
As such its performance and security must consider not just a VM and the hypervisor, but also Dom0.
Its interesting structure makes a number of trade-offs, and an analysis of Xen will need to consider why Amazon (its largest user) has been moving away from it, onto Linux KVM-based systems.

- [homepage](https://xenproject.org/)
- [github](https://github.com/xen-project/xen)
- There are countless papers on Xen.

### gVisor

gVisor is used as the foundation for serving Google Cloud Functions.
gVisor makes the observation that containers are not designed to protect the kernel from applications, thus a bug in the kernel might be used to compromise the entire system.
Instead, gVisor intercepts all system requests from applications, and implements a user-level kernel-like thing.
In some sense, gVisor conceptually lies between containers and virtualization, and is implemented in a manner that is completely different from both.
A lot of gVisor is written in go, but go is relatively easy to read/understand, so I don't see this inhibiting a group from diving in.

- [homepage](https://gvisor.dev/)
- [github](https://github.com/google/gvisor)
- A paper doing an [analysis of performance](https://www.usenix.org/conference/hotcloud19/presentation/young).

### Node Isolates and `isolated-vm`

Node is the server-side javascript VM.
Server-side javascript has proven quite useful as a development team can avoid needing to consider and use multiple languages, and they can leverage the same, large, collection of libraries.
However, once you're running on the server, you might increasingly be concerned about isolating different scripts running for different clients.
Node supports isolates and infrastructure built on top of them to provide *some degree* of isolation.
These are provided as part of the *language runtime*, and not as part of the OS.
If you want to dive into the massive complexity of such a runtime, this is a great way to do it!

- [API documentation](https://v8docs.nodesource.com/node-0.8/d5/dda/classv8_1_1_isolate.html)
- [npm documentation](https://www.npmjs.com/package/isolated-vm)
- [github](https://github.com/laverdet/isolated-vm)
- There are multiple papers that assess performance.

### OSv Unikernel

Unikernels are "library OSes" (in the vain of [exokernel](https://dl.acm.org/doi/10.1145/224056.224076) OSes) in which the OS is a library loaded with the application.
Demikernel is one example of such a system.
OSv is a full replacement for Linux as a unikernel!
Unikernels are an interesting take on using virtualization as the core isolation facility in the system, and remove isolation (thus its performance impact) within the VM.
OSv is supported on multiple of the virtualization infrastructures above.

- [github](https://github.com/cloudius-systems/osv)
- [paper](https://www.usenix.org/conference/atc14/technical-sessions/presentation/kivity)
- [solo5](https://github.com/Solo5/solo5) is another unikernel, but it is more of a unikernel framework, which makes it much harder to approach and understand.

# Thoughts on Potential Projects

**Ignore this section in 2021.**

IoT systems are increasingly popular.
Many of them forego security and isolation for simplicity.
Lets build a secure RTOS to control the physical world in a trustworthy manner!

The *final* product will have the following features:

- Multithreaded with communication and synchronization mechanisms between threads including

	- thread creation and prioritization
	- `go`-like channels
	- locks for critical sections

- An isolation-providing process-based abstraction for applications

- A nameserver that enables processes to

As we're implementing about an RTOS, we should keep it as simple as possible, avoid generalizations, and avoid dynamic memory allocation.

## RTOS

Lets start by creating the core services for a RTOS in a *single protection domain* (i.e. in a single component).
These services include:

1. threads,
2. preemptive, priority-based scheduling,
3. timers so that threads can block for periods of time,
4. blocking locks (not spinlocks), and
5. channels to pass data from a producer to a consumer.

## RTOS + Application Isolation

Application threads should be in a separate protection domain than the core RTOS.
They will use synchronous invocations to communicate with and make requests from the RTOS component.
We'll make a simplifying assumption that only a single application thread executes in the application's component (i.e. that they are single-threaded).
To communicate with the RTOS component, this requires that we set up shared memory between the application and the RTOS to pass arguments, and get return values.

## Extensibility

Lastly, we're going to enable applications to register themselves as the providers of specific services in a namespace.
Implement a simple hierarchical namespace that applications can register themselves in, and other applications can "open" to communicate via channels with the service.
This will enable the system to be extended with functionality and services as applications "hook themselves in" to the shared namespace.
