This is a project in progress recreating several common unix command line programs, like:

- ls
- cd
- grep

## ls
As of right now the ls copy lists the contents of any given directory, or the current directory
if none is given. It does not print hidden files (files beginning with '.') by default. It also 
optionally takes a set of flags as an argument.

`{name} [-sph] [DIRECTORY]`

Flags and the directory can be given in any order.
There are currently three flags:

- `h` prints a guide with each flag and what it does
- `s` prints the size of each file and directory along with their names
- `p` prints hidden files and directories alongside normal ones
