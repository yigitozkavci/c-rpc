# Usage:

```
make -f Makefile.add

# This is the unknown adder program's executable.
# You can throw the c source away after creating the executable
gcc ext_add.c -o ext_add

# For running the server:
./add_server localhost

# For running the client:
./add_client localhost

# Client then will prompt for values to add
```
