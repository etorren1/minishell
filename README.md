# Minishell <a name="top"></a>
This project is about creating a self simple shell like bash or zsh.

<img src="https://github.com/etorren1/minishell/blob/master/images/vid1.gif" minishell/>

## Compile and run MacOS and Linux

`make && ./minishell`

## Featuries

### Termcap
Interaction with the terminal is implemented using the termcap library

### History
Shell command history saved in the file `.minishell_history`

### Pipes
The output of each command in the pipeline is connected to the input of the next command via a pipe. Pipes runing parallel

<img src="https://github.com/etorren1/minishell/blob/master/images/img1.png" width="90%"/>

### Redirections
- "<" redirect input.
- ">" redirect output.
- "<<" heredoc: should be given a delimiter, then read the input until a line containing the
delimiter is seen.
- ">>" redirect output in append mode
<img src="https://github.com/etorren1/minishell/blob/master/images/img3.png" width="90%"/>

### Symbols and signals
Handle '(single quote), "(double quote), $?(status code) and Ctrl+C, Ctrl+D, Ctrl+\ signals  
Handle ENV environment variables

<img src="https://github.com/etorren1/minishell/blob/master/images/img2.png" width="90%"/>

## Developers
[etorren](https://github.com/etorren1)  
[vaha1st](https://github.com/vaha1st)
***
<a href="#top">Gotop</a>
