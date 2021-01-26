# Lectures and Questions

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

1. Where does a semantic gap exist in the discussed resources? 
    What would the system have a hard time doing?
2. What are the downsides of this design? 

References:

- Lecture [video](https://youtu.be/aWHZaYwWRTM).
- See Section on "Example OS Design: Composite" in the book.

## C3:

Questions (complete in the provided form):

- TBD

References:

- [TBD](TBD).
	Starting point help: TBD.

## L4:

Questions (complete in the provided form):

- TBD

References:

- Lecture [video](TBD).
- See Section on "" in the book.

## C4:

Questions (complete in the provided form):

- TBD

References:

- [TBD](TBD).
	Starting point help: TBD.

## L5:

Questions (complete in the provided form):

- TBD

References:

- Lecture [video](TBD).
- See Section on "" in the book.

## C5:

Questions (complete in the provided form):

- TBD

References:

- [TBD](TBD).
	Starting point help: TBD.

## L6:

Questions (complete in the provided form):

- TBD

References:

- Lecture [video](TBD).
- See Section on "" in the book.

## C6:

Questions (complete in the provided form):

- TBD

References:

- [TBD](TBD).
	Starting point help: TBD.

## L7:

Questions (complete in the provided form):

- Lecture [video](TBD).
- TBD

References:

- See Section on "" in the book.

## C7:

Questions (complete in the provided form):

- TBD

References:

- [TBD](TBD).
	Starting point help: TBD.

## L8:

Questions (complete in the provided form):

- TBD

References:

- Lecture [video](TBD).
- See Section on "" in the book.

## C8:

Questions (complete in the provided form):

- TBD

References:

- [TBD](TBD).
	Starting point help: TBD.

## L9:

Questions (complete in the provided form):

- TBD

References:

- Lecture [video](TBD).
- See Section on "" in the book.

## C9:

Questions (complete in the provided form):

- TBD

References:

- [TBD](TBD).
	Starting point help: TBD.

## L10:

Questions (complete in the provided form):

- TBD

References:

- Lecture [video](TBD).
- See Section on "" in the book.

## C10:

Questions (complete in the provided form):

- TBD

References:

- [TBD](TBD).
	Starting point help: TBD.

## L11:

Questions (complete in the provided form):

- TBD

References:

- Lecture [video](TBD).
- See Section on "" in the book.

## C11:

Questions (complete in the provided form):

- TBD

References:

- [TBD](TBD).
	Starting point help: TBD.

## L12:

Questions (complete in the provided form):

- TBD

References:

- Lecture [video](TBD).
- See Section on "" in the book.

## C12:

Questions (complete in the provided form):

- TBD

References:

- [TBD](TBD).
	Starting point help: TBD.

## L13:

Questions (complete in the provided form):

- TBD

References:

- Lecture [video](TBD).
- See Section on "" in the book.
