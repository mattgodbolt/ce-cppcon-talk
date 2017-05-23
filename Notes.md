Titles:
* 5 years of Compiler Explorer
* 14 million compilations
* Why you should love asm
* Compilation for the masses
* Compiler Explorer - what it is and why you should care
* Democratising asm
* Don't be afraid of assembly
* Compiler Explorer - assembly for the masses

In 2012, Matt was arguing with a colleague about whether it was more efficient to
pre-increment or post-increment iterators. Comparing the machine code of both approaches
showed they were equivalent (most of the time), but the difficulty in generating the disassemblies
inspired Matt to create a little website that did the work for him.

Five years on and Compiler Explorer is now a public site relied on by many to quickly see
the code their compiler emits, or to compare different compilers' output, error messages and warnings.

In this talk, Matt will explain how he uses Compiler Explorer in his day to day work programming
low-latency trading systems, and show some real-world examples. He'll demonstrate some of Compiler Explorer's
lesser-known features and show how clever compilers can be. Perhaps more importantly he'll convince you why you should be
using it too, even if you don't know assembly or don't worry about counting CPU cycles.

Matt will also touch on how it works behind the scenes, share some stories
of things that have gone wrong over the years, and describe how it has scaled from a shell script
running in a terminal to a reliable, scalable website.

Matt Godbolt is a software engineer with trading firm DRW. He is passionate about
efficient code, and has previously worked for Google, ran his own C++ tools company, and spent
ten years in the video game industry.

---- gives too much away?
Five years later and the site -- Compiler Explorer -- now serves many in the
C++ community on a daily basis, helping others answer similar questions, or just
compare how different compilers optimize their code.


In XX, Matt created a handy little tool for himself and his colleagues to show
how the C++ code he was mgaciilyy turned into assembly by his colleagues (to end a debate)
X years on it's now a public site relied on by many to quickly see how their code
turns into asm, or how compilers differ on code generation, error messages or warnings.

In this talk, Matt will explain why CE was created, how he uses it and - perhaps more importantly - 
why you should be using it or something like it in your day-to-day programming. 
He'll explain how it works behind the
scenes and tell some stories of how others use it and how it has scaled beyond a little open source
hack to an ecostystem of thingies....

-- why = reason!
-- even i fyou don't know asm or odnt care about perf

Compiler Explorer
-----------------

Hi, welcome. I'm me and I've been coding in C++ for 20 years. Low level assembly programmer at heart.
Begrudgingly moved to C and then C++ as programs got more complex and realised compilers are smarter
than me. But still can't let go of the low level part.

My problem / why?
 - Jordan and me? bash?
 - staring at disassembly
 - is compiler smart enough for XX?

Who here has used Compiler Explorer?

Explain it, short demo. Need a good example!
<<<< Compiler Explorer presentation mode?


C++ fancy new range fors? Faster or not?

People use it for XXX?
- understanding what actually compiles to?
  - e.g. boost::multi index thing with Nick that time
  - auto foo = bar(); // unintentional copy
  - RVO?
  - what can be compiled away to nothing (examples?)
- teaching!
  - number of classes use it (XXX lookup)
  - Jason Turner
- comparing code generation between compilers
- reporting compiler bugs
- C++ "REPL"

How it works behind the scenes?
Deploying and compiling all the compilers

War stories
- S3 downtime
- hacking attempts

NB NEEDS A STORY and teaching point(s). 
Need passion...hopefully groovy on that front

we are hiring!

~~

Notes!

FACTS
* Started in 2012
* Go, D, Rust also
* XXX compiles/month

--- Torrens

1. Start off by letting them know what’s going to happen (10 seconds max, though).
2. Let them know where they are a couple of times as you progress.
3. ‘Signpost’ the end.

A good story (see ‘Presentation Fails #6’) and objective (‘Presentation Fails #4’) do most of this work for you; here’s a structure you can use:

1. Initial situation
2. Disaster
3. Bold, new action
4. Solution

That may not seem to apply to your material. If you’re really stuck, you could use something as simple as this:

1. Where we were
2. What we did
3. Where we are now

Or this:

1. Here’s an amazing thing we should do
2. Here’s how we’ll do it
3. Call-to-action re: what you need to do now to achieve the amazing thing

Or even:

1. Superb idea
2. Why it’s superb
3. Summing up of points 1 and 2

You can see how those combine e.g. Where we were/Initial situation, or How/Why, or Solution/Call-to-action.


