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

| Date  | Class topic                  | Due                                                                                                    |
|-------|------------------------------|--------------------------------------------------------------------------------------------------------|
| T1.14 | organization, reading code   |                                                                                                        |
| R1.16 | complexity                   |                                                                                                        |
| T1.21 | xv6 + busybox                | [xv6](https://github.com/gwu-cs-advos/organization/blob/main/class.md#2-xv6)                           |
| R1.23 | abstraction                  |                                                                                                        |
| T1.28 | plan9 + busybox + systemd    | [busybox](https://github.com/gwu-cs-advos/organization/blob/main/class.md#3-busybox)                   |
| R1.30 | organizing components        |                                                                                                        |
| T2.04 | plan9 + go                   | [plan9](https://github.com/gwu-cs-advos/organization/blob/main/class.md#4-plan9)                       |
| R2.06 | organizing components        |                                                                                                        |
| T2.11 | go + libuv + node            | [go](https://github.com/gwu-cs-advos/organization/blob/main/class.md#5-go)                             |
| R2.13 | isolation                    |                                                                                                        |
| T2.18 | libuv + demikernel           | [libuv](https://github.com/gwu-cs-advos/organization/blob/main/class.md#6-libuv)                       |
| R2.20 | isolation                    |                                                                                                        |
| T2.25 | composite design             | [demikernel](https://github.com/gwu-cs-advos/organization/blob/main/class.md#7-demikernel)             |
| R2.27 | isolation                    |                                                                                                        |
| T3.04 | composite runtime            | [composite kernel](https://github.com/gwu-cs-advos/organization/blob/main/class.md#8-composite-kernel) |
| R3.06 | interface design             | [UNIX Service](https://github.com/gwu-cs-advos/organization/blob/main/class.md#1-unix-service)         |
| T3.11 | Spring recess                |                                                                                                        |
| R3.13 | Spring recess                |                                                                                                        |
| T3.18 | composite scheduling         | [composite crt](https://github.com/gwu-cs-advos/organization/blob/main/class.md#9-composite-crt)       |
| R3.20 | specialization               |                                                                                                        |
| T3.25 | unikraft                     | [composite slm](https://github.com/gwu-cs-advos/organization/blob/main/class.md#10-composite-slm)      |
| R3.27 | interface & component design |                                                                                                        |
| T4.01 | nova                         | [unikraft](https://github.com/gwu-cs-advos/organization/blob/main/class.md#11-unikraft)                |
| R4.03 | interface & component design |                                                                                                        |
| T4.08 | komodo                       | [nova](https://github.com/gwu-cs-advos/organization/blob/main/class.md#12-nova)                        |
| R4.10 | interface & component design |                                                                                                        |
| T4.15 | komodo + nickel              | [komodo](https://github.com/gwu-cs-advos/organization/blob/main/class.md#13-komodo)                    |
| R4.17 | security                     |                                                                                                        |
| T4.22 | nickel                       | [nickel](https://github.com/gwu-cs-advos/organization/blob/main/class.md#14-nickel)                    |
| R4.24 |                              |                                                                                                        |

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
- Channel send](https://github.com/gwu-cs-advos/go/blob/master/src/runtime/chan.go#L176)
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
	What APIs does can a client use to "block" awaiting events?
2. DK does not *actually* block (despite having APIs labeled as blocking).
	I define blocking as "being removed from the scheduler runqueue to allow other threads to execute".
	Provide evidence of this in the code.
	Why do you think this is?

For discussion in class:
- In what ways are demikernel's design very specialized to its goals?
- What problem domains do you think are a good fit for the demikernel?

## 8: composite kernel
## 9: composite crt
## 10: composite slm
## 11: unikraft
## 12: nova
## 13: komodo
## 14: nickel

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
