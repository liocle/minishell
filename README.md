# Minishell

Minishell is a simplified UNIX shell developed as part of the Hive Helsinki curriculum.  
It is a **from-scratch implementation** of core shell features like command execution,  
process handling, input/output redirection, pipes, and signal handling.

## **📌 What This Project Demonstrates**
This project is an **exercise in system programming in C**.  
It showcases key **low-level programming concepts**, including:

- **System calls**: `fork()`, `execve()`, `pipe()`, `dup2()`, `waitpid()`, etc.
- **Process control**: Managing child processes, job control.
- **Memory management**: Avoiding leaks, handling dynamic allocations.
- **File descriptors & redirections**: Implementing `<`, `>`, `<<`, `>>`.
- **Signal handling**: Handling `SIGINT (Ctrl+C)`, `SIGQUIT (Ctrl+\)`.
- **Environment management**: Handling `$PATH`, variable expansion.

---

## **👥 Collaborators**
- [Markus Laaksonen](https://github.com/mxafi)  
- [Lionel](https://github.com/liocle)  

---

## **🚀 Features**
✅ **Execute commands** like Bash  
✅ **Built-in commands**: `cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`  
✅ **Pipes (`|`)**: Chain multiple commands  
✅ **Input/output redirection**: `<`, `>`, `<<`, `>>`  
✅ **Signal handling**: Handle `Ctrl-C`, `Ctrl-D`, `Ctrl-\`  
✅ **Environment variables**: `$PATH`, `$HOME`, `$?`, etc.  
✅ **Command history** (via `readline`)  

---

## **⚠️ Compatibility**
✅ **Currently supports:** **Linux**  
❌ **MacOS support is currently broken** due to Readline differences.  

---

## **🛠 Installation**
1. **Clone the repository**:
   
```sh
   $ git clone https://github.com/liocle/minishell.git
   $ cd minishell
```

2. **Install dependencies**:
   
```sh
   $ sudo apt update && sudo apt install libreadline-dev libncurses-dev
```

3. **Compile the project**:
   
```sh
   $ make
```

4. **Run Minishell**:
   
```sh
   $ ./minishell
```

## **📌 Usage Examples**
```sh
$ ls -l              # List files 
$ echo Hello World   # Print "Hello World"
$ export PAGER=less  # Set an environment variable
$ cd /home/user      # Change directory
$ cat file | grep foo > output.txt  # Use pipes and redirections
```

## **💡 What I Learned**
This project deepened my understanding of C and UNIX internals, including:

- Process creation & management (fork(), execve(), waitpid())
- File descriptors (open(), close(), dup2())
- Signal handling (SIGINT, SIGQUIT, signal(), sigaction())
- Memory management (malloc(), free(), detecting leaks)
- Inter-process communication (pipe())
- I now have hands-on experience writing system-level C code and working with complex debugging scenarios.

## **💡 Real-World Applications**

✅ **Real-world C experience** → This project mimics real shell behavior, reinforcing key system programming skills.  
✅ **System calls knowledge** → I now understand how UNIX shells execute commands, handle pipes, and manage processes.   
✅ **Debugging skills** → Learned to debug memory leaks, segmentation faults.  
✅ **Handling edge cases** → Unclosed quotes, invalid input, redirections, `$?` expansion, etc.


## **🛠 Implemented Built-in Commands**
- `cd`
- `echo -n`
- `pwd`
- `export`
- `unset`
- `env`
- `exit` 

Minishell also executes any external command found in `$PATH`.

## **🤝 Contributing**
Want to improve Minishell? Follow these steps:

1. Fork the repository.
2. Create a feature branch.
3. Commit your changes.
4. Submit a pull request.

## **📜 License**
This project was built as part of the Hive Helsinki curriculum and is intended for educational purposes.
