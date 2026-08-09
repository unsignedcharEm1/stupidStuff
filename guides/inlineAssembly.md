
# Introduction
---
Inline Assembly is a way to use assembly in pure C/C++ code.

Before we start our journey in learning inline, you must know x86 assembly as a prerequisite and be familiar with **at&t** syntax, because thats what our compiler uses for inline assembly.

You can still use intel syntax using `.intel_syntax noprefix` at the top of your assembly 
but i strongly recommend *learning at&t for the best experience*

To read this guide you have to kind of break the chronological order and skim through the relevant sections.. it'll be worth it!
## Basic Syntax:
----
```c
__asm__ (
	// Multiline assembly statements must end with \n\t
	"assembly statement 1\n\t" 
	"assembly statement 2" // You do not have to use \n\t for single line
	: // output
	: // input
	: // Clobbers
);
```

note that you can also use `asm` instead of `__asm__` but the latter is preferred because you  might also have a C variable defined `asm` like:
```C
int asm;
```
so its safer to use `__asm__` instead

# Input, Output, Placeholders and Clobbers:
----
## Input

When your inline assembly runs, the compiler treats it as a literal isolated black box
and it has no idea about the C/C++ variables outside of it.

To tell the compiler to load any C variable to Any Register of our choice before our inline assembly runs we can use the input section.

### Example:

```C
int var = 67;
__asm__ (
	"nop" // Do No operations
	: // Output
	: "r" (var) // Heres our input section
	: // Clobbers
)
```

Looking at this specifically 
```c
"r" (var)
```
Means whatever is in my C variable `var` load it into any general register (`"r"`) that our compiler thinks its the best.. (could be `rax`, `rbx`, `rdx`, `rsi` whatever)

if we wanted to use a specific register to load the `var`'s value in then we can use *register constraints* (we will get into them later)

## Output

Now what if you do something in your assembly code and you wanted to save whatever is in your `register` back to your C variable?

Thats what output section does.

Basically when your inline assembly finishes executing, whatever registers are listed in your output section will get saved into C variables that are listed.

```C
int var;
__asm__ (
	"nop" // Do No operations
	: "=r" (var) // Output
	: // Input
	: // Clobbers
)
```

Here `"=r"` means use any general register ONLY for output that our compiler will pick for us and get whatever is in it and then put it back into our `var`

Okaaaaaaaaay...... but wait... a second.. if we let our compiler pick a random general register for us.. how do we even know the name of the register it picked and do something with it?

Good question.

Thats where our placeholders come in.

## Placeholders

Lets take the code from our input example and modify it so it does something.
```C
int var = 67;
__asm__ (
	"addl $10, %0\n\t" // woah??
	"incl %0"
	: // Output
	: "r" (var) // Heres our input section
	: // Clobbers
)
```

Woah what is this `%0`? Well thats your placeholder for whatever general register your compiler has picked for you and it refers to the register where the value of the `var` got loaded in.

Place holders generally follow this pattern if you add a lot of inputs like n of them:
```
`%0`, `%1`, `%2`, `%3`, ... `%n`
```

To make it more clear we will provide an example that uses both input and output sections
```C
int a = 50, 
b = 17, 
c = 0;
__asm__ (
	"addl %1, %2\n\t"
	"movl %2, %0"
	: "=r" (c) // output; %0
	: "r" (a), "r" (b)// input; %1 %2
	: // Clobbers
)
```

See? our registers got their placeholders in order, the register in the output section got assigned the `%0` register because its the first thing to appear!

If we didnt have anything in the output section then the registers in our input sections would get `%0` and `%1` respectively instead of `%1` and `%2`

If you tried printing the value of `c` hopefully you should get the value `67`

## Clobbers

What on earth is a clobber??

It's basically a way to let your compiler know about the registers you have touched in your inline assembly code.

Say you have this code:
```C
for (int i = 0; i < 67; i++) {
	__asm__ volatile (
		// Inline assembly  does something here..
	);
}
```

And your compiler decides to store the iteration count of this loop in the register `rcx`.

then your inline assembly code uses that *same* `rcx` register to do something on it
and sets the value of it into something arbitrary large value.

Do you see where it is going?

When your inline assembly finishes your compiler tries to use that same `rcx` for tracking iteration count and.. never ends up finishing the loop. (or just segfaults)

Basically a register is `clobbered` when your inline assembly uses a register does something to it like putting a value.

To prevent this from happening we put the registers we use in our inline assembly's clobber section to warn the compiler that we are USING that specific register and tell it not to use it for something else.

from our example above:
```C
for (int i = 0; i < 67; i++) {
	__asm__ volatile (
		// Inline assembly  does something here.. involving rcx register
		: // Output
		: // Input
		: "rcx" // Clobber
	);
}
```

Now the compiler explicitly knows that our inline assembly uses `rcx` register and it'll decide to use any other register like `rdx` or just store the iteration count into the stack memory.

It is very very important to add the registers you have modified in your inline assembly code into clobber section to prevent critical bugs.
# Register Constraints
---

Finally moving onto our most anticipated topic.. constraints

Register Constraints are a way to define which specific registers to assign for input or output.

Constraint Table:

| Constraint Symbol | Associated Register                                                                           | Name              |
| ----------------- | --------------------------------------------------------------------------------------------- | ----------------- |
| r                 | Any General Purpose Register (rax, rbx, rcx, rdi, rsi etc.) ; Compiler decides which to pick. | -                 |
| a                 | rax, eax, ax                                                                                  | Accumulator       |
| b                 | rbx, ebx, bx                                                                                  | Base              |
| c                 | rcx, ecx, cx                                                                                  | Counter           |
| d                 | rdx, edx, dx                                                                                  | Data              |
| S                 | rsi, esi, si                                                                                  | Source Index      |
| D                 | rdi, edi, di                                                                                  | Destination Index |
We also have table for Output prefixes:

| prefix | meaning                                                    |
| ------ | ---------------------------------------------------------- |
| =      | write only ; use  only for output                          |
| +      | read-write only; use the specified for reading and writing |

remember using "=r" (var) in output? thats literally it.

if we use "+r (var)" in our output section that'd mean load whatever into any general purpose register from `var` before running the inline assembly and when the inline assembly finishes load whatever is in the general purpose register back into `var`

```c
int var = 0;
__asm__ volatile (
	"movl $67, %0" 
	: "+r" (var)
	: // input
	: // Clobbers
);
```

if we were to print the value of `var` we would get 67.
# Volatile keyword
---
You might have noticed you often see
```C
__asm__ volatile (
 // code here...
);
```
instead of
```C
__asm__ (
 // code here...
);
```

Thats because the `volatile` keyword tells the compiler to NOT optimize our assembly code.

And thats very logical because we dont want our compiler to delete or modify our inline assembly if it doesnt look like its doing "anything" to the compiler even though its doing its job.

We just want our inline assembly to run as it is so the usage of `volatile` is highly encouraged.

*Please use the keyword for everything you have learned in this guide.*