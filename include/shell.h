#ifndef _SHELL_HEADER_GUARD_
#define _SHELL_HEADER_GUARD_

#include <SimpleSerialShell.h>

#define WITH_HELPINFO
#ifdef WITH_HELPINFO
#define ADD_COMMAND(name, argumentHints, function) \
    shell.addCommand(F(name " " argumentHints), function)
#else
// if there is no room for a help hint,
// shorten the string to just the command
#define ADD_COMMAND(name, argumentHints, function) \
    shell.addCommand(F(name), function)
#endif

int addShellCommands(SimpleSerialShell & shell);

#endif
