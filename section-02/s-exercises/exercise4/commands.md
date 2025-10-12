flag{arm_nm_gdb_master}

nm vault.elf | grep "flag"
#This lists all the symbols in the binary, I passed that output and looked for symbols with the word flag, I saw there was secret_flag and **loader_flags**
gdb vault.elf
#This starts the GNU Debugger reading symbols from vault.elf
p secret_flag
#Run in the GNU Debugger, this prints the value of the variable secret_flag, what it resulted in was the correct form for the answer
