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

# Coding

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

## Code & Lecture Questions

You'll be reading a lot of code, and watching lectures throughout the class.
Each student starts the class with a code and lecture questions grade of between A-: 3.7.
The grade scale for each questionaire is:

|        | not sufficient | sufficient | significant insight |
|--------|----------------|------------|---------------------|
| points | `-1`           | `0`        | `1`                 |

See the spreadsheet for your grade.
I must *completely subjectively* provide this assignment.
My goal is to discuss the material in class so that you understand what's expected.

Your final grade in this category is calcuated as $$3.7 + \sum_{week_i} (0.1 \times g_i)$$.
That is to say, each -1 decreases your grade by 0.1 points, and each 1 increases it by 0.1.

*Transparency.*
The goal of this grading scale is to make it obvious what your grade is at any point.

## Class Participation

You have an A in participation to start the class.
I'll use peer evaluation via forms to assess participation and involvement for in-class group discussions.
Each student will give scores to each other in discussion of system code.
The final impact of any student's scores on another will be a normalized modifier based on the average score over all ratings (of other students).
So deviations from the average score are what modify people's grades.

If you fill out a form for someone outside of your group, each time you'll lose 10% of your participation grade.

I'll track participation during the class, and that will increase your grade.

*Transparency.*
I'll give you warnings if your scores are consistently low.

## Homework & Project

These will be graded by Demo.
Again, A- is the baseline for completing the assigned task.
Your grade is modified up to A if you do a great job, and show significant thought in your implementation.
It is modified downwards if you

1. don't provide sufficient testing,
2. don't consider necessary cases, or
3. don't provide necessary functionality.

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
