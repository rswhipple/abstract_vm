# abstract_vm
AbstractVM is a machine with a stack that is able to compute simple arithmetic expressions. 
These arithmetic expressions are provided to the machine as basic assembly programs.

# Installation

**Navigate to Directory**

```cd abstract_vm```

**Compile**

```make```

# Usage
The machine is able to run programs from files passed as parameters or from the standard entry. When parameters are passed by the standard entry, the end of the program is indicated by the special symbol ;;.

**Run with Standard Entry**

```./abstract_vm```

**Run with file**

```./abstract_vm <path/to/file/file_name.avm>```

## Assembly Language Grammar
The assembly language of MyAbstractVM is generated from the following grammar (# corresponds to the end of an entry, not to the character '#'):
```
S := [INSTR SEP]* #

INSTR :=
    push VALUE
  | pop
  | dump
  | assert VALUE
  | add
  | sub
  | mul
  | div
  | mod
  | print
  | exit

VALUE :=
   int8(N)
 | int16(N)
 | int32(N)
 | float(Z)
 | double(Z)

N := [-]?[0..9]+

Z := [-]?[0..9]+.[0..9]+

SEP := '\n'
```

## Example Program
```
push int32(42)
push int32(33)
add
push float(44.55)
mul
push double(42.42)
push int32(42)
dump
pop
assert double(42.42)
exit
```

# Design