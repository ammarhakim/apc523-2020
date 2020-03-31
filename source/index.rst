APC523 Lectures 13 and 14: Hardware and Software Issues in Computational Physics
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

These are notes, lecture slides and code for use in Princeton
University's graduate course "Numerical Algorithms for Scientific
Computing" for the year 2020 and for Lectures 13 and 14. The main
instructor for this is `Greg Hammett
<https://w3.pppl.gov/~hammett/>`_. All material is copyrighted by
Ammar Hakim and released under the `Creative Commons CC BY License
<https://creativecommons.org/licenses/>`_.

.. contents::

Background
----------

Computational physics software is very complex. In addition to the
physics itself being complicated (multiple spatial and temporal
scales, highly nonlinear physics, coupling between models, huge number
of unknowns, etc), the algorithms required may be sophisticated,
difficult to implement efficiently and may require complex
data-structures. In Lectures 13 and 14 we will look at the specific
software and hardware issues that arise in many computational physics
codes.

In general, to achieve expertise in this topic one needs to write a
lot of code under the supervision of a "Master Craftsman". However, I
will try my best to point out resources and issues that commonly arise
while writing computational physics codes, which will allow you
learn/explore on your own.


Github repo for lectures and code
---------------------------------

You can get all the tex files for the slides, source for this website
and the code I ran in class by cloning the `Github repo
<https://github.com/ammarhakim/apc523-2020>`_ for these lectures.


Lecture 13: Hardware and Software Issues: History and Optimization
------------------------------------------------------------------

`PDF of Lecture 13 slides <./_static/lec13.pdf>`_

In this lecture we will look at hardware oriented optimization for our
algorithms. We will begin by looking at the early history of computer
hardware. Numerical computations really drove the design of computers
since the beginning, and even though now non-numeric applications
dominate, numerics continues to push the boundaries of hardware
design. Even in what may appear as non-numeric applications,
mathematical algorithms are deeply embedded in nearly all forms of
software. For example, games and movies use very sophisticated
rendering algorithms (almost always hardware accelerated) and
designing better, realistic rendering is a multi-billion dollar
industry.

The first and perhaps greatest pioneer in computer hardware was
`Charles Babbage <https://en.wikipedia.org/wiki/Charles_Babbage>`_. He
essentially, ab-inito, designed a series of mechanical computers,
culminating in the Analytical Engine. Most of Babbage's machines were
not built in his lifetime. However, his design for the Analytical
Engine contains all the modern architectural details found in our
processors (of course, Babbage worked with mechanical machines and not
electronics). By a stroke of misfortune (probably as Babbage never
published anything), Babbage's ideas were not widely known, and
especially his designs fell into obscurity. They were only
rediscovered in 1960s, much after the modern von Neumann architecture
was designed. That two independent designs made a century apart should
be so similar is remarkable.

`Allan Bromley <https://en.wikipedia.org/wiki/Allan_G._Bromley>`_ is
the credited for rediscovering Babbage's legacy. See his `paper
<./_static/Bromley-1982.pdf>`_ in Annals of the History of Computing
for a detailed overview of the Analytical Engine. Babbage's Difference
engine has been built twice now. See `Computer History Museum page
<https://www.computerhistory.org/babbage/>`_. Babbage also designed an
extraordinary printer which was also built by the Science
Museum. London. See `BBC news report
<http://news.bbc.co.uk/2/hi/science/nature/710950.stm>`_.

The von Neumann architecture is named after the polymath `John von
Neumann <https://en.wikipedia.org/wiki/John_von_Neumann>`_. He worked
on his designs over years, including at the Institute of Advanced
Study where he designed a machined called the `IAS Machine
<https://en.wikipedia.org/wiki/IAS_machine>`_. von Neumann and Herman
Goldstine wrote the first major paper on `error analysis of Gaussian
elimination <https://epubs.siam.org/doi/10.1137/080734716>`_, bringing
numerical analysis into the mainstream of applied mathematics.

`Moore's Law <https://en.wikipedia.org/wiki/Moore's_law>`_ continues
to hold and number of transistors on-chip are doubling every two
years. However, we are hitting limit of clock speeds now and the way
towards faster computing is via multi-core machines. Many companies
ship chips with large number of cores. For example, Intel's `Cascade
Lake
<https://www.intel.com/content/www/us/en/design/products-and-solutions/processors-and-chipsets/cascade-lake/2nd-gen-intel-xeon-scalable-processors.html>`_
architecture has upto 28 cores. AMD's `Epyc chips
<https://www.amd.com/en/processors/epyc-7002-series>`_ come with up to
64 cores. These are now becoming available in various supercomputing
centers (including Princeton Research Computing).

We looked at a matrix-matrix multiply problem, showing how rearranging
the data improves performance. However, we saw that professional grade
libraries like Eigen still out-perform our hand-written code by
:math:`5\times` or more. Further improvements can be made by using
blocking algorithms and SIMD instructions, in essence, vectorizing the
code.

For excruciating details on how to optimize C++ code see `Agner Fog's
website <https://www.agner.org/optimize/>`_. In particular, he has
five(!) manuals on all sorts of gory details on processor
architectures and how you can utilize this information to optimize
your code. His `first manual
<https://www.agner.org/optimize/optimizing_cpp.pdf>`_ is probably the
most useful.

We saw an example of SIMD programming. Manually programming SIMD is
painful and very tedious. The processor intrinsics are not intuitive
and need significant expertise to use. Wrapper C++ libraries should be
used instead. For example, Agner Fog's `VectorClass
<https://github.com/vectorclass>`_ library or Agenium Scale's `NSMID
library <https://github.com/agenium-scale/nsimd>`_ are good libraries
to use. (Intel has it's own library but it does not seem to be widely
used or even maintained. I may be wrong, though).

Lecture 14: Hardware and Software Issues: C++ and Parallel Programming
----------------------------------------------------------------------

`PDF of Lecture 14 slides <./_static/lec14.pdf>`_

In this lecture we will look at some concepts in software engineering
and parallel programming. In particular we will focus on MPI standard,
mentioning briefly OpenMP and GPUs. The latter are major topic in
themselves and can't be covered in a single lecture like this.

My general recommendation for new projects is to use modern C++
(i.e. use C++ language as standardized in 2011 and after). Modern C++
is a very powerful language that has the right combination of
high-level features and low-level control that can result in very
flexible but optimized code. (Often, keeping a code flexible and
ensuring it is efficient is difficult). Most newer large libraries
being built are being written in C++ and it is a good to get familiar
with the language.

However, C++ is a difficult language to learn and very hard to use
effectively. It is best to study good C++ code and apprentice to a
"Master Craftsman" to become a real expert. I recommend Bjarne
Stroustrup's "The C++ Programming Language" as the standard
reference. Stroustrup is the inventor of C++ and also wrote the first
compiler for it.

The most comprehensive and complete reference documentation for C++ is
the `cppreference website <https://en.cppreference.com/w/>`_. If you
write any serious program in C++ this is indispensable. This is not
for beginning C++ programmers.

When using C++ use the Standard Library (called the "Standard Template
Library" (STL)) extensively. For example, use the `std::vector<>`
class to allocate arrays and not allocate memory directly
yourself. Use plenty of `struct` or `class` and in parts of the code
use objects oriented programming. Objects oriented programming is a
powerful paradigm but is not always suitable for computational
code. For example, the STL is **not object oriented**. Instead it uses
the idea of "types" with operators that work on these abstract types
that satisfy some property. The theory of types has a long and
distinguished history in mathematics and logic, going back to Bertrand
Russell. Many programming languages have a very sophisticated concept
of types, though the C++ type-system leaves much to be desired.

The Message Passing Interface (MPI) is the de-facto standard in
high-performance computing (HPC) for message based communication
between processors. The MPI standard specifies an API that
applications can use to communicate in parallel. See the
`documentation here <https://www.open-mpi.org/doc/current/>`_. The MPI
standard is complex. However, for most explicit codes you only need to
understand a few key methods and can learn others as and when needed.

I went over the basic design pattern of an explicit, parallel PDE
solver. (In the CS literature "Design Patterns" mean something very
specific: these encode a fundamental algorithmic pattern that occurs
again and again in large number of applications. CS folks have
designed and discovered many patterns and good programmers should be
aware of some of these). I showed that to communicate between
sub-domains one needs to copy "skin-cell" data from one sub-domain to
the "ghost-cell" region of another sub-domain. The size and layout the
skin/ghost-cell regions depends on the stencil you are using (for
example, if you are using a 5-point of 9-point Laplacian stencil). For
unstructured grids the layout of skin/ghost-cell regions is very
complex and needs significant book-keeping.

