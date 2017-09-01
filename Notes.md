# v2 Outline
1.  Intro: Who am I? Backstory
2.  Asm 101 (5m version)
3.  Microwalkthrough 
4.  Comparison (shows before/after/diff) ... leading in to "once I built this tool..."
5.  Muls
6.  Div/Mod
7.  Hash maps?
8.  sigma / popcount?
9.  How it works 1
10. opt view/ast view
11. How it works 2
12. Local demo
13. Outro


## Notes from first runthrough
* Made it to about halfway in 75 minutes - needs shortening...
* Jeff Sacks
  * Consider an outline at beginning so we know where we're going
  * ASM section should be a little shorter, was dropping off towards end
  * Explain "Haswell"
* Constantin:
  * Never said which of the two was better
  * Didn't present any measurements; practice what you preach
* Foemmel:
  * Maybe make a story and tell it through optimisations?
  * Hash table? Div->Mod->Hash
  * Benchmarks of accumulate
  * Long multiplication was clear enough without long walkthrough
* General:
  * ASM section was great
  * Add a UI tour
  * Put # of assembly lines in UI, show diffs
  * "Regression in compiler" (can't recall what this meant)
  * Hard to retain mental state between slides
  * Better highlighting of code
  * Limit to 2-3 examples

maybe segue into hash example at "compilers are super smart"?
could build own hash map? shows most of the opts. but has to be super leading?
* shows "class" no code generated
* Could use dynamic sized?
* Then array<Order *, ...> with fixed size?
* boost multi? clang?

```
// setup
  #include <array>
  #include <vector>
  #include <unordered_map>
  #include <cstdint>
  using namespace std;
  struct Order {
    Order *next;
    uint64_t id;
  };
using OrderId = uint64_t;
struct  OrderMap {
  static constexpr auto NumBuckets = 1023;
  array<Order*, NumBuckets> bucket;
  Order *find(OrderId key);
};

Order *OrderMap::find(OrderId key) {
  auto hash = std::hash<OrderId>()(key);
  auto bucketIndex = hash % bucket.size();
  for (auto ptr = bucket[bucketIndex]; ptr; ptr = ptr->next)
    if (ptr->id == key) return ptr;
  return nullptr;
}

```

---------------

# v1 Outline

* Why
  * Goals
* Backstory
* ASM 101
  * Registers
  * Calling convention
  * Instructions
  * Memory instructions
* Back to backstory
  * v1!
* And now
  * Demo  
  * Code walkthrough
  * Optimizer off
  * Show the other approaches
* Compilers are super smart!
  * Multiplication
  * Divi / Hash
  * numBitsSet
* Compilers not clairvoyant
  * external functions
  * virtual functions
    * devirt, static, non-static TODO
  * __restrict max
  * optimized sum TODO
  * guessing likelihood (foo(int a, int b, int c...)) clang vs gcc TODO
* UB can be your friend? shout to Chandler
  * Inf loops in clang
  * index signed vs unsigned? TODO see below
  * heap elision? TODO
* Using CE
  * Defeating optimizer TODO
  * Templates TODO
  * Power use demo?
* Case study - how I use it?
* Uses of CE TODO
* How it works
  * node
  * EC2
  * the compilers
  * security
  * frontend
  * TODO stats on usage, errors etc
  * running it locally
* Conclusions

NOTES
* Add summary slides after each section?
* counting bits seems out of place 
a = (x**2)/2 + x / 2
a - x = (x**2)/2 - x/2  

## TO BE PLACED
* non-virtual thunks (scrap?)
* variant?
* vectorization?
* stats
* asan
* pass by reference
  * LICM? (Assuming size() is this) TODO
  * CSE? TODO  
  * TODO Constants TODO?
* Timings for "add order" / "remove order" / ""


```
unsigned clz(unsigned a) {
  unsigned mask = 0x80000000;
  unsigned count = 0;
  while (mask) {
    if (a & mask) count++;
    mask>>=1;
  }
  return count;
}
```

----

Titles:
* 5 years of Compiler Explorer
* 14 million compilations
* Why you should love asm
* Compilation for the masses
* Compiler Explorer - what it is and why you should care
* Democratising asm
* Don't be afraid of assembly
* Compiler Explorer - assembly for the masses
jj
* Charting your code/compiler with Compiler Explorer
* Code prospecting? (with Compiler Explorer?)
* Demystifying your [compiler/code] with Compiler Explorer
* A Bolt from beyond; Compiler Explorer
* Holy Lightning strikes (batman), it's CE
* Don't fear the compiler. Explore it
* Assembly spelunking your C++ with CE
* Compiler Explorer, or how I learned to stop worrying and love assembly
* Unbolting the lid of your compiler with CE
* "What has my compiler done for me lately?"
* Compilational sympathy?
* Assembly! Wait, come back!
* Compiler Explorer: The Right To Assembly
* CE - Assembly is a right not a privilege
* Unbolting the secrets of the compiler

Foemmel likes 16, 18 (cliched), 8. His ideas 22-24

via medium of Bowie songs?
"Keynotes should be inspiring and memorable" <- @lefticus

[12:07 PM, 7/7/2017] Kimberly Godbolt: Everyone loves a 'how to'                        
[12:07 PM, 7/7/2017] Kimberly Godbolt: Discover? Uncover your code?                        
[12:08 PM, 7/7/2017] Kimberly Godbolt: Making your code work harder                        
[12:08 PM, 7/7/2017] Kimberly Godbolt: Or something?                        
[12:08 PM, 7/7/2017] Kimberly Godbolt: Secrets of your code with Compiler Explorer                        
[12:08 PM, 7/7/2017] Kimberly Godbolt: Oooh I'm intrigued                        
[12:09 PM, 7/7/2017] Kimberly Godbolt: Can you tell I'm in telly?                        
[12:09 PM, 7/7/2017] Kimberly Godbolt: Unlocking the secrets                        
[12:09 PM, 7/7/2017] Kimberly Godbolt: Haha totally wrong                        
[12:09 PM, 7/7/2017] Kimberly Godbolt: Understanding but that's how brainstorm work right?


---------------
in this talk Matt will not only show you how easy (and fun!) it is to understand the assembly code
geenrated by your compiler, but also how important it can be. 

0000000000000

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
-- even if you don't know asm or don't care about perf

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
- EFS fun
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


### More notes

Infinite loop detection. Linked list walk clang vs GCC

Fold operator repl style thing

Move construction vs copy

Shout to Chandler and Michael Spencer talks on UB

Shout to John Regehr 

Follow-alomg mode (URL to keep updating the layout, websockets?)

Pre vs post increment
Algorithm for each vs non

Trivia:
-- people running a "most output from a tweet" competition

Simon Brand [7:22 AM] 
@mattgodbolt I'd be interested in the roadmap, understanding how to get the most useful output (making things volatile 
and such), how the different compiler versions are maintained, and how I could leverage it for other cool projects (maybe 
a collaborative compiler for interviews or something).

what do you use it for?
Simon Brand [7:19 AM] 
@mattgodbolt I use it for demonstrating compiler optimisations.

Arne Mertz [7:22 AM] 
@mattgodbolt what I use it for:
1) to play around with C++17 features out of curiosity (I don't have a bleeding edge compiler locally)
2) to show colleagues that the tips I give them compile and don't create worse assembly
3) to discuss stuff here on Slack
tbh, my point 1) has become less valid in the past weeks since someone pointed me to Wandbox, because I can execute code there.
@mattgodbolt I forgot one point: since this week, I use CE to produce minimal examples for compiler bugs/ICEs and narrow
down which version they were introduced. The turnaround times are just great for things like that.

Miro Knejp [7:22 AM] 
is "to prove people wrong" a valid reason? :smile:
I also use it to check on new features or edge cases of the language that I'm less familiar with, and to see how 
different compilers handle the same code, e.g. that clang discovered my loop was a summation and replaced it with the 
closed form was quite entertaining to me. these are things you usually don't discover at work

Björn Fahller [7:37 AM] 
I use it mostly to show my colleagues how different code constructs works - most specifically to show that abstractions 
typically are very cheap.
I also use it for experimental TMP stuff, where it's easier to check with a `static_assert` in CE with different compilers 
than to do the same with many compilers installed locally. (edited)

Peter Bindels [7:38 AM] 
I use it to show colleagues what's new in C++11/14/17 and why it's awesome
I also use it to see what things work on MSVC, without needing a Windows box. (+2 thumbs ups)

Nir Friedman [12:36 PM] 
Sorry if this is cheesy, but wanted to thank you personally for Compiler Explorer
It's an awesome tool that has definitely improved my QoL as a C++ dev, and I've undoubtedly learned things because it was so easy to use

that otherwise I would have just shrugged off and never investigated

so, thanks! And the big update to it some number of months ago with the tabs for the compiler output, also very useful.


Links to cool code optimisation 
https://godbolt.org/g/tuO5Ij - devirtualisation

------

symbol interposition

tips for defeating the optimizer in the right way


---------------

Code examples (watch https://www.youtube.com/watch?v=-o-Wjy_ISvs&t=5s&index=20&list=WL)

* range-for vs old-for
* boost::multi_index thing
* auto foo = bar(); // unintentional copy
* Find a RVO thing?
* Over-optimized thing (compiles to nothing?)
* Infinite loop detection. Linked list walk clang vs GCC
* Fold operator repl style thing
* Move construction vs copy
* Pre vs post increment
* Algorithm for each vs non? https://godbolt.org/g/gS9NOV makes nice s-x-s example? (also NB code gen wildly diff at O3 between the two compared to O2)
* adc? https://godbolt.org/g/6WBYZP where intel is smart? https://godbolt.org/g/7yrhn5 is nearest GCC will do


#Compiler Explorer
infinite loop detection. Linked list walk clang vs GCC

Fold operator repl style thing

Move construction vs copy

Shout to Chamdler and Michael Spencer talks on UB

Shout to John Regehr 

Vinnie Falco: https://godbolt.org/g/YyRg4z beast

used it the other day to "explore" c++17 string_view (specifrically to_string)

JT's twitter puzzle (https://twitter.com/lefticus/status/870731364160512000); used attribute noinline https://godbolt.org/g/lvo9wz to find [ https://godbolt.org/g/2wP50w actual answer 6 it seems? ] https://godbolt.org/g/pGviKZ too

Gcc flag Fipa-pta maybe? If can find a case where it works. https://kristerw.blogspot.com/2017/05/interprocedural-optimization-in-gcc.html?m=1

-fsanitize=address

entire smallpt

auto lambda demo: https://godbolt.org/g/5fOC4q

Kent's email about "works on my machine" / Godbolt

variant stuff, clang opts out

Non virtual thunks

cute opt: https://godbolt.org/g/Tk8Af4 and https://godbolt.org/g/Zdvzke (ordering? interesting)

DRW repo: "First working version
 master
 1 parent 0ee0c10 commit de67452fc937d31ecc48991d1449051f362087f4 @mgodbolt mgodbolt committed on May 9, 2012"

 pass by value / pass by reference https://godbolt.org/g/XWFR7s

 aliasing: https://godbolt.org/g/wczpd3

 https://bugs.llvm.org/show_bug.cgi?id=28343 - type based aliasing

 HACKING ATTEMPTS

 New int; leak memory thing? (memory alloc elision)

 https://bugs.llvm.org/show_bug.cgi?id=28343

#GCC Explorer
Follow-alomg mode (URL to keep updating the layout, websockets?)

Pre vs post increment
Algorithm for each vs non

Trivia:
-- people running a "most output from a tweet" competition

Simon Brand [7:22 AM] 
@mattgodbolt I'd be interested in the roadmap, understanding how to get the most useful output (making things volatile and such), how the different compiler versions are maintained, and how I could leverage it for other cool projects (maybe a collaborative compiler for interviews or something).

what do you use it for?
Simon Brand [7:19 AM] 
@mattgodbolt I use it for demonstrating compiler optimisations.

Arne Mertz [7:22 AM] 
@mattgodbolt what I use it for:
1) to play around with C++17 features out of curiosity (I don't have a bleeding edge compiler locally)
2) to show colleagues that the tips I give them compile and don't create worse assembly
3) to discuss stuff here on Slack
tbh, my point 1) has become less valid in the past weeks since someone pointed me to Wandbox, because I can execute code there.
@mattgodbolt I forgot one point: since this week, I use CE to produce minimal examples for compiler bugs/ICEs and narrow down which version they were introduced. The turnaround times are just great for things like that.

Miro Knejp [7:22 AM] 
is "to prove people wrong" a valid reason? :smile:
I also use it to check on new features or edge cases of the language that I'm less familiar with, and to see how different compilers handle the same code, e.g. that clang discovered my loop was a summation and replaced it with the closed form was quite entertaining to me. these are things you usually don't discover at work

Björn Fahller [7:37 AM] 
I use it mostly to show my colleagues how different code constructs works - most specifically to show that abstractions typically are very cheap.
I also use it for experimental TMP stuff, where it's easier to check with a static_assert in CE with different compilers than to do the same with many compilers installed locally. (edited)

Peter Bindels [7:38 AM] 
I use it to show colleagues what's new in C++11/14/17 and why it's awesome
I also use it to see what things work on MSVC, without needing a Windows box. (+2 thumbs ups)

Nir Friedman [12:36 PM] 
Sorry if this is cheesy, but wanted to thank you personally for Compiler Explorer
It's an awesome tool that has definitely improved my QoL as a C++ dev, and I've undoubtedly learned things because it was so easy to use

that otherwise I would have just shrugged off and never investigated

so, thanks! And the big update to it some number of months ago with the tabs for the compiler output, also very useful.

Links to cool code optimisation 
`https://gcc.godbolt.org/#g:!((g:!((g:!((h:codeEditor,i:(j:1,source:'namespace+%7B%0A++struct+Iface+%7B%0A++++virtual+~Iface()+%7B%7D%0A++++virtual+int+doThing()+const+%3D+0%3B%0A++%7D%3B%0A%0A++struct+Bob+:+Iface+%7B+%0A++++int+doThing()+const+override+%7B+return+1%3B+%7D%0A++%7D%3B%0A%0A++struct+Ian+:+Iface+%7B+%0A++++int+doThing()+const+override+%7B+return+2%3B+%7D%0A++%7D%3B%0A%0A++int+test(const+Iface+%26obj)+%7B%0A++++int+a+%3D+0%3B%0A++++for+(int+i+%3D+0%3B+i+%3C+10000%3B+%2B%2Bi)%0A++++++a+%2B%3D+obj.doThing()%3B%0A++++return+a%3B%0A++%7D%0A%7D%0A%0Aint+main(int+argc,+const+char+*argv%5B%5D)+%7B%0A++Ian+ian%3B%0A++Bob+bob%3B%0A++if+(argc+%3D%3D+2)+%0A++++return+test(ian)%3B%0A++else%0A++++return+test(bob)%3B%0A%7D'),l:'5',n:'0',o:'C%2B%2B+source+%231',t:'0')),k:50,l:'4',m:100,n:'0',o:'',s:0,t:'0'),(g:!((g:!((h:compiler,i:(compiler:g7snapshot,filters:(b:'0',commentOnly:'0',directives:'0',intel:'0'),options:'-O3',source:1),l:'5',n:'0',o:'x86-64+gcc+7+(snapshot)+(Editor+%231,+Compiler+%231)',t:'0')),k:50,l:'4',m:50.05471818428769,n:'0',o:'',s:0,t:'0'),(g:!((h:compiler,i:(compiler:clang_trunk,filters:(b:'0',commentOnly:'0',directives:'0',intel:'0'),options:'-O3',source:1),l:'5',n:'0',o:'x86-64+clang+(trunk)+(Editor+%231,+Compiler+%232)',t:'0')),l:'4',m:49.94528181571231,n:'0',o:'',s:0,t:'0')),k:50,l:'3',n:'0',o:'',t:'0')),l:'2',n:'0',o:'',t:'0')),version:4`

-----
for below?
    Intro - 


-----------------------

Hi everyone,

I'm going to be talking today about a C++ website I set up in 2012 to scratch my
own itch.  Since then it's gone from tens of hits a day to many thousands, and
has ballooned into something which takes up most of my spare time.  It's also
rather unexpectedly turned my family name into a noun and a verb.

My name's Matt Godbolt and I'm a programmer at DRW, a trading firm based out of Chicago.
My career path has taken me through games programming, setting up my own C++ toolchain
company, mobile phone development and a couple years at Google before ending up at DRW.
We're hiring: If you like what I'm saying here, you should come speak to me after this talk about coming
to work with me. 

The site is - well, what I call it is - Compiler Explorer. Most people refer to it
as godbolt -- how many here have heard of it? Used it? Use it regularly?

CE is a site that lets you type in your C++ code and interactively see how it's compiled
to assembly.

[[insert appropriate response here]]

What I'm hoping from this talk is to convince you of a few things:

* Assembly isn't scary
* Compilers are smart^

^ most of the time.

Along the way I'll explain why the site was set up, how I use it and how some others are
using it and why I think you should be using it. I'll talk a little bit about how it
has evolved over the years, how it's written, maintained and deployed. some
cool features about the site that even regular users might not know about.

who has ever looked at x86 asm? Regularly looks at it? Writes in it? Writes often in it? Wow, unlucky...
What about non-x86? I'm assuming most of you program to Intel machines, and 64-bit ones at that. The things
that go on here mostly apply to any architecture, but I'm going to be concentrating on x86_64.
For the rest of you let's show what CE looks like and show you how un-scary the ASM is.

[[simple code here]] maybe even something with several dumb statements. -O0 will show all
* show asm output with -O0, talk about each step. Explain what it's doing, step through it
* show -O1 output

So let's cover a bit more about x86 in general
[some slides on assembly]
* registers
* addressing modes. Also talk about CISC versus RISC
[jokes about intel vs at&t. also tabs and spaces, vi / emacs]

Ok, that's cool. So what can we observe now we've learned a little about this?

First - a story. In 2012 a colleague and I were just starting to dip our toe into the
new C++0x stuff coming along. One thing we had started looking at was the use of range-based
for versus old-fashioned iteration or counter-based fors. We'd argued a bunch. I should explain,
for some of the work we do, performance is really important and we spend a lot of time thinking about
good practises and guidelines that have not performance drawbacks. And in some other languages, using
range-based iterators has been expensive (cough, java, cough).

So to answer the question I hacked a UNIX command line to output the compiled code. As we experimented
I used `watch` in conjucntion with the command and we could edit the code in vi and see the asm output.
[maybe demo]?

Shortly after that Compiler Explorer was born. Or GCC Explorer as it was called back then. So, that brings
me on to our first major topic: Compilers are SUPER CLEVER!
* range-for example
  * maybe we external function call?
  * make acuumulate<T> and show "oh noes where's my code" or a class?
  * show std::accumulate?
* some examples here

But sometimes they're TOO CLEVER for what you want.
* Examples of optimizer throwing away work
  * defeating optimizer tricks
* Examples of template code "going away"

More curated examples here...

Compilers CAN be dumb too! Well, as dumb as the person writing the code.

* Examples...
 * `auto` copy when you didn't mean it
 * calling out of line function pessimisation
 * restrict keyword?

IN CONTEXT? 
* map lookups? - trading stuff? unordered_map vs hand-written or boost multimap, the modulus thing.
* formatting a number?

So, how does this stuff all work behind the scenes?

* Simple example
* Magic javascript libraries
  * shout out to CodeMirror and Monaco. And then MS for OSSing it!
  * node, javascript...
    * maybe gag about if you think C++ is crazy, try JS

* All the compilers
 * help from Intel and MS
 * loads still "coming soon"

Road map - the future?
* more compilers
* execution

Shout out to those that helped along the way
